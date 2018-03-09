//
//  WDUserManager.h
//   WDePOS
//
//  Created by Danko, Radoslav on 19/10/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDUserManager
 *  @brief User Management
 */
@interface WDUserManager : NSObject
-(instancetype )initWithSDK:(id)sdk;
#pragma mark - User information and credential management
/**
 *  @brief Get current merchant user - based on the user used during the SDK initialisation
 *  @param completion Block executed at the end of the login method
 **/
-(void)currentUser:(MerchantDetailCompletion)completion;

/**
 *  @brief Change the user password
 *  @param credentialManagementRequest One of AcceptRequestPasswordReset, AcceptRemindUsername, AcceptChangePassword objects
 *  If AcceptChangePassword is to be used then WDePOS needs to be initialised with current Environment, username and password
 *  otherwise initialise WDePOS with environment only
 *  @param completion Block executed at the end of the method
 */
-(void)manageCredentials:(id )credentialManagementRequest completion:(CredentialManagementCompletion )completion;

/**
 *  @brief Get password policy, which defines the minimal lenght of password, valid characters, etc
 *  @param completion Block executed at the end of the method
 */
-(void)passwordPolicy:(PasswordPolicyCompletion )completion;

@end

NS_ASSUME_NONNULL_END
