//
//  WDPaymentMethodMask.h
//  acceptSDK
//
//  Created by Pulik, Jaroslav on 27/08/2018.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#ifndef WDPaymentMethodMask_h
#define WDPaymentMethodMask_h

/**
 *  @brief WDPaymentMethodMask
 *  @discussion These constants are mask bits for specifying the payment method type
 **/
typedef NS_OPTIONS(NSUInteger, WDPaymentMethodMask)   {
    WDPaymentMethodMaskCashOnly = 1 << 20,
    WDPaymentMethodMaskCardOnly = 1 << 21,
    WDPaymentMethodMaskAlipayOnly = 1 << 22,
    WDPaymentMethodMaskWeChatOnly = 1 << 23,
    //    WDPaymentMethodMaskCouponOnly = 1 << 24,
    WDPaymentMethodMaskStandard = (WDPaymentMethodCash | WDPaymentMethodCard),
    WDPaymentMethodMaskQR = (WDPaymentMethodAlipay | WDPaymentMethodWeChat),
    WDPaymentMethodMaskAll = (WDPaymentMethodCash | WDPaymentMethodCard | WDPaymentMethodAlipay | WDPaymentMethodWeChat)
};

#endif /* WDPaymentMethodMask_h */
