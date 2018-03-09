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
@interface WDPaymentDetail : WDObject<NSCoding>
/**
 */
@property (nonatomic, readonly) WDPaymentMethod paymentMethod;
/**
 */
@property (nonatomic) WDTransactionType transactionType;
/**
 */
@property (nonnull, nonatomic, retain) NSString *internalId;
/**
 */
@property (nonatomic) WDPaymentState status;
/**
 */
@property (nonnull, nonatomic, retain) NSDecimalNumber *amount;
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
/**
 */
-(nonnull instancetype)init __attribute__((unavailable("use initWithPaymentMethod:paymentMethod:")));
/**
 */
+(nonnull instancetype)new __attribute__((unavailable("use initWithPaymentMethod:paymentMethod:")));
/**
 */
- (nonnull instancetype)initWithPaymentMethod:(WDPaymentMethod)paymentMethod;
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

