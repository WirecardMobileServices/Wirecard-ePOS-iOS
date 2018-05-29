//
//  UserTestsSwift.swift
//  DemoEPOS
//
//  Created by Fortes, Francisco on 7/25/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

import Foundation
import XCTest
import WDePOS

class CatalogueTestsSwift: BaseTestsSwift
{
    var serviceGroup : DispatchGroup!
    
    override func setUp()
    {
        super.setUp()
        self.serviceGroup = DispatchGroup()
    }
  
    func testCatalogue()
    {
        //PART 1: We log-in and request user data
        //--------------------------------------
        

        if (loggedUser == nil || (loggedUser?.isKind(of: WDMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }

        //PART 2: We request catalogue data
        //--------------------------------------
        expectation = self.expectation(description: "Requesting Catalogue Data")
        self.requestCatalogueData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if self.successfulDownload == nil || self.successfulDownload == false
        {
            XCTFail("Error while downloading catalogue data. Chances are there was a timeout on backend or your connection got interrupted. In any case, you may retry.")
        }
    }
    
    func requestCatalogueData()
    {
        guard let merchantId = self.loggedUser?.merchant?.merchantId else
        {
            XCTFail("Something went really wrong - requestCatalogueData")
            self.expectation.fulfill()
            return
        }
        
        self.successfulDownload = true
        
        let completionProductCatalogue : ProductCatalogueCompletion = {[weak self](arrCatalogues : [WDProductCatalogue]?, error : Error?) in
            self?.returnedErr = error
            self?.successfulDownload = error == nil
            if let arrCatalogues = arrCatalogues
            {
                if arrCatalogues.count == 0
                {
                    //No catalogues, so we finish the test. But for fully testing, please create a catalogue with categories and products in backend
                    self?.expectation.fulfill()
                }
                else
                {
                    for catalogue in arrCatalogues
                    {
                        if self?.successfulDownload == true
                        {
                            self?.loadContentForCatalogue(catalogue: catalogue)
                        }
                    }
                }
            }
            self?.serviceGroup.leave()
        }
        self.serviceGroup.enter()
        
        sdk.inventoryManager.productCatalogues(merchantId, completion: completionProductCatalogue)
        
        self.serviceGroup?.notify(queue: DispatchQueue.main, execute: {
                self.expectation.fulfill()
        })
    }
    
    func loadContentForCatalogue(catalogue : WDProductCatalogue)
    {
        let completionCatalogue : ProductCatalogueCategoryCompletion = {[weak self](result : [WDProductCatalogueCategory]? , error : Error?) in
            
            let completionProductContent : ProductCatalogueProductCompletion = {(result : [WDProductCatalogueProduct]?, totalCount : NSNumber?, error : Error?) in
                if  error != nil || self?.successfulDownload == false
                {
                    self?.returnedErr = error
                    self?.successfulDownload = false
                }
                else if let result = result, result.count > 0
                {
                    self?.loadContentForProducts(products: result,
                                                 catalogueId: catalogue.productCatalogueId!,
                                                 categoryId: nil)
                }
                self?.serviceGroup.leave()
            }

            let query : WDProductsQuery = WDProductsQuery.init(page: 0,
                                                                           pageSize: 100,
                                                                           catalogueId: catalogue.productCatalogueId!,
                                                                           categoryId: catalogue.productCatalogueId!)
            self?.serviceGroup?.enter()
            self?.sdk.inventoryManager.products(query,
                                                uncategorized: true,
                                                completion: completionProductContent)
            
            //Then we request categorized products
            if let result = result {
                for category : WDProductCatalogueCategory in result
                {
                    category.parentCategoryId = catalogue.productCatalogueId
                    self?.loadContentForCategory(category: category,
                                                 catalogueId:catalogue.productCatalogueId!,
                                                 dbVersion: Decimal(0))
                    //Note: you may want to keep track of versions to compare to existing data in backend and do proper upsert in your app
                }
            }
            
            self?.serviceGroup.leave()
        }

        self.serviceGroup.enter()
        sdk.inventoryManager.productCategoriesTree(catalogue.productCatalogueId!, completion: completionCatalogue)
    }
    
    func loadContentForProducts(products : [WDProductCatalogueProduct]?, catalogueId : String, categoryId : String?)
    {
        if let products = products, products.first != nil
        {
            self.serviceGroup.enter()
            var queries : [WDProductsQuery] = []
            for product : WDProductCatalogueProduct in products
            {
                if let productImageId : String = product.imageId, productImageId.count > 0
                {
                    let query : WDProductsQuery = WDProductsQuery.init(page: 0,
                                                                                   pageSize: 100,
                                                                                   catalogueId: catalogueId)
                    query.productCategoryId = categoryId
                    query.productCategoryId = categoryId
                    queries.append(query)
                }
            }
            
            let completionImage : ProductCatalogueImageCompletion = {[weak self](prodsImage : [WDProductImage]?, error : Error?) in
                self?.serviceGroup.leave()
            }
            
            if queries.count > 0 && self.successfulDownload == true
            {
                sdk.inventoryManager.productsImage(queries,
                                                   completion: completionImage)
            }
            else
            {
                self.serviceGroup.leave()
            }
        }
        else
        {
            self.successfulDownload = false
        }
    }
    
    func loadContentForCategory(category : WDProductCatalogueCategory?, catalogueId : String, dbVersion : Decimal)
    {
        if let category = category
        {
            let completionGetProducts : ProductCatalogueProductCompletion = {[weak self](result : [WDProductCatalogueProduct]?, totalCount : NSNumber?, error : Error?) in
                if error != nil || self?.successfulDownload == false
                {
                    self?.returnedErr = error
                    self?.successfulDownload = false
                }
                else
                {
                    if let result = result {
                        self?.loadContentForProducts(products: result,
                                                     catalogueId: catalogueId,
                                                     categoryId: category.categoryId!)
                    }
                }
                self?.serviceGroup.leave()
            }
            
            let query : WDProductsQuery = WDProductsQuery.init(page: 0,
                                                                           pageSize: 100,
                                                                           catalogueId: catalogueId,
                                                                           categoryId: category.categoryId!)
            for subcategory : WDProductCatalogueCategory in category.subcategories!
            {
                //Structure is 1 catalogue including 0 to many categories including zero to many products, and one product can belong to zero or many categories
                if category.categoryId != catalogueId && subcategory.parentCategoryId?.count == 0
                {
                    subcategory.parentCategoryId = category.categoryId
                }
                self.loadContentForCategory(category: subcategory,
                                            catalogueId: catalogueId,
                                            dbVersion: dbVersion)
            }
            
            self.serviceGroup.enter()
            sdk.inventoryManager.products(query,
                                          uncategorized: false,
                                          completion: completionGetProducts)
        }
        else
        {
            self.successfulDownload = false
        }
    }
}
