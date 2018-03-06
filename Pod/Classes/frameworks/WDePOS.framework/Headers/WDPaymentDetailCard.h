//
//  WDPaymentDetailCard.h
//   WDePOS
//
//  Created by Danko, Radoslav on 04/05/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import "WDPaymentDetail.h"
/**
 *  @class WDPaymentDetailCard
 *  @brief Card Payment Detail - contains the information specific to Card payment
 **/
@interface WDPaymentDetailCard : WDPaymentDetail
/**
 */
@property (nullable, nonatomic, retain) NSString *cardHolderName;
/**
 */
@property (nullable, nonatomic, retain) NSString *maskedCardNumber;
/**
 */
@property (nullable, nonatomic, retain) NSString *authorizationCode;
/**
 */
@property (nullable, nonatomic, retain) NSString *aid;
/**
 */
@property (nullable, nonatomic, retain) NSString *applicationLabel;
/**
 */
@property (nullable, nonatomic, retain) NSString *cardBrand;
/**
 */
@property (nullable, nonatomic, retain) NSString *posEntryMode;
/**
 */
@property (nullable, nonatomic, retain) NSString *tid;
/**
 */
@property (nullable, nonatomic, retain) NSString *mid;
/**
 */
@property (nullable, nonatomic, strong) NSString *signatureImage;
/**
 */
@property (nullable, nonatomic, strong) NSString *emvData;
/**
 */
@property (nullable, nonatomic, strong) NSString *emvUpdateData;
/**
 */
@property (nullable, nonatomic, retain) NSNumber *customerPhonePresent;
/**
 */
@property (nullable, nonatomic, retain) NSNumber *customerEmailPresent;
/**
 */
@property (nullable, nonatomic, retain) NSString *terminalSerialNo;
/**
 */
@property (nullable, nonatomic, retain) NSString *terminalVendor;
/**
 */
@property (nullable, nonatomic, retain) NSString *terminalModel;
/**
 */
@property (nullable, nonatomic, retain) NSString *issuerScript;
@end
