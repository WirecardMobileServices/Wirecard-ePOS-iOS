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

enum paymentOperation
{
    case regularCard
    case cardAuth
    case cardPreAuth
}

class SpireTestsSwift: BaseTestsSwift, WDManagerDelegate
{
    var configCompletionStatus : WDUpdateConfigurationStatus!

    /*
     
     IMPORTANT NOTE:
     -This test requires an actual iOS device (not simulator).
     -You have to have a Spire terminal paired through your iOS device settings.
     -Your terminal must have been provided by Wirecard, and be turned on.
     -If your backend settings include cash management with mandatory cash registers, you will need to run CashTests first (to have valid ids)
     */
    
    override func setUp()
    {
        super.setUp()
    }
    
    func setupSpire()
    {
        #if arch(i386) || arch(x86_64)
            let file:NSString = (#file as NSString).lastPathComponent as NSString
            NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
            return
            
        #else
        
        //PART 1: We log-in and request user data
        //--------------------------------------
        

        if (loggedUser == nil || (loggedUser?.isKind(of: WDMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        else
        {
            UserHelper.sharedInstance().setUser(loggedUser)
        }
        
        //PART 2: We discover Spire terminals
        //paired to your iOS device.
        //--------------------------------------
        expectation = self.expectation(description: "Discovering devices")
        self.discoverDevices(.WDPosMateExtensionUUID)
        self.waitForExpectations(timeout: 100, handler: nil)
        if (self.selectedDevice == nil)
        {
            XCTFail("No paired terminal found. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        else
        {
            sdk.terminalManager.add(self, forDevice: selectedDevice!)
        }
        
        //PART 3: We check for updates on the terminal
        //---------------------------------------------
        expectation = self.expectation(description: "Checking for terminal update")
        self.checkingForTerminalConfigUpdates()
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.configCompletionStatus == .failure)
        {
            XCTFail("Error when updating the terminal. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        #endif
        
    }
    
    func testCardPurchaseAndRefund()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        setupSpire()
        doPurchaseAndRefund()
        #endif
    }
    
    func testAuthorisedAndCapture()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        setupSpire()
        doAuthorisedAndCapture()
        #endif
    }

    func testPreAuthorisedAndSupplement()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        setupSpire()
        doPreAuthorisedAndSupplement()
        #endif
    }
    
    func testSepaEFTPayment()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        setupSpire()
        doSepaEFTPayment()
        #endif
    }
    
    func doPurchaseAndRefund()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        //PART 4: We do a card sale using Spire terminal
        //---------------------------------------------
        expectation = self.expectation(description: "Card sale")
        self.doCardPayment(paymentOperation: .regularCard)
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.saleResponse == nil)
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
            //NOTE:  if your merchant settings have cash mgmt enabled in backend, you will need to run cash tests first - otherwise you will receive a "not authorized" kind of error
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from:self.saleResponse)
        }
        
        //PART 5: We refund the sale we just did
        //(for testing purposes; this is important if you develop using an actual credit card)
        //Algo note that refunds are allowed only for some period of time (ie: midnight on current time, or next 24 hours, etc) and after that, only reversals are allowed. But refunds are for free, while reversals actually cost money (so use reversals responsibly!)
        //-------------------------------------------
        expectation = self.expectation(description: "Refund sale")
        self.refundTransaction()
        self.waitForExpectations(timeout: 300, handler: nil)
        if let response = self.saleResponse, response.status != .returned && response.status != .partiallyReturned
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        else if self.saleResponse == nil
        {
            XCTFail("Sale response empty. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        #endif
    }
    
    func doAuthorisedAndCapture()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        //PART 4: We do a card sale using Spire terminal
        //---------------------------------------------
        expectation = self.expectation(description: "Card auth")
        self.doCardPayment(paymentOperation: .cardAuth)
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.saleResponse == nil)
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
            //NOTE:  if your merchant settings have cash mgmt enabled in backend, you will need to run cash tests first - otherwise you will receive a "not authorized" kind of error
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from:self.saleResponse)
        }
        
        //PART 5: We capture the sale we just did
        //(for testing purposes; this is important if you develop using an actual credit card)
        //Algo note that refunds are allowed only for some period of time (ie: midnight on current time, or next 24 hours, etc) and after that, only reversals are allowed. But refunds are for free, while reversals actually cost money (so use reversals responsibly!)
        //-------------------------------------------
        expectation = self.expectation(description: "Capture the auth")
        self.captureSale()
        self.waitForExpectations(timeout: 300, handler: nil)
        if let response = self.saleResponse, let payment = response.payments.first as? WDPaymentDetail, payment.status != .captured
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        else if self.saleResponse == nil
        {
            XCTFail("Sale response empty. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        #endif
    }
    
    func doPreAuthorisedAndSupplement()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        //PART 4: We do a card pre-auth using Spire terminal
        //---------------------------------------------
        expectation = self.expectation(description: "Card pre-auth")
        self.doCardPayment(paymentOperation: .cardPreAuth)
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.saleResponse == nil)
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
            //NOTE:  if your merchant settings have cash mgmt enabled in backend, you will need to run cash tests first - otherwise you will receive a "not authorized" kind of error
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from:self.saleResponse)
        }
        
        //PART 5: We add a supplement to the previous pre-auth payment (to increase the pre-auth amount on the sale)
        //-------------------------------------------
        expectation = self.expectation(description: "Add supplement to pre-auth")
        self.addSupplement()
        self.waitForExpectations(timeout: 300, handler: nil)
        if let response = self.saleResponse, let payment = response.payments.first as? WDPaymentDetail, payment.status != .completed
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        else if self.saleResponse == nil
        {
            XCTFail("Sale response empty. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
        }
        #endif
    }
    
    func checkingForTerminalConfigUpdates()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        let completionUpdate : UpdateTerminalCompletion = {[weak self](updStatus : WDUpdateConfigurationStatus?, updError : Error?) in
            //Note that completion here will happen when:
            // 1- The update has been completed, but also the terminal has fully restarted and entered stand-by (this may take a couple of minutes in the case of firmware)
            // 2- There was no response from terminal (something went wrong) for several seconds, meaning update failed.
            self?.returnedErr = updError
            self?.configCompletionStatus = updStatus
            self?.expectation.fulfill()
        }
        
        let progress : UpdateConfigurationProgress = {(progressUpdate : WDUpdateConfigurationProgressUpdate) in
            print("Terminal update progress: \(progressUpdate.rawValue)")
        }

        //Note: You may update the application (Spire devices) or firmware (others) using WDTerminalUpdateTypeApplication or WDTerminalUpdateTypeFirmware in updateType below
        //Note: The accept SDK will keep track of what version was previously installed, and decide if an update is required by comparing with the latest in backend.
        //This means, the first time you run this test, the configuration will be updated on the terminal. A second time will tell you "WDUpdateConfigurationStatusUnnecessary"
        //To force the actual update again you will have to remove the demo app from your iOS device and re-run the test.
        
        sdk.terminalManager.update(selectedDevice!,
                                   updateType:WDTerminalUpdateTypeMaskConfiguration,
                                   progress:progress,
                                   completion:completionUpdate)
        #endif
    }
    
    func doCardPayment(paymentOperation : paymentOperation)
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        guard let sale = SaleHelper.sharedInstance().newSale() else
        {
            XCTFail("Something went really wrong - doCardPayment")
            self.expectation.fulfill()
            return
        }
        self.aSale = sale
        self.aSale.cashRegisterId = UserHelper.sharedInstance()?.selectedCashRegisterId() ?? ""
        self.aSale.addSaleItem(NSDecimalNumber(string: "3.4"),
                               quantity:NSDecimalNumber(string: "5"),
                               taxRate:UserHelper.sharedInstance().preferredSaleItemTax(),
                               itemDescription:"Red Apple",
                               productId:"Dummy ID 1",
                               externalProductId : nil)
        self.aSale.addSaleItem(NSDecimalNumber(string: "2.25"),
                               quantity:NSDecimalNumber(string: "3"),
                               taxRate:UserHelper.sharedInstance().preferredSaleItemTax(),
                               itemDescription:"Orange",
                               productId:"Dummy ID 2",
                               externalProductId : nil)
        //You can add a service charge to the whole basket -- but this is optional
        self.aSale.addServiceChargeRate(UserHelper.sharedInstance().serviceChargeRate(), taxRate:UserHelper.sharedInstance().serviceChargeTax())
        //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchant has defined in setup.
        self.aSale.addGratuity(NSDecimalNumber(string: "1.0"),
                               taxRate:UserHelper.sharedInstance().tipTax())
        //You can add a discount for the whole basket when productId is nil, or per productId otherwise. Below, a discount of 6%
        self.aSale.addFlatDiscount(NSDecimalNumber(string: "6.0"))
    //    self.aSale.cashRegisterId = UserHelper.sharedInstance().selectedCashRegisterId() //Note: if your backend settings have cash mgmt enabled in backend, you will need to run cash tests first to get this value as well as shiftId below
        self.aSale.shiftId = UserHelper.sharedInstance().lastShiftId()
        self.aSale.resetPayments()
        
        if paymentOperation == .cardAuth
        {
            self.aSale.addCardAuthorization(self.aSale.totalToPay() ?? .zero,
                                      terminal:self.selectedDevice!)
        }
        else if paymentOperation == .regularCard
        {
            self.aSale.addCardPayment(self.aSale.totalToPay() ?? .zero,
                                      terminal:self.selectedDevice!)
        }
        else if paymentOperation == .cardPreAuth
        {
            self.aSale.addCardPreAuthorization(NSDecimalNumber(string: "5"),
                                            terminal: self.selectedDevice!)
        }
        
        if let paymentConfiguration : WDSaleRequestConfiguration = WDSaleRequestConfiguration.init(saleRequest: self.aSale)
        {
            sdk.terminalManager.setActive(self.selectedDevice, completion:{[weak self]() in
                self?.sdk.saleManager.pay(paymentConfiguration, with: (self?.paymentHandler)!)
            })
        }
        #endif
    }
    
    func refundTransaction()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        guard let saleToBeRefunded = self.saleResponse!.saleReturn() else
        {
            XCTFail("Something went really wrong - refundTransaction saleReturn")
            self.expectation.fulfill()
            return
        }
        //This is an example of full refund: all items are refunded, EXCEPT SERVICE CHARGE and GRATUITY
        saleToBeRefunded.removeServiceCharge()
        saleToBeRefunded.removeGratuity()
        guard let totalToPay = saleToBeRefunded.totalToPay() else
        {
            XCTFail("Something went really wrong - refundTransaction totalToPay")
            self.expectation.fulfill()
            return
        }
        saleToBeRefunded.cashRegisterId = UserHelper.sharedInstance().selectedCashRegisterId()
        //saleToBeRefunded.cashierId = self.aSale.cashierId
        saleToBeRefunded.customerId = self.aSale.customerId
        //This is an example of full refund: all items are refunded, EXCEPT SERVICE CHARGE
        saleToBeRefunded.removeServiceCharge()
        //For partial refund, see CashTests example
        saleToBeRefunded.addCardPayment(totalToPay, terminal:WDTerminal.init()) //terminal is unnecessary here
        self.saleResponse = nil
        sdk.saleManager.refundSale(saleToBeRefunded, message:"Refunded in demo app for testing reasons", completion:{[weak self](acceptSale : WDSaleResponse?, error : Error?) in
            self?.returnedErr = error
            self?.saleResponse = acceptSale
            self?.expectation.fulfill()
        })
        #endif
    }
    
    func captureSale()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        guard let saleToBeCaptured = self.saleResponse else
        {
            XCTFail("Something went really wrong - no sale to capture")
            self.expectation.fulfill()
            return
        }
        
        
        let refSaleRequest = saleToBeCaptured.referenceSaleRequest()
        
        refSaleRequest.addCardCapture(saleToBeCaptured.totalToPay() ?? NSDecimalNumber.one, originalPaymentId: saleToBeCaptured.processedCardPayments().first?.internalId ?? "")
        
        if let paymentConfiguration = WDSaleRequestConfiguration(saleRequest: refSaleRequest)
        {
            sdk.terminalManager.setActive(self.selectedDevice, completion:{[weak self]() in
                self?.sdk.saleManager.pay(paymentConfiguration, with: (self?.paymentHandler)!)
            })
        }
        #endif
    }

    func addSupplement()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        guard let currentSale = self.saleResponse else
        {
            XCTFail("Something went really wrong - no sale to capture")
            self.expectation.fulfill()
            return
        }
        
        
        let refSaleRequest = currentSale.referenceSaleRequest()
        
        refSaleRequest.addCardPreAuthorizationSupplement(NSDecimalNumber.one, originalTransactionId: currentSale.processedCardPayments().first?.internalId ?? "", authorizationCode:currentSale.processedCardPayments().first?.authorizationCode ?? "")
                
        if let paymentConfiguration = WDSaleRequestConfiguration(saleRequest: refSaleRequest)
        {
            sdk.terminalManager.setActive(self.selectedDevice, completion:{[weak self]() in
                self?.sdk.saleManager.pay(paymentConfiguration, with: (self?.paymentHandler)!)
            })
        }
        #endif
    }
    
    func doSepaEFTPayment()
    {
        #if arch(i386) || arch(x86_64)
        let file:NSString = (#file as NSString).lastPathComponent as NSString
        NSLog("\n\t\t    [%@ %@] Not runnable on simulator 📱",file.deletingPathExtension , #function);
        return

        #else
        //PART 4: We do a card sale using Spire terminal
        //---------------------------------------------
        expectation = self.expectation(description: "SEPA EFT sale")
        
        guard let sale = SaleHelper.sharedInstance().newSale() else
        {
            XCTFail("Something went really wrong - doSepaEFTPayment")
            self.expectation.fulfill()
            return
        }
        self.aSale = sale
        self.aSale.cashRegisterId = UserHelper.sharedInstance()?.selectedCashRegisterId() ?? ""
        self.aSale.addSaleItem(NSDecimalNumber(string: "3.4"),
                               quantity:NSDecimalNumber(string: "5"),
                               taxRate:UserHelper.sharedInstance().preferredSaleItemTax(),
                               itemDescription:"Red Apple",
                               productId:"Dummy ID 1",
                               externalProductId : nil)
        //    self.aSale.cashRegisterId = UserHelper.sharedInstance().selectedCashRegisterId() //Note: if your backend settings have cash mgmt enabled in backend, you will need to run cash tests first to get this value as well as shiftId below
        self.aSale.shiftId = UserHelper.sharedInstance().lastShiftId()
        self.aSale.resetPayments()
        
        
        self.aSale.addEFTCardPayment(self.aSale.totalToPay() ?? .zero,
                                     terminal:self.selectedDevice!)
        
        if let paymentConfiguration : WDSaleRequestConfiguration = WDSaleRequestConfiguration.init(saleRequest: self.aSale)
        {
            sdk.terminalManager.setActive(self.selectedDevice, completion:{[weak self]() in
                self?.sdk.saleManager.pay(paymentConfiguration, with: (self?.paymentHandler)!)
            })
        }
        
        self.waitForExpectations(timeout: 300, handler: nil)
        if (self.saleResponse == nil)
        {
            XCTFail("Sale did not succeed. Make sure your terminal is paired in your iOS device settings and that the terminal is in stand-by mode (ie. by switching off and then on and waiting until the screen lights off).")
            //NOTE:  if your merchant settings have cash mgmt enabled in backend, you will need to run cash tests first - otherwise you will receive a "not authorized" kind of error
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from:self.saleResponse)
        }
        #endif
    }
    
    
    func device(_ device: WDTerminal, connectionStatusDidChange status:WDExtensionConnectionStatus)
    {
        print("Connection status changed \(status)")

    }
    
    func discoverDevices(_ extensionUUID: WDExtensionTypeUUID)
    {
        sdk.terminalManager.discoverDevices(extensionUUID,
                                           completion: {[weak self](arr : [WDTerminal]?, error : Error?) in
                                            self?.selectedDevice = arr?.first
                                            self?.returnedErr = error
                                            self?.expectation.fulfill()
        })
    }
}
