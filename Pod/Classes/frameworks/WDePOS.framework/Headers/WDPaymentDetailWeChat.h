//
//  WDPaymentDetailWeChat.h
//  WDePOS
//
//  Created by Danko, Radoslav on 15/11/2017.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import "WDPaymentDetail.h"

/**
 *  @class WDPaymentDetailWeChat
 *  @brief WeChat Payment Detail - contains the information specific to WeChat
 **/
@interface WDPaymentDetailWeChat : WDPaymentDetail<WDPaymentDetailRefundable, WDPaymentDetailReversable>

@property (nonnull, nonatomic, strong) NSString *partnerTransactionId;
@property (nonnull, nonatomic, strong) NSString *timeStamp;
@property (nonnull, nonatomic, strong) NSString *wechatProviderTransactionId;
@property (nonnull, nonatomic, strong) NSString *wechatTimeEnd;
@property (nonnull, nonatomic, strong) NSDecimalNumber *wechatRate;
@property (nonnull, nonatomic, strong) NSString *wechatDeviceInfo;
@property (nonnull, nonatomic, strong) NSDecimalNumber *transactionAmountCny;
@property (nonnull, nonatomic, strong) NSString *wechatSubMchId;
-(id _Nullable )castTo:(Class _Nonnull )targetClass;

/// Reversal to be used in Sale Reverse - to reverse this payment
-(WDPaymentReverseWeChat * _Nullable )reversal;
/// Refund to be used in Sale Refund - to refund this payment
-(WDPaymentRefundWeChat * _Nullable)refund;
@end
