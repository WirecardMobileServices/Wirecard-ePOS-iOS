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
#import "DDLog.h"
#import "BaseTests.h"

@interface StatsTestsObjC : BaseTestsObcj
{

}

@end

@implementation StatsTestsObjC

- (void)setUp
{
    [super setUp];
}

-(void)testTransactionsStatistics
{
    //PART 1: We log-in and request user data
    //--------------------------------------
    

    if (!loggedUser || ![loggedUser isKindOfClass:[WDMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }

    
    //PART 2: We request stats from user sales
    //----------------------------------------
    expectation = [self expectationWithDescription:@"Requesting Stats"];
    [self getSaleStats];
    [self waitForExpectationsWithTimeout:100 handler:nil];
}

-(void)getSaleStats
{
    
    // End of Sale Statistics process
    SaleStatisticsCompletion completion = ^(NSArray  <WDSaleStatistics *>* _Nullable statistics, NSError* _Nullable error){
        // statistics - list of WDSaleStatistics objects
        // SaleStatistics has all the details of Sale statistics including
        // - MIN, MAX, AVG amounts
        // - Turnover
        // - Transaction count
        returnedErr = error;
        //Check the value returned as results, including max, min, turnover, etc per time units, for you to show by text or barchart/piechart graphics.
        [expectation fulfill];
    };
    
    // Query parameters such as filters start/end Sale dates, Sale status and reporting Period
    WDStatisticsQuery *query = [WDStatisticsQuery new];
    query.merchantId = loggedUser.merchant.merchantId; //Your Merchant ID
    //Recommendation: check NSDate+Utils implementation for a useful set of functions to handle daily, weekly and monthly intervals
    query.processedFrom = [[NSDate date] firstDateOfWeek];//from first date of week
    query.processedTo = [NSDate date]; //till today
    query.status = WDStatisticStatusCompleted; // Completed Sales only
    query.period = WDStatisticPeriodDay; //This is how the stats data will grouped in the response. You can have it weekly, monthly, etc.
    query.currency = @"EUR"; // Performed Sales Currency

    // Obtain Sale statistics
    [sdk.saleManager salesStatistics:query // Sale statistics query parameters
                          completion:completion]; // End of Sale Statistics Query process
    
}

@end
