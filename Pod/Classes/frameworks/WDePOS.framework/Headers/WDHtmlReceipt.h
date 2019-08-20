//
//  WDHtmlReceipt.h
//  WDePOS
//
//  Created by Timko, Marek on 18/06/2018.
//

#import <Foundation/Foundation.h>
#import "WDSale.h"
#import "NSArray+Extension.h"

@class WDReceiptItem, WDSaleSummaryItem;
@class WDHtmlReceipt, WDHtmlReceiptContent, WDHtmlReceiptData, WDHtmlReceiptImages, WDHtmlReceiptConfig;

/**
 *  @class WDHtmlReceipt
 *  @brief Receipt with Data, Images and also complete html based on the standard Wirecard Receipt template
 *  @discussion Complete Receipt Data - to be used to construct a receipt or use html to render it b
 **/
@interface WDHtmlReceipt : NSObject

@property (nullable, nonatomic, strong, readonly) WDHtmlReceiptData *receipt;
@property (nullable, nonatomic, strong, readonly) WDHtmlReceiptImages *images;
@property (nullable, nonatomic, strong, readonly) NSString *html;

- (nonnull instancetype)init __attribute__((unavailable("use initFromSaleResponse:isForCardholder:includeReturns:")));
+ (nonnull instancetype)new __attribute__((unavailable("use initFromSaleResponse:isForCardholder:includeReturns:")));
- (nullable instancetype)initFromSaleResponse:(nonnull WDSaleResponse *)saleResponse isForCardholder:(BOOL)isForCardholder includeReturns:(BOOL)showReturns locale:(nonnull NSLocale *)locale;

@end

/**
 *  @class WDHtmlReceiptImages
 *  @brief Receipt Images - header/footer logos, barcode
 *  @discussion Images to be printed on the receipt
 **/
@interface WDHtmlReceiptImages: NSObject
@property (nullable, nonatomic, strong) NSString *headerLogo;
@property (nullable, nonatomic, strong) NSString *barcode;
@property (nullable, nonatomic, strong) NSString *footerLogo;
@end

/**
 *  @class WDHtmlReceiptDetailRow
 *  @brief Receipt Detail data as label-value
 *  @discussion Details of each payment method
 **/
@interface WDHtmlReceiptDetailRow : NSObject
@property (nullable, nonatomic, strong, readonly) NSString *label;
@property (nullable, nonatomic, strong, readonly) NSString *value;
@property (nullable, nonatomic, strong, readonly) NSString *center;
@property (nonatomic, assign, readonly) BOOL bold;
@end
/**
 *  @class WDHtmlReceiptItemRow
 *  @brief Receipt Item
 *  @discussion Receipt Item containting description, total, unit price, discount
 **/
@interface WDHtmlReceiptItemRow : NSObject
@property (nullable, nonatomic, strong, readonly) NSString *itemDescription;
@property (nullable, nonatomic, strong, readonly) NSString *itemTotal;
@property (nullable, nonatomic, strong, readonly) NSString *quantity;
@property (nullable, nonatomic, strong, readonly) NSString *unitPrice;
@property (nullable, nonatomic, strong, readonly) NSString *unitTax;
@property (nullable, nonatomic, strong, readonly) NSString *discount;
@property (nullable, nonatomic, strong, readonly) NSString *discountPercentage;
@end
/**
 *  @class WDHtmlReceiptTaxRow
 *  @brief Receipt Taxes
 *  @discussion Receipt Tax item containting value, net amount and tax amount
 **/
@interface WDHtmlReceiptTaxRow : NSObject
@property (nullable, nonatomic, strong, readonly) NSString *value;
@property (nullable, nonatomic, strong, readonly) NSString *nettoAmount;
@property (nullable, nonatomic, strong, readonly) NSString *taxAmount;
@end

/**
 *  @class WDHtmlReceiptPaymentRow
 *  @brief Receipt Payment Method
 *  @discussion Receipt Payment Method - contains payment method details and logo, image (can be barcode or QRcode for the payment) and barcodeData - string representing data encoded in image (data in the barcode or QRCode)
 **/
@interface WDHtmlReceiptPaymentRow: NSObject
@property (nullable, nonatomic, strong, readonly) NSString *logo;
@property (nullable, nonatomic, strong, readonly) NSString *title;
@property (nullable, nonatomic, strong, readonly) NSArray<WDHtmlReceiptDetailRow*> *details;
@property (nullable, nonatomic, strong, readonly) NSString *image;
@property (nullable, nonatomic, strong, readonly) NSString *barcodeData;
@end

/**
 *  @class WDHtmlReceiptData
 *  @brief Receipt Data
 *  @discussion Receipt Data containing all the details e.g. Address, Cashier detail, payment details, taxes etc.
 **/
@interface WDHtmlReceiptData : NSObject
// header labels
@property (nullable, nonatomic, strong, readonly) NSString *headerLabel;
@property (nullable, nonatomic, strong, readonly) NSString *receiptNumberLabel;
// header values
/// "Disclaimer for Customer\nMerchant / Customer Copy"
@property (nullable, nonatomic, strong, readonly) NSString *receiptType;
@property (nullable, nonatomic, strong, readonly) NSString *saleStatus;
@property (nullable, nonatomic, strong, readonly) NSString *receiptNumber;
@property (nullable, nonatomic, strong, readonly) NSString *processedDate;
@property (nullable, nonatomic, strong, readonly) NSString *merchantName;
@property (nullable, nonatomic, strong, readonly) WDReceiptAddress *address;
@property (nullable, nonatomic, strong, readonly) NSString *taxNumber;
@property (nullable, nonatomic, strong, readonly) NSString *cashierIdLabel;
@property (nullable, nonatomic, strong, readonly) NSString *cashierId;
@property (nullable, nonatomic, strong, readonly) NSString *shopLabel;
@property (nullable, nonatomic, strong, readonly) NSString *shop;
@property (nullable, nonatomic, strong, readonly) NSString *processedDateLabel;
// items
@property (nullable, nonatomic, strong, readonly) NSArray<WDHtmlReceiptItemRow*> *saleItems;//renamed from saleItems
@property (nullable, nonatomic, strong, readonly) NSString *unitPricesTaxation;
@property (nullable, nonatomic, strong, readonly) NSString *taxPercentage;
@property (nullable, nonatomic, strong, readonly) NSString *netto;
@property (nullable, nonatomic, strong, readonly) NSString *brutto;
@property (nullable, nonatomic, strong, readonly) NSString *tax;
@property (nullable, nonatomic, strong, readonly) NSArray<WDHtmlReceiptTaxRow*> *taxItems;
@property (nullable, nonatomic, strong, readonly) NSString *totalAmountLabel;
@property (nullable, nonatomic, strong, readonly) NSString *totalAmount;
@property (nullable, nonatomic, strong, readonly) NSString *subTotalAmountLabel;
@property (nullable, nonatomic, strong, readonly) NSString *subTotalAmount;
@property (nullable, nonatomic, strong, readonly) NSString *serviceChargeLabel;
@property (nullable, nonatomic, strong, readonly) NSString *serviceChargeAmount;
@property (nullable, nonatomic, strong, readonly) NSString *serviceChargeTax;
@property (nullable, nonatomic, strong, readonly) NSString *discountAmount;
@property (nullable, nonatomic, strong, readonly) NSString *tipLabel;
@property (nullable, nonatomic, strong, readonly) NSString *tipTax;
@property (nullable, nonatomic, strong, readonly) NSString *tipInclusiveTaxAmount;
@property (nullable, nonatomic, strong, readonly) NSString *vouchersLabel;
@property (nullable, nonatomic, strong, readonly) NSString *vouchersAmount;
@property (nullable, nonatomic, strong, readonly) NSString *customerCardLabel;
@property (nullable, nonatomic, strong, readonly) NSString *customerCardID;
// details
@property (nullable, nonatomic, strong, readonly) NSString *detailsTitle;
@property (nullable, nonatomic, strong, readonly) NSArray<WDHtmlReceiptPaymentRow*> *payments;
@property (nullable, nonatomic, strong, readonly) NSArray<WDHtmlReceiptPaymentRow*> *alternativePayments;
// footer
@property (nullable, nonatomic, strong, readonly) NSString *signatureLabel;
@property (nullable, nonatomic, strong, readonly) NSString *signature;
/// "Please retain receipt for future reference."
@property (nullable, nonatomic, strong, readonly) NSString *retainLabel;
/// "Payment issued by Wirecard ePOS"
@property (nullable, nonatomic, strong, readonly) NSString *issuedByLabel;
@property (nullable, nonatomic, strong, readonly) NSString *barcode;
@property (nullable, nonatomic, strong, readonly) NSString *barcodeData;
/// "HAVE A NICE DAY!"
@property (nullable, nonatomic, strong, readonly) NSString *closingLabel;
/// Helper labels
@property (nullable, nonatomic, strong, readonly) NSString *noTaxLabel;
@property (nullable, nonatomic, strong, readonly) NSString *discountLabel;

- (nonnull instancetype)init __attribute__((unavailable("use initFromSaleResponse:isForCardholder:includeReturns:locale:")));
+ (nonnull instancetype)new __attribute__((unavailable("use initFromSaleResponse:isForCardholder:includeReturns:locale:")));
- (nonnull instancetype)initFromSaleResponse:(nonnull WDSaleResponse *)saleResponse isForCardholder:(BOOL)isForCardholder includeReturns:(BOOL)showReturns locale:(nonnull NSLocale*)locale;
/// Receipt description - to be used for console printout
- (nonnull NSString *)receiptDescription;
@end
