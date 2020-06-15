//
//  WDPaymentRequestWeChat.h
//  WDePOS
//
//  Created by Danko, Radoslav on 15/11/2017.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import "WDPayment.h"

/**
 *  @class WDPaymentRequestWeChat
 *  @brief WeChat Payment Request - contains the information specific to WeChat
 **/
@interface WDPaymentRequestWeChat : WDPayment
/**
 */
@property (nonnull, nonatomic, strong) NSString * consumerId;

@end
