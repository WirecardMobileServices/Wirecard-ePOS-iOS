//
//  WDPayment.h
//   WDePOS
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDObject.h"
NS_ASSUME_NONNULL_BEGIN
/**
 *  @brief WDPaymentMethod
 *  @discussion Enumerator with the payment types.
 **/
typedef NS_ENUM(NSInteger, WDPaymentMethod ){
    WDPaymentMethodCash, //Default
    WDPaymentMethodCard,
    WDPaymentMethodAlipay,
    WDPaymentMethodWeChat,
    WDPaymentMethodCoupon,
    WDPaymentMethodUnknown
    
};

/**
 *  @brief WDTransactionType
 *  @discussion Enumerator with the transaction types.
 **/
//typedef NS_ENUM(NSInteger, WDTransactionType) {
//    WDTransactionTypeUnknown = 0,
//    WDTransactionTypeCardPurchase,
//    WDTransactionTypeCardRefund,
//    WDTransactionTypeCardAuthorize,
//    WDTransactionTypeCardCapture,
//    WDTransactionTypeCardReversal,
//    WDTransactionTypeCardAutoResolve,
//    WDTransactionTypeCashPurchase,
//    WDTransactionTypeCashRefund,
//    WDTransactionTypeCashReversal,
//    WDTransactionTypeCouponPurchase,
//    WDTransactionTypeCouponReversal,
//    WDTransactionTypeAlipayPurchase,
//    WDTransactionTypeAlipayReversal,
//    WDTransactionTypeAlipayRefund
//};
typedef NS_ENUM(NSInteger, WDTransactionType) {
    WDTransactionTypePurchase, //Default
    WDTransactionTypeAuthorize,
    WDTransactionTypeCapture,
    WDTransactionTypeRefund,
    WDTransactionTypeReferenceRefund,
    WDTransactionTypeReversal,
    WDTransactionTypeAutoResolve,
    WDTransactionTypeUnknown
};

/**
 *  @brief WDPaymentState
 *  @discussion Payment Status enumeration
 **/
typedef NS_ENUM(NSUInteger, WDPaymentState) {
    WDPaymentStateUnknown=0,
    WDPaymentStateNotNeeded,
    WDPaymentStateSkipped,
    WDPaymentStateApproved,
    WDPaymentStateCompleted,
    WDPaymentStateCaptured,
    WDPaymentStateReversed,
    WDPaymentStateRefunded,
    WDPaymentStatePartiallyRefunded,
    WDPaymentStateInitialized,
    WDPaymentStateIncomplete,
    WDPaymentStateDeclined,
    WDPaymentStateRejected,
    WDPaymentStateFailed,
    WDPaymentStateFailedMin,
    WDPaymentStateUnconfirmed
};

/**
 *  @class WDPayment
 *  @brief Payment Request - contains the information about payment method, transaction type and amount
 **/
@interface WDPayment : WDObject<NSCoding>
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use initWithAmount:paymentMethod:transactionType:")));
+ (nonnull instancetype)new __attribute__((unavailable("use initWithAmount:paymentMethod:transactionType:")));

/**
 */
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                          paymentMethod:(WDPaymentMethod)paymentMethod
                        transactionType:(WDTransactionType)transactionType NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nonatomic, readonly) WDPaymentMethod paymentMethod;
/**
 */
@property (nonatomic, readonly) WDTransactionType transactionType;
/**
 */
@property (nonnull, nonatomic, strong) NSDecimalNumber *amount;

@end
NS_ASSUME_NONNULL_END
