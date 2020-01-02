
# Wirecard ePOS SDK

<img src="https://raw.githubusercontent.com/WirecardMobileServices/Wirecard-ePOS-iOS/master/docs/logo.png" alt="Wirecard-ePOS-iOS" width=400 height=64>

[![CI Status](http://img.shields.io/travis/WirecardMobileServices/Wirecard-ePOS-iOS.svg?style=flat)](https://travis-ci.org/WirecardMobileServices/Wirecard-ePOS-iOS)
[![Version](https://img.shields.io/cocoapods/v/WDePOS.svg?style=flat)](http://cocoapods.org/pods/WDePOS)
[![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)
[![License](https://img.shields.io/cocoapods/l/WDePOS.svg?style=flat)](http://cocoapods.org/pods/WDePOS)
[![Platform](https://img.shields.io/cocoapods/p/WDePOS.svg?style=flat)](http://cocoapods.org/pods/WDePOS)

## Overview
The library enables cashless payment processing with selected mPOS terminals (magStripe and Chip and PIN) via the fully-licensed Wirecard Bank, Wirecard Retail Services which allows acceptance of many different cards, including Visa, MasterCard and American Express. In addition alternative payment method Alipay is also available.

[<img src="https://raw.githubusercontent.com/WirecardMobileServices/Wirecard-ePOS-iOS/master/docs/survey.png" style="display:block;margin-left:auto;margin-right:auto;"/>](https://docs.google.com/forms/d/e/1FAIpQLSf5T7hXKn0WcOl4JwVVAfJFYkz62rN_4anLlzZrTIv2YhrGpA/viewform?embedded=true)

The SDK and Wirecard Payment infrastructure supports:

### Card present transactions
Debit and credit cards are standard 

* VISA, Mastercard
* Rupay
* American Express

### Alternative payment methods

* Alipay
* WeChat

### Payment operations

* Purchase
* Authorisation and Pre-Authorisation
* Capture
* Reversal
* Refund   

## ePOS backend - Switch
Switch system is mobile Cashier backend sale system for merchants, which provides the following base features:

* Management of Partners, Merchants, Users, Cashiers, Cash registers, mPOS Terminals and Merchant's Product catalogues
* Processing Sales with combined payment methods (currently support for: Card, Cash and Gift card payments, but API is open to adding of new payment methods)
* Card payments can be routed to the right Payment gateway based on rules configured for Merchant
* Merchant's ERP system integration (Sale notifications, Products stock and Cashiers activity tracking).  
  Currently cloud SAP (Business by Design) is supported.
* Loyalty (Voucher) system services - providing GiftCards selling and GiftCard payment method for attracting customers.
* Sales history with the possibility to invoke actions (like Reversal, Refund, Receipt generation, etc.)
* Possibility to communicate with HSM module for data decryption and reencryption
* Terminals supported: Spire SPm2, Spire Posmate, bbpos Chipper, IDTECH UnimagPro, Miura (HSM is needed)

Find more information about Switch in the [Switch Fact Sheet](https://github.com/WirecardMobileServices/Wirecard-ePOS-iOS/blob/master/docs/Fact-Sheet-ePOS.pdf) and [Switch ePOS backend overview](https://github.com/WirecardMobileServices/Wirecard-ePOS-iOS/blob/master/docs/SWITCH-Overview.pdf)

## Whitelabel solution
Wirecard Technologies is using the Wirecard-ePOS in their Whitelabel application which is fully integrated professional mPOS solution. The **Whitelabel** app is **VISA and Mastercard certified** and utilises the Wirecard infrastructure for card payment processing.

[<img src="https://raw.githubusercontent.com/WirecardMobileServices/Wirecard-ePOS-iOS/master/docs/sdkarchv09.png" alt="Whitelabel architecture" width=400 height=422>](./docs/sdkarchv09.png "Whitelabel Architecture")

## Payment UI
The SDK provides minimalistic Payment UI consiting of the following screens:

- Amount Entry
- Payment Method selection
- Signature Capture
- Payment Process
- Cash Register selection
- Card application selection
- Open/Close Shift
- Payment QRCode scanner

Please refer to eClear example application to see the implementation details.

## Installation

There are two ways how to install the SDK.

1. Clone from GitHub and integrate the framework as per the information available at the [Developer Portal](https://wirecardmobileservices.github.io/Wirecard-ePOS-Developer/int-setup-ios-cocoa/ "Developer Portal")
2. Wirecard ePOS SDK is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

```
platform :ios, '9.0'
use_frameworks!
target 'YourTarget' do
    pod 'WDePOS/All'
end
```
It is possible to use Wirecard ePOS with core functionality and one of supported terminal extension.
E.g. to use Wirecard ePOS and Spire SPm2 smart terminal please modify your podfile as follows:

```
platform :ios, '9.0'
use_frameworks!
target 'YourTarget' do
    pod 'WDePOS/Spire'
end
```

Visit our [Wirecard ePOS Developer Portal](https://wirecardmobileservices.github.io/Wirecard-ePOS-Developer "Developer Portal") for more information on how to integrate the Wirecard ePOS SDK into your application 

## Contact

Get in touch with [Wirecard ePOS development team](mailto:mpos-svk@wirecard.com "Wirecard-ePOS") for Wirecard ePOS support and ePOS Whitelabel solution

Get in touch with [Wirecard ePOS retail team](mailto:retail.mpos@wirecard.com "mPOS Retails") for Wirecard payment processing services


## Documentation

All the necessary information can be found on [Wirecard ePOS Developer Portal](https://wirecardmobileservices.github.io/Wirecard-ePOS-Developer "Developer Portal")

The Switch ePOS backend documentation:

* [Switch REST tests](https://switch-test.wirecard.com/mswitch-server/swagger/index.html)
* [Switch Sale API](https://switch-test.wirecard.com/mswitch-server/doc/api-doc-sale.html)


## Requirements

* Computer running OSX
* XCode 9
* Device running iOS > 9.0
* One of Wirecard approved terminals, printers, cash drawers, barcode scanners
	* Spire [PosMate](http://www.spirepayments.com/product/posmate/ "PosMate")
	* Spire [SPm2](http://www.spirepayments.com/product/spm2/ "SPm2")
	* Datecs printer [DPP-250](http://www.datecs.bg/en/products/DPP-250/2/175 "DPP-250")
	* StarMicronics [TSP650](http://www.starmicronics.com/pages/TSP650-Series "TSP650")
	* StarMicronics [mPOP](http://www.starmicronics.com/pages/mPOP "mPOP") 	* StarMicronics [SMD2](http://www.starmicronics.com/pages/SMD2-1214 "SMD2")
	* SocketMobile [Series 7](https://www.socketmobile.com/products/series-7/series-7-colorful/overview "Series 7")	
	

## Authors

   Wirecard Technologies Slovakia,  mpos-svk@wirecard.com 
   
   Radoslav Danko
   
   Francisco Fortes
   
   Marek Timko
   
   Jaroslav Pulik

## License

Wirecard-ePOS is available under the MIT license. See the LICENSE file for more info.
