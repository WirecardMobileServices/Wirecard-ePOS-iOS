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

class UserTestsSwift: BaseTestsSwift
{
    var userHelper : UserHelper!
    
    override func setUp()
    {
        super.setUp()
    }
    
    func testCredentialsAndGetUser()
    {
        

        if (loggedUser == nil || (loggedUser?.isKind(of: WDMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
    }
    
    
    func testRemindUsername()
    {
        expectation = self.expectation(description: "Remind Username")
        let request : WDRemindUsername = WDRemindUsername()
        request.email = "your@email.com";//Here goes the email address you want to send the username for reminder
        sdk.userManager.manageCredentials(request,
                                          completion: {[weak self](result : WDResult?, error: Error?) in
            self?.returnedErr = error
            self?.resultStatus = result?.status
            self?.expectation.fulfill()
        })
        self.waitForExpectations(timeout: 100, handler: nil)
        if (returnedErr != nil || resultStatus != .OK)
        {
            XCTFail("Failed to remind username")
        }
    }
    
    func testRequestPasswordReset()
    {
        expectation = self.expectation(description: "Request Password Reset")
        let request : WDRequestPasswordReset = WDRequestPasswordReset()
        request.username = "Your username here";//Here goes the username of the user who wants to reset the password. Password will be sent to his/her email. Note that, even when the username was not found, this will return OK: it is not secure to disclose that a username is correct.
        sdk.userManager.manageCredentials(request,
                                          completion: {[weak self](result : WDResult?, error: Error?) in
            self?.returnedErr = error
            self?.resultStatus = result?.status
            self?.expectation.fulfill()
        })
        self.waitForExpectations(timeout: 100, handler: nil)
        if (returnedErr != nil || resultStatus != .OK)
        {
            XCTFail("Failed to reset password.")
        }
    }
    
    func testChangePassword()
    {
        #if arch(i386) || arch(x86_64)
            let file:NSString = (#file as NSString).lastPathComponent as NSString
            NSLog("\n\t\t    [%@ %@] Not to run in automated tests 🤖",file.deletingPathExtension , #function);
            return
            
        #endif
        expectation = self.expectation(description: "Change Password")
        let changePassword : WDChangePassword = WDChangePassword()
        //NOTE: To test password change functionality please provide below your own old password and your new password instead of the dummy strings
        changePassword.currentPassword = "Your current password here"; // old password of the current user
        changePassword.theNewPassword = "Your new, validated password here"; // new password of the current user
        //Note that you should offer the functionality to change password only to users already authenticated users in your app, as the SDK needs the credentials from its initialization:
        sdk.userManager.manageCredentials(changePassword,
                                          completion: {[weak self](result : WDResult?, error : Error?) in
            /* "result" are the details from the credential management process.
             WDResultStatusOK indicates the process ended with OK status.
             WDResultStatusPasswordCriteriaNotMet - in the case of changing the password indicates that the new password does not meet the criteria.
             WDResultStatusPasswordValidationFailure - in the case of changing password indicates the password validation failure old and new password mismatch.
             
             Note that result.detail will tell you what may have failed, including incorrect current password, password criteria not met, etc.
             The password policy can be requested using sdk.userManager.passwordPolicy, so you can use this criteria in your UI, and even for validating the strings yourself, though this is necessary as you will get a validation result in completion anyways.
             */
            self?.returnedErr = error
            self?.resultStatus = result?.status
            self?.expectation.fulfill()
        })
            
        self.waitForExpectations(timeout: 100, handler: nil)
        if (returnedErr != nil || resultStatus != .OK)
        {
            XCTFail("Failed to change password.")
        }
    }
    
}
