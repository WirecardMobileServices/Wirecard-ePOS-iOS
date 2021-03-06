//
//  WDPayment.h
//   WDePOS
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDObject.h"

NS_ASSUME_NONNULL_BEGIN
/**
 *  @brief WDPaymentMethod
 *  @discussion Enumerator with the payment types.
 **/
typedef NS_ENUM(NSInteger, WDPaymentMethod ){
    WDPaymentMethodCash         = 1 << 0, //Default,
    WDPaymentMethodCard         = 1 << 1,
    WDPaymentMethodAlipay       = 1 << 2,
    WDPaymentMethodWeChat       = 1 << 3,
    WDPaymentMethodCoupon       = 1 << 4,
    WDPaymentMethodEFTCard       = 1 << 5,
    WDPaymentMethodUnknown      = 1 << 6
};

/**
 *  @brief WDTransactionType
 *  @discussion Enumerator with the transaction types.
 **/
typedef NS_ENUM(NSInteger, WDTransactionType) {
    WDTransactionTypePurchase               = 1 << 0, //Default
    WDTransactionTypeAuthorize              = 1 << 1,
    WDTransactionTypePreAuthorize           = 1 << 2,
    WDTransactionTypePreAuthorizeSupplement = 1 << 3,
    WDTransactionTypeCapture                = 1 << 4,
    WDTransactionTypeRefund                 = 1 << 5,
    WDTransactionTypeReferenceRefund        = 1 << 6,
    WDTransactionTypeReversal               = 1 << 7,
    WDTransactionTypeAutoResolve            = 1 << 8,
    WDTransactionTypeUnknown                = 1 << 9
};

/**
 *  @brief WDPaymentState
 *  @discussion Payment Status enumeration
 **/
typedef NS_ENUM(NSUInteger, WDPaymentState) {
    WDPaymentStateUnknown           = 1 << 0,
    WDPaymentStateReversed          = 1 << 1,
    WDPaymentStateCompleted         = 1 << 2,
    WDPaymentStateRejected          = 1 << 3,
    WDPaymentStateFailed            = 1 << 4,
    WDPaymentStateFailedIntervene   = 1 << 5,
    WDPaymentStateIncomplete        = 1 << 6,
    WDPaymentStateRefunded          = 1 << 7,
    WDPaymentStateInitialized       = 1 << 8,
    WDPaymentStateApproved          = 1 << 9,
    WDPaymentStateUserPaying        = 1 << 10,
    WDPaymentStateCaptured          = 1 << 11
};

/**
 *  @class WDPaymentreference - Payment Reference
 *  @brief Payment  - contains the id of the referenced payments
 **/
@interface WDPaymentReference : WDObject<NSCoding>
@property (nonatomic, readonly) NSString * type;
@property (nonatomic, readonly) NSString * internalId;
@end

/**
 *  @class WDPayment - the base class for various types of Requests [Purchase, Refund, Reversal]
 *  @brief Payment  - contains the information about payment method, transaction type
 **/
@interface WDPaymentCore : WDObject<NSCoding>
/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("manual initialization not allowed")));
+ (nonnull instancetype)new __attribute__((unavailable("manual initialization not allowed")));
/**
 */
@property (nonatomic, readonly) WDPaymentMethod paymentMethod;
/**
 */
@property (nonatomic, readonly) WDTransactionType transactionType;
@end

/**
 *  @class WDPaymentRequest - Payment Request to be included in the Sale
 *  @brief Payment Request - contains the information about payment method, transaction type and amount
 **/
@interface WDPayment : WDPaymentCore
/**
 */
@property (nonnull, nonatomic, readonly) NSDecimalNumber *amount;
@property (nullable, nonatomic, readonly) NSString *notifyUrl;

@end

/**
 *  @class WDPaymentRefund - Payment Refund to be used in the Sale Refund
 *  @brief Payment Refund - contains the information about the original Payment to be refunded
 **/
@interface WDPaymentRefund : WDPayment
/**
 */
@property (nonatomic, readonly, nullable) NSString *originalPaymentId;
@end

/**
 *  @class WDPaymentRefundCard - Card Payment Refund
 **/
@interface WDPaymentRefundCard : WDPaymentRefund
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                      originalPaymentId:(nonnull NSString *)originalPaymentId;
- (nullable instancetype)initEFTWithAmount:(nonnull NSDecimalNumber *)amount
                      originalPaymentId:(nonnull NSString *)originalPaymentId;
@end
/**
 *  @class WDPaymentReverseCash - Cash Payment Refund
 **/
@interface  WDPaymentRefundCash : WDPaymentRefund
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                      originalPaymentId:(nonnull NSString *)originalPaymentId;
@end
/**
 *  @class WDPaymentReverseWeChat - WeChat Payment Refund
 **/
@interface  WDPaymentRefundWeChat : WDPaymentRefund
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                      originalPaymentId:(nonnull NSString *)originalPaymentId;
@end
/**
 *  @class WDPaymentReverseAlipay - Alipay Payment Refund
 **/
@interface  WDPaymentRefundAlipay : WDPaymentRefund
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                      originalPaymentId:(nonnull NSString *)originalPaymentId;
@end
/**
 *  @class WDPaymentReverseAlipay - Alipay Payment Refund
 **/
@interface  WDPaymentRefundCardCapture : WDPaymentRefund
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                      originalPaymentId:(nonnull NSString *)originalPaymentId;
@end

/**
 *  @class WDPaymentReverse - Payment Reversal to be used in the Sale Reversal
 *  @brief Payment Request - contains the information about the original Payment to be reversed
 **/
@interface WDPaymentReverse : WDPaymentCore
/**
 */
@property (nonnull, nonatomic, readonly) NSString *originalPaymentId;

@end

/**
 *  @class WDPaymentReverseCard - Card Payment Reversal
 **/
@interface WDPaymentReverseCard : WDPaymentReverse @end
/**
 *  @class WDPaymentReverseCash - Cash Payment Reversal
 **/
@interface  WDPaymentReverseCash : WDPaymentReverse @end
/**
 *  @class WDPaymentReverseWeChat - WeChat Payment Reversal
 **/
@interface  WDPaymentReverseWeChat : WDPaymentReverse @end
/**
 *  @class WDPaymentReverseAlipay - Alipay Payment Reversal
 **/
@interface  WDPaymentReverseAlipay : WDPaymentReverse @end
/**
 *  @class WDPaymentReverseCardCapture - Card Capture Reversal
 **/
@interface WDPaymentReverseCardCapture : WDPaymentReverse @end

/**
 *  @class WDPaymentCapture - Payment Capture to be used in the Referenced Sale with previous  Authorization
 *  @brief Payment Capture - contains the information about the original Payment Authorization to be captured
 **/
@interface WDPaymentCapture : WDPayment
/**
 */
@property (nullable, nonatomic, readonly) NSString *originalPaymentId;
@end

/**
 *  @class WDPaymentCaptureCard -  Card Capture to be used in the Referenced Sale with previous Card Authorization
 *  @brief Card Capture - contains the information about the original Payment Authorization to be captured
 **/
@interface WDPaymentCaptureCard : WDPaymentCapture @end


/**
*  @class WDPaymentPreAuthorizeSupplement -  Pre-Authorize Supplement to be used in the Referenced Sale with previous  Pre-Authorization
 *  @brief Payment Capture - contains the information about the original Payment Authorization to be captured
**/
@interface WDPaymentPreAuthorizeSupplement : WDPayment
/**
 */
@property (nullable, nonatomic, retain) NSString *originalTransactionId;
@property (nullable, nonatomic, retain) NSString *authorizationCode;
@end

/**
 *  @class WDPaymentPreAuthorizeSupplementCard -  Card Pre-Authorize Supplement to be used in the Referenced Sale with previous Card Pre-Authorization
 *  @brief Card Capture - contains the information about the original Payment Pre-Authorization
 **/
@interface WDPaymentPreAuthorizeSupplementCard : WDPaymentPreAuthorizeSupplement
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                  originalTransactionId:(nonnull NSString *)originalTransactionId
                      authorizationCode:(nonnull NSString *)authorizationCode;
@end

NS_ASSUME_NONNULL_END
