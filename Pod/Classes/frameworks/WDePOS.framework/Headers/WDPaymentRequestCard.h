//
//  WDPaymentRequestCard.h
//   WDePOS
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDPayment.h"

@class WDTerminal;

/**
 *  @class WDPaymentRequestCard
 *  @brief Card Payment Request - contains the information specific to Card payment
 **/
@interface WDPaymentRequestCard : WDPayment
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithAmount:transactionType:terminal:")));
+(nonnull instancetype)new __attribute__((unavailable("use initWithAmount:transactionType:terminal:")));
-(nonnull instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                        paymentMethod:(WDPaymentMethod)paymentMethod
                      transactionType:(WDTransactionType)transactionType __attribute__((unavailable("use initWithAmount:transactionType:terminal:")));

/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype )initWithAmount:(nonnull NSDecimalNumber *)amount
                         transactionType:(WDTransactionType)transactionType
                                terminal:(nonnull WDTerminal *)terminal NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonnull, nonatomic, strong) WDTerminal * terminal;

@end
