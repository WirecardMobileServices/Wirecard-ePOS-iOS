//
//  CashTests.m
//  AlphaMPOS
//
//  Created by Francisco Fortes on 31/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <libextobjc/EXTScope.h>
#import "BaseTests.h"
#import "TestUtils.h"

@interface PaymentHandler ()
@property (nonatomic, copy) void (^completion)(WDSaleResponse*, NSError*);
@end

@implementation PaymentHandler

- (instancetype)initWithCompletionBlock:(void (^)(WDSaleResponse*, NSError*))completionBlock {
    if ( (self = [super init]) ) {
        _completion = completionBlock;
    }
    return self;
}

// The end of the payment process
- (void)completion:(WDSaleResponse * _Nullable)saleResponse saleResponseError:(NSError * _Nullable)saleResponseError {
    //sale - Is the completed Sale - contains the sale status, details, results
    //error - If any error is encountered during the sale it would be reported
    //in the form of error and hierarchy of underlying errors to give you as much details as possible
    if (self.completion) {
        self.completion(saleResponse, saleResponseError);
    }
}

// Updates from the payment flow
- (void)progress:(WDStateUpdate)paymentProgress {
    // statusUpdate - coded statuses are reported throughout the payment flow

    NSLog(@"Transaction flow progress status: %ld", (long)paymentProgress);
    //You may decide to update your UI based on the status received here.
}

// In the case the Cardholder Signature is required by the Payment flow this block will be executed
// Your task is to respond to it by collecting the signature image from the customer and
// posting it back in the sendCollectedSignature method
- (void)collectSignature:(WDSignatureRequest * _Nonnull)signatureRequest {
    //signatureRequest - comes from the payment flow and once you collect the signature from the customer
    // send it back in the signatureRequest.sendCollectedSignature
    NSLog(@"Cardholder name:%@",signatureRequest.cardHolderName);
    NSLog(@"Issuer:%@",signatureRequest.issuer);
    signatureRequest.sendCollectedSignature([TestUtils signatureImageFromText:@"Test"],nil); //In a real case scenario, you will send the signature image drawn by the client
    //The signature image is transferred to the backend and stored with the Sale
}

// Note: Applicable to terminals without BUTTONS
// In the case the Cardholder Signature was collected then the merchant is required to confirm it's validity
// A. If the terminal has buttons that are used for Approving/Rejecting then this block is either never called from Payment flow
// or it's signatureVerificationCallback comes nil
// B. If the terminal does not have buttons then the Application must present a user interface to Approve/Reject the Cardholder Signature
- (void)confirm:(WDPaymentConfirmationType)confirmationType paymentConfirmationResult:(PaymentConfirmationResult _Nullable)paymentConfirmationResult {

    if (paymentConfirmationResult) {
        // Here the simplified use of Approving the Cardholder Signature is demonstrated
        paymentConfirmationResult(WDPaymentConfirmationResultApproved);
    }

};

// Note: Applicable to terminals without BUTTONS
// In the case the payment Card has more than one card application available then the client application
// has to present user interface for the Cardholder to select preferred card application
// The list of card applications is present in appSelectionRequest.appsArray as a list of Strings
- (void)cardApplication:(WDAppSelectionRequest * _Nonnull)appSelectionRequest {
    // There is more than 1 card application available
    // Present the UI for the Cardholder to select preferred card application (Debit | Credit)
    if(appSelectionRequest.appsArray.count > 0){
        // Here we demonstrate the simplified use of selecting the first card application from the list of available card applications
        // and sending it to the Payment flow
        appSelectionRequest.selectCardApplication(0);
    }
}

@end

@implementation BaseTestsObcj

- (void)setUp
{
    [super setUp];
    self.continueAfterFailure = NO;
    
    if(sdk == nil){
        sdk = [WDePOS sharedInstance];
        loggedUser = sdk.authenticatedUser;
        saleHelper = [SaleHelper sharedInstance];
        userHelper = [UserHelper sharedInstance];
    }
    
    if(!loggedUser){

        expectation = [self expectationWithDescription:@"Setup"];
        
        [sdk setupWithEnvironment:WDEnvironmentPublicTest username:KUSERNAME password:KPASSWORD completion:^(WDMerchantUser * _Nullable currentUser, WDMerchantCashier * _Nullable cashier, NSError * _Nullable error) {
            [sdk addDelegate:self];
            [sdk setDevMode:YES]; //Setting dev mode as enabled will write logs in your app's document folder and fill the console log with debug messages - do not forget to disable it
                                  //before releasing your app to the public!!
            [WDePOS ddSetLogLevel:DDLogLevelInfo];
            loggedUser = currentUser;
            returnedErr = error;
            [expectation fulfill];
        }];
        
        [self waitForExpectationsWithTimeout:25 handler:nil];


    }
    
    if(!_paymentHandler){
        _paymentHandler = [[PaymentHandler alloc] initWithCompletionBlock:^(WDSaleResponse *transaction, NSError *error) {
            NSLog(@"Payment Completion Error:%@",error);
            saleResponse = transaction;
            returnedErr = error;
            [expectation fulfill];
        }];
    }
    XCTAssert(true,@"Setup success");
}

- (void)tearDown
{
    [super tearDown];
}



@end
