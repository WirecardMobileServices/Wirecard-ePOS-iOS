//
//  UserTestsSwift.swift
//  DemoEPOS
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import WDePOS

class CashTestsSwift: BaseTestsSwift
{
    override func setUp()
    {
        super.setUp()
    }

    /*
     
     Note: The following test is an example of a complete usage of our cash management system.
     You are encourage to run separate parts, if you like. For example, consecutive closing
     and opening of shifts, and pay In or Out operations.
     Keep track of the errors though, as the status of the last shift will determine the
     approval of some requests run out of the following sequence of events.
          
     */
    
    func testGetCashManagement()
    {
        //PART 1: We log-in and request user data
        //--------------------------------------
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser?.isKind(of: WDMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        else
        {
            UserHelper.sharedInstance().setUser(self.loggedUser)
        }

        //Cash management per se, using mandatory cash registers and cash shifts, can be disabled or enabled in backend side. We detect here what's the case and do cash management or directly jumpint into cash payment
        if self.loggedUser?.merchant?.cashRegistersRequired == true
        {
            //PART 2: We request cash registers
            //--------------------------------------
            expectation = self.expectation(description: "We request cash registers")
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
            
            //PART 3: We request cash shifts
            //--------------------------------------
            expectation = self.expectation(description: "Gettig Cash Shifts")
            self.getLastShift()
            //Your shift keep track of what users open, close and do operations on them, for statistic report purposes.
            self.waitForExpectations(timeout: 100, handler: nil)
            
            //PART 4: We check the validity of last shift, and create a new one if none is found, or existing ones are invalid
            //--------------------------------------
            expectation = self.expectation(description: "Check Last Cash Shift and Create New One If Needed")
            let openTime : NSDate = NSDate.init(date: self.lastShift?.openTime, hour: 0, minute: 0, second: 0)
            if self.lastShift != nil && self.lastShift?.shiftStatus == "OPEN" && openTime.isStillToday() == false
            {
                //The shif exist, but it was open more than 24 hours ago. We need to close it, then open a new one.
                self.closeShift()
            }
            else if self.lastShift == nil
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
            self.waitForExpectations(timeout: 100, handler: nil)
            
            if self.lastShift == nil
            {
                XCTFail("There was an error handling the shifts. Please debug and keep track of any returned error.")
            }
            else
            {
                UserHelper.sharedInstance().storeOpenShiftId(self.lastShift?.internalId)
            }
            
            //PART 5: We request activities of a shift
            //--------------------------------------
             expectation = self.expectation(description: "Gettig Activities of a Shift")
            //Note: While you can only close the last shift (no more than one shift can be open at a cash registers)
            //You can request details of activities of any existing shift you know the id.
            self.getShiftActivities()
            self.waitForExpectations(timeout: 100, handler: nil)
            
            //PART 6: We request a Cash In/Out operation of the last shift - the open one
            //--------------------------------------
            expectation = self.expectation(description: "Requesting a Cash Operation")
            self.doingCashOperation()
            self.waitForExpectations(timeout: 100, handler: nil)
            if self.cashOperationSucceed == false
            {
                XCTFail("There was an error Paying In or Out. Please debug and keep track of any returned error.")
            }
            
        } //End of Cash Register required
        
        
        //PART 7: We execute a Cash sale with a basket full of items
        //--------------------------------------
        expectation = self.expectation(description: "Do a Cash Sale payment")
        self.doCashPayment()
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.saleResponse == nil
        {
            XCTFail("There was an error when doing a cash transaction. Please debug and keep track of any returned error.")
        }
        else
        {
            SaleHelper.sharedInstance().saleToSaveId(from: self.saleResponse)
        }
        
        //PART 8: We refund the cash sale we just did
        //-------------------------------------------
        expectation = self.expectation(description: "Do a sale refund")
        self.refundTransaction()
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.saleResponse == nil || self.saleResponse?.status != .returned
        {
             XCTFail("There was an error when doing a cash transaction. Please debug and keep track of any returned error.")
        }
    }
    
    func getCashRegisters()
    {
        guard let merchantId = self.loggedUser?.merchant?.merchantId else
        {
            XCTFail("Something went really wrong - getCashRegisters")
            self.expectation.fulfill()
            return
        }
        
        sdk.cashManager.cashRegisters(merchantId,
                                      shopId: nil,
                                      cashDrawerVendor: nil,
                                      completion: {[weak self](arrCashiers : [WDCashRegister]?, error : Error?) in
                                        
            //Note: you may have several cash registers in the arrCashiers, and you can select any of them if marked as enabled. You can allow the user to do the selection through some picker for example
            if let cashregs : [WDCashRegister] = arrCashiers
            {
                for cashReg : WDCashRegister in cashregs
                {
                    if cashReg.drawerStatus == "ENABLED" {
                        self?.cashRegister = cashReg
                        break
                    }
                }
            }

            self?.returnedErr = error
            self?.expectation.fulfill()
        })
    }
    
    func getLastShift()
    {
        guard let cashRegisterId = self.cashRegister?.internalId else
        {
            XCTFail("Something went really wrong - getLastShift")
            self.expectation.fulfill()
            return
        }
        
        let query : WDShiftQuery = WDShiftQuery.init(page: 0,
                                                                 pageSize: 20,
                                                                 orderBy: .openTime,
                                                                 order: .descending)
        sdk.cashManager.shifts(cashRegisterId,
                               query: query,
                               completion: {[weak self](arrShifts : [WDCashShift]?, error : Error?) in
            self?.returnedErr = error
            //if shifts founds, with a openTime descending sorting, the first will always be the oldest shift. We will check the status and open date, and close it or use it if it is still valid. If no shifts found for given cash register, We will create a new one further in the test
            self?.lastShift = arrShifts?.first
            self?.expectation.fulfill()
        })
    }
    
    func getCloseShiftDetailsThenOpen() //Used as a Z-Report example
    {
        guard let lastShiftId = self.lastShift?.internalId, let cashRegisterId = self.cashRegister?.internalId else
        {
            XCTFail("Something went really wrong - getCloseShiftDetailsThenOpen")
            self.expectation.fulfill()
            return
        }
        
        sdk.cashManager.shiftDetails(lastShiftId,
                                     cashRegister: cashRegisterId,
                                     completion: {[weak self](cashShift : WDCashShift?, error : Error?) in
            guard let reportCategories = cashShift?.shiftReport?.reportCategories, reportCategories.count <= 0, error != nil, cashShift?.shiftReport != nil
                else
            {
                self?.returnedErr = error
                XCTFail("Error - Could not get Z-Reports");
                self?.expectation.fulfill()
                return
            }
            self?.openShift()
        })
    }
    
    func openShift()
    {
        guard let cashRegisterId = self.cashRegister?.internalId else
        {
            XCTFail("Something went really wrong - openShift")
            self.expectation.fulfill()
            return
        }
        sdk.cashManager.openShift(cashRegisterId,
                                  note: "Here you can include a text note",
                                  amount: NSDecimalNumber.init(value: 100),
                                  completion: {[weak self](success : Bool, error : Error?) in
            self?.returnedErr = error
            if error == nil && success == true
            {
                self?.getLastShift()
            }
            else
            {
                self?.expectation.fulfill()
            }
        })
    }
    
    func closeShift()
    {
        guard let cashRegisterId = self.cashRegister?.internalId else
        {
            XCTFail("Something went really wrong - closeShift")
            self.expectation.fulfill()
            return
        }
        sdk.cashManager.closeShift(cashRegisterId,
                                   note: "Here you can include a text note",
                                   amount: NSDecimalNumber.init(value:100),
                                   completion:{[weak self](success : Bool, error : Error?) in
            self?.returnedErr = error
            if error == nil && success == true
            {
                self?.openShift()
            }
            else
            {
                self?.expectation.fulfill()
            }
        })
    }
    
    func getShiftActivities()
    {
        guard let lastShiftId = self.lastShift?.internalId, let cashRegisterId = self.cashRegister?.internalId else
        {
            XCTFail("Something went really wrong - getShiftActivities")
            self.expectation.fulfill()
            return
        }
        let query : WDShiftQuery = WDShiftQuery.init(page: 0,
                                                                 pageSize: 10)
        sdk.cashManager.getOperationsForShift(lastShiftId,
                                              query: query,
                                              belongingToCashRegister: cashRegisterId,
                                              completion: {[weak self](arrActivities : [WDCashActivity]?, error : Error?) in
            //Cash activities are used for statistics.
            self?.expectation.fulfill()
        })
    }
    
    func doingCashOperation()
    {
        guard let cashRegisterId = self.cashRegister?.internalId, let currencyCode = self.cashRegister?.currency?.code else
        {
            XCTFail("Something went really wrong - doingCashOperation")
            self.expectation.fulfill()
            return
        }
        //Note: The operation of paying cash In or Out of a register is determined by the sign of the amount. In the "Pay In" below, the amount -100 would do a "Pay Out".
        sdk.cashManager.cashOperation(cashRegisterId,
                                      note: "Here you can add a text note",
                                      amount: NSDecimalNumber.init(value: 100),
                                      currency: currencyCode,
                                      completion: {[weak self](success : Bool, error : Error?) in
            self?.cashOperationSucceed = error == nil && success == true
            self?.expectation.fulfill()
        })
    }
    
    func doCashPayment()
    {
        //We will define a dummy payment configuration as an example. Feel free to modify and add content; the sale complexity is up to you.
        self.aSale = SaleHelper.sharedInstance().newSale()
        self.aSale?.addSaleItem(NSDecimalNumber.init(value:2.5),
                                quantity: 5,
                                taxRate: UserHelper.sharedInstance().preferredSaleItemTax(),
                                itemDescription: "Red Apple",
                                productId: "DummyID1")
        self.aSale?.addSaleItem(NSDecimalNumber.init(value:1.25),
                                quantity: 3,
                                taxRate: UserHelper.sharedInstance().preferredSaleItemTax(),
                                itemDescription: "Golden Apple",
                                productId: "DummyID2")
        self.aSale?.addServiceCharge(UserHelper.sharedInstance().serviceChargeRate(),
                                     taxRate:UserHelper.sharedInstance().serviceChargeTax())
        //You can add a tip of any value you want. Notice that backend validate taxes, so their values should match the ones your merchant has defined in setup.
        self.aSale?.addGratuity(NSDecimalNumber(floatLiteral: 1.0),
                                taxRate:UserHelper.sharedInstance().tipTax())
        //You can add a discount for the whole basket when productId is nil, or per productId otherwise. Below, a discount of 6%
        self.aSale?.addDiscount(NSDecimalNumber(floatLiteral: 6.0),
                                productId:nil)
        let paymentConfiguration : WDPaymentConfig = WDPaymentConfig.init()
        paymentConfiguration.sale = self.aSale!
        paymentConfiguration.sale.cashRegisterId = cashRegister?.internalId ?? ""
        paymentConfiguration.sale.shiftId = self.lastShift?.internalId ?? nil
        paymentConfiguration.sale.resetPayments()
        paymentConfiguration.sale.addCashPayment(paymentConfiguration.sale.totalToPay() ?? NSDecimalNumber.init(value:0))
        sdk.saleManager.pay(paymentConfiguration, delegate: self.paymentHandler!)
    }
    
    func refundTransaction()
    {
        guard let saleToBeRefunded : WDSaleRequest = self.saleResponse?.saleReturn() else
        {
            XCTFail("Something went really wrong getting saleToBeRefunded")
            return;
        }
        
        guard let saleResponse = saleResponse else
        {
            XCTFail("Something went really wrong getting saleResponse")
            return;
        }
        saleToBeRefunded.removeAllItems()
        saleToBeRefunded.cashRegisterId = cashRegister?.internalId ?? ""
        saleToBeRefunded.cashierId = saleResponse.cashierId
        saleToBeRefunded.customerId = saleResponse.customerId
        //This is an example of partial refund: only one item is refunded
        guard let anItem : WDSaleItemCore = aSale?.items?.first else
        {
            XCTFail("Something went really wrong getting anItem")
            return;
        }
        saleToBeRefunded.addSaleItem(anItem.unitPrice,
                                     quantity: 1,
                                     taxRate: anItem.taxRate,
                                     itemDescription: anItem.itemDescription,
                                     productId: (anItem as? WDSaleItem)?.externalProductId)
        saleToBeRefunded.addCashPayment(saleToBeRefunded.totalToPay() ?? NSDecimalNumber.init(value:0))
        sdk.saleManager.refundSale(saleToBeRefunded,
                                   message: "Refunded in demo app for testing reasons",
                                   completion: {[weak self](acceptSale : WDSaleResponse?, error : Error?) in
            self?.saleResponse = acceptSale
            self?.returnedErr = error
            self?.expectation.fulfill()
        })
    }
}
