//
//  WDePOSSale.h
//   WDePOS
//
//  Created by Danko, Radoslav on 16/02/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDSaleItem.h"
#import <CoreLocation/CoreLocation.h>
#import "WDDataTypes.h"
#import "WDSaleProcessing.h"

@class WDTerminal, WDMerchant, WDMerchantUser, WDAddress, WDShop, WDReceiptData, WDHtmlReceipt;

NS_ASSUME_NONNULL_BEGIN
#pragma mark - AcceptSaleSummaryItem
/**
 *  @class WDSaleSummaryItem
 *  @brief Tax Summary item
 **/
@interface WDSaleSummaryItem : WDObject
/**
 */
@property (nonatomic) NSDecimalNumber  *quantity;
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

#pragma mark - Sale Core
/**
 *  @class WDSaleCore
 *  @brief The Sale Core object is the base for all higher level Sale to be used for Sale operations
 **/
@interface WDSaleCore: WDObject <NSCoding>
/**
 * @brief Sale internal unique ID Set by backend after processing the Sale
 */
@property (nonatomic, strong, readonly) NSString *saleId;
/**
 */
@property (nonatomic, readonly) WDSaleType type;
/**
 */
@property (nonatomic, strong, readonly) NSString *currency;
/**
 */
@property (nonatomic, strong, readonly) NSNumber *version;
/**
 */
@property (nonatomic, strong, readonly) NSArray *payments;
/**
 */
@property (nullable, nonatomic, strong) NSString * note;
/**
 *  @brief Returns the terminal information in the case Card payment is present
 **/
-(WDTerminal* _Nullable)terminal;
/**
 */
-(NSString *)saleTypeDescription;

@end


#pragma mark - Sale
/**
 *  @class WDSale
 *  @brief The Sale object contains all necessary Sale information
 *  @discussion Sale to be performed (WDSaleRequest) 
 *
 *              Sale already processed (WDSaleResponse)
 **/
@interface WDSale : WDSaleCore
/**
 */
@property (nonatomic, strong, readonly) NSString * externalId;
/**
 */
@property (nullable, nonatomic, strong, readonly) NSArray <WDSaleItemCore *>* items;
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
-(NSDecimalNumber*)totalSaleItemsQuantity;
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
-(NSDecimalNumber * _Nullable)totalNoSCTaxed:(BOOL)taxed;
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
-(NSDecimalNumberHandler *)roundModePlainInteger;

//-(NSDecimalNumberHandler *)roundModeBankers;
@end

//#pragma mark - Sale Request Core
///**
// *  @class WDSaleCore Request
// *  @brief The base of a Sale Request to be processed.
// **/
//@interface WDSaleCore(Request)
///**
// * @brief EMV - Amount, Authorised (Numeric) (9f02) for card payment request
// */
//-(unsigned long long)authorizedAmountCard;
///**
// * @brief total amount to pay
// */
//-(NSDecimalNumber *)total;
//@end

#pragma mark - Referenced Sale Request
/**
 *  @class WDReferencedSaleRequest
 *  @brief The Sale to be processed - as part of a multitender Sale.
 * Initial Sale already created by previous WDSaleRequest
 *  @discussion References the Original Sale to process another payment
 **/
@interface WDReferenceSaleRequest : WDSaleCore <WDReferenceSaleProcessing>
/**
 *  @brief Add another payment method to the original Sale to settle it
 *  @param originalSaleId Unique identifier of the original Sale
 **/
-(instancetype)initWithOriginalSaleId:(NSString *)originalSaleId NS_DESIGNATED_INITIALIZER;
-(instancetype)initWithOriginalSaleId:(NSString *)originalSaleId
                                 note:(nullable NSString *)note NS_DESIGNATED_INITIALIZER;
-(instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
/**
 */
@property (nullable, nonatomic, strong) NSString *cashRegisterId;
@end

#pragma mark - Sale Request
/**
 *  @class WDSaleRequest
 *  @brief The Sale to be processed
 *  @discussion Contains all necessary information to perform the Sale
 **/
@interface WDSaleRequest : WDSale <WDSaleProcessing>
/**
 */
@property (nullable, nonatomic, strong) NSString *shopId;
/**
 */
@property (nullable, nonatomic, strong) NSString *cashierId __attribute__((deprecated));
/**
 */
@property (nullable, nonatomic, strong) NSString *customerId;
/**
 */
@property (nullable, nonatomic, strong) NSString *cashRegisterId;
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
/**
 *  @brief Create new Sale Purchase
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
                         gratuityTaxRate:(NSDecimalNumber * _Nullable) gratuityTaxRate ;
/**
 *  @brief Create new Sale Purchase where no Items to be added later
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
                         gratuityTaxRate:(NSDecimalNumber * _Nullable) gratuityTaxRate  ;
-(instancetype)initWithCoder:(NSCoder *)decoder;
///
/**
 *  @brief set Amount and tax rate - no items to be added later
 *  @param saleAmount Amount
 *  @param note sale description
 **/
-(void)setSaleAmount:(NSDecimalNumber *)saleAmount
                note:(nullable NSString *)note;

/**
 *  @brief set Note for the sale
 *  @param note sale description
 **/
-(void)setSaleNote:(nullable NSString *)note;

/**
 *  @brief Add sale item to the sale
 *  @param unitPrice Unit price
 *  @param taxRate tax rate of the sale item (percentage e.g. tax rate of 10% = 10.0)
 *  @param itemDescription sale item description
 *  @param productId Sale item (a product) has a unique identifier in the inventory
 **/
-(void)addSaleItem:(NSDecimalNumber *)unitPrice
          quantity:(NSDecimalNumber *)quantity
           taxRate:(NSDecimalNumber *)taxRate
   itemDescription:(nullable NSString *)itemDescription
         productId:(nullable NSString *)productId __deprecated_msg("use addSaleItem:quantity:taxRate:itemDescription:productId:externalProductId:");

/**
 *  @brief Add sale item to the sale
 *  @param unitPrice Unit price
 *  @param taxRate tax rate of the sale item (percentage e.g. tax rate of 10% = 10.0)
 *  @param itemDescription sale item description
 *  @param productId Sale item (a product) has an unique identifier in the inventory
 *  @param externalProductId Sale item (a product) can have an unique identifier in the ERP
 **/
-(void)addSaleItem:(NSDecimalNumber *)unitPrice
          quantity:(NSDecimalNumber *)quantity
           taxRate:(NSDecimalNumber *)taxRate
   itemDescription:(nullable NSString *)itemDescription
         productId:(nullable NSString *)productId
 externalProductId:(nullable NSString *)externalProductId;

/**
 *  @brief Add sale item to the sale
 *  @param unitPrice Unit price
 *  @param discountRate Item's Discount (percentage e.g. discount rate of 5% = 5.0, in range: 0.0 - 100.0)
 *  @param taxRate tax rate of the sale item (percentage e.g. tax rate of 10% = 10.0)
 *  @param itemDescription sale item description
 *  @param productId Sale item (a product) has an unique identifier in the inventory
 **/
-(void)addSaleItem:(NSDecimalNumber *)unitPrice
      discountRate:(NSDecimalNumber *)discountRate
          quantity:(NSDecimalNumber *)quantity
           taxRate:(NSDecimalNumber *)taxRate
   itemDescription:(nullable NSString *)itemDescription
         productId:(nullable NSString *)productId __deprecated_msg("use addSaleItem:discountRate:quantity:taxRate:itemDescription:productId:externalProductId:");

/**
 *  @brief Add sale item to the sale
 *  @param unitPrice Unit price
 *  @param discountRate Item's Discount (percentage e.g. discount rate of 5% = 5.0, in range: 0.0 - 100.0)
 *  @param taxRate tax rate of the sale item (percentage e.g. tax rate of 10% = 10.0)
 *  @param itemDescription sale item description
 *  @param productId Sale item (a product) has a unique identifier in the inventory
 *  @param externalProductId Sale item (a product) can have an unique identifier in the ERP
 **/
-(void)addSaleItem:(NSDecimalNumber *)unitPrice
      discountRate:(NSDecimalNumber *)discountRate
          quantity:(NSDecimalNumber *)quantity
           taxRate:(NSDecimalNumber *)taxRate
   itemDescription:(nullable NSString *)itemDescription
         productId:(nullable NSString *)productId
 externalProductId:(nullable NSString *)externalProductId;

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
 *  @brief Add flat discount to the sale - applied to the total gross price as discount percentage

 *  @param discountRate Flat Discount (e.g. 5.0 for 5%)
 **/
-(void)addFlatDiscount:(NSDecimalNumber *)discountRate;

/**
 *  @brief Add service charge to the sale - applied to the total netto price
 *  @param serviceChargeRate service charge rate (percentage e.g. service charge of 2.75% = 2.75)
 *  @param taxRate tax rate of the service charge (percentage e.g. tax rate of 10% = 10.0)
 **/
-(void)addServiceCharge:(NSDecimalNumber *)serviceChargeRate
                taxRate:(NSDecimalNumber *)taxRate __deprecated_msg("Use addServiceChargeRate or addServiceChargeAmount");

/**
 *  @brief Add service charge rate to the sale - applied to the total netto price
 *  @param serviceChargeRate service charge rate (percentage e.g. service charge of 2.75% = 2.75)
 *  @param taxRate tax rate of the service charge (percentage e.g. tax rate of 10% = 10.0)
 **/
-(void)addServiceChargeRate:(NSDecimalNumber *)serviceChargeRate
                    taxRate:(NSDecimalNumber *)taxRate;

/**
 *  @brief Add service charge amount to the sale - Service charge added as an item, on top of the total netto price
 *  @param serviceChargeAmount service charge amount (e.g. 2.75 eur as service charge price) added on top of total netto price
 *  @param taxRate tax rate of the service charge (percentage e.g. tax rate of 10% = 10.0)
 **/
-(void)addServiceChargeAmount:(NSDecimalNumber *)serviceChargeAmount
                    taxRate:(NSDecimalNumber *)taxRate;

/**
 *  @brief Remove the specified item formthe items list - Sale recalculation will be performed automatically
 *  @param itemToRemove item to remove
 **/
-(void)removeItem:(WDSaleItemCore *)itemToRemove;
/**
 *  @brief Remove all Items - Sale recalculation will be performed after item(s) are added again using add*Item
 **/
-(void)removeAllItems;
/**
 *  @brief Refresh sale calculation - in the case Item qty changed and Discount is present the recalc is needed
 **/
-(void)recalculate;
/**
 * @brief Gratuity amount as unsigned integer
 */
-(NSUInteger)gratuityIntAmount;

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

/// does this Sale Request have some items which can be refunded
-(BOOL)hasReturnableItems;
@end

#pragma mark - Sale Request  - Purchase
@interface WDSaleRequestPurchase : WDSaleRequest
/**
 *  @brief Create new Sale Purchase
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
 *  @brief Create new Sale Purchase where no Items to be added later
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
-(instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - Sale Request - Return
@interface WDSaleRequestReturn : WDSaleRequest<WDSaleReturnProcessing>

/**
 *  @brief Create Sale Return
 *  @param saleId Original Sale identifier as understood by Switch backend system
 *  @param externalId Refund Id as understood by external system
 *  @param location sale location (the gps location of the terminal at the time of payment)
 *  @param inclusiveTaxes prices are tax inclusive
 *  @param currency sale currency
 *  @param note sale description
 *  This parameter is also conveyed to Payment Gateways [PE (Usage), EE(descriptor)]
 **/
-(nullable instancetype)initWithOriginalSaleId:(NSString * _Nullable)saleId
                                    externalId:(NSString *_Nullable)externalId
                                      location:(CLLocation* _Nullable)location
                                inclusiveTaxes:(BOOL)inclusiveTaxes
                                      currency:(NSString * )currency
                                          note:(NSString * _Nullable)note NS_DESIGNATED_INITIALIZER;
/**
 *  @brief Create new Sale where no Items to be added later
 *  @param saleId Original Sale identifier as understood by Switch backend system
 *  @param externalId Refund Id as understood by external system
 *  @param location sale location (the gps location of the terminal at the time of payment)
 *  @param inclusiveTaxes prices are tax inclusive
 *  @param saleAmount The total Sale amount
 *  @param currency sale currency
 *  @param note sale description
 *  This parameter is also conveyed to Payment Gateways [PE (Usage), EE(descriptor)]
 **/
-(nullable instancetype)initWithOriginalSaleId:(NSString * _Nullable)saleId
                                    externalId:(NSString *_Nullable)externalId
                                      location:(CLLocation* _Nullable)location
                                inclusiveTaxes:(BOOL)inclusiveTaxes
                                    saleAmount:(NSDecimalNumber *)saleAmount
                                      currency:(NSString * )currency
                                          note:(NSString * _Nullable)note NS_DESIGNATED_INITIALIZER;
-(instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - Sale Request - Refund
@interface WDSaleRequestRefund : WDSaleRequest
/**
 *  @brief Create new Sale Refund
 *  @param saleId Original Sale identifier as understood by Switch backend system
 *  @param externalId Refund Id as understood by external system
 *  @param note Refund description
 **/
-(nullable instancetype)initWithOriginalSaleId:(NSString *)saleId
                                    externalId:(NSString *_Nullable)externalId
                                          note:(NSString * _Nullable)note NS_DESIGNATED_INITIALIZER;
-(instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
@end

#pragma mark - Sale Maintain
@interface WDSaleMaintain : WDObject <NSCoding>
/**
 * @brief Original Sale internal unique ID (In the case of Returned sale) Set by backend after processing the Sale
 */
@property (nullable, nonatomic, strong,readonly) NSString *originalSaleId;
/**
 * @brief Cash Register ID as set during the payment process - this is linked to the cash drawer and the shifts of the cashier
 */
@property (nullable, nonatomic, strong) NSString *cashRegisterId;
/**
 * @brief Note to attach to the modify sale operation
 */
@property (nullable, nonatomic, strong) NSString * note;
/**
 * @brief Items to update the Sale with
 */
@property (nullable, nonatomic, strong) NSArray <WDSaleItemCore *>* items;
/**
 * @brief Total amount for this updated Sale
 */
@property (nullable, nonatomic, strong) NSDecimalNumber * totalAmount;
/**
 * @brief Inclusive taxes for this updated Sale
 */
@property (nonatomic) BOOL inclusiveTaxes;
/**
 * @brief Sale version to update
 */
@property (nullable, nonatomic, strong) NSNumber *version;

/**
 *  @brief Create the new Sale Maintain request
 *  @param saleId Original Sale identifier as understood by Switch backend system
 *  @param items Sale Items - will replace the current Sale Items list with this one
 *               Can be empty if the original Sale was without the items, or if you want to clear the Sale Items
 *  @param amount Sale Amount must match the sum of item amounts
 *  @param inclusiveTaxes prices are tax inclusive
 *  @param note Sale maintenance description
 *  @param version the Sale version to modify
 **/
-(nullable instancetype)initWithOriginalSaleId:(NSString *)saleId
                                         items:( NSArray <WDSaleItemCore *>* _Nullable)items
                                        amount:(NSDecimalNumber *_Nullable)amount
                                        inclusiveTaxes:(BOOL)inclusiveTaxes
                                          note:(NSString * _Nullable)note
                                          version:(NSNumber * _Nullable)version NS_DESIGNATED_INITIALIZER;
-(instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;
@end

#pragma mark - Sale Response
/**
 *  @class WDSaleResponse
 *  @brief The processed Sale
 *  @discussion Contains all details about performed Sale
 **/
@interface WDSaleResponse : WDSale
/**
 * @brief Sale internal unique ID Set by backend after processing the Sale
 */
@property (nonatomic, strong,readonly) NSString *internalId __deprecated_msg("will become SaleCore.saleId");
/**
 * @brief Original Sale internal unique ID (In the case of Returned sale) Set by backend after processing the Sale
 */
@property (nullable, nonatomic, strong,readonly) NSString *originalSaleId;
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
 * @brief Cash Register ID as set during the payment process - this is linked to the cash drawer and the shifts of the cashier
 */
@property (nonatomic, strong,readonly) NSString *cashRegisterId;
/**
 * @brief Shift ID as set during the payment process - this is linked to the cash drawer and the shifts of the cashier
 */
@property (nonatomic, strong,readonly) NSString *shiftId;
/**
 * @brief Customer ID as set during the payment process - the customer of the shop
 */
@property (nonatomic, strong,readonly) NSString *customerId;
/**
 * @brief multitender indicates the sales contains more than one payment method
 */
@property (nonatomic, assign) BOOL multitender;
/**
 * @brief clientInfo Information about the client system which initiated this Sale
 */
@property (nonatomic, strong, readonly) WDClientInformation *clientInformation;
/**
 * @brief array of Sale returns in the case this sale has status of RETURNED
 */
@property (nonatomic, strong, readonly) NSArray <WDSaleResponse *>* returns;
/**
 * @brief After the Sale was processed by backend and Card Payment was requested
 */
-(WDPaymentDetailCard *)processedCardPayment __deprecated_msg("use processedCardPayments");
/**
 * @brief After the Sale was processed by backend and Cash Payment was requested
 */
-(WDPaymentDetail *)processedCashPayment __deprecated_msg("use processedCashPayments");
/**
 * @brief After the Sale was processed by backend and Alipay Payment was requested
 */
-(WDPaymentDetailAlipay *)processedAlipayPayment __deprecated_msg("use processedAlipayPayments");
/**
 * @brief After the Sale was processed by backend and WeChat Payment was requested
 */
-(WDPaymentDetailWeChat *)processedWeChatPayment __deprecated_msg("use processedWeChatPayments");
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
 * @brief All the Card payments processed as part of this Sale
 */
-(NSArray <WDPaymentDetailCard *>*)processedCardPayments;
/**
 * @brief All the Cash payments processed as part of this Sale
 */
-(NSArray <WDPaymentDetailCash *>*)processedCashPayments;
/**
 * @brief All the Alipay payments processed as part of this Sale
 */
-(NSArray <WDPaymentDetailAlipay *>*)processedAlipayPayments;
/**
 * @brief All the WeChat payments processed as part of this Sale
 */
-(NSArray <WDPaymentDetailWeChat *>*)processedWeChatPayments;

/**
 * @brief All payments that can be subject to reversal - curently with the Completed status
 */
-(NSArray *)reversiblePayments;

/**
 * @brief Default Design of the Sale Receipt
 * @discussion To show your custom application name in the receipt footer: Define the Application Name to be displayed on the receipt in the application plist file as WDApplicationName <NSString>
 *
 * To show your custom Logo on the receipt: Supply your receipt Logo images and replace headerLogo (250x100 px) png file in the acceptResources.bundle
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
 * To show your custom Logo on the receipt: Supply your receipt Logo images and replace headerLogo (250x100 px) png file in the acceptResources.bundle
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
 * @brief Default Design of the Sale Receipt
 * @discussion To show your custom application name in the receipt footer: Define the Application Name to be displayed on the receipt in the application plist file as WDApplicationName <NSString>
 *
 * To show your custom Logo on the receipt: Supply your receipt Logo images and replace headerLogo (250x100 px) png file in the acceptResources.bundle
 *
 * @param forCardholder is it the Cardholder receipt ? Some receipt items are not available in Merchant copy of a receipt
 * @param showReturns should the receipt contain all returns sub-receipts ?
 * @param format Format of the receipt
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param locale to use for localization of receipt labels (locale.languageCode) and  date formats (locale.countryCode)
 * @param completion Receipt in the requested format
 */
-(void)receipt:(BOOL)forCardholder
   showReturns:(BOOL)showReturns
        format:(WDPrintFormat)format
           dpi:(WDPrintDpi)dpi
        locale:(NSLocale *)locale
    completion:(ReceiptCompletion)completion;

/**
 * @brief Create the SaleResponse object with specified Payment details to be used to create the Single Payment Receipt
 * @param paymentId for which to create the receipt
 * @return SaleResponse with Single Payment to be used with receipt:showReturns:format:dpi:locale:completion
*/
-(WDSaleResponse*)paymentForReceipt:(NSString*)paymentId;


/**
 * @brief Returns all data necessary for creating the Sale Return - single payment only
 * For multi tender sales you need to create the Sale Returns manually
 */
-(WDSaleRequestReturn * _Nullable)saleReturn;
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
/**
 * @brief Create Reference Sale Request from this Sale - To be used for multi-tender Sale where additional payments can be added to the original Sale
 */
-(WDReferenceSaleRequest *)referenceSaleRequest;
/**
 * @brief Create Reference Sale Request from this Sale with a cashRegisterId - To be used for multi-tender Sale where additional payments can be added to the original Sale
 */
-(WDReferenceSaleRequest *)referenceSaleRequestWithCashRegisterId:(NSString* _Nullable)cashRegiterId;
/**
 */
- (NSDecimalNumber *)totalPaid;
/**
 * @brief Returns all data necessary for mantaining a Sale
 * It can be use to modigy the items, total amount, tax mode and description of an open sale
 */
-(WDSaleMaintain * _Nullable)saleMaintain;
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
