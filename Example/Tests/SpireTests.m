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
#import "DDLog.h"
#import "TestUtils.h"
#import "BaseTests.h"


@interface SpireTestsObjc : BaseTestsObcj
{
    __block WDUpdateConfigurationStatus configCompletionStatus;
}

@end

@implementation SpireTestsObjc


/*
 
 IMPORTANT NOTE: 
 -This test requires an actual iOS device (not simulator).
 -You have to have a Spire terminal paired through your iOS device settings.
 -Your terminal must have been provided by Wirecard, and be turned on.
 -If your backend settings include cash management with mandatory cash registers, you will need to run CashTests first (to have valid ids)
*/

- (void)setUp
{
    loggedUser = nil;
    [super setUp];
}

-(void)testSpire
{
#if TARGET_OS_SIMULATOR
    NSLog(@"\n\t\t   %s Not runnable on simulator 📱",__PRETTY_FUNCTION__);
    return;
    
#else
    
    //PART 1: We log-in and request user data
    //--------------------------------------
    
//    [self loginAndGetUserData];
//    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!loggedUser || ![loggedUser isKindOfClass:[WDMerchantUser class]])
    {
        XCTFail(@"Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.");
    }
    else
    {
        [[UserHelper sharedInstance] setUser:loggedUser];
    }
    
    //PART 2: We discover Spire terminals
    //paired to your iOS device.
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Discovering devices"];
    [self discoverDevices:WDPosMateExtensionUUID];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!selectedDevice || ![selectedDevice isKindOfClass:[WDTerminal class]])
    {
        XCTFail(@"No paired terminal found. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }

    //PART 3: We check for updates on the terminal
    //---------------------------------------------
    expectation = [self expectationWithDescription:@"Checking for terminal update"];
    [self checkingForTerminalConfigUpdates];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (configCompletionStatus == WDUpdateConfigurationStatusFailure)
    {
        XCTFail(@"Error when updating the terminal. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }
    
    //PART 4: We do a card sale using Spire terminal
    //---------------------------------------------
    expectation = [self expectationWithDescription:@"Card sale"];
    [self doCardPayment];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!saleResponse)
    {
        XCTFail(@"Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
        //NOTE:  if your merchant settings have cash mgmt enabled in backend, you will need to run cash tests first - otherwise you will receive a "not authorized" kind of error
    }
    else
    {
        //We save one valid sale id for other tests cases such as Printer ones
        [[SaleHelper sharedInstance] saleToSaveIdFrom:saleResponse];
    }
    
    //PART 5: We refund the sale we just did
    //(for testing purposes; this is important
    //if you develop using an actual credit card)
    //-------------------------------------------
    expectation = [self expectationWithDescription:@"Refund sale"];
    [self refundTransaction];
    [self waitForExpectationsWithTimeout:300 handler:nil];
    if (!saleResponse || saleResponse.status != WDSaleStateReturned)
    {
        XCTFail(@"Sale did cancel. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).");
    }
    
#endif
}

-(void)checkingForTerminalConfigUpdates
{
    UpdateTerminalCompletion completionUpdate = ^(WDUpdateConfigurationStatus updStatus, NSError *updError)
    {
        //Note that completion here will happen when:
        // 1- The update has been completed, but also the terminal has fully restarted and entered stand-by (this may take a couple of minutes in the case of firmware)
        // 2- There was no response from terminal (something went wrong) for several seconds, meaning update failed.
        returnedErr = updError;
        configCompletionStatus = updStatus;
        [expectation fulfill];
    };
    
    UpdateConfigurationProgress progress = ^(WDUpdateConfigurationProgressUpdate progressUpdate)
    {
        NSLog(@"Terminal update progress: %ld",(long)progressUpdate);
    };
    
    //Note: You may update the application (Spire devices) or firmware (others) using WDTerminalUpdateTypeApplication or WDTerminalUpdateTypeFirmware in updateType below
    //Note: The accept SDK will keep track of what version was previously installed, and decide if an update is required by comparing with the latest in backend.
    //This means, the first time you run this test, the configuration will be updated on the terminal. A second time will tell you "WDUpdateConfigurationStatusUnnecessary"
    //To force the actual update again you will have to remove the demo app from your iOS device and re-run the test.
     [sdk.terminalManager update:selectedDevice
                      updateType:WDTerminalUpdateTypeMaskConfiguration
                        progress:progress completion:completionUpdate];
}

-(void)doCardPayment
{
    aSale = [[SaleHelper sharedInstance] newSale];
    [aSale addSaleItem:[NSDecimalNumber decimalNumberWithString:@"2.5"]
              quantity:[NSDecimalNumber decimalNumberWithString:@"5"]
               taxRate:[[UserHelper sharedInstance] preferredSaleItemTax]
       itemDescription:@"Red Apple"
             productId:@"dummyId1"
     externalProductId:nil];
    [aSale addSaleItem:[NSDecimalNumber decimalNumberWithString:@"1.34"]
              quantity:[NSDecimalNumber decimalNumberWithString:@"2"]
               taxRate:[[UserHelper sharedInstance] preferredSaleItemTax]
       itemDescription:@"Pineapple"
             productId:@"dummyId2"
     externalProductId:nil];
    //You can add a service charge to the whole basket -- though this is totally optional
    [aSale addServiceCharge:[[UserHelper sharedInstance] serviceChargeRate]
                    taxRate:[[UserHelper sharedInstance] serviceChargeTax]];
    //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchan has defined in setup.
    [aSale addGratuity:[NSDecimalNumber decimalNumberWithString:@"1"]
               taxRate:[[UserHelper sharedInstance] tipTax]];
    //You can add a discount for the whole basket when productId is nil, or per productId otherwise
    [aSale addFlatDiscount:[NSDecimalNumber decimalNumberWithString:@"6"]];
    aSale.cashRegisterId = [[UserHelper sharedInstance] selectedCashRegisterId]; //Note: if your backend settings have cash mgmt enabled in backend, you will need to run cash tests first to get this value as well as shiftId below
    aSale.shiftId = [[UserHelper sharedInstance] lastShiftId];
    [aSale resetPayments];
    [aSale addCardPayment:aSale.totalToPay
                                     terminal:selectedDevice];
    
    WDSaleRequestConfiguration *paymentConfiguration = [[WDSaleRequestConfiguration alloc] initWithSaleRequest:aSale];
    
    [sdk.terminalManager setActive:selectedDevice completion:
    ^{
        [[sdk saleManager] pay:paymentConfiguration withDelegate:_paymentHandler];
    }];
}

-(void)refundTransaction
{
    WDSaleRequest *saleToBeRefunded = [saleResponse saleReturn];
    saleToBeRefunded.cashRegisterId = [[UserHelper sharedInstance] selectedCashRegisterId];
    saleToBeRefunded.customerId = saleResponse.customerId;
    //This is an example of full refund: all items are refunded, EXCEPT SERVICE CHARGE
    [saleToBeRefunded removeServiceCharge];
    
     //For partial refund, see CashTests
    [saleToBeRefunded addCardPayment:[saleToBeRefunded totalToPay] terminal:[WDTerminal new]];
    
    saleResponse = nil;
    
    [[sdk saleManager] refundSale:saleToBeRefunded message:@"Refunded in demo app for testing reasons" completion:^(WDSaleResponse *acceptSale, NSError *error)
     {
         returnedErr = error;
         saleResponse = acceptSale;
         [expectation fulfill];
     }];
}

-(void)discoverDevices:(WDExtensionTypeUUID)extensionUUID
{
    DeviceDiscoveryCompletion completionTerminals = ^(NSArray *arr, NSError *err)
    {
        returnedErr = err;
        selectedDevice = arr.firstObject;
        [expectation fulfill];
    };
    
    [sdk.terminalManager discoverDevices:extensionUUID completion:completionTerminals];
}

@end
