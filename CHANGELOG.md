# Change Log
All notable changes to Wirecard epos will be documented in this file.

## [2.11.2] - 2020-03-09

### Deprecated

- IMPORTANT: this may affect your current UI implementation => `WDStateTapOrInsertOrSwipeCard` was removed, please use `WDStatePresentCard`.

### Added
 
- Adopted PSD2 requirements for Strong customer authentication (SCA).

### Changed

- Subtotal amounts are now not combined with total discount amount.

### Fixed

- Terminal updates do not time out unnecessarily with slow download speeds.
- Several fixes in the Example unit test app

## [2.11.1] - 2020-02-04

### Fixed

- Adapting to latest Mantle version

## [2.11.0] - 2019-12-19

### Added

- New payment types: Preauthorization, supplement & capture

## [2.10.4] - 2019-11-5

### Fixed

- WKWebKit fix for long receipts and z-reports

## [2.10.3] - 2019-11-4

### Fixed

- Swift 5.1.2 compiler compatibility
- Missing architectures

## [2.10.0] - 2019-10-16

### Fixed

- Slow mPOP connection fix
- iOS 13 mandatory changes (ie UIWebView replaced by WKWebView in receipt/z-report pdf generation)
- EFT Card (SEPA) payments authorized by signature instead of PIN
- Possibility to complete/modify an open sale during a different shift and/or using a different cash register.

## [2.9.0] - 2019-08-20

### Added

- New payment method: EFT Card payment
- Include Notification (Callback) URL in Sale Purchase request
- Printer Star SM-L200 support

### Fixed

- Datecs printer library update
- Minor bug fixes

## [2.8.0] - 2019-05-29

### Added
- Card Authorisation and Card Capture as new payment methods
- Better handling of disconnections on Datecs printer
- Separate Header/Footer images on receipt
- Different receipts for full sales and payments
- Brandable localisation files for setting your own translations on receipt content

### Fixed
- Pos entry mode fix based on 9f26 and online tag (Spm2)
- Several fixes on WDBrand classes

### Deprecated
- `addCardPayment:terminal:terminal`, use `addCardPayment:amount:originalPaymentId`
- `addCouponPayment:couponId:brandId`, use `addCouponPayment:amount:couponId:brandId`
- `addAlipayPayment:consumerId`, use `addAlipayPayment:amount:consumerId:originalPaymentId`
- `addWeChatPayment:consumerId`, use `addWeChatPayment:amount:consumerId:originalPaymentId`


## [2.7.0] - 2019-04-17 

### Added
- Multitender support: Combining payment methods into one Sale
- Referenced sale request: References the Original Sale to process another payment
- Product Stock management

### Deprecated
- WDSaleRequest: can now contain only one payment method 
- WDPaymentConfig: use WDSaleRequestConfiguration
- WDSaleManager
	* `pay:delegate:` use `pay:withDelegate:` - uses the new WDSaleRequestConfiguration instead of deprecated WDPaymentConfig
	* `reverseSale:cashRegisterId:message:completion:` use `reverseSale:message:completion:`
	* `addSaleItem:quantity:taxRate:itemDescription:productId:` use `addSaleItem:quantity:taxRate:itemDescription:productId:externalProductId`
	* `addSaleItem:discountRate:quantity:taxRate:itemDescription:productId:` use `addSaleItem:discountRate:quantity:taxRate:itemDescription:productId:externalProductId:`
	* processedCashPayment changed to processedCashPayments - returns array of the processed cash payments now
	* processedCardPayment changed to processedCardPayments - returns array of the processed card payments now
	* processedAlipayPayment changed to processedAlipayPayments - returns array of the processed Alipay payments now
	* processedWeChatPayment changed to processedWeChatPayments - returns array of the processed WeChat payments now
- WDSaleResponse's property internalId is now saleId
- WDSaleRequest's property cashierId is deprecated

### Changed
- Detection of POS entry mode for Contactless card transaction - POS entry mode value based on another data that could be provided by Spm2 terminal
- Track all transactions Declined Offline by terminal on backend

### Fixed
- Tax summary and Service charge calculations on the receipt


## [2.6.0] - 2018-11-07 

### Changed
- New Sale and transaction states added

## [2.5.1] - 2018-10-03 

### Fixed
- eClear example

## [2.5.0] - 2018-10-01 
### Added
- New field in WDMerchantUser - date of the last user's password change
- Tax categories getter for specified country code
- Cash register details added
- Receipt and Z-Report template uses Mustache template
- Sale search filter for payment method added

### Fixed
- Disable device to enter "sleep" state during terminal firmware update
- Minor bugfixes

### Changed 
- Cash register's activities numbers uses NSDecimalNumber instead of NSNumber
- Datecs library from vendor updated
- WDBrand framework embeded in WDePOSUI framework


## [2.4.4] - 2018-09-20 
### Fixed
- Fixes for Xcode 10
- Added UI and WDBrand content

## [2.4.3] - 2018-08-07 
### Fixed
- Change password
- Partial refund

## [2.4.2] - 2018-06-26 
### Added
- New sale state: Partially Refunded

## [2.4.1] - 2018-06-01 
### Fixed
- Cash register update

## [2.4.0] - 2018-05-29 
### Added
- Carthage support
- Spire configuration archive validation 
- Automatic Terminal registration - if free TID/MID record available

### Changed
- Z-Report improvements
- SSL certificates

### Fixed
- Resume printing - Datecs 250
- PIN verified flag present on Datecs receipt
- ContactLess cases - signature request and confirmation
- WeChat CNY amount
- Alipay long business name

## [2.3.3] - 2018-04-17 
### Fixed
- Mastercard contactless with online PIN
- Receipt texts
- Cash register handling
- Enter signature timeout
- Payment confirmation timeout
- Swift 4.1 migration

## [2.3.1] - 2018-03-09 
### Fixed
- Magstripe fallback requires PIN based on service code
- Authorization response code for Amex terminated transactions

## [2.3.0] - 2018-03-07 
### Changed
- SDK product name

### Fixed
- Signature confirmation fix
- Flat discount removal
- PosMate configuration update

## [2.2.3] - 2018-02-15 
### Fixed
- Language Change for default receipt
- AMEX payment flow
- Spire extension memory management
- Environment setup - *AFNetworking SSLPinning issue
- EMV parser

## [2.2.2] - 2018-01-23 
### Added
- UI Component - initial phone design
- UI Component - eClear demo application
- Item Discounts functionality

### Changed
- Using delegation in Sale Manager instead of closures
- SPm2 BT background communication

### Fixed
- Discount, Grauity calculations

## [2.2.0] - 2017-12-06 
### Added
- WeChat payment method
- Sale Manager uses delegation instead of closures
- Item Discounts functionality

### Fixed
- Product Catalogue maintenance

## [2.1.0] - 2017-09-22 
### Added
- Product Catalogue maintenance updates
- Datecs DPP-250 Refund Receipts with Original receipt created
- AOSA added to Contactless Offline flow
- Demo application tests updated

## [2.0.0] - 2017-08-24 "Initial Commit"

* Card Payment - mPOS terminals
* Cash Payment
* Alipay Payment
* Cash Management
* Sale History
* Sale Statistics
* Product Catalogue

