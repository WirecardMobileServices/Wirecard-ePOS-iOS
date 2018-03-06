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

class ERPTestsSwift: BaseTestsSwift
{
    var member : WDMember?
    var discountsReceived : Bool?
    var stocksReceived : Bool?
    
    override func setUp()
    {
        super.setUp()
    }
 
    /*
     
     Note: The following test is an example of a how to use ERP/SAP queries. For them to work, you need to have
     ERP enabled in backend side, and actual data such as catalogue, members, products, etc. linked to your account.
     Responses coming from external systems can generate unexpected results, so make sure to have correct data
     already defined.
     
     The ERP features compatible with the accept SDK includes:
     - The ability to search for a Member ID, name or surname. Exact matched will return the member you are looking for,
     and aproximate sarch will return an array of the matches (ie for displaying them in a dynamic search table)
     - The ability to request special prices for an array of products ID, that will return discount prices if a member ID has that privilege.
     - The ability to request stock for an array of products in a single shop, or for a single product in all merchant's shops.
     */
    
    func testSearchMembers()
    {
        //PART 1: We log-in and request user data
        //--------------------------------------
        expectation = self.expectation(description: "Requesting User Data")
        self.loginAndGetUserData()
        self.waitForExpectations(timeout: 100, handler: nil)
        if (loggedUser == nil || (loggedUser?.isKind(of: WDMerchantUser.self)) == false)
        {
            XCTFail("Error, did not return Merchant User. Are your credentials correct? Try login into the backend through internet browser.")
        }
        else
        {
            UserHelper.sharedInstance().setUser(self.loggedUser)
        }
        
        if self.loggedUser?.merchant?.erpSystemType?.uppercased() == "SAP_BY_DESIGN"
        {
            //PART 2: We search members
            //--------------------------------------
            expectation = self.expectation(description: "We search members")
            self.searchMembersMatching(searchString: "John") //feel free to modify this to your own name or your customer's
            self.waitForExpectations(timeout: 100, handler: nil)
            if self.member == nil
            {
                XCTFail("No member found. Make sure you have ERP SAP set in your merchant with valid members")
            }
            
            //PART 3: We request discount prices for a member
            //----------------------------------------------
            expectation = self.expectation(description: "We request discount prices for a member")
            self.fetchDiscountPrices()
            self.waitForExpectations(timeout: 100, handler: nil)
            if self.discountsReceived == nil || self.discountsReceived! == false
            {
                XCTFail("No product stocks received. Make sure you have ERP SAP set in your merchant with valid products and stock availability enabled")
            }
            
            //PART 4: We request stocks for some products
            //----------------------------------------------
            expectation = self.expectation(description: "We request discount prices for a member")
            self.fetchProductsStocks()
            self.waitForExpectations(timeout: 100, handler: nil)
            if self.discountsReceived == nil || self.discountsReceived == false
            {
                XCTFail("No product stocks received. Make sure you have ERP SAP set in your merchant with valid products and stock availability enabled")
            }
        }
        //else nothing to test, your merchant is not properly configured in backend. Please ask support for enabling ERP/SAP in your account
    }
    
    func searchMembersMatching(searchString :  String?)
    {
        let completion : MembersCompletion = {[weak self](members : [WDMember]?, error : Error?) in
            self?.member = members?.first
            self?.returnedErr = error
            self?.expectation.fulfill()
        }
        sdk.customerManager.memberInformation(nil,
                                              surname: nil,
                                              firstName: searchString,
                                              exactMatch: false,
                                              completion: completion)
    }
    
    func fetchDiscountPrices()
    {
        guard let memberId = self.member?.memberId else
        {
            XCTFail("Something went really wrong - fetchDiscountPrices")
            self.expectation.fulfill()
            return
        }
        
        let productsIDs = ["productA", "productB"] //Don't forget to put actual productsIds from your catalogue here
        sdk.inventoryManager.productPrice(forMember: memberId,
                                          externalIDs: productsIDs,
                                          currency: "EUR",
                                          grossPrice: true,
                                          completion: {[weak self](productPrices : [WDProductPrice]?, error : Error?) in
            if let productPrices = productPrices
            {
                self?.discountsReceived = productPrices.count > 0
            }
            else
            {
                self?.discountsReceived = false
            }
            
            self?.returnedErr = error
            self?.expectation.fulfill()
        })
    }
    
    func fetchProductsStocks()
    {
        let completion : ProductStocksCompletion = {[weak self](stocks : [WDProductStock]?, error : Error?) in
            if let stocks = stocks
            {
                self?.stocksReceived = stocks.count > 0
            }
            else
            {
                self?.stocksReceived = false
            }
            self?.returnedErr = error
            self?.expectation.fulfill()
        }
        
        let aProduct : WDProductCatalogueProduct = WDProductCatalogueProduct.init()
        aProduct.externalId = "product external (SAP) ID"
        sdk.inventoryManager.productStock(inAllShops: aProduct,
                                          completion: completion)
        
        //Alternatively you can ask stock for a series of products in a single shop, instead of a single product in all shops as above.
        //But please note that your ERP SAP may be limited to around 10 products per stock query, so make sure you use this request responsibly
        //[[sdk inventoryManager] productsStock:productsArray inShop:@"ShopID" completion:completion];
    }
}
