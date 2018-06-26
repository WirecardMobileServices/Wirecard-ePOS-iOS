# Change Log
All notable changes to Wirecard epos will be documented in this file.

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

