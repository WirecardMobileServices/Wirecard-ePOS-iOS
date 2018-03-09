//
//  WDPaymentDetailCoupon.h
//   WDePOS
//
//  Created by Danko, Radoslav on 04/05/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDPaymentDetail.h"
/**
 *  @class WDPaymentDetailCoupon
 *  @brief Coupon Payment Detail - contains the information specific to Coupon payment
 **/
@interface WDPaymentDetailCoupon : WDPaymentDetail
/**
 */
@property (nullable, nonatomic, retain) NSString *couponId;
@property (nullable, nonatomic, retain) NSString *brandId;
@end
