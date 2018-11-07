//
//  WDPaymentRequestAlipay.h
//  WDePOS
//
//  Created by Timko, Marek on 07/07/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDPayment.h"

/**
 *  @class WDPaymentRequestAlipay
 *  @brief Alipay Payment Request - contains the information specific to Alipay
 **/
@interface WDPaymentRequestAlipay : WDPayment
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use initWithAmount:transactionType:consumerId:")));
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
