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
#import "BaseTests.h"

@interface UserTestsObjc : BaseTestsObcj
{

}

@end

@implementation UserTestsObjc

- (void)setUp
{
    [super setUp];
}

-(void)testCredentialsAndGetUser
{
    expectation = [self expectationWithDescription:@"testCredentialsAndGetUser"];
    MerchantDetailCompletion completion = ^(WDMerchantUser *merchantUser, NSError *err)
    {
        loggedUser = merchantUser;
        returnedErr = err;
        [expectation fulfill];
    };
    loggedUser = nil;
    [[sdk userManager] currentUser:completion];
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || !loggedUser)
    {
        XCTFail(@"Failed to get user, probably credentials were wrong.");
    }
}

- (void)testRemindUsername
{
    expectation = [self expectationWithDescription:@"testRemindUsername"];
    WDRemindUsername *request = [WDRemindUsername new];
    request.email = @"your@email.com";//Here goes the email address you want to send the username for reminder
    [sdk.userManager manageCredentials:request
                            completion:^(WDResult * result, NSError* error)
    {
        returnedErr = error;
        resultStatus = result.status;
        [expectation fulfill];
    }];
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || resultStatus != WDResultStatusOK)
    {
        XCTFail(@"Failed to remind username.");
    }
}

- (void)testRequestPasswordReset
{
    expectation = [self expectationWithDescription:@"testRemindUsername"];
    WDRequestPasswordReset *request = [WDRequestPasswordReset new];
    request.username = @"Your username";//Here goes the username of the user who wants to reset the password. Password will be sent to his/her email
    //Note that, even when the username was not found, this will return OK: it is not secure to confirm a username is correct in such a request.
    [sdk.userManager manageCredentials:request
                            completion:^(WDResult * result, NSError* error)
     {
         resultStatus = result.status;
         returnedErr = error;
         [expectation fulfill];
     }];
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || resultStatus != WDResultStatusOK)
    {
        XCTFail(@"Failed to reset password.");
    }
}

- (void)testChangePassword
{
#if TARGET_OS_SIMULATOR
    NSLog(@"\n\t\t   %s Not to run in automated tests 🤖",__PRETTY_FUNCTION__);
    return;
    
#else
    expectation = [self expectationWithDescription:@"testChangePassword"];
    
    //End of credential management process
    CredentialManagementCompletion completion = ^(WDResult * _Nullable result, NSError* _Nullable error){
        //result - details from the credential management process
        // WDResultStatusOK indicates the process ended with OK status
        // WDResultStatusPasswordCriteriaNotMet - in the case of changing the password indicates that the new password does not
        //                                            meet the criteria
        // WDResultStatusPasswordValidationFailure - in the case of changing password indicates the password validation failure
        //                                               old and new password mismatch
        
        //Note that result.detail will tell you what may have failed, including incorrect current password, password criteria not met, etc.
        //The password policy can be requested using sdk.userManager.passwordPolicy, so you can use this criteria in your UI, and even for validating the strings yourself, though this is necessary as you will get a validation result in completion anyways.
        returnedErr = error;
        resultStatus = result.status;
        [expectation fulfill];
    };
    
    //******************* CHANGE PASSWORD *******************//
    // Change Password details - available only to the AUTHENTICATED user
    WDChangePassword *changePassword = [WDChangePassword new];
    //NOTE: To test password change functionality please provide your own old password and your new password
    changePassword.currentPassword = @"Your current password here"; // old password of the current user
    changePassword.theNewPassword = @"Your new, validated password here"; // new password of the current user
    
    
    // Change password for the AUTHENTICATED user
   //Note that current password and username are setup in sdk already, see first function in this file
    [sdk.userManager manageCredentials:changePassword // Change password object
                            completion:completion];//End of credential management process
    
    
    [self waitForExpectationsWithTimeout:100 handler:nil];
    if (returnedErr || resultStatus != WDResultStatusOK)
    {
        XCTFail(@"Failed to change password.");
    }
    
#endif

}


 
@end
