//
//  WDPaymentRequestAlipay.h
//  WDePOS
//
//  Created by Timko, Marek on 07/07/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "WDPayment.h"

/**
 *  @class WDPaymentRequestAlipay
 *  @brief Alipay Payment Request - contains the information specific to Alipay
 **/
@interface WDPaymentRequestAlipay : WDPayment
/**
 */
@property (nonnull, nonatomic, strong) NSString * consumerId;

@end
