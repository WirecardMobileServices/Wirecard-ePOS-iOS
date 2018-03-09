//
//  WDPaymentDetailAlipay.h
//  WDePOS
//
//  Created by Timko, Marek on 10/07/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDPaymentDetail.h"

/**
 *  @class WDPaymentDetailAlipay
 *  @brief Alipay Payment Detail - contains the information specific to Alipay
 **/
@interface WDPaymentDetailAlipay : WDPaymentDetail

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
@end
