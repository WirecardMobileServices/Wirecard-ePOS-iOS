//
//  WDPaymentCore+Extension.h
//  WDePOSResources
//
//  Created by Danko, Radoslav on 01/10/2019.
//  Copyright © 2019 Wirecard. All rights reserved.
//

#import <WDePOS/WDePOS.h>

NS_ASSUME_NONNULL_BEGIN


/**
 Supported Payment Types to be used when searching for Sales
 */
@interface WDPaymentCore (Extension)
+(WDPaymentCore *)cashPurchasePaymentType;
+(WDPaymentCore *)cardPurchasePaymentType;
+(WDPaymentCore *)cardAuthorizationPaymentType;
+(WDPaymentCore *)eftCardPurchasePaymentType;
+(WDPaymentCore *)alipayPurchasePaymentType;
+(WDPaymentCore *)wechatPurchasePaymentType;
@end

NS_ASSUME_NONNULL_END
