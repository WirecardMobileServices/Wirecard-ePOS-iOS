//
//  TestDomainDataServices.m
//  WDePOS
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "UserHelper.h"
#import "SaleHelper.h"
#import "BaseTests.h"

@interface SalesTestsObjC : BaseTestsObcj
{

}

@end

@implementation SalesTestsObjC

#pragma mark - Helpers

- (void)setUp
{
    [super setUp];
}

-(void)testSales
{
    //PART 1: We log-in and request user data
    //--------------------------------------
    

    if (!loggedUser || ![loggedUser isKindOfClass:[WDMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    
    
    //PART 2: We request sales from current user
    //----------------------------------------
    expectation = [self expectationWithDescription:@"Requesting Sales"];
    [self getSales];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!saleResponse)
    {
        XCTFail(@"Error getting a complete sale. Please create some test (ie. run CashTest). Otherwise, debug and check the returned error");
    }
    else
    {
        //We save one valid sale id for other tests cases such as Printer ones
        [[SaleHelper sharedInstance] saleToSaveIdFrom:saleResponse];
    }

}

-(void)getSales
{
    WDSalesQuery *query = [[WDSalesQuery alloc] init];
    query.page =  0; //Increase this if you want to do dynamic paging in your UI
    query.pageSize = 20; //Each sale includes a lot of data, so paging with small pageSizes is recommended
    query.orderBy = WDSaleQueryOrderByCreatedAt; //You can also sort by amount using WDTransactionsQueryOrderByAmount
    query.orderSort = WDQuerySortDescending;//Can be WDTransactionsQuerySortAscending
    query.statuses = @[@(WDSaleStateCompleted),
                       @(WDSaleStateFailed),
                       @(WDSaleStateReturned),
                       @(WDSaleStateCanceled)];//You can define more or less statuses for the query, depending on your needs.
    //You can use a receiptId provided by backend in query.receiptId if you have one
    [[sdk saleManager] querySales:query
                       completion:^(NSArray<WDSaleResponse *> * arr, NSError * error)
    {
        saleResponse = [arr firstObject];
        returnedErr = error;
        [expectation fulfill];
    }];
}


@end
