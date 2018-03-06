//
//  TestUtils.h
//  WDePOS
//
//  Created by Francisco Fortes on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import "SaleHelper.h"
#import "UserHelper.h"
#import "DDLog.h"

@interface PaymentHandler : NSObject<WDPaymentDelegate>
@end

@interface BaseTestsObcj : XCTestCase <WDePOSDelegate>
{
    __block NSError *returnedErr;
    __weak XCTestExpectation *expectation;
    WDePOS *sdk;
    SaleHelper *saleHelper;
    UserHelper *userHelper;
    __block WDMerchantUser *loggedUser;
    __block WDCashRegister *cashRegister;
    __block WDCashShift *lastShift;
    __block WDSaleRequest *aSale;
    __block WDSaleResponse *saleResponse;
    __block WDResultStatus resultStatus;
    __block WDTerminal *selectedDevice;
    __block PaymentHandler *_paymentHandler;
}

-(void)loginAndGetUserData;

@end
