//
//  WDZReport.h
//  WDePOS
//
//  Created by Danko, Radoslav on 09/07/2018.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"
#import "NSArray+Extension.h"

/**
 *  @class WDHtmlZReportDetailRow
 *  @brief Receipt Detail data as label-value
 *  @discussion Details of each payment method
 **/
@interface WDHtmlZReportDetailRow : NSObject
@property (nullable, nonatomic, strong, readonly) NSString *label;
@property (nullable, nonatomic, strong, readonly) NSString *value;
@property (nullable, nonatomic, strong, readonly) NSString *center;
@end

/**
 *  @class WDZReportCategoryItemRow
 *  @brief ZReport Category Item
 **/
@interface WDHtmlZReportCategoryItemRow : NSObject
/**
 */
@property (nonatomic,strong,nonnull,readonly) NSString *title;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSString *netAmount;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSString *taxAmount;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSString *grossAmount;
/// Designates if the current item is the last item in array category items
@property (nonatomic,readonly) BOOL last;
@end

/**
 *  @class WDZReportCategoryRow
 *  @brief ZReport Category
 **/
@interface WDHtmlZReportCategoryRow : NSObject
/**
 */
@property (nonatomic,strong,nonnull,readonly) NSString *title;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSString *netAmountLabel;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSString *taxAmountLabel;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSString *grossAmountLabel;
/**
 */
@property (nonatomic,strong,nullable,readonly) NSArray<WDHtmlZReportCategoryItemRow*>* items;
@end


/**
 *  @class WDHtmlReceiptImages
 *  @brief Receipt Images - header/footer logos, barcode
 *  @discussion Images to be printed on the receipt
 **/
@interface WDHtmlZReportImages: NSObject
@property (nullable, nonatomic, strong) NSString *headerLogo;
@property (nullable, nonatomic, strong) NSString *headerLogoSmall;
@property (nullable, nonatomic, strong) NSString *footerLogo;
@end

/**
 *  @class WDZReportNew
 *  @brief ZReport
 **/
@interface WDHtmlZReport:NSObject
- (nonnull instancetype)init __attribute__((unavailable("use initWithShift:cashRegister:")));
+ (nonnull instancetype)new __attribute__((unavailable("use initWithShift:cashRegister:")));
- (nonnull instancetype)initWithShift:(nonnull WDCashShift*)shift cashRegister:(nonnull WDCashRegister*)cashRegister locale:(nonnull NSLocale*)locale;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *reportId;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *reportIdLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *currentTime;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *currentDate;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *openedByLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *closedByLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *openedBy;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *closedBy;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *openDate;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *closeDate;
/**
 */
@property (nullable, nonatomic, strong,readonly) NSString *merchantName;
/**
 */
@property (nullable, nonatomic, strong,readonly) WDReceiptAddress *address;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *taxNumber;
/**
 */
@property (nullable, nonatomic, strong,readonly) NSString *externalShopId;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *shopName;
/**
 */
@property (nullable, nonatomic, strong,readonly) WDReceiptAddress *shopAddress;
/**
 */
@property (nullable, nonatomic, strong,readonly) NSString *merchantShopLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *cashRegisterLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *cashRegisterName;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *cashRegisterNameLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *cashRegisterId;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *cashRegisterIdLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *noDataLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *closingLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *shiftDataLabel;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSString *dateLabel;
/**
 */
@property (nullable, nonatomic, strong, readonly) NSArray<WDHtmlZReportDetailRow*> *details;
/**
 */
@property (nullable,nonatomic,strong,readonly) NSArray<WDHtmlZReportCategoryRow*>* categories;
/**
 */
@property (nullable, nonatomic, strong, readonly) WDHtmlZReportImages *images;
/**
 */
@property (nullable, nonatomic, strong, readonly) NSString *html;
@end

