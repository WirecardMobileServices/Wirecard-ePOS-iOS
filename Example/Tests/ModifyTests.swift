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

class ModifyTests: CashTestsSwift
{
    override func setUp()
    {
        super.setUp()
    }

    /*
     
     Note: The following tests are examples of sale modification/maintenance.
     If you have cash management enabled in your merchant, you may need to have a valid open shift (you can do it using cash mgmg tests).
     
     */
    
    func testModifySale()
    {
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
        self.doIncompleteCashPayment(amount: NSDecimalNumber.init(value: 1.11))
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.saleResponse == nil
        {
            XCTFail("There was an error when doing a cash transaction. Please debug and keep track of any returned error.")
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from: self.saleResponse)
        }
        
        //PART 4: We execute a modification on the sale we left open above
        //----------------------------------------------------------------
        self.aSale.addSaleItem(NSDecimalNumber.init(value:3.23),
                    quantity: NSDecimalNumber(value: 1),
                    taxRate: UserHelper.sharedInstance().preferredSaleItemTax() ?? NSDecimalNumber.zero,
                    itemDescription: "Water bottle",
                    productId: "DummyID3",
                    externalProductId:nil)
        guard let saleMaintain = self.saleResponse?.saleMaintain() else
        {
            XCTFail("There was an error creating the Sale Maintain object")
            return
        }
        saleMaintain.items = self.aSale.items
        saleMaintain.totalAmount = self.aSale.total()
        saleMaintain.note = "I added a new item and I am reusing the sale request to easily recalculate sale total"
        
        expectation = self.expectation(description: "Modify sale")

        sdk.saleManager.maintainSale(saleMaintain) { [weak self](acceptSale : WDSaleResponse?, error : Error?) in
            self?.returnedErr = error
            self?.saleResponse = acceptSale
            self?.expectation.fulfill()
        }
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.saleResponse == nil
        {
            XCTFail("There was an error when doing a multi-tender transaction. Please debug and keep track of any returned error.")
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
    
    override func testGetCashManagement()
    {
        //do nothing. Please find full cash manament tests in CashTestsSwift
    }
    
    func doIncompleteCashPayment(amount : NSDecimalNumber?)
    {
        //We will define a dummy payment configuration as an example. Feel free to modify and add content; the sale complexity is up to you.
        self.aSale = SaleHelper.sharedInstance().newSale()
        self.aSale?.addSaleItem(NSDecimalNumber.init(value:1.0),
                                quantity: NSDecimalNumber(value: 1),
                                taxRate: UserHelper.sharedInstance().preferredSaleItemTax() ?? NSDecimalNumber.zero,
                                itemDescription: "Red Apple",
                                productId: "DummyID1",
                                externalProductId:nil)
        self.aSale?.addSaleItem(NSDecimalNumber.init(value:1.25),
                                quantity: NSDecimalNumber(value: 1),
                                taxRate: UserHelper.sharedInstance().preferredSaleItemTax() ?? NSDecimalNumber.zero,
                                itemDescription: "Golden Apple",
                                productId: "DummyID2",
                                externalProductId:nil)
//        self.aSale?.addServiceCharge(UserHelper.sharedInstance().serviceChargeRate(),
//                                     taxRate:UserHelper.sharedInstance().serviceChargeTax())
//        //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchant has defined in setup.
//        self.aSale?.addGratuity(NSDecimalNumber(floatLiteral: 1.0),
//                                taxRate:UserHelper.sharedInstance().tipTax())
//        //You can add a discount for the whole basket when productId is nil, or per productId otherwise. Below, a discount of 6%
//        self.aSale?.addFlatDiscount(NSDecimalNumber(floatLiteral: 6.0))
        
        if let cashRegisterId = cashRegister?.internalId
        {
            self.aSale.cashRegisterId = cashRegisterId
        }
        self.aSale.shiftId = self.lastShift?.internalId ?? nil
        self.aSale.resetPayments()
        if amount == nil
        {
            self.aSale.addCashPayment(self.aSale.totalToPay() ?? NSDecimalNumber.init(value:0))
        }
        else
        {
            self.aSale.addCashPayment(amount ?? NSDecimalNumber.init(value:0))
        }
        
        if let paymentConfiguration : WDSaleRequestConfiguration = WDSaleRequestConfiguration.init(saleRequest: self.aSale)
        {
            sdk.saleManager.pay(paymentConfiguration, with: self.paymentHandler!)
        }
    }
}
