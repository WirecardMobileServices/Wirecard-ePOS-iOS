//
//  WDPaymentDetailAlipay.h
//  WDePOS
//
//  Created by Timko, Marek on 10/07/2017.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import "WDPaymentDetail.h"

/**
 *  @class WDPaymentDetailAlipay
 *  @brief Alipay Payment Detail - contains the information specific to Alipay
 **/
@interface WDPaymentDetailAlipay : WDPaymentDetail <WDPaymentDetailRefundable, WDPaymentDetailReversable>

@property (nonnull, nonatomic, strong) NSString *partnerTransactionId;
@property (nonnull, nonatomic, strong) NSString *alipayPayTime;
@property (nonnull, nonatomic, strong) NSString *alipayTransactionId;
@property (nonnull, nonatomic, strong) NSString *alipayBuyerUserId;
@property (nonnull, nonatomic, strong) NSString *alipayBuyerLoginId;
@property (nonnull, nonatomic, strong) NSDecimalNumber *exchangeRate;
@property (nonnull, nonatomic, strong) NSDecimalNumber *transactionAmountCny;
@property (nonnull, nonatomic, strong) NSString *alipayBusinessName;
@property (nonnull, nonatomic, strong) NSString *terminalId;
@property (nonnull, nonatomic, strong) NSString *transactionBarcodeId;
-(id _Nullable )castTo:(Class _Nonnull )targetClass;

/// Reversal to be used in Sale Reverse - to reverse this payment
-(WDPaymentReverseAlipay * _Nullable )reversal;
/// Refund to be used in Sale Refund - to Refund this payment
-(WDPaymentRefundAlipay * _Nullable)refund;
@end
