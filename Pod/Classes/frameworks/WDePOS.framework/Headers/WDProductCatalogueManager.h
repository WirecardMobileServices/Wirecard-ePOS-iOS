//
//  WDProductCatalogueManager.h
//   WDePOS
//
//  Created by Danko, Radoslav on 20/10/16.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"
NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDProductCatalogueManager
 *  @brief Product Catalogue Management
 */
@interface WDProductCatalogueManager : NSObject
#pragma mark - ☰ Inventory -

#pragma mark  ⎿ Product Catalogue
/**
 *  @brief Get product catalogues
 *  @param merchantId Merchant ID for which to get available product catalgoues
 *  @param completion Block that will return the product catalogues
 **/
-(void)productCatalogues:(NSString *)merchantId completion:(nonnull ProductCatalogueCompletion)completion;
/**
 *  @brief Create product catalogue
 *  @param productCatalogue product catalogue data to be created
 *         productCatalogueId to be left nil
 *  @param completion Block that will return the created product catalogue
 **/
-(void)makeProductCatalogue:(WDProductCatalogue *)productCatalogue completion:(ProductCatalogueCompletion)completion;
/**
 *  @brief Update product catalogue
 *  @param productCatalogue product catalogue to be deleted
 *         productCatalogueId and lastUpated attributes are required only
 *  @param completion Block that will return the crated product catalogue
 **/
-(void)updateProductCatalogue:(WDProductCatalogue *)productCatalogue completion:(ProductCatalogueCompletion)completion;
/**
 *  @brief Delete product catalogue
 *  @param productCatalogue product catalogue data to be updated
 *  @param completion Block that will return empty array if success or error in the case of failures
 **/
-(void)deleteProductCatalogue:(WDProductCatalogue *)productCatalogue completion:(ProductCatalogueCompletion)completion;

#pragma mark - ⎿ Product Categories
/**
 *  @brief Get product catalogue categories tree
 *  @param productCatalogueId product catalogue for which to get the categories tree
 *  @param completion Block that will return the product catalogue categories tree
 **/
-(void)productCategoriesTree:(NSString *)productCatalogueId completion:(nonnull ProductCatalogueCategoryCompletion)completion;
/**
 *  @brief Get product catalogue category
 *  @param categoryId product category Id to get the data for
 *  @param productCatalogueId product catalogue for which to get the category
 *  @param completion Block that will return the product catalogue category
 **/
-(void)productCategory:(NSString *)categoryId
       inProductCatalogue:(NSString *)productCatalogueId
               completion:(nonnull ProductCatalogueCategoryCompletion)completion;
/**
 *  @brief Create product catalogue category
 *  @param productCatalogueCategory product catalogue category data to be created
 *  @param productCatalogueId in which to create the category
 *  @param completion Block that will return the created product catalogue category
 **/
-(void)makeCategory:(WDProductCatalogueCategory *)productCatalogueCategory
                 inCatalogue:(NSString *)productCatalogueId
                  completion:(ProductCatalogueCategoryCompletion)completion;

/**
 *  @brief Update product catalogue category
 *  @param productCatalogueCategory product catalogue category data to be updated
 *  @param productCatalogueId in which to update the category
 *  @param completion Block that will return the updated product catalogue category
 **/
-(void)updateProductCatalogueCategory:(WDProductCatalogueCategory *)productCatalogueCategory
                          inCatalogue:(NSString *)productCatalogueId
                           completion:(ProductCatalogueCategoryCompletion)completion;
/**
 *  @brief Delete product catalogue category
 *  @param productCatalogueCategory product catalogue category data to be deleted
 *  @param productCatalogueId in which to delete the category
 *  @param completion Block that will return the empty array if success or error in the case of failure
 **/
-(void)deleteProductCatalogueCategory:(WDProductCatalogueCategory *)productCatalogueCategory
                          inCatalogue:(NSString *)productCatalogueId
                           completion:(ProductCatalogueCategoryCompletion)completion;
#pragma mark - ⎿ Products
/**
 *  @brief Query products in the product catalogue
 *  @param query product search criteria
 *  @param completion Block that will return the array of products
 **/
-(void)products:(WDProductsQuery *)query
     uncategorized:(BOOL)uncategorized
        completion:(ProductCatalogueProductCompletion)completion;

/**
 *  @brief Query changes in products for a product catalogue happened after a date in the query
 *  @param query product search criteria
 *  @param completion Block that will return the array of products
 **/
-(void)productsChanges:(WDProductsQuery *)query
               completion:(ProductCatalogueProductChangeCompletion)completion;

/**
 *  @brief Create product catalogue product
 *  @param product product data to be created
 *  @param productCatalogueId in which to create the product
 *  @param productImage Product image
 *  @param completion Block that will return the created product
 **/
-(void)makeProduct:(WDProductCatalogueProduct *)product
       inCatalogue:(NSString *)productCatalogueId
      productImage:(nullable NSString *)productImage
        completion:(ProductCatalogueProductCompletion)completion;

/**
 *  @brief Update product catalogue product
 *  @param product product data to be updated
 *  @param productCatalogueId in which to update the product
 *  @param completion Block that will return the updated product
 **/
-(void)updateProduct:(WDProductCatalogueProduct *)product
         inCatalogue:(NSString *)productCatalogueId
        productImage:(nullable NSString *)productImage
          completion:(ProductCatalogueProductCompletion)completion;

/**
 *  @brief Delete product catalogue product
 *  @param product product data to be updated - productId is sufficient
 *  @param productCatalogueId in which to delete the product
 *  @param completion Block that will return the empty array if success or error in the case of failure
 **/
-(void)deleteProduct:(WDProductCatalogueProduct *)product
         inCatalogue:(NSString *)productCatalogueId
          completion:(ProductCatalogueProductCompletion)completion;

/**
 *  @brief Get product catalogue image
 *  @param query Values for the query of the product image
 *  @param completion Block that will return the Product image response
 **/
-(void)productImage:(WDProductsQuery *)query
            completion:(ProductCatalogueImageCompletion)completion;

/**
 *  @brief Get products catalogue image -
 *  @param queries Query multiple products at the same time - Values for the query of the product image
 *  @param completion Block that will return the Product image responses
 **/
-(void)productsImage:(NSArray <WDProductsQuery *>*)queries
             completion:(ProductCatalogueImageCompletion)completion;

#pragma mark - ⎿ Products - ERP queries
/**
 *  @brief Get products availability stock
 *  @param products Array with the products we want the stock from. Note that there may be limitations, please check error in case the array is too big. Equal or less then 10 are fine.
 *  @param shopId The shop we want the stocks info.
 *  @param completion Block that will return the stock availability per product Id
 **/
-(void)productsStock:(NSArray<WDProductCatalogueProduct *>*)products
              inShop:(NSString *)shopId
          completion:(ProductStocksCompletion)completion;


/**
 *  @brief Get a product availability in all merchant shops
 *  @param product Single produc to ask for Stock.
 *  @param completion Block that will return the stock availability per product Id in all merchant shops
 **/
-(void)productStockInAllShops:(WDProductCatalogueProduct*)product
                   completion:(ProductStocksCompletion)completion;

/**
 *  @brief Maintain product stocks for the <b>Internal Catalogue</b> Product
 *  @param stocks product stocks to create
 *  @param catalogueId product catalogue identifier
 *  @param productId product identifier
 *  @param completion Block that will return the created Product Stocks
 **/
-(void)maintainStocks:(NSArray<WDProductStockMaintain *> * _Nonnull)stocks
             catalogueId:(NSString* _Nonnull)catalogueId
               productId:(NSString *_Nonnull)productId
              completion:(ProductStocksCompletion _Nullable)completion;

/**
 *  @brief Get products prices for the specified customer ID
 *  @param memberId Member's ID in the ERP
 *  @param externalIDs Array with the external product IDs we want to get the prices for.
 *  @param currency The currency Code.
 *  @param grossPrice Get the gross or netto price.
 *  @param completion Block that will return the products prices availability per external product Id
 **/
- (void)productPriceForMember:(NSString *)memberId
                    externalIDs:(NSArray<NSString *> *)externalIDs
                   currency:(NSString *)currency
                 grossPrice:(BOOL)grossPrice
                     completion:(ProductPricesCompletion)completion;

/**
 *  @brief Get supported BarCode types for the merchant.
 *  @param completion Block that will return the array of BarCode types.
 **/
-(void)barCodeTypes:(nonnull BarCodeTypeCompletion)completion;

/**
 *  @brief Get tax categories for given country code.
 *  @param countryCode The country Code.
 *  @param completion Block that will return the array of Tax categories.
 **/
-(void)taxCategoriesFor:(NSString *_Nullable)countryCode withCompletion:(nonnull TaxCategoryCompletion)completion;

@end
NS_ASSUME_NONNULL_END
