//
//  CashTests.m
//  AlphaMPOS
//
//  Created by Francisco Fortes on 31/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "SaleHelper.h"
#import "UserHelper.h"
#import "BaseTests.h"

@interface ERPTestsObjC : BaseTestsObcj
{
    __block WDMember *member;
    __block BOOL discountsReceived;
    __block BOOL stocksReceived;
}
@end


@implementation ERPTestsObjC

- (void)setUp
{
    [super setUp];
}

/*
 
 Note: The following test is an example of a how to use ERP/SAP queries. For them to work, you need to have
 ERP enabled in backend side, and actual data such as catalogue, members, products, etc. linked to your account.
 Responses coming from external systems can generate unexpected results, so make sure to have correct data
 already defined.
 
 The ERP features compatible with the accept SDK includes:
    - The ability to search for a Member ID, name or surname. Exact matched will return the member you are looking for,
    and aproximate sarch will return an array of the matches (ie for displaying them in a dynamic search table)
    - The ability to request special prices for an array of products ID, that will return discount prices if a member ID has that privilege.
    - The ability to request stock for an array of products in a single shop, or for a single product in all merchant's shops.
 */


-(void)testSearchMembers
{
    //PART 1: We log-in and request user data
    //--------------------------------------
    

    if (!loggedUser || ![loggedUser isKindOfClass:WDMerchantUser.class])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    else
    {
        [[UserHelper sharedInstance] setUser:loggedUser];
    }
    
    if ([loggedUser.merchant.erpSystemType.uppercaseString isEqualToString:@"SAP_BY_DESIGN"]) //If no erp System type then no need to continue
    {
        //PART 2: We search members
        //--------------------------------------
        expectation = [self expectationWithDescription:@"We search members"];
        [self searchMembersMatching:@"John"];
        [self waitForExpectationsWithTimeout:100 handler:nil];
        if (!member)
        {
            XCTFail(@"No member found. Make sure you have ERP SAP set in your merchant with valid members");
        }

        //PART 3: We request discount prices for a member
        //----------------------------------------------
        expectation = [self expectationWithDescription:@"We request discount prices for a member"];
        [self fetchDiscountPrices];
        [self waitForExpectationsWithTimeout:100 handler:nil];
        if (!discountsReceived)
        {
            XCTFail(@"No member discounted prices received. Make sure you have ERP SAP set in your merchant with valid products");
        }
        
        //PART 4: We request stocks for some products
        //----------------------------------------------
        expectation = [self expectationWithDescription:@"We request stocks for some products"];
        [self fetchProductsStocks];
        [self waitForExpectationsWithTimeout:100 handler:nil];
        if (!discountsReceived)
        {
            XCTFail(@"No product stocks received. Make sure you have ERP SAP set in your merchant with valid products and stock availability enabled");
        }
    }
}

-(void)loginAndGetUserData
{
    MerchantDetailCompletion completion = ^(WDMerchantUser *merchantUser, NSError *err)
    {
        loggedUser = merchantUser;
        returnedErr = err;
        [expectation fulfill];
    };
    loggedUser = nil;
    [[sdk userManager] currentUser:completion];
}


-(void)searchMembersMatching:(NSString*)searchString
{
    MembersCompletion completion = ^(NSArray <WDMember *>*members, NSError *err)
    {
        returnedErr = err;
        member = members.firstObject;
        [expectation fulfill];
    };
    
    //You can optimize the search in your app UI by choosing what parameter you want to choose between member id, member surname and member firstname
    [[sdk customerManager] memberInformation:nil
                                     surname:nil
                                   firstName:searchString
                                  exactMatch:NO
                                  completion:completion];
}

-(void)fetchDiscountPrices
{
    void (^completion)(NSArray<WDProductPrice *> *, NSError *) = ^(NSArray<WDProductPrice *> * _Nullable productPrices, NSError * _Nullable error)
    {
        discountsReceived = productPrices.count > 0;
        returnedErr = error;
        [expectation fulfill];
    };
    
    NSArray *productIDs = [NSArray arrayWithObjects:@"productA", @"productB", nil];
    
    [[sdk inventoryManager] productPriceForMember:member.memberId
                                      externalIDs:productIDs
                                         currency:@"EUR"
                                       grossPrice:YES
                                       completion:completion];
}

//Alternatively you can ask stock for a series of products in a single shop, instead of a single product in all shops as above.
//But please note that your ERP SAP may be limited to around 10 products per stock query, so make sure you use this request responsibly
//[[sdk inventoryManager] productsStock:productsArray inShop:@"ShopID" completion:completion];
-(void)fetchProductsStocks
{
    ProductStocksCompletion completion = ^(NSArray <WDProductStock *>*stocks, NSError *error)
    {
        stocksReceived = stocks.count > 0;
        returnedErr = error;
        [expectation fulfill];
    };
    
    WDProductCatalogueProduct *aProduct = [WDProductCatalogueProduct new];
    aProduct.externalId = @"product external (SAP) ID";
    [[sdk inventoryManager] productStockInAllShops:aProduct
                                        completion:completion];
}

@end
