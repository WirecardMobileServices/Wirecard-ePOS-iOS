//
//  WDSSessionManagerCredentials.h
//   WDePOS
//
//  Created by Danko, Radoslav on 09/12/2016.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 *  @class WDSSessionManagerCredentials
 *  @brief Session credentials
 **/
@interface WDSSessionManagerCredentials : NSObject
+(nonnull WDSSessionManagerCredentials *)sharedInstance;
@property (nonatomic, strong)  NSString *_Nullable username;
@property (nonatomic, strong)  NSString *_Nullable password;
@property (nonatomic, strong)  NSMutableDictionary *_Nullable users;
@end
