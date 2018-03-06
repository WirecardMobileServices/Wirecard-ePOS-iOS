//
//  TestDomainDataServices.m
//  WDePOS
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "SaleHelper.h"
#import "UserHelper.h"
#import "DDLog.h"
#import "BaseTests.h"

@interface CatalogueTestsObjC : BaseTestsObcj
{
    __block BOOL successfulDownload;
    dispatch_group_t _serviceGroup;
}
@end

@implementation CatalogueTestsObjC


- (void)setUp
{
    [super setUp];
}

-(void)testCatalogue
{
    //PART 1: We log-in and request user data
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Requesting User Data"];
    [self loginAndGetUserData];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!loggedUser || ![loggedUser isKindOfClass:[WDMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    
    //PART 2: We request catalogue data
    //----------------------------------
    expectation = [self expectationWithDescription:@"Requesting Catalogue Data"];
    [self requestCatalogueData];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!successfulDownload)
    {
        XCTFail(@"Error while downloading catalogue data. Chances are there was a timeout on backend or your connection got interrupted. In any case, you may retry.");
    }
    
}

-(void)requestCatalogueData
{
    successfulDownload = YES;
    _serviceGroup = dispatch_group_create();
    
     @weakify(self);
    ProductCatalogueCompletion completionProductCatalogue = ^(NSArray *arrCatalogues, NSError *err)
    {
        @strongify(self);
        returnedErr = err;
        successfulDownload = !err;
        if (arrCatalogues.count == 0)
        {
            //No catalogues, so we finish the test. But for fully testing, please create a catalogue with categories and products in backend
            [expectation fulfill];
            return;
        }

        for (WDProductCatalogue *catalogue in arrCatalogues)
        {
            if (successfulDownload)
            {
                //This is a quite intensive test that mostly request data - in practice you would store the catalogue data in your app and show it in the UI.
                //The functions below are just an example on how to request catalogues, categories and products, for the purpose of saving them later in a DB
                //Notice that catalogues may be quite big, with lots of images, etc., and this test does not focus in how to sync such a complex database
                [self loadContentForCatalogue:catalogue];
            }
        }
        
        dispatch_group_leave(_serviceGroup);
    };

    dispatch_group_enter(_serviceGroup);
    
    [sdk.inventoryManager productCatalogues:loggedUser.merchant.merchantId
                                 completion:completionProductCatalogue];
    
    
    dispatch_group_notify(_serviceGroup,dispatch_get_main_queue(),
    ^{
      [expectation fulfill];
    });
}

-(void)loadContentForCatalogue:(WDProductCatalogue*)catalogue
{
     @weakify(self);
    NSLog(@"Loading content for catalogue named: %@", catalogue.name);
    ProductCatalogueCategoryCompletion completionCatalogue = ^(NSArray <WDProductCatalogueCategory *>* result, NSError* err)
    {
        @strongify(self);
        ProductCatalogueProductCompletion completionProductContent = ^(NSArray <WDProductCatalogueProduct *>* result, NSNumber * _Nullable totalCount, NSError* err)
        {
            if (err || !successfulDownload)
            {
                returnedErr = err;
                successfulDownload = NO;
            }
            else
            {
                [self loadContentForProducts:result
                               inCatalogueId:catalogue.productCatalogueId
                                 andCategory:nil];
            }
            dispatch_group_leave(_serviceGroup);
        };
            
        WDProductsQuery *query = [WDProductsQuery new];
        query.productCatalogueId = catalogue.productCatalogueId;
        query.productCategoryId = catalogue.productCatalogueId;
        dispatch_group_enter(_serviceGroup);
        [sdk.inventoryManager products:query
                         uncategorized:YES
                            completion:completionProductContent];//This is used for getting uncategorized products
        
        //Then we request categorized products
        for (WDProductCatalogueCategory *category in result)
        {
            [category setParentCategoryId:catalogue.productCatalogueId];
            [self loadContentForCategory:category
                           inCatalogueId:catalogue.productCatalogueId
                              andVersion:[NSDecimalNumber decimalNumberWithString:@"0"]];
            //Note: you may want to keep track of versions to compare to existing data in backend and do proper upsert in your app
        }
        
        dispatch_group_leave(_serviceGroup);
    };
    

    dispatch_group_enter(_serviceGroup);
    [sdk.inventoryManager productCategoriesTree:catalogue.productCatalogueId
                                     completion:completionCatalogue];
}

-(void)loadContentForProducts:(NSArray <WDProductCatalogueProduct*>*)products inCatalogueId:(NSString*)catalogueId andCategory:(NSString*)categoryId
{
    NSLog(@"Loading content for products of catalogueId: %@and categoryId: %@", catalogueId, categoryId);
    if ([[products firstObject] isKindOfClass:WDProductCatalogueProduct.class])
    {
        dispatch_group_enter(_serviceGroup);
        NSMutableArray *queries= [[NSMutableArray alloc] init];
        
        for (WDProductCatalogueProduct *product in products)
        {
            if (product.imageId.length) //Having imageId means there is an image for this product we can request
            {
                WDProductsQuery *query = [WDProductsQuery new];
                query.productCatalogueId = catalogueId;
                query.productCategoryId = categoryId;
                query.productId = product.productId;
                [queries addObject:query];
            }
        }
        
        ProductCatalogueImageCompletion completionImage = ^(NSArray <WDProductImage *>*prodsImage, NSError *err)
        {
            //Here you receive the image data, such as path, etc.
            dispatch_group_leave(_serviceGroup);
        };
        
        if (queries.count && successfulDownload)
        {
            [sdk.inventoryManager productsImage:queries
                                     completion:completionImage];
        }
        else
        {
            dispatch_group_leave(_serviceGroup);
        }
    }
    else if (products.count)
    {
        successfulDownload = NO;
    }
}

-(void)loadContentForCategory:(WDProductCatalogueCategory*)category inCatalogueId:(NSString*)catalogueId andVersion:(NSDecimalNumber*)dbVersion
{
     @weakify(self);
    NSLog(@"Loading content for category named: %@", category.name);
    __block NSString *catalogueIdCopy = [catalogueId copy];
    __block NSString *categoryId = [category categoryId];
    
    if ([category isKindOfClass:WDProductCatalogueCategory.class])
    {
        ProductCatalogueProductCompletion completionGetProducts = ^(NSArray <WDProductCatalogueProduct *>* result,NSNumber * _Nullable totalCount, NSError* err)
        {
            @strongify(self);
            if (err || !successfulDownload)
            {
                returnedErr = err;
                successfulDownload = NO;
            }
            else
            {
                [self loadContentForProducts:result
                               inCatalogueId:catalogueIdCopy
                                 andCategory:categoryId];
            }
            dispatch_group_leave(_serviceGroup);
        };
        
        WDProductsQuery *query = [WDProductsQuery new];
        query.productCatalogueId = catalogueIdCopy;
        query.productCategoryId = category.categoryId;
        
        for (id subcategory in category.subcategories) //Structure is 1 catalogue including 0 to many categories including zero to many products, and one product can belong to zero or many categories
        {
            if ([subcategory isKindOfClass: WDProductCatalogueCategory.class])
            {
                if (![category.categoryId isEqualToString:catalogueId] && ![[(WDProductCatalogueCategory*)subcategory parentCategoryId] length])
                {
                    [(WDProductCatalogueCategory*)subcategory setParentCategoryId:category.categoryId];
                }
                [self loadContentForCategory:subcategory
                               inCatalogueId:catalogueIdCopy
                                  andVersion:dbVersion];
            }
        }
        
        dispatch_group_enter(_serviceGroup);
        [sdk.inventoryManager products:query
                         uncategorized:NO
                            completion:completionGetProducts];
    }
    else
    {
        successfulDownload = NO;
    }
}

@end
