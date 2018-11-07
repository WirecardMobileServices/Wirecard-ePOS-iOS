//
//  WDPayment.h
//   WDePOS
//
//  Created by Danko, Radoslav on 23/10/15.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "WDPayment.h"


/**
 *  @class WDPaymentDetail
 *  @brief Complete information about performed Payment
 **/
@interface WDPaymentDetail : WDPayment
/**
 */
@property (nonnull, nonatomic, retain) NSString *internalId;
/**
 */
@property (nonatomic) WDPaymentState status;
/**
 */
@property (nullable, nonatomic, retain) NSDate *processedByGateway;
/**
 */
@property (nullable, nonatomic, retain) NSDate *lastUpdated;
/**
 */
@property (nullable, nonatomic, retain) NSString *gatewayReference;
/**
 */
@property (nonnull, nonatomic, retain) NSDate *initialized;
/**
 */
@property (nullable, nonatomic, retain) NSString *gateway;
/**
 */
@property (nullable, nonatomic, strong) NSString *technicalMessage;
/**
 */
@property (nullable, nonatomic, strong) NSArray * refundPayments;
/**
 */
@property (nullable, nonatomic, strong) NSArray * reversalPayments;
/**
 */
@property (nullable, nonatomic, strong) NSArray * autoResolvePayments;

/// Default NSObject init is unavailable
- (nonnull instancetype)init __attribute__((unavailable("use initWithAmount:paymentMethod:transactionType:")));
+ (nonnull instancetype)new __attribute__((unavailable("use initWithAmount:paymentMethod:transactionType:")));
/**
 */
- (nullable instancetype)initWithAmount:(nonnull NSDecimalNumber *)amount
                          paymentMethod:(WDPaymentMethod)paymentMethod
                        transactionType:(WDTransactionType)transactionType NS_DESIGNATED_INITIALIZER;
/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
-(NSString *_Nullable)statusDescription;
/**
 */
-(NSString *_Nullable)paymentMethodDescription;
/**
 */
-(BOOL)paymentStatusPositive;
/**
 */
-(BOOL)refundable;
/**
 */
-(BOOL)reversible;

@end

