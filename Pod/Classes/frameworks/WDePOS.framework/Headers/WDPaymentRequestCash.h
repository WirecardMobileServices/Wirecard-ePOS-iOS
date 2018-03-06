//
//  WDPaymentRequestCash.h
//   WDePOS
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDPayment.h"

/**
 *  @class WDPaymentRequestCash
 *  @brief Cash Payment Detail - contains the information specific to Cash payment
 **/
@interface WDPaymentRequestCash : WDPayment
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithAmount:transactionType:")));
+(nonnull instancetype)new __attribute__((unavailable("use initWithAmount:transactionType:")));
-(nonnull instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                        paymentMethod:(WDPaymentMethod)paymentMethod
                      transactionType:(WDTransactionType)transactionType __attribute__((unavailable("use initWithAmount:transactionType:")));
-(nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
-(nullable instancetype)initWithAmount:(NSDecimalNumber * __nonnull)amount
                       transactionType:(WDTransactionType)transactionType NS_DESIGNATED_INITIALIZER;
@end
