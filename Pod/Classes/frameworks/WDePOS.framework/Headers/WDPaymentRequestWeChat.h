//
//  WDPaymentRequestWeChat.h
//  WDePOS
//
//  Created by Danko, Radoslav on 15/11/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDPayment.h"

/**
 *  @class WDPaymentRequestWeChat
 *  @brief WeChat Payment Request - contains the information specific to WeChat
 **/
@interface WDPaymentRequestWeChat : WDPayment
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use initWithAmount:consumerId:")));
- (nonnull instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount paymentMethod:(WDPaymentMethod)paymentMethod transactionType:(WDTransactionType)transactionType __attribute__((unavailable("use initWithAmount:transactionType:consumerId:")));
/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype )initWithAmount:(nonnull NSDecimalNumber *)amount
                         transactionType:(WDTransactionType)transactionType
                              consumerId:(nonnull NSString *)consumerId NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonnull, nonatomic, strong) NSString * consumerId;

@end
