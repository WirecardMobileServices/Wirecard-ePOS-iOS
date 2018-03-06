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
#import "DDLog.h"
#import "BaseTests.h"

@interface CashTestsObcj : BaseTestsObcj
{
    __block BOOL cashOperationSucceed;
}
@end

@implementation CashTestsObcj

- (void)setUp
{
    [super setUp];
}

/*
 
 Note: The following test is an example of a complete usage of our cash management system.
 You are encourage to run separate parts, if you like. For example, consecutive closing
 and opening of shifts, and pay In or Out operations.
 Keep track of the errors though, as the status of the last shift will determine the
 approval of some requests run out of the following sequence of events.
 
 */

-(void)testGetCashManagement
{
    //PART 1: We log-in and request user data
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Requesting User Data"];
    [self loginAndGetUserData];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!loggedUser || ![loggedUser isKindOfClass:WDMerchantUser.class])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    else
    {
        [[UserHelper sharedInstance] setUser:loggedUser];
    }
    
    //Cash management per se, using mandatory cash registers and cash shifts, can be disabled or enabled in backend side. We detect here what's the case and do cash management
    //or directly jumpint into cash payment
    if (loggedUser.merchant.cashRegistersRequired.boolValue)
    {
        //PART 2: We request cash registers
        //--------------------------------------
        expectation = [self expectationWithDescription:@"We request cash registers"];
        [self getCashRegisters];
        [self waitForExpectationsWithTimeout:100 handler:nil];
        //Note: ideally, you will consider the Cash Drawer serial number receive inside the cashRegister response, as it indicates where physical the money is stored,
        if (!cashRegister)
        {
            XCTFail(@"No valid cash register  found for the given user's merchant. You can create one with the test for that purpose");
        }
        else
        {
            [[UserHelper sharedInstance] storeCashRegisterId:cashRegister.internalId];
        }
        
        
        //PART 3: We request cash shifts
        //--------------------------------------
        expectation = [self expectationWithDescription:@"Gettig Cash Shifts"];
        [self getLastShift];
        //Your shift keep track of what users open, close and do operations on them, for statistic report purposes.
        [self waitForExpectationsWithTimeout:100 handler:nil];
        
        
        //PART 4: We check the validity of last shift, and create a new one if none is found, or existing ones are invalid
        //--------------------------------------
        expectation = [self expectationWithDescription:@"Check Last Cash Shift and Create New One If Needed"];
        if (lastShift && [lastShift.shiftStatus isEqualToString:@"OPEN"] && ![lastShift.openTime isStillToday])
        {
            //The shif exist, but it was open more than 24 hours ago. We need to close it, then open a new one.
            [self closeShift];
        }
        else if (!lastShift)
        {
            //The shift does not exist: we simply open a new one.
            [self openShift];
        }
        else if (lastShift.closeTime)
        {
            //The shift is closed. Closed shift have a special parameter, shiftReport, with statistics about catalogue
            //categories, discounts, taxes, etc. that you may consider useful. We can simply open a new shift as
            //above, but we will get more content of the shift itself so you can check the structure of these reports.
            [self getCloseShiftDetailsThenOpen];
        }
        else
        {
            //The shift is open, and was open within the last 24 hours: it is perfectly valid to be used. Nothing to do.
            [expectation fulfill];
            
        }
        [self waitForExpectationsWithTimeout:100 handler:nil];
        if (!lastShift)
        {
            XCTFail(@"There was an error handling the shifts. Please debug and keep track of any returned error.");
        }
        else
        {
            [[UserHelper sharedInstance] storeOpenShiftId:lastShift.internalId];
        }
        
    
        //PART 5: We request activities of a shift
        //--------------------------------------
        expectation = [self expectationWithDescription:@"Gettig Activities of a Shift"];
        //Note: While you can only close the last shift (no more than one shift can be open at a cash registers)
        //You can request details of activities of any existing shift you know the id.
        [self getShiftActivities];
        [self waitForExpectationsWithTimeout:100 handler:nil];
        
        
        //PART 6: We request a Cash In/Out operation
        //of the last shift - the open one
        //--------------------------------------
        expectation = [self expectationWithDescription:@"Requesting a Cash Operation"];
        [self doingCashOperation];
        [self waitForExpectationsWithTimeout:100 handler:nil];
        if (!cashOperationSucceed)
        {
            XCTFail(@"There was an error Paying In or Out. Please debug and keep track of any returned error.");
        }
    }//End of Cash Register required
    
    //PART 7: We execute a Cash sale with a
    //basket full of items
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Do a Cash Sale payment"];
    [self doCashPayment];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!saleResponse)
    {
        XCTFail(@"There was an error when doing a cash transaction. Please debug and keep track of any returned error.");
    }
    else
    {
        //We save one valid sale id for other tests cases such as Printer ones
        [[SaleHelper sharedInstance] saleToSaveIdFrom:saleResponse];
    }
    
    //PART 8: We refund the cash sale we just did
    //-------------------------------------------
    expectation = [self expectationWithDescription:@"Do a sale refund"];
    [self refundTransaction];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!saleResponse || saleResponse.status != WDSaleStateReturned)
    {
        XCTFail(@"There was an error when doing a cash transaction. Please debug and keep track of any returned error.");
    }
}

-(void)getCashRegisters
{
     [[sdk cashManager] cashRegisters:loggedUser.merchant.merchantId
                               shopId:nil
                     cashDrawerVendor:nil
                           completion:^(NSArray<WDCashRegister *> * arrCashiers, NSError * cashiersErr)
     {
         //Note: you may have several cash registers in the arrCashiers, and you can select any of them if marked as enabled. You can allow the user to do the selection through some picker for example
         for (WDCashRegister *cashReg in arrCashiers)
         {
             if ([cashReg.drawerStatus isEqualToString:@"ENABLED"]) {
                 cashRegister = cashReg;
                 break;
             }
         }
         returnedErr = cashiersErr;
        [expectation fulfill];
     }];
}

-(void)getLastShift
{
    WDShiftQuery *query = [[WDShiftQuery alloc] init];
    query.page = 0;
    query.pageSize = 20;
    query.orderBy = WDShiftQueryOrderByOpenTime;
    query.orderSort = WDQuerySortDescending;
    
    [[sdk cashManager] shifts:cashRegister.internalId
                        query:query
                   completion:^(NSArray<WDCashShift *> * arrShifts, NSError * cashiersErr)
     {
         returnedErr = cashiersErr;
         //if shifts founds, with a openTime descending sorting, the first will always be the oldest shift. We will check the status and open date, and close it or use it if it is still valid. If no shifts found for given cash register, We will create a new one further in the test
         lastShift = [arrShifts firstObject];
         [expectation fulfill];
     }];
}

-(void)getCloseShiftDetailsThenOpen //Used as a Z-Report example
{
     @weakify(self);
    [[sdk cashManager] shiftDetails:lastShift.internalId
                       cashRegister:cashRegister.internalId
                         completion:^(WDCashShift * _Nullable cashShift, NSError * _Nullable err )
     {
         @strongify(self);
         if (!err && cashShift && cashShift.shiftReport && cashShift.shiftReport.reportCategories.count)
         {
             //You can check the content of a Z-Report, that you may as well print in the format of your choosing
             [self openShift];
         }
         else
         {
             returnedErr = err;
             XCTFail(@"Error - Could not get Z-Reports with error %@", err);
             [expectation fulfill];
         }
     }];
}

-(void)openShift
{
     @weakify(self);
    [[sdk cashManager] openShift:cashRegister.internalId
                            note:@"Here you can include a text note"
                          amount:[NSDecimalNumber decimalNumberWithString:@"100"]
                      completion:^(BOOL success, NSError *error)
     {
         @strongify(self);
         returnedErr = error;
         if (!error && success)
         {
             //We need to request the just created shift. If other users will modify shift values, is always good to keep up to date
             [self getLastShift];
         }
         else
         {
             [expectation fulfill];
         }
     }];
}

-(void)closeShift
{
     @weakify(self);
    [[sdk cashManager] closeShift:cashRegister.internalId
                             note:@"Here you can include a text note"
                           amount:[NSDecimalNumber decimalNumberWithString:@"100"]
                       completion:^(BOOL success, NSError *error)
     {
         @strongify(self);
         returnedErr = error;
         if (!error && success)
         {
             //We open a new shift if the closing was successful.
             [self openShift];
         }
         else
         {
             [expectation fulfill];
         }
     }];
}

-(void)getShiftActivities
{
    WDShiftQuery *query = [[WDShiftQuery alloc] init];
    query.page = 0;
    query.pageSize = 10;
    
    [[sdk cashManager] getOperationsForShift:lastShift.internalId
                                       query:query
                     belongingToCashRegister:cashRegister.internalId
                                  completion:^(NSArray<WDCashActivity *> * arrActivities, NSError * cashiersErr)
     {
         //Cash activities are used for statistics.
         [expectation fulfill];
     }];
}

-(void)doingCashOperation
{
    //Note: The operation of paying cash In or Out of a register is determined by the sign of the amount. In the "Pay In" below, the amount -100 would do a "Pay Out".
    [[sdk cashManager] cashOperation:cashRegister.internalId
                                note:@"Here you can add a text note"
                              amount:[NSDecimalNumber decimalNumberWithString:@"100"]
                            currency:cashRegister.currency.code
                          completion:^(BOOL success, NSError *error)
     {
         cashOperationSucceed = (!error && success);
         [expectation fulfill];
     }];
}

-(void)doCashPayment
{
    //We will define a dummy payment configuration as an example. Feel free to modify and add content; the sale complexity is up to you.
    WDPaymentConfig *paymentConfiguration = [WDPaymentConfig new];
    aSale = [[SaleHelper sharedInstance] newSale];
    [aSale addSaleItem:[NSDecimalNumber decimalNumberWithString:@"2.5"]
              quantity:5
               taxRate:[[UserHelper sharedInstance] preferredSaleItemTax]
       itemDescription:@"Red Apple"
             productId:@"dummyId1"];
    [aSale addSaleItem:[NSDecimalNumber decimalNumberWithString:@"1.34"]
              quantity:2
               taxRate:[[UserHelper sharedInstance] preferredSaleItemTax]
       itemDescription:@"Pineapple"
             productId:@"dummyId2"];
    //You can add a service charge to the whole basket
    [aSale addServiceCharge:[[UserHelper sharedInstance]
                             serviceChargeRate]
                    taxRate:[[UserHelper sharedInstance] serviceChargeTax]];
    //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchan has defined in setup.
    [aSale addGratuity:[NSDecimalNumber decimalNumberWithString:@"1"]
               taxRate:[[UserHelper sharedInstance] tipTax]];
    //You can add a discount for the whole basket when productId is nil, or per productId otherwise
    [aSale addDiscount:[NSDecimalNumber decimalNumberWithString:@"6"]
             productId:nil];
    paymentConfiguration.sale = aSale;
    paymentConfiguration.sale.cashRegisterId = cashRegister? cashRegister.internalId : nil;
    paymentConfiguration.sale.shiftId = lastShift? lastShift.internalId : @"";
    [paymentConfiguration.sale resetPayments];
    [paymentConfiguration.sale addCashPayment:paymentConfiguration.sale.totalToPay];
    [[sdk saleManager] pay:paymentConfiguration delegate:_paymentHandler];
}

-(void)refundTransaction
{
    WDSaleRequest *saleToBeRefunded = [saleResponse saleReturn];
    
    [saleToBeRefunded removeAllItems];
    saleToBeRefunded.cashRegisterId = cashRegister? cashRegister.internalId : nil;
    saleToBeRefunded.cashierId = saleResponse.cashierId;
    saleToBeRefunded.customerId = saleResponse.customerId;
    WDSaleItemCore *anItem = [aSale.items firstObject];
    
    //This is an example of partial refund: only one item is refunded
    [saleToBeRefunded addSaleItem:anItem.unitPrice
                         quantity:1
                          taxRate:anItem.taxRate
                  itemDescription:anItem.itemDescription
                        productId: ((WDSaleItem *)([anItem isKindOfClass:[WDSaleItem class]] ? anItem : nil)).externalProductId];
    
    [saleToBeRefunded addCashPayment:[saleToBeRefunded totalToPay]];
    saleResponse = nil;
    
    [[sdk saleManager] refundSale:saleToBeRefunded
                          message:@"Refunded in demo app for testing reasons"
                       completion:^(WDSaleResponse *acceptSale, NSError *error)
     {
         returnedErr = error;
         saleResponse = acceptSale;
         [expectation fulfill];
     }];
}

@end
