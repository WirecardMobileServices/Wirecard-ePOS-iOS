//
//  WDReceiptItem.h
//   WDePOS
//
//  Created by Danko, Radoslav on 23/10/15.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class WDReceiptItem
 *  @brief Receipt Item data
 **/
@interface WDReceiptItem : NSObject
/// Default NSObject init is unavailable
- (instancetype)init __attribute__((unavailable("use initWithCurrency")));
/**
 */
@property (nonatomic) NSDecimalNumber  *itemQuantity;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *itemGrossPrice;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *itemTaxRate;
/**
 */
@property (nonatomic, strong) NSString  *itemDescription;
/**
 */
@property (nonatomic, strong, readonly) NSString *currency;
/**
 */
@property (nonatomic ) BOOL inclusiveTax;
/**
 * @discussion Calculated Item Netto price
 */
-(NSDecimalNumber  *)itemNettoPrice;
/**
 * @discussion Calculated Item Tax Amount
 */
-(NSDecimalNumber  *)itemTaxAmount;
/**
 * @discussion Calculated Netto price
 */
-(NSDecimalNumber *)totalNetto;
/**
 * @discussion Calculated Gross price
 */
-(NSDecimalNumber *)totalGross;
/**
 * @discussion Calculated Tax Amount
 */
-(NSDecimalNumber *)totalTaxAmount;
@end

