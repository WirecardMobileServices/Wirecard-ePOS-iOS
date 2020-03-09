//
//  WDPaymentRequestCard.h
//   WDePOS
//
//  Created by Danko, Radoslav on 03/05/16.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import "WDPayment.h"

@class WDTerminal;

/**
 *  @class WDPaymentRequestCard
 *  @brief Card Payment Request - contains the information specific to Card payment
 **/
@interface WDPaymentRequestCard : WDPayment
/**
 */
@property (nonnull, nonatomic, strong) WDTerminal * terminal;

- (nullable instancetype)initEFTCardWithAmount:(nonnull NSDecimalNumber *)amount
                      terminal:(nonnull WDTerminal *)terminal;

- (nullable instancetype)initEFTCardWithAmount:(nonnull NSDecimalNumber *)amount
                                      terminal:(nonnull WDTerminal *)terminal
                                     notifyUrl:(nonnull NSString *)notifyUrl;

@end
