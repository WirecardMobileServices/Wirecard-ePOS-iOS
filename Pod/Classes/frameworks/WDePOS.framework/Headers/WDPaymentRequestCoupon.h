//
//  WDPaymentRequestCoupon.h
//   WDePOS
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDPayment.h"

/**
 *  @class WDPaymentRequestCoupon
 *  @brief Coupon Payment Request - contains the information specific to Coupon payment
 **/
@interface WDPaymentRequestCoupon : WDPayment
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithAmount")));

-(nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount paymentMethod:(WDPaymentMethod)paymentMethod transactionType:(WDTransactionType)transactionType __attribute__((unavailable("use initWithAmount:transactionType:internalId:externalId:")));
-(nullable instancetype)initWithAmount:(NSDecimalNumber * __nonnull)amount
                       transactionType:(WDTransactionType)transactionType
                              internalId:(NSString *__nonnull)internalId
                               externalId:(NSString *__nonnull)externalId NS_DESIGNATED_INITIALIZER;

@property (nullable, nonatomic, strong) NSString *internalId;
@property (nullable, nonatomic, strong) NSString *externalId;

@end
