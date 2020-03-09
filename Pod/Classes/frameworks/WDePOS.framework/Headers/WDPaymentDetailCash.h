//
//  WDPaymentDetailCash.h
//  WDePOS
//
//  Created by Pulik, Jaroslav on 29/11/2018.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import "WDPaymentDetail.h"

/**
 *  @class WDPaymentDetailCash
 *  @brief Cash Payment Detail - contains the information specific to Cash payment
 **/
@interface WDPaymentDetailCash : WDPaymentDetail<WDPaymentDetailRefundable, WDPaymentDetailReversable>
/// Reversal to be used in Sale Reverse - to reverse this payment
-(WDPaymentReverseCash * _Nullable )reversal;
/// Refund to be used in Sale Refund - to refund this payment
-(WDPaymentRefundCash * _Nullable)refund;
@end
