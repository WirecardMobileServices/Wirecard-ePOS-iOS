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

@property (nullable, nonatomic, readonly) NSString *internalId;
@property (nullable, nonatomic, readonly) NSString *externalId;

@end
