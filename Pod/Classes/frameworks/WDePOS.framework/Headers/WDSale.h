//
//  WDePOSSale.h
//   WDePOS
//
//  Created by Danko, Radoslav on 16/02/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDSaleItem.h"
#import <CoreLocation/CoreLocation.h>
#import "WDDataTypes.h"

@class WDTerminal, WDMerchant, WDMerchantUser,WDAddress,WDShop,WDReceiptData;



NS_ASSUME_NONNULL_BEGIN
#pragma mark - AcceptSaleSummaryItem
/**
 *  @class WDSaleSummaryItem
 *  @brief Tax Summary item
 **/
@interface WDSaleSummaryItem : WDObject
/**
 */
@property (nonatomic) NSUInteger  quantity;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber  *total;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber  *totalDiscounted;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber  *discountRate;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber  *taxRate;
/**
 */
@property (nonnull, nonatomic, strong) NSString  *currency;
/**
 */
@property (nonatomic ) BOOL inclusiveTaxes;
/**
 * @discussion Calculated price after tax and discount - price with discounts/surcharges taxed. Rounding to currency fraction enabled
 */
-(NSDecimalNumber  *)totalAfterTaxAfterDiscount;
/**
 * @discussion Calculated price after tax and discount - price with discounts/surcharges taxed
 */
-(NSDecimalNumber  *)totalAfterTaxAfterDiscountWithRounding:(BOOL)withRounding;
/**
 * @discussion Calculated  total before tax - without including any discounts/surcharges. Rounding to currency fraction enabled
 */
-(NSDecimalNumber  *)totalBeforeTaxBeforeDiscount;
/**
 * @discussion Calculated  total before tax - without including any discounts/surcharges
 */
-(NSDecimalNumber  *)totalBeforeTaxBeforeDiscountWithRounding:(BOOL)withRounding;
/**
 * @discussion Calculated  total after tax - without including any discounts/surcharges
 */
-(NSDecimalNumber  *)totalAfterTaxBeforeDiscount;
/**
 * @discussion Calculated total before tax - after discounts
 */
-(NSDecimalNumber  *)totalBeforeTaxAfterDiscount;
/**
 * @discussion Calculated total before tax - after discounts. Rounding to currency fraction enabled
 */
-(NSDecimalNumber  *)totalBeforeTaxAfterDiscountWithRounding:(BOOL)withRounding;
/**
 * @discussion Calculated Tax Amount with rounding applied.
 */
-(NSDecimalNumber  *)taxAmount;
/**
 * @discussion Calculated Tax Amount.
 */
-(NSDecimalNumber  *)taxAmountWithRounding:(BOOL)withRounding;
/**
 * @discussion Rounding Mode/Behavior used in all calculations
 */
-(NSDecimalNumberHandler *)roundModePlain;
-(NSDecimalNumberHandler *)roundModeDown;
@end

#pragma mark - AcceptSale
/**
 *  @class WDSale
 *  @brief The Sale object contains all necessary Sale information
 *  @discussion Sale to be performed (WDSaleRequest) 
 *
 *              Sale already processed (WDSaleResponse)
 **/
@interface WDSale : WDObject <NSCoding>
/**
 */
@property (nonatomic, strong, readonly) NSString * externalId;
/**
 */
@property (nullable, nonatomic, strong, readonly) NSArray <WDSaleItemCore *>* items;
/**
 */
@property (nullable, nonatomic, strong, readonly) NSString * note;
/**
 */
@property (nonatomic, strong) NSString * currency;
/**
 */
@property (nullable, nonatomic, strong, readonly) CLLocation *location;
/**
 */
@property (nonatomic) BOOL inclusiveTaxes;
/**
 */
@property (nonatomic, strong, readonly) NSDecimalNumber  *gratutityTaxRate;
/**
 */
@property (nullable, nonatomic, strong, readonly) NSDecimalNumber  *flatDiscount;
/**
 */
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)coder NS_DESIGNATED_INITIALIZER;
/**
 */
- ( instancetype)init NS_DESIGNATED_INITIALIZER;
/**
 */
-(NSDecimalNumber*)totalSaleItemsQuantity;
/**
 */
-(NSArray *)payments;
/**
 *  @brief Returns the terminal information in the case Card payment is present
 **/
-(WDTerminal* _Nullable)terminal;

/**
 */
-(NSDecimalNumber * _Nullable)totalGross;
/**
 */
-(NSDecimalNumber * _Nullable)totalNetBeforeAnyModifier;//No Discount, SC, Coupon or Tip
/**
 */
-(NSDecimalNumber * _Nullable)totalToPay;
/**
 */
-(NSDecimalNumber * _Nullable)totalGratuity;
/**
 */
-(NSDecimalNumber * _Nullable)totalToPayBeforeDiscount;
/**
 */
-(NSDecimalNumber * _Nullable)totalServiceCharge;
/**
 */
-(NSDecimalNumber * _Nullable)totalServiceChargeWithTax;
/**
 */
-(NSDecimalNumber * _Nullable)totalDiscount;
/**
 */
-(NSDecimalNumber * _Nullable)totalToPayAfterDiscount;
/**
 */
-(NSDecimalNumber * _Nullable)totalCoupon;
/**
 */
-(NSArray<WDSaleSummaryItem*> *)taxSummary;
/**
 */
-(NSArray<WDSaleSummaryItem*> *)serviceChargeSummary;
/**
 */
-(NSArray<WDSaleSummaryItem*> *)tipSummary;
/**
 */
-(NSArray<WDSaleSummaryItem*> *)discountSummary;
/**
 */
-(NSArray<WDSaleSummaryItem*> *)couponSummary;
/**
 */
-(BOOL)hasAtLeastOneCashPayment;
/**
 */
-(void)setUpdatedLocation:(CLLocation*)newLocation;
/// Plain Rounding for this Sale - taking in consideration the Currency - number of decimal places
-(NSDecimalNumberHandler *)roundModePlain;
-(NSDecimalNumberHandler *)roundModeDown;
//-(NSDecimalNumberHandler *)roundModeBankers;
@end

#pragma mark - AcceptSaleRequest

/**
 *  @class WDSaleRequest
 *  @brief The Sale to be processed
 *  @discussion Contains all necessary information to perform the Sale
 **/
@interface WDSaleRequest : WDSale
/**
 */
@property (nonatomic) WDSaleType type;
/**
 */
@property (nonatomic, strong) NSString *shopId;
/**
 */
@property (nonatomic, strong) NSString *cashierId;
/**
 */
@property (nullable, nonatomic, strong) NSString *customerId;
/**
 */
@property (nonatomic, strong) NSString *cashRegisterId;
/**
 */
@property (nullable, nonatomic, strong) NSString *shiftId;
/**
 */
@property (nonatomic,strong) NSNumber *validateCashReturn;
/// Default NSObject new is unavailable
+( instancetype)new __attribute__((unavailable("use initWithUniqueId")));
/// Default NSObject init is unavailable
-( instancetype)init __attribute__((unavailable("use initWithUniqueId")));
///
- ( instancetype)initWithCoder:(NSCoder *)coder;

/**
 *  @brief Create new Sale
 *  @param uniqueId Unique identifier of this sale as understood by your backend system - one can use WDUtils.uniqueID to generate one
 *  This parameter is also conveyed to Payment Gateways [PE (FunctionID), EE(order_number)]
 *  @param location sale location (the gps location of the terminal at the time of payment)
 *  @param inclusiveTaxes prices are tax inclusive
 *  @param currency sale currency
 *  @param note sale description
 *  This parameter is also conveyed to Payment Gateways [PE (Usage), EE(descriptor)]
 *  @param gratuityTaxRate tax rate of the gratuity items
 **/
-(nullable instancetype)initWithUniqueId:(NSString * _Nullable)uniqueId
                       location:(CLLocation* _Nullable)location
                 inclusiveTaxes:(BOOL)inclusiveTaxes
                       currency:(NSString * )currency
                           note:(NSString * _Nullable)note
                         gratuityTaxRate:(NSDecimalNumber * _Nullable) gratuityTaxRate NS_DESIGNATED_INITIALIZER;
/**
 *  @brief Create new Sale where no Items to be added later
 *  @param uniqueId Unique identifier of this sale as understood by your backend system - one can use WDUtils.uniqueID to generate one
 *  This parameter is also conveyed to Payment Gateways [PE (FunctionID), EE(order_number)]
 *  @param location sale location (the gps location of the terminal at the time of payment)
 *  @param inclusiveTaxes prices are tax inclusive
 *  @param saleAmount The total Sale amount
 *  @param currency sale currency
 *  @param note sale description
 *  This parameter is also conveyed to Payment Gateways [PE (Usage), EE(descriptor)]
 *  @param gratuityTaxRate tax rate of the gratuity items
 **/
-(nullable instancetype)initWithUniqueId:(NSString * _Nullable)uniqueId
                                location:(CLLocation* _Nullable)location
                          inclusiveTaxes:(BOOL)inclusiveTaxes
                              saleAmount:(NSDecimalNumber *)saleAmount
                                currency:(NSString * )currency
                                    note:(NSString * _Nullable)note
                         gratuityTaxRate:(NSDecimalNumber * _Nullable) gratuityTaxRate  NS_DESIGNATED_INITIALIZER;

/**
 *  @brief set Amount and tax rate - no items to be added later
 *  @param saleAmount Amount
 *  @param note sale description
 **/
-(void)setSaleAmount:(NSDecimalNumber *)saleAmount
                note:(nullable NSString *)note;

/**
 *  @brief Add sale item to the sale
 *  @param unitPrice Unit price
 *  @param taxRate tax rate of the sale item (percentage e.g. tax rate of 10% = 10.0)
 *  @param itemDescription sale item description
 *  @param productId Sale item (a product) has a unique identifier in the inventory
 **/
-(void)addSaleItem:(NSDecimalNumber *)unitPrice
          quantity:(NSInteger)quantity
           taxRate:(NSDecimalNumber *)taxRate
   itemDescription:(nullable NSString *)itemDescription
         productId:(NSString * __nullable)productId;

/**
 *  @brief Add sale item to the sale
 *  @param unitPrice Unit price
 *  @param discountRate Item's Discount  (percentage e.g. discount rate of 5% = 5.0)
 *  @param taxRate tax rate of the sale item (percentage e.g. tax rate of 10% = 10.0)
 *  @param itemDescription sale item description
 *  @param productId Sale item (a product) has a unique identifier in the inventory
 **/
-(void)addSaleItem:(NSDecimalNumber *)unitPrice
      discountRate:(NSDecimalNumber *)discountRate
          quantity:(NSInteger)quantity
           taxRate:(NSDecimalNumber *)taxRate
   itemDescription:(nullable NSString *)itemDescription
         productId:(NSString * __nullable)productId;

/**
 *  @brief Add coupon to the sale - Customer buys coupon - to be added to the basket
 *  @param unitPrice Unit price of the sale coupon
 *  @param couponId Coupon has a unique identifier in the inventory
 **/
-(void)addCoupon:(NSDecimalNumber *)unitPrice
       couponId:(NSString * __nullable)couponId;

/**
 *  @brief Add gratuity to the sale
 *  @param unitPrice Gratuity amount
 *  @param taxRate tax rate of the gratuity (percentage e.g. tax rate of 10% = 10.0)
 **/
-(void)addGratuity:(NSDecimalNumber *)unitPrice
           taxRate:(NSDecimalNumber *)taxRate;

/**
 *  @brief Add discount to the sale - applied to the total gross price as discount percentage

 *  @param discountRate Flat Discount (e.g. 5.0 for 5%)
 *  @param productId Discount has a unique identifier in the inventory
 **/
-(void)addDiscount:(NSDecimalNumber *)discountRate
         productId:(NSString * __nullable)productId;

/**
 *  @brief Add service charge to the sale - applied to the total netto price
 *  @param serviceChargeRate service charge rate (percentage e.g. service charge of 2.75% = 2.75)
 *  @param taxRate tax rate of the service charge (percentage e.g. tax rate of 10% = 10.0)
 **/
-(void)addServiceCharge:(NSDecimalNumber *)serviceChargeRate
                taxRate:(NSDecimalNumber *)taxRate;

/**
 *  @brief Add Cash payment to the sale
 *  @param amount Cash amount
 **/
-(void)addCashPayment:(NSDecimalNumber * __nonnull)amount;

/**
 *  @brief Add Card payment to the sale
 *  @param amount Card amount
 *  @param terminal Terminal to execute Card payment on
 **/
-(void)addCardPayment:(NSDecimalNumber * __nonnull)amount
                 terminal:(WDTerminal *)terminal;

/**
 *  @brief Add Coupon payment to the sale
 *  @param amount Coupon amount
 **/
-(void)addCouponPayment:(NSDecimalNumber * __nonnull)amount
                   couponId:(NSString *__nonnull)couponId
                    brandId:(NSString *__nonnull)brandId;
/**
 *  @brief Add Alipay payment to the sale
 *  @param amount Alipay amount
 *  @param consumerId Alipay consumer id
 **/
-(void)addAlipayPayment:(NSDecimalNumber * __nonnull)amount
                 consumerId:(NSString *__nonnull)consumerId;

/**
 *  @brief Add WeChat payment to the sale
 *  @param amount Alipay amount
 *  @param consumerId Alipay consumer id
 **/
-(void)addWeChatPayment:(NSDecimalNumber * __nonnull)amount
             consumerId:(NSString *__nonnull)consumerId;

/**
 *  @brief Remove the specified item formthe items list - Sale recalculation will be performed automatically
 *  @param itemToRemove item to remove
 **/
-(void)removeItem:(WDSaleItem *)itemToRemove;
/**
 *  @brief Remove all Items - Sale recalculation will be performed after item(s) are added again using add*Item
 **/
-(void)removeAllItems;
/**
 *  @brief Refresh sale calculation - in the case Item qty changed and Discount is present the recalc is needed
 **/
-(void)recalculate;
/**
 */
-(NSString *)saleTypeDescription;
/**
 * @brief EMV - Amount, Authorised (Numeric) (9f02) for card payment request
 */
-(NSUInteger)authorizedAmountCard;
/**
 * @brief Gratuity amount as unsigned integer
 */
-(NSUInteger)gratuityIntAmount;
/**
 * @brief Returns the Card payment if present on this Sale request
 */
-(WDPaymentRequestCard *)requestedCardPayment;
/**
 * @brief Returns the Coupon payment if present on this Sale request
 */
-(WDPaymentRequestCoupon *)requestedCouponPayment;
/**
 * @brief Returns the Cash payment if present on this Sale request
 */
-(WDPaymentRequestCash *)requestedCashPayment;
/**
 * @brief Returns the Alipay payment if present on this Sale request
 */
-(WDPaymentRequestAlipay *)requestedAlipayPayment;
/**
 * @brief Remove service charge item from sale
 */
-(void)removeServiceCharge;
/**
 * @brief Remove gratuity/tip item from sale
 */
-(void)removeGratuity;
/**
 * @brief Remove flat discount item from sale
 */
-(void)removeFlatDiscount;
/**
 * @brief Remove card payment from sale
 */
-(void)removeCardPayment;
/**
 * @brief Remove cash payment from sale
 */
-(void)removeCashPayment;
/**
 * @brief Remove coupon payment from sale
 */
-(void)removeCouponPayment;
/**
 * @brief Remove Alipay payment from sale
 */
-(void)removeAlipayPayment;
/**
 * @brief Remove all payments from sale - add payments afterwards using addXXXPayment
 */
-(void)resetPayments;
/// does this Sale Request have some items which can be refunded
-(BOOL)hasReturnableItems;
@end

#pragma mark - AcceptSaleResponse
/**
 *  @class WDSaleResponse
 *  @brief The processed Sale
 *  @discussion Contains all details about performed Sale
 **/
@interface WDSaleResponse : WDSale
/**
 */
@property (nonatomic,readonly) WDSaleType type;
/**
 * @brief Sale internal unique ID Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) NSString *internalId;
/**
 * @brief Original Sale internal unique ID (In the case of Returned sale) Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) NSString *originalSaleId;
/**
 * @brief Sale status Set by backend after processing the Sale
 */
@property (nonatomic, readonly) WDSaleState status;
/**
 * @brief Sale initialized by payment gateway Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) NSDate *initialized;
/**
 * @brief Merchant Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) WDMerchant *merchant;
/**
 * @brief Merchant user Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) WDMerchantUser *user;
/**
 * @brief Merchant's shop user Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) WDShop *shop;
/**
 * @brief Cashier ID as set during the payment process - the person performing the sale
 */
@property (nonatomic, strong,readonly) NSString *cashierId;
/**
 * @brief Customer ID as set during the payment process - the customer of the shop
 */
@property (nonatomic, strong,readonly) NSString *customerId;
/**
 * @brief array of Sale returns in the case this sale has status of RETURNED
 */
@property (nonatomic, strong, readonly) NSArray <WDSaleResponse *>* returns;
/**
 * @brief After the SaWDPaymentDetailCardle was processed by backend and Card Payment was requested
 */
-(WDPaymentDetailCard *)processedCardPayment;
/**
 * @brief After the Sale was processed by backend and Cash Payment was requested
 */
-(WDPaymentDetail *)processedCashPayment;
/**
 * @brief After the Sale was processed by backend and Alipay Payment was requested
 */
-(WDPaymentDetailAlipay *)processedAlipayPayment;
/**
 * @brief After the Sale was processed by backend and WeChat Payment was requested
 */
-(WDPaymentDetailWeChat *)processedWeChatPayment;
/**
 * @brief Merchant receipt unique id
 */
@property (nullable, nonatomic, strong, readonly) NSNumber *merchantReceiptId;
/**
 * @brief Flag YES if all payments are approved | approved by gateway | captured
 */
-(BOOL)allPaymentsApproved;
/**
 * @brief Returns the most onerous status of all payments composing this sale
 */
-(WDPaymentState)mostOnerousStatus;
/**
 * @brief Returns all data necessary for creating the Receipt
 */
-(WDReceiptData *)getReceiptData;

/**
 * @brief Default Design of the Sale Receipt
 * @discussion To show your custom application name in the receipt footer: Define the Application Name to be displayed on the receipt in the application plist file as WDApplicationName <NSString>
 *
 * To show your custom Logo on the receipt: Supply your receipt Logo images and replace wd-merchantLogo (250x100 px) png file in the acceptResources.bundle
 *
 * @param forCardholder is it the Cardholder receipt ? Some receipt items are not available in Merchant copy of a receipt
 * @param showReturns should the receipt contain all returns sub-receipts ?
 * @param format Format of the receipt
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param completion Receipt in the requested format
 */
-(void)receipt:(BOOL)forCardholder
 showReturns:(BOOL)showReturns
      format:(WDPrintFormat)format
         dpi:(WDPrintDpi)dpi
    completion:(ReceiptCompletion)completion;

/**
 * @brief Default Design of the Sale Receipt
 * @discussion To show your custom application name in the receipt footer: Define the Application Name to be displayed on the receipt in the application plist file as WDApplicationName <NSString>
 *
 * To show your custom Logo on the receipt: Supply your receipt Logo images and replace wd-merchantLogo (250x100 px) png file in the acceptResources.bundle
 *
 * @param forCardholder is it the Cardholder receipt ? Some receipt items are not available in Merchant copy of a receipt
 * @param showReturns should the receipt contain all returns sub-receipts ?
 * @param format Format of the receipt
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param language to use for localization of receipt labels - check WDLocalizationManager for supportedLanguages
 * @param completion Receipt in the requested format
 */
-(void)receipt:(BOOL)forCardholder
   showReturns:(BOOL)showReturns
        format:(WDPrintFormat)format
           dpi:(WDPrintDpi)dpi
      language:(NSString *)language
    completion:(ReceiptCompletion)completion;

/**
 * @brief Returns all data necessary for creating the Sale Return
 */
-(WDSaleRequest * _Nullable)saleReturn;
/**
 * @brief Sets cashierId when missing, for example, partial returns
 */
-(void)setCashierId:(NSString * _Nonnull)cashierId;
/**
 *  @brief Indicates if a sale is still refundable, either because it was never refunded, or because there are still items available from a prior partial refund
 **/
-(BOOL)isRefundable;
/**
 *  @brief Indicates if a sale is reversible
 **/
-(BOOL)isReversible;
@end

#pragma mark - Sale helpers
/**
 *  @brief get the Internal sale types  as dictionary
 *  @return Dictionary of mapping internal Switch sale type to external WDePOS sale type
 **/
NSDictionary *  WDASaleTypes(void);

/**
 *  @discussion Get the Internal Switch Sale type from the external sale type
 *  @return Switch Sale operation
 **/
NSString *const WDASaleTypeFromSaleType(WDSaleType saleType);

/**
 *  @discussion Get the  Sale operation from the internal sale operation
 *  @return WDePOS Sale operation
 **/
WDSaleType WDSaleTypeFromSaleType(NSString * type);

NS_ASSUME_NONNULL_END
