//
//  WdAcceptReceipt.h
//  Pods
//
//  Created by Danko, Radoslav on 8/7/14.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class WDReceiptPaymentItem;
@class WDReceiptTaxSummary;

/**
 *  @class WDReceiptAlipayDetails
 *  @brief Receipt content for Alipay payment - to be used by Datecs printer
 **/
@interface WDReceiptAlipayDetails : NSObject
/**
 */
@property (nullable,nonatomic,strong) UIImage *alipayLogo;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber * transactionAmountCny;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber * exchangeRate;
/**
 */
@property (nullable,nonatomic) NSString * alipayTransactionId;
/**
 */
@property (nullable,nonatomic) NSString * alipayBusinessName;
/**
 */
@property (nullable,nonatomic) NSString * alipayBuyerLoginId;
/**
 */
@property (nullable,nonatomic) NSString * alipayBuyerUserId;
/**
 */
@property (nullable,nonatomic) NSString * terminalId;
/**
 */
@property (nullable,nonatomic) NSString * partnerTransactionId;
/**
 */
@property (nullable,nonatomic) NSString * alipayPayTime;
/**
 */
@end

/**
 *  @class WDReceiptWeChatDetails
 *  @brief Receipt content for WeChat payment - to be used by Datecs printer
 **/
@interface WDReceiptWeChatDetails : NSObject
/**
 */
@property (nonnull, nonatomic, strong) NSString *partnerTransactionId;
/**
 */
@property (nonnull, nonatomic, strong) NSString *wechatProviderTransactionId;
/**
 */
@property (nonnull, nonatomic, strong) NSString *wechatTimeEnd;
/**
 */
@property (nonnull, nonatomic, strong) NSDecimalNumber *wechatRate;
/**
 */
@property (nullable,nonatomic) NSDecimalNumber * transactionAmountCny;
/**
 */
@property (nonnull, nonatomic, strong) NSString *wechatDeviceInfo;
/**
 */
@property (nonnull, nonatomic, strong) NSString *wechatCashFee;
/**
 */
@property (nonnull, nonatomic, strong) NSString *wechatSubMchId;
/**
 */
@end

/**
 *  @class WDReceiptMerchant
 *  @brief Receipt Merchant Information
 **/
@interface WDReceiptMerchant : NSObject
/**
 */
@property (nullable,nonatomic,strong) NSString *shopID;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantName;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressLine1;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressZipCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantAddressCityAndCountry;

@end

/**
 *  @class WDReceipt
 *  @brief Receipt content for Payment  - to be used by Datecs printer
 **/
@interface WDReceipt : WDReceiptMerchant
/**
 */
@property (nullable,nonatomic,strong) NSString *header;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantID;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantTaxNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantPhone;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptDateHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentDateHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptDate;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptTimeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedReceiptNumberHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptID;
/**
 */
@property (nullable,nonatomic,strong) NSString *aidHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *aid;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCardTypeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *cardType;
/**
 */
@property (nullable,nonatomic,strong) NSString *transactionTypeString;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTransactionTypeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCardNumberHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *cardNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCardHolderHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *cardHolder;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedExpiryDateHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *expiryDate;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTerminalIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *terminalID;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedApprovalCodeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *approvalCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedAmountHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedAOSAHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *amount;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTransactionStatusHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *transactionStatus;
/**
 */
@property (nullable,nonatomic,strong) NSArray *paymentItems;
/**
 */
@property (nullable,nonatomic,strong) NSArray<WDReceiptPaymentItem *> *paymentItemsData;
/**
 */
@property (nullable,nonatomic,strong) NSArray<WDReceiptTaxSummary *> *taxSummaryItems;
/**
 */
@property (nullable,nonatomic,strong) NSString *taxSummary;
/**
 */
@property (nullable,nonatomic,strong) NSString *tipSummary;
/**
 */
@property (nullable,nonatomic,strong) NSString *serviceChargeSummary;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentDetailsHeader;
/**
 * Create WDApplicationName custom string value in the Info.plist of your application to appear as "Issued by YOUR_APP_NAME"
 */
@property (nullable,nonatomic,strong) NSString *footer;
/**
 */
@property (nullable,nonatomic,strong) NSString *footerThankYou;
/**
 */
@property (nullable,nonatomic,strong) NSString *footerCopyright;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptStringToQRCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *receiptStringToBarCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *availableOfflineSpendingAmount;
/**
 */
@property (nonatomic) BOOL verifiedOnDeviceCVM;
/**
 */
@property (nullable,nonatomic,strong) NSString *appCrypt;
/**
 */
@property (nullable,nonatomic,strong) NSString *cryptID;
/**
 */
@property (nullable,nonatomic,strong) NSString *appTransCounter;
/**
 */
@property (nullable,nonatomic,strong) NSString *declinedReason;
/**
 */
@property (nonatomic) BOOL PINVerified;
/**
 */
@property (nullable,nonatomic,strong) NSString *saleTypeAsText;
/**
 */
@property (nonatomic) BOOL isContactless;
/**
 */
@property (nullable,nonatomic,strong) NSString *posEntryModeInterpreted;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashierID;
/**
 */
@property (nullable,nonatomic,strong) NSString *subtotal;
/**
 */
@property (nullable,nonatomic,strong) NSString *tip;
/**
 */
@property (nullable,nonatomic,strong) NSString *serviceCharge;
/**
 */
@property (nullable,nonatomic,strong) NSString *serviceChargeWithTax;
/**
 */
@property (nullable,nonatomic,strong) NSString *discount;
/**
 */
@property (nullable,nonatomic,strong) NSString *voucher;
/**
 */
@property (nullable,nonatomic,strong) NSString *customerCard;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashierIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedShopIDHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedSubtotalHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTipHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedServiceChargeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedServiceChargeWithTaxHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedDiscountHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedVoucherHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCustomerCardHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentTypeHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTaxHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedNetHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedGrossHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedTaxAmountHeader;
/**
 */
@property (nullable,nonatomic,strong) NSString *paymentType;
/**
 */
@property (nullable,nonatomic,strong) UIImage *headerLogo;
/**
 */
@property (nullable,nonatomic, strong) WDReceiptAlipayDetails *alipayDetails;
/**
 */
@property (nullable,nonatomic, strong) WDReceiptWeChatDetails *wechatDetails;
@end


/**
 *********************************************
 */

/**
 *  @class WDZReportCategoryItem
 *  @brief ZReport Category Item
 **/
@interface WDZReportCategoryItem : NSObject
/**
 */
@property (nonatomic,strong,nonnull) NSString *categoryItemName;
/**
 */
@property (nonatomic,strong,nonnull) NSString *parentCategoryName;
/**
 */
@property (nonatomic,strong,nullable) NSString *netAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *taxAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *grossAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *localisedNetAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *localisedTaxAmount;
/**
 */
@property (nonatomic,strong,nullable) NSString *localisedGrossAmount;
@end

/**
 *********************************************
 */

/**
 *  @class WDZReportCategory
 *  @brief ZReport Category
 **/
@interface WDZReportCategory : NSObject
/**
 */
@property (nonatomic,strong,nonnull) NSString *categoryName;
/**
 */
@property (nonatomic,strong,nullable) NSArray<WDZReportCategoryItem*>* categoryItems;
@end

/**
*********************************************
*/

/**
 *  @class WDZReport
 *  @brief ZReport
 **/
@interface WDZReport : WDReceiptMerchant
/**
 */
@property (nullable,nonatomic,strong) UIImage *imageReportLogo;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopName;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressLine1;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressZipCode;
/**
 */
@property (nullable,nonatomic,strong) NSString *shopAddressCityAndCountry;
/**
 */
@property (nullable,nonatomic,strong) NSString *merchantTaxNumber;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashRegisterName;
/**
 */
@property (nullable,nonatomic,strong) NSString *zReportId;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashRegisterExternalId;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedZReportId;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashRegister;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedRegisterName;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedRegisterExternalId;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedShiftData;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOpenTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *openTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *currentReportTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *currentReportDate;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOpenedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *openedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *closeTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *closedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *openingAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashPurchases;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashRefunds;
/**
 */
@property (nullable,nonatomic,strong) NSString *cashOperationsBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *closingCashBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *closingActualAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *overShort;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCloseTime;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosedBy;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOpeningAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashPurchases;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashRefunds;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashOperationsBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedCashOperationsBalanceLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosingCashBalance;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosingCashBalanceLine2;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedClosingActualAmount;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedOverShort;
/**
 */
@property (nullable,nonatomic,strong) NSArray<WDZReportCategory*>* categories;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedPaymentMethods;
/**
 */
@property (nullable,nonatomic,strong) NSString *localisedEnds;

@end

/**
 *  @class WDReceiptTaxSummary
 *  @brief Data of receipt tax summary item
 **/
@interface WDReceiptTaxSummary : NSObject
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull netto;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull gross;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull taxAmount;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull taxRate;
/**
 */
@property (nonatomic, strong) NSString * _Nullable currency;

- (instancetype _Nonnull)initWithNetto:(NSDecimalNumber * _Nonnull)netto
                                 gross:(NSDecimalNumber * _Nonnull)gross
                             taxAmount:(NSDecimalNumber * _Nonnull)taxAmount
                               taxRate:(NSString * _Nonnull)taxRate
                              currency:(NSString * _Nullable)currency;
@end

/**
 *  @class WDReceiptPaymentItem
 *  @brief Data of receipt payment list item
 */
@interface WDReceiptPaymentItem : NSObject
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitPrice;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull totalPrice;
/**
 */
@property (nonatomic, strong) NSDecimalNumber * _Nonnull discountAmount;
/**
 */
@property (nonatomic) NSInteger quantity;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull itemDescription;
/**
 */
@property (nonatomic, strong) NSString * _Nonnull taxRate;
/**
 */
@property (nonatomic, strong) NSString * _Nullable currency;
/**
 */
@property (nonatomic, strong) NSString * _Nullable discountRate;

- (instancetype _Nonnull)initWithUnitPrice:(NSDecimalNumber * _Nonnull)unitPrice
                                totalPrice:(NSDecimalNumber * _Nonnull)totalPrice
                             discountAmount:(NSDecimalNumber * _Nullable)discountAmount
                                  quantity:(NSInteger)quantity
                               description:(NSString * _Nonnull)description
                                   taxRate:(NSString * _Nonnull)taxRate
                              discountRate:(NSString * _Nullable)discountRate
                                  currency:(NSString * _Nullable)currency;

@end
