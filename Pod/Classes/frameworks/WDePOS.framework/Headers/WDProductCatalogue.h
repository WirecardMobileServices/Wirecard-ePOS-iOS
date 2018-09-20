//
//  WDProductCatalogue.h
//   WDePOS
//
//  Created by Danko, Radoslav on 22/01/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "WDObject.h"

@class WDUnitPrice,WDTaxCategory, WDAddress;

NS_ASSUME_NONNULL_BEGIN
/**
 *  @class WDProductCatalogueCore
 *  @brief  Product Catalogue core object
 **/
@interface WDProductCatalogueCore : WDObject <NSCoding>
@property (nullable, nonatomic, strong) NSString *productCatalogueId;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSString *discount;
@property (nullable, nonatomic, strong) NSNumber *version;
@end

/**
 *  @class WDProductCatalogue
 *  @discussion  Product Catalogue object
 **/
@interface WDProductCatalogue : WDProductCatalogueCore

@property (nullable, nonatomic, strong) NSString *merchantId;
@property (nullable, nonatomic, strong) NSString *optionalDescription;
@property (nullable, nonatomic, strong) NSDate *upsertDate;
@property (nullable, nonatomic, strong) NSString *type;

/**
 *  @brief Create Product Catalogue
 *  @param merchantId Merchant ID for under which to create the product catalogue
 *  @param name Product Catalogue name
 *  @param description Product Catalogue description
 *  @return new Product Catalogue
 **/
-(instancetype)initWithMerchantId:(NSString *)merchantId
                             name:(NSString *)name
                      description:(NSString *)description;

/**
 *  @brief Create Product Catalogue
 *  @param merchantId Merchant ID for under which to create the product catalogue
 *  @param name Product Catalogue name
 *  @param description Product Catalogue description
 *  @param discount Product Catalogue discount
 *  @return new Product Catalogue
 **/
-(instancetype)initWithMerchantId:(NSString *)merchantId
                             name:(NSString *)name
                      description:(nullable NSString *)description
                         discount:(nullable NSString *)discount;
@end

/**
 *  @class WDProductCatalogueCategory
 *  @brief  Product Catalogue Category object
 **/
@interface WDProductCatalogueCategory : WDProductCatalogueCore
/**
 *  @brief Create Product Category
 *  @param parentId Parent Category ID under which to create the new category - will become root category if nil specified
 *  @param name Product Category name
 *  @param displayOrder ordering sequence of the category - used when displaying the categories
 *  @return new Product Category
 **/
-(instancetype)initWithParentCategoryId:(nullable NSString *)parentId
                                   name:(NSString *)name
                           displayOrder:(NSNumber *)displayOrder;

/**
 *  @brief Create Product Category
 *  @param parentId Parent Category ID under which to create the new category - will become root category if nil specified
 *  @param name Product Category name
 *  @param discount discount Category discount to be applied on all subcategories and products
 *  @param displayOrder ordering sequence of the category - used when displaying the categories
 *  @return new Product Category
 **/
-(instancetype)initWithParentCategoryId:(nullable NSString *)parentId
                                   name:(NSString *)name
                               discount:(nullable NSString *)discount
                           displayOrder:(NSNumber *)displayOrder;

@property (nullable, nonatomic, strong) NSString *categoryId;
@property (nullable, nonatomic, strong) NSString *parentCategoryId;
@property (nullable, nonatomic, strong) NSNumber *displayOrder;
@property (nullable, nonatomic, strong) NSArray <WDProductCatalogueCategory *> *subcategories;
@end

/**
 *  @class WDBarCodeType
 *  @brief  Bar Code type
 **/
@interface WDBarCodeType : WDObject <NSCoding>
@property (nonatomic, strong) NSString *barCodeTypeId;
@property (nonatomic, strong) NSString *barCodeTypeName;
@end

/**
 *  @class WDProductCatalogueProduct
 *  @brief Product details
 **/
@interface WDProductCatalogueProduct: WDProductCatalogueCore <NSCoding>
/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDUnitPrice*> *)unitPrices
                       taxCategory:(WDTaxCategory*)taxCategory;

/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @param externalId External ID - product id recognized in external system - ERP or other
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDUnitPrice*> *)unitPrices
                       taxCategory:(WDTaxCategory*)taxCategory
                        externalId:(NSString*)externalId;

/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @param productCategories Categorize this product - more than one category can be assigned
 *  @param externalId External ID - product id recognized in external system - ERP or other
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDUnitPrice*> *)unitPrices
                       taxCategory:(WDTaxCategory*)taxCategory
                 productCategories:(NSArray <WDProductCatalogueCategory*> *)productCategories
                        externalId:(NSString*)externalId;

/**
 *  @brief Create Product
 *  @param name Product Name
 *  @param unitPrices the product Unit prices
 *  @param taxCategory Tax Category for this product
 *  @param productCategories Categorize this product - more than one category can be assigned
 *  @param externalId External ID - product id recognized in external system - ERP or other
 *  @param discount discount Product discount to be applied on certain product
 *  @return new Product
 **/
-(instancetype)initWithProductName:(NSString *)name
                        unitPrices:(NSArray <WDUnitPrice*> *)unitPrices
                       taxCategory:(WDTaxCategory*)taxCategory
                 productCategories:(NSArray <WDProductCatalogueCategory*> *)productCategories
                        externalId:(NSString*)externalId
                          discount:(nullable NSString *)discount;

@property (nullable, nonatomic, strong) WDBarCodeType *barCodeType;
@property (nullable, nonatomic, strong) NSString *barCodeValue;
@property (nullable, nonatomic, strong) NSString *externalId;
@property (nullable, nonatomic, strong) NSString *imageId;
@property (nullable, nonatomic, strong) NSString *productId;
@property (nullable, nonatomic, strong) NSString *productName DEPRECATED_ATTRIBUTE;
@property (nullable, nonatomic, strong) NSArray <WDProductCatalogueCategory*> *productCategories;
@property (nonatomic, strong) NSArray <WDUnitPrice*> *productUnitPrices;
@property (nonatomic, strong) WDTaxCategory *taxCategory;
@end

/**
 *  @class WDProductAvailability
 *  @brief Product availability
 **/
@interface WDProductAvailability: WDObject <NSCoding>
@property (nonatomic, strong) NSString *externalProductId;
@property (nonatomic, strong) NSNumber *stockQuantity;
@end

/**
 *  @class WDProductStock
 *  @brief Product stocks
 **/
@interface WDProductStock: WDObject <NSCoding>
@property (nonatomic, strong) NSArray <WDProductAvailability*>* productsAvailability;
@property (nonatomic, strong) NSString *siteId;
@property (nonatomic, strong) WDAddress *address;
@end

/**
 *  @class WDProductCatalogueDiscount
 *  @brief Product Catalogue discount - flat discount
 **/
@interface WDProductCatalogueDiscount: WDObject <NSCoding>
@property (nullable,nonatomic, strong) NSNumber *flatDiscount;
@end

/**
 *  @class WDProductPrice
 *  @brief ERP product price information
 **/
@interface WDProductPrice : WDObject <NSCoding>
/**
 */
@property (nullable, nonatomic, strong) NSString *currencyCode;
/**
 */
@property (nullable, nonatomic, strong) NSString *externalProductId;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *unitPrice;

@end

NS_ASSUME_NONNULL_END
