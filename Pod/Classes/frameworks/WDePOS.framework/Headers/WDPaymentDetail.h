//
//  WDPayment.h
//   WDePOS
//
//  Created by Danko, Radoslav on 23/10/15.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "WDPayment.h"

@protocol WDPaymentDetailRefundable
/**
 */
-(WDPaymentRefund * _Nullable)refund;

@end

@protocol WDPaymentDetailReversable
/**
 */
-(WDPaymentReverse* _Nullable )reversal;
@end

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
@property (nullable, nonatomic, strong) NSArray * refundTransactions;
/**
 */
@property (nullable, nonatomic, strong) NSArray * reversalTransactions;
/**
 * Elements of the array can be either WDPayment or WDPaymentReference
 */
@property (nullable, nonatomic, strong) NSArray <WDObject *> *referencedTransactions;
/**
 */
@property (nullable, nonatomic, strong) NSArray * autoResolveTransactions;

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

/**
 *  @class WDPaymentDetailCardReferenced
 *  @brief Referenced Payment Detail - contains the information specific to the payment
 **/
@interface WDPaymentDetailReferenced : WDPaymentDetail
@end
