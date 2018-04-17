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
#import <WDePOS/NSString+WDExtras.h>
#import "BaseTests.h"

@interface StarIOTestsObjC : BaseTestsObcj <WDScanning, WDPrinting, WDManagerDelegate>
{
    __block BOOL printingSuccess;
    __block BOOL openingDrawerSuccess;
    __block BOOL openingDrawerDone;
    __block BOOL scanningSuccess;
    WDExtensionTypeUUID deviceModel;
}

@end

@implementation StarIOTestsObjC

- (void)setUp
{
    [super setUp];
    deviceModel = WDMPOPExtensionUUID;
    openingDrawerSuccess = NO;
    openingDrawerDone = NO;
    scanningSuccess = NO;
}

-(void)testStarMicronics
{
#if TARGET_OS_SIMULATOR
    NSLog(@"\n\t\t   %s Not runnable on simulator 📱",__PRETTY_FUNCTION__);
    return;
    
#endif
    
    //PART 1: We detect paired devices
    //--------------------------------------
    expectation = [self expectationWithDescription:@"We detect paired devices"];
    [self discoverDevices:deviceModel];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!selectedDevice)
    {
        XCTFail(@"No device found. Please make the hardware is switched on and paired to yout iOS device settings");
    }
    else
    {
        [sdk.scannerManager addScannerManagerDelegate:self
                                           forScanner:selectedDevice];
        [sdk.printerManager addPrinterManagerDelegate:self
                                           forPrinter:selectedDevice];
        [sdk.cashDrawerManager addManagerDelegate:self
                                        forDevice:selectedDevice];
    }
    
    //PART 2: We open the cash drawer
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Open cash drawer"];
    //Open of cash drawer is trigger in delegate method connectionStatusDidChange below, once it is connected
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!openingDrawerSuccess)
    {
        XCTFail(@"Device communication failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair it first.");
    }
    
    //PART 3: Printing receipt
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Printing receipt"];
    [self printReceipt];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!printingSuccess)
    {
        XCTFail(@"Printing failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair to it first.");
    }
    
    if (deviceModel == WDMPOPExtensionUUID) //StarMicronics does not have barcode scanner
    {
        //PART 4: Scanning barcode
        //--------------------------------------
        expectation = [self expectationWithDescription:@"Read barcode"];
        [self waitForExpectationsWithTimeout:100 handler:nil];
    }
}

-(void)openCashDrawer
{
    void (^completion)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
        if (!openingDrawerSuccess)
        {
            openingDrawerSuccess = success && !error;
            returnedErr = error;
            [expectation fulfill];
        }
    };
    
    [sdk.cashDrawerManager openCashDrawer:selectedDevice completion:completion];
}

-(void)printReceipt
{
    PrinterStateUpdate progress = ^(WDPrinterStateUpdate update)
    {
        NSLog(@"Print progress is: %ld", (long)update);
    };
    
    PrintCompletion completion  = ^(BOOL success, NSError *error) {
        printingSuccess = !error && success;
        returnedErr = error;
        [expectation fulfill];
    };
    
    WDPrinterConfig *printerConfig = [[WDPrinterConfig alloc] initWithPrinter:selectedDevice printJobs:@[[UIImage imageNamed:@"fakereceipt"]]];
    /*
     Note that the printer adds border to the image and that cannot be avoided. Try to not include
     borders also in the picture or the image will be scaled down too much.
     For mPOP and StarMicronics devices, printing from image results in more flexibility and not a big impact in speed of efficiency (Only Datecs is limited due
     to battery usage and paper size)
    
     If you wish to use the Default Design receipt you can obtain the SaleResponse from
     A. saleManager pay:
     B. saleManager querySales:
     Here we demonstrate the use of saleManager query: to obtain a SaleResponse a use it for printing the Default Sale Receipt
        Query parameters such as paging, order by , sort
        and specific filters such as full text search, sale creation date, sale operation, sale status
    NOTE: Star Micronics devices only accept receipts in the format UIImage
     */
    WDSalesQuery *query = [WDSalesQuery new];
    query.page = 0;
    query.pageSize = 20;
    query.orderBy = WDSaleQueryOrderByCreatedAt; // Order by Creation date
    query.orderSort = WDQuerySortDescending; // Sort Descending - latest Sale first
    query.statuses = @[@(WDSaleStateCompleted)]; // Only Sales with Completed status
    query.saleTypes = @[    @(WDSaleTypePurchase) ];// Purchases
    
    //query Sales
    [[sdk saleManager] querySales:query completion:^(NSArray<WDSaleResponse *> * arr, NSError * error)
     {
         saleResponse = [arr firstObject]; //Use the first returned sale
         if (saleResponse){
         
             //alternatively use the Default Designed receipt for Datecs
             [saleResponse receipt:YES //Is the receipt for cardholder use
                       showReturns:NO //Should the receipt contain returns ?
                            format:WDPrintFormatUIImage //The receipt format is UIImage object for StarIO or mPOP
                               dpi:WDPrintDpiStarMicronics //The dots per width is set to StarMicronics
                        completion:^(NSArray* _Nullable receipts, NSError* _Nullable error) {
                            //Receipt as per format specified HTML | PDF | UIImage | WDReceipt object
                            returnedErr = error;
                            printerConfig.printJobs = receipts;
                            [sdk.printerManager print:printerConfig
                                             progress:progress
                                           completion:completion];
                            
                        }];
         }
         else{
             [expectation fulfill];
         }
         returnedErr = error;
         
     }];
}

- (void)device:(WDTerminal*)device barcodeReceived:(NSString *)barcodeReceived symbology:(WDBarcodeSymbology)symbology
{
    NSLog(@"Barcode read with value as string: %@", barcodeReceived);
    if (!scanningSuccess) {
        scanningSuccess = YES;
        [expectation fulfill];
    }
}

-(void)device:(WDTerminal *)device paperSatusUpdated:(WDPrinterPaperStatus)status
{
    //You can warn the user about the level of paper by listening to this delegate call
    NSLog(@"The level of paper in your printer is %ld", status);
}

- (void)device:(WDTerminal*)device connectionStatusDidChange:(WDExtensionConnectionStatus)status
{
    NSLog(@"Connection status changed %ld", status);
    if (status == WDExtensionConnectionStatusConnected && !openingDrawerDone)
    {
        openingDrawerDone = YES;
        [self openCashDrawer];
    }
}

-(void)device:(WDTerminal *)device batteryLevelDidChange:(NSInteger)batteryLevel
{
    //Never called as this device does not report it
}

-(void)discoverDevices:(WDExtensionTypeUUID)extensionUUID
{
    DeviceDiscoveryCompletion completionTerminals = ^(NSArray *arr, NSError *err)
    {
        returnedErr = err;
        selectedDevice = arr.firstObject;
        [expectation fulfill];
    };
    
    [sdk.cashDrawerManager discoverDevices:extensionUUID completion:completionTerminals];
}
@end
