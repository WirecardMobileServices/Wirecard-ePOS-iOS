//
//  WDSaleProcessing.h
//  WDePOS
//
//  Created by Timko, Marek on 25/10/2018.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDDataTypes.h"

/**
 @protocol WDSaleProcessing - The Sale Request core supported methods
 */
@protocol WDSaleProcessingCore <NSObject>
- (void)removeCardPayment;
- (void)removeCashPayment;
- (void)removeCouponPayment;
- (void)removeAlipayPayment;
- (void)removeWeChatPayment;

- (void)resetPayments;

/**
 * @brief Returns the Cash payment if present on this Sale request
 */
- (nullable WDPaymentRequestCash *)requestedCashPayment;
/**
 * @brief Returns the Card payment if present on this Sale request
 */
- (nullable WDPaymentRequestCard *)requestedCardPayment;
/**
 * @brief Returns the Coupon payment if present on this Sale request
 */
- (nullable WDPaymentRequestCoupon *)requestedCouponPayment;
/**
 * @brief Returns the Alipay payment if present on this Sale request
 */
- (nullable WDPaymentRequestAlipay *)requestedAlipayPayment;
/**
 * @brief Returns the WeChat payment if present on this Sale request
 */
- (nullable WDPaymentRequestWeChat *)requestedWeChatPayment;

- (unsigned long long)authorizedAmountCard;
- (nullable NSDecimalNumber *)total;
@end

/**
 @protocol WDSaleProcessing - The Sale Request supported methods
 */
@protocol WDSaleProcessing <WDSaleProcessingCore>
@required
///Add Cash Payment to the Sale to settle it by this payment
- (void)addCashPayment:(nonnull NSDecimalNumber *)amount;
///Add Card Payment to the Sale to settle it by this payment
- (void)addCardPayment:(nonnull NSDecimalNumber *)amount terminal:(nonnull WDTerminal *)terminal;
///Add Alipay Payment to the Sale to settle it by this payment
- (void)addAlipayPayment:(nonnull NSDecimalNumber *)amount consumerId:(nonnull NSString *)consumerId;
///Add WeChat Payment to the Sale to settle it by this payment
- (void)addWeChatPayment:(nonnull NSDecimalNumber *)amount consumerId:(nonnull NSString *)consumerId;
///Add Card Authorization to the Sale to settle it by this payment
-(void)addCardAuthorization:(NSDecimalNumber * __nonnull)amount terminal:(nonnull WDTerminal *)terminal;

@end

/**
 @protocol WDSaleProcessing - The Return Sale Request supported methods
 */
@protocol WDSaleReturnProcessing <WDSaleProcessingCore>
@required
///Add Card Payment to the Sale - to be used for Sale Refunds as we are referring to the original Payment by its Payment Id
- (void)addCardPayment:(nonnull NSDecimalNumber *)amount originalPaymentId:(nullable NSString *)originalPaymentId;
///Add Alipay Payment Refund to the Sale - to be used for Sale Refunds as we are referring to the original Payment by its Payment Id
- (void)addAlipayPayment:(nonnull NSDecimalNumber *)amount consumerId:(nonnull NSString *)consumerId originalPaymentId:(nullable NSString *)originalPaymentId;
///Add WeChat Payment Refund to the Sale - to be used for Sale Refunds as we are referring to the original Payment by its Payment Id
- (void)addWeChatPayment:(nonnull NSDecimalNumber *)amount consumerId:(nonnull NSString *)consumerId originalPaymentId:(nullable NSString *)originalPaymentId;
///Add Card Capture Refund to the Sale - to be used for Sale Refunds as we are referring to the original Payment by its Payment Id
-(void)addCardCapture:(NSDecimalNumber * __nonnull)amount originalPaymentId:(NSString * __nonnull)originalPaymentId;
@end

/**
 @protocol WDSaleProcessing - The Referenced Sale Request supported methods
 */
@protocol WDReferenceSaleProcessing <WDSaleProcessing>
@required
///Add Card Capture to the Sale - to be used for Sale with previous authorization - to Capture it - as we are referring to the original Payment by its Payment Id
-(void)addCardCapture:(NSDecimalNumber * __nonnull)amount originalPaymentId:(NSString * __nonnull)originalPaymentId;
@end
