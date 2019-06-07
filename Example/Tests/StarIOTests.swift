//
//  StatsTests.swift
//  DemoEPOS
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import WDePOS

class StarIOTestsSwift: BaseTestsSwift, WDScanning, WDPrinting, WDManagerDelegate
{
    var userHelper : UserHelper!
    var printingSuccess : Bool?
    var openingDrawerSuccess, isConnected  : Bool?
    var scanningSuccess : Bool?
    var deviceModel : WDExtensionTypeUUID!
    
    override func setUp()
    {
        super.setUp()
        deviceModel = .WDMPOPExtensionUUID // Use .WDStarMicronicsExtensionUUID for printer
        self.openingDrawerSuccess = false
        self.isConnected = false
        self.scanningSuccess = false
        self.scanningSuccess = false
    }

    func testStarMicronics()
    {
        #if arch(i386) || arch(x86_64)
            let file:NSString = (#file as NSString).lastPathComponent as NSString
            NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
            return
            
        #else
        
        //PART 1: We detect paired devices
        //--------------------------------------
        expectation = self.expectation(description: "We detect paired devices")
        self.discoverDevices(deviceModel)
        self.waitForExpectations(timeout: 100, handler: nil)
        if (selectedDevice == nil)
        {
            XCTFail("No device found. Please make the hardware is switched on and paired to yout iOS device settings");
        }
        else
        {
            sdk.scannerManager.add(self, forDevice: selectedDevice!)
            sdk.printerManager.add(self, forDevice: selectedDevice!)
            sdk.cashDrawerManager.add(self, forDevice: selectedDevice!)
        }
        
        //PART 2: We open the cash drawer
        //--------------------------------------
        expectation = self.expectation(description: "Open cash drawer")
        self.waitForExpectations(timeout: 100, handler: nil)
        if (isConnected == false)
        {
            XCTFail("Device communication failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair it first.");
        }
        
        expectation = self.expectation(description: "Open cash drawer")
        self.openCashDrawer() //It will retry if failed
        self.waitForExpectations(timeout: 100, handler: nil)
        
        
        //PART 4: Getting a sale
        //--------------------------------------
        expectation = self.expectation(description: "Getting a sale")
        self.gettingSale()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (saleResponse == nil)
        {
            XCTFail("No sale could be reached. Please run cash unit test first, for example.");
        }
        
        //PART 3: Printing receipt
        //--------------------------------------
        expectation = self.expectation(description: "Printing receipt")
        self.printReceipt()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (printingSuccess == false)
        {
            XCTFail("Printing failed. Please make the hardware is switched on and paired to yout iOS device settings. If it was paired to other iOS device, please unpair to it first.");
        }
        
        if (deviceModel == .WDMPOPExtensionUUID) //StarMicronics CB2002 does not have barcode scanner, so disable this if you are not using mPOP one
        {
            //PART 4: Scanning barcode
            //--------------------------------------
            expectation = self.expectation(description: "Read barcode")
            self.waitForExpectations(timeout: 100, handler: nil)
        }
        
        #endif
    }
    
    func openCashDrawer()
    {
        if let selectedDevice = self.selectedDevice {
            sdk.cashDrawerManager.openCashDrawer(selectedDevice,
                                                 completion: {[weak self](success : Bool?, error : Error?) in
                                                    if error != nil || success == false
                                                    {
                                                        //We retry if failed. In your application, handle the error properly and trigger the open drawing from UI, ie. from a button. On unit tests, when print, open and scanning is all triggered and monitored on a unit tests, the StarIO device is known to fail sometimes.
                                                        self?.openCashDrawer()
                                                        return
                                                    }
                                                    self?.openingDrawerSuccess = success
                                                    self?.returnedErr = error
                                                    self?.expectation.fulfill()
            })
        }
    }
    
    func gettingSale()
    {
        let statuses = [NSNumber].init(arrayLiteral: NSNumber.init(value: WDSaleState.completed.rawValue))
        let types = [NSNumber].init(arrayLiteral:NSNumber.init(value: WDSaleType.purchase.rawValue))
        let paymentMethods = [NSNumber].init(arrayLiteral:NSNumber.init(value: WDPaymentMethod.cash.rawValue))

        let query : WDSalesQuery = WDSalesQuery.init(page: 0,
                                                                 pageSize: 20,
                                                                 orderBy: .createdAt,
                                                                 order: .descending,
                                                                 statuses: statuses,
                                                                 saleTypes: types,
                                                                 paymentMethods: paymentMethods)

        sdk.saleManager.querySales(query, completion: {[weak self](arr : [WDSaleResponse]?, error : Error?) in
            self?.returnedErr = error
            self?.saleResponse = arr?.first //Use the first returned sale for this example
            self?.expectation.fulfill()
        })
    }
    
    func printReceipt()
    {
        guard let receiptImage = UIImage.init(named: "fakereceipt") else
        {
            XCTFail("Something went really wrong - printReceipt")
            self.expectation.fulfill()
            return
        }
        
        let printProgress : PrinterStateUpdate = {(update : WDPrinterStateUpdate) in
            print("Print progress is \(update.rawValue)")
        }
        
        let printCompletion : PrintCompletion = {[weak self](success : Bool?, error : Error?) in
            self?.printingSuccess = success
            self?.returnedErr = error
            self?.expectation.fulfill()
        }
        
        guard let selectedDevice = self.selectedDevice else {
            XCTFail("No selected device to print - printReceipt")
            self.expectation.fulfill()
            return
        }

        let printerConfig : WDPrinterConfig = WDPrinterConfig.init(printer: selectedDevice,
                                                                               printJobs: [UIImage].init(arrayLiteral: receiptImage))
        /*Note that the printer adds borders to the image and it cannot be avoided. Try  not to include
        borders in the picture -- otherwise the image will be scaled down.
        If you wish to use the Default Design receipt you can obtain the SaleResponse from
            a) a saleManager pay:
            b) a saleManager querySales:
        Here we demonstrate the use of saleManager/saleResponse query.
        NOTE: Star Micronics devices only accept receipts in the format UIImage
        */

        self.saleResponse?.receipt(true,
                              showReturns: false,
                              format: .uiImage,
                              dpi: .starMicronics,
                              completion: {[weak self](receipts : [Any]?, error : Error?) in
            self?.returnedErr = error
            //Receipt as per format specified HTML | PDF | UIImage | WDReceipt object
            if let receipts = receipts
            {
                printerConfig.printJobs = receipts
                self?.sdk.printerManager.print(printerConfig,
                                               progress: printProgress,
                                               completion: printCompletion)
            }
            else
            {
                self?.expectation.fulfill()
            }
        })
    }
    
    func device(_ device: WDTerminal, connectionStatusDidChange status:WDExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")
        if (status == .connected && self.isConnected == false)
        {
            self.isConnected = true
            self.expectation.fulfill()
        }
    }
    
    func device(_ device: WDTerminal, batteryLevelDidChange batteryLevel: Int)
    {
        //StarIO devices do not inform about battery levels
    }
    
    func device(_ device: WDTerminal, paperStatusUpdated status: WDPrinterPaperStatus)
    {
        print("The level of paper in your printer is \(status)")
    }
    
    func removeSpecialCharsFromString(text: String) -> String
    {
        let okayChars : Set<Character> =
            Set("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLKMNOPQRSTUVWXYZ1234567890+-*=(),.:!_")
        return String(text.filter {okayChars.contains($0) })
    }
    
    func device(_ device: WDTerminal, barcodeReceived: String, symbology: WDBarcodeSymbology) //Data received through barcode scanner
    {
        print("Barcode read with value as string: \(barcodeReceived)")
        
        if self.scanningSuccess == false {
            self.scanningSuccess = true
            self.expectation.fulfill()
        }
    }

    func discoverDevices(_ extensionUUID: WDExtensionTypeUUID)
    {
        sdk.cashDrawerManager.discoverDevices(extensionUUID,
                                           completion: {[weak self](arr : [WDTerminal]?, error : Error?) in
                                            self?.selectedDevice = arr?.first
                                            self?.returnedErr = error
                                            self?.expectation.fulfill()
        })
    }

    
}



