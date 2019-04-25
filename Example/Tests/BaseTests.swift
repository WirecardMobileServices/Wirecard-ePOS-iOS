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
import CocoaLumberjack

class PaymentHandler : NSObject, WDPaymentDelegate {
    var completion: ((_ transaction: WDSaleResponse?, _ error: Error?) -> Void)?

    init(completion: @escaping (_ transaction: WDSaleResponse?, _ error: Error?) -> Void) {
        self.completion = completion
        super.init()
    }

    // Updates from the payment flow
    func progress(_ paymentProgress: WDStateUpdate) {
        // statusUpdate - coded statuses are reported throughout the payment flow
    }

    // In the case the Cardholder Signature is required by the Payment flow this block will be executed
    // Your task is to respond to it by collecting the signature image from the customer and
    // posting it back in the sendCollectedSignature method
    func collectSignature(_ signatureRequest: WDSignatureRequest) {
        //signatureRequest - comes from the payment flow and once you collect the signature from the customer
        // send it back in the signatureRequest.sendCollectedSignature
        signatureRequest.sendCollectedSignature(TestUtils.signatureImage(fromText: "Test"),nil)
        //The signature image is transferred to the backend and stored with the Sale
    }

    // Note: Applicable to terminals without BUTTONS
    // In the case the Cardholder Signature was collected then the merchant is required to confirm it's validity
    // A. If the terminal has buttons that are used for Approving/Rejecting then this block is either never called from Payment flow
    // or it's signatureVerificationCallback comes nil
    // B. If the terminal does not have buttons then the Application must present a user interface to Approve/Reject the Cardholder Signature
    func confirm(_ confirmationType: WDPaymentConfirmationType, paymentConfirmationResult: PaymentConfirmationResult? = nil) {
        if let paymentConfirmationResult = paymentConfirmationResult {
            // Here the simplified use of Approving the Cardholder Signature is demonstrated
            paymentConfirmationResult(WDPaymentConfirmationResult.approved)
        }
    }

    // Note: Applicable to terminals without BUTTONS
    // In the case the payment Card has more than one card application available then the client application
    // has to present user interface for the Cardholder to select preferred card application
    // The list of card applications is present in appSelectionRequest.appsArray as a list of Strings
    func cardApplication(_ appSelectionRequest: WDAppSelectionRequest) {
        // There is more than 1 card application available
        // Present the UI for the Cardholder to select preferred card application (Debit | Credit)
        if ((appSelectionRequest.appsArray?.count) != nil) {
            // Here we demonstrate the simplified use of selecting the first card application from the list of available card applications
            // and sending it to the Payment flow
            appSelectionRequest.selectCardApplication(UInt(0))
        }
    }

    // The end of the payment process
    func completion(_ saleResponse: WDSaleResponse?, saleResponseError: Error?) {
        //sale - Is the completed Sale - contains the sale status, details, results
        //error - If any error is encountered during the sale it would be reported
        //in the form of error and hierarchy of underlying errors to give you as much details as possible
        self.completion?(saleResponse, saleResponseError)
    }
}

class BaseTestsSwift: XCTestCase, WDePOSDelegate
{
    var returnedErr : Error!
    var expectation : XCTestExpectation!
    var sdk : WDePOS!
    var loggedUser : WDMerchantUser?
    var cashRegister : WDCashRegister?
    var lastShift : WDCashShift?
    var aSale : WDSaleRequest!
    var saleResponse : WDSaleResponse?
    var cashOperationSucceed : Bool?
    var resultStatus : WDResultStatus?
    var successfulDownload : Bool?
    var selectedDevice : WDTerminal?
    var connectionStatus : WDExtensionConnectionStatus?
    var paymentHandler: PaymentHandler?
    
    override func setUp()
    {
        super.setUp()
        self.continueAfterFailure = false
        if(sdk == nil){
            sdk = WDePOS.sharedInstance()
            self.loggedUser = sdk.authenticatedUser
        }
        if (self.loggedUser == nil){
        
            expectation = self.expectation(description: "Setup")
            
            sdk.setup(with: .publicTest,
                      username: KUSERNAME,
                      password: KPASSWORD,
                      completion:{[weak self]( currentUser:WDMerchantUser? , cashier:WDMerchantCashier?, error:Error?) in
                
                self?.sdk.add(self!)
                self?.sdk.setDevMode(true) //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - Do not forget to disable it before releasing your app to the public!!
                WDePOS.ddSetLogLevel(DDLogLevel.info.rawValue)
                        self?.loggedUser = currentUser
                        self?.returnedErr = error
                self?.expectation.fulfill()
            })
            
            self.waitForExpectations(timeout: 25, handler: nil)
        }
        
        if(self.paymentHandler == nil){
            self.paymentHandler = PaymentHandler(completion: { (transaction: WDSaleResponse?, error: Error?) in
                self.saleResponse = transaction
                self.returnedErr = error
                self.expectation.fulfill()
            })
        }
    }
    
    override func tearDown()
    {
        super.tearDown()
    }
  

}
