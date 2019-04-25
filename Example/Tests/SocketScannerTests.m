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

@interface SocketScannerTestsObjC : BaseTestsObcj <WDScanning>

@end

/*
 
 Note: when using Socket Scanner pod/library, you are required to have some libstdc++ linked in your frameworks
 and libraries to be able to compile.
 
*/

@implementation SocketScannerTestsObjC

- (void)setUp
{
    [super setUp];
}

-(void)testSocketScanner
{
#if TARGET_OS_SIMULATOR
    NSLog(@"\n\t\t   %s Not runnable on simulator 📱",__PRETTY_FUNCTION__);
    return;
    
#else
    
    //PART 1: We discover Socket scanners
    //paired to your iOS device.
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Discovering devices"];
    [self discoverDevices:WDSocketExtensionUUID];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (!selectedDevice)
    {
        XCTFail(@"No paired scanner found. Make sure your terminal is paired in your iOS device settings and that the scanner is in stand-by mode (ie. by switching off and then on). For pairing you need to scan the pairing barcode in your Socket Scanner printed instructions");
    }

    //PART 2: We set delegate for listening
    //on paired scanner.
    //--------------------------------------
    expectation = [self expectationWithDescription:@"Setting active scanner to listen to"];
    [self setDelegateAndActiveScanner];
    [self waitForExpectationsWithTimeout:100 handler:nil];
    
#endif
}

-(void)setDelegateAndActiveScanner
{
    [sdk.scannerManager addScannerManagerDelegate:self forScanner:selectedDevice];
    
    //When something is scanned, it will trigger the function below, dataReceived. So please, scan a barcode to pass the test.
    //You have a barcode in this demo, a file image under the name barcode_example
}

- (void)device:(WDTerminal*)device barcodeReceived:(NSString *)barcodeReceived symbology:(WDBarcodeSymbology)symbology
{
    NSLog(@"Barcode read with value as string: %@", barcodeReceived);
    [expectation fulfill];
}

-(void)device:(WDTerminal *)device batteryLevelDidChange:(NSInteger)batteryLevel
{
    //This is a delegate function that will be called when there is a battery level change
    NSLog(@"Battery level for Socket Scanner is currently %ld", (long)batteryLevel);
}

-(void)discoverDevices:(WDExtensionTypeUUID)extensionUUID
{
    DeviceDiscoveryCompletion completionTerminals = ^(NSArray *arr, NSError *err)
    {
        returnedErr = err;
        selectedDevice = arr.firstObject;
        [expectation fulfill];
    };
    
    [sdk.scannerManager discoverDevices:extensionUUID completion:completionTerminals];
}

@end
