//
//  MultitenderTests.swift
//  DemoEPOS
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import WDePOS

class MultitenderTests: CashTestsSwift
{
    override func setUp()
    {
        super.setUp()
    }

    /*
     
     Note: The following tests are examples of multi-tender payments.
     If you have cash management enabled in your merchant, you may need to have a valid open shift (you can do it using cash mgmg tests).
     
     */
    
    func testMultitenderPayments()
    {
        var completeSuccessfully = false
        var originalSaleResponseBackup : WDSaleResponse?
        //PART 1: We log-in and request user data
        //--------------------------------------
        if (loggedUser == nil || (loggedUser?.isKind(of: WDMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        else
        {
            UserHelper.sharedInstance().setUser(self.loggedUser)
        }

        if self.loggedUser?.merchant?.cashRegistersRequired == true
        {
            //PART 2: We request cash registers
            //--------------------------------------
            expectation = self.expectation(description: "We request cash registers")
            self.doCashManagement()
            self.waitForExpectations(timeout: 100, handler: nil)
            
            if self.lastShift == nil
            {
                XCTFail("There was an error handling the shifts. Please debug and keep track of any returned error.")
            }
            else
            {
                UserHelper.sharedInstance().storeOpenShiftId(self.lastShift?.internalId)
            }
        }
        
        //PART 3: We execute a Cash sale
        //--------------------------------------
        expectation = self.expectation(description: "Do a Cash Sale payment")
        self.doCashPayment(amount: NSDecimalNumber(string: "2.34"))
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.saleResponse == nil
        {
            XCTFail("There was an error when doing a cash transaction. Please debug and keep track of any returned error.")
        }
        else
        {
            originalSaleResponseBackup = self.saleResponse
            SaleHelper.sharedInstance().saleToSaveId(from: self.saleResponse)
        }
        
        //PART 4: We execute a second transaction continuing the payment above (it will be under its original sale id, composing a multi-tender payment)
        //--------------------------------------
        expectation = self.expectation(description: "Do a multi-tender payment")
        self.doMultitenderCashTransaction(amount : NSDecimalNumber(string: "3.21"))
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.saleResponse == nil
        {
            XCTFail("There was an error when doing a multi-tender transaction. Please debug and keep track of any returned error.")
        }
        else
        {
            completeSuccessfully = true
        }

       
        if completeSuccessfully == true
        {
            //PART 5a, with successful completion: We execute another transaction that will match the original total amount to pay, thus closing the sale as done
            //--------------------------------------
            expectation = self.expectation(description: "Do a multi-tender payment")
            self.doMultitenderCashTransaction(amount : NSDecimalNumber(string: "10.07"))
            self.waitForExpectations(timeout: 100, handler: nil)
            if self.saleResponse == nil
            {
                XCTFail("There was an error when doing a multi-tender transaction. Please debug and keep track of any returned error.")
            }
        }
        else
        {
            //PART 5b, with cancellation: We cancel all sub payments so to close the original sale with unsuccessful status
            //--------------------------------------
            expectation = self.expectation(description: "Do a sale refund")
            self.saleResponse = originalSaleResponseBackup
            SaleHelper.sharedInstance().saleToSaveId(from: self.saleResponse)
            self.refundTransaction(withAmount: NSDecimalNumber(string: "5.55")) //We refund the exact total of the sub payments we did
            //Note: we refund (cancel) the payment as we did cash payment, but usually the default (and cheapest) option is to reverse (return) the payments, specially for card payments.
            self.waitForExpectations(timeout: 100, handler: nil)
            if let response = self.saleResponse, response.status != .failed
            {
                XCTFail("There was an error when doing a cash transaction. Please debug and keep track of any returned error.")
            }
            else if self.saleResponse == nil
            {
                XCTFail("No sale response. Please debug and keep track of any returned error.")
            }
        }
    }
    
    func doCashManagement()
    {
        self.getCashRegisters()
        self.waitForExpectations(timeout: 100, handler: nil)
        //Note: ideally, you will consider the Cash Drawer serial number receive inside the cashRegister response, as it indicates where physical the money is stored,
        if self.cashRegister == nil
        {
            XCTFail("No valid cash register  found for the given user's merchant. You can create one with the test for that purpose")
        }
        else
        {
            UserHelper.sharedInstance().storeCashRegisterId(self.cashRegister?.internalId)
        }
        
        //PART 2b: We request cash shifts
        //--------------------------------------
        expectation = self.expectation(description: "Getting Cash Shifts")
        self.getLastShift()
        //Your shift keep track of what users open, close and do operations on them, for statistic report purposes.
        self.waitForExpectations(timeout: 100, handler: nil)
        
        //PART 2c: We check the validity of last shift, and create a new one if none is found, or existing ones are invalid
        //--------------------------------------
        
        expectation = self.expectation(description: "Check Last Cash Shift and Create New One If Needed")
        if self.lastShift == nil
        {
            //The shift does not exist: we simply open a new one.
            self.openShift()
        }
        else if self.lastShift?.closeTime != nil
        {
            //The shift is closed. Closed shift have a special parameter, shiftReport, with statistics about catalogue
            //categories, discounts, taxes, etc. that you may consider useful. We can simply open a new shift as
            //above, but we will get more content of the shift itself so you can check the structure of these reports.
            self.getCloseShiftDetailsThenOpen()
        }
        else
        {
            //The shift is open, and was open within the last 24 hours: it is perfectly valid to be used. Nothing to do.
            self.expectation.fulfill()
        }
    }
   
    func doMultitenderCashTransaction(amount : NSDecimalNumber)
    {
        let multiTenderRequest : WDReferenceSaleRequest = WDReferenceSaleRequest.init(originalSaleId: SaleHelper.sharedInstance().saleIdSaved())
        multiTenderRequest.addCashPayment(amount)
        
        if let paymentConfiguration : WDSaleRequestConfiguration = WDSaleRequestConfiguration.init(saleRequest: multiTenderRequest)
        {
            sdk.saleManager.pay(paymentConfiguration, with: self.paymentHandler!)
        }
    }
    
    override func testGetCashManagement()
    {
        //do nothing. Please find full cash manament tests in CashTestsSwift
    }
}
