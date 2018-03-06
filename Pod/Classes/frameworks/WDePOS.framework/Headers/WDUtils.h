//
//  WDUtils.h
//   WDePOS
//
//  Created by Danko, Radoslav on 22/03/2017.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"

/**
 *  @class WDUtils
 *  @brief The package of WDePOS Utility functions
 **/
@interface WDUtils : NSObject
/**
 *  @brief Number of fraction digits for this currency
 *  @param currencyAsISO4217Code Currency code as per ISO 4217
 *  @return Number of fraction digits
 **/
+ (SInt16) numberOfFractionDigitsForCurrency:(NSString *)currencyAsISO4217Code;
/**
 *  @brief Does this vendor have BT terminal
 *  @param vendorUUID Vendor UUID
 *  @return YES if Vendor does have BT terminal which are supported by the SDK
 **/
+(BOOL)isVendorHavingBluetoothTerminals:(WDExtensionTypeUUID)vendorUUID;
/**
 *  @brief Format given number to String with defined Currency and current Locale
 *  @param currencyCode Currency code as per ISO 4217
 *  @param showSymbol Show symbol for currency if possible
 *  @return Formatted number with currency symbol or ISO code
 **/
+(NSString *)formatNumber:(NSDecimalNumber *)number withCurrencyCode:(NSString *)currencyCode showSymbol:(BOOL)showSymbol;

/**
 *  @brief Format given number to String with defined Currency and current Locale
 *  @param currencyCode Currency code as per ISO 4217
 *  @param showSymbol Show symbol for currency if possible
 *  @param locale Use the specififed locale - if nil then currentLocale is used
 *  @return Formatted number with currency symbol or ISO code
 **/
+(NSString *)formatNumber:(NSDecimalNumber *)number withCurrencyCode:(NSString *)currencyCode showSymbol:(BOOL)showSymbol locale:(NSLocale *)locale;
/**
 *  @brief Get the Decimal divider for the currency - to be used to divide amount units
 *  @param forCurrency Currency code as per ISO 4217
 *  @return Decimal divider as per the specified currency
 **/
+(NSDecimalNumber *)decimalDivider:(NSString *)forCurrency;

/**
 *  @brief Format Date with the specified format
 *  @param date Date to format
 *  @param format Format to use for the Date
 *  @return String from Date formatted as specified
 **/
+(NSString*)formatDate:(NSDate *)date format:(NSString*)format;

/**
 *  @brief Format Date with the current locale
 *  @return String from Date formatted in current locale with the separator
 **/
+(NSString*)formatDateWithCurrentLocale;

/**
 *  @brief Obtain the default design of html template name for Receipt or ZReport as specified
 *  @param name Name of the default html template to obtain
 *  @return HTML template
 **/
+(NSString*)htmlTemplate:(NSString *)name;

/**
 *  @brief Replace ##KEY## key in the html template with specified value
 *  @param html HTML template containing ##KEY## to be modified with value
 *  @param keyProcessor callback that presents the KEY to which it awaits VALUE
 **/
+ (void)replace:(NSMutableString*)html withKeyProcessor:(NSString*(^)(NSString * key))keyProcessor;

/**
 *  @brief Return the resource path if exists in the Main Bundle or acceptResources bundle
 *  @param resourceName The name of the resource
 *  @param type the resource type - file extension
 **/
+(NSString*)pathForResource:(NSString *)resourceName ofType:(NSString *)type;

/**
 *  @brief Return the device hardware string
 *  @return Device hardware string
 **/
+ (NSString*)hardwareString;
/**
 *  @brief Generate the Unique ID
 *  @return Unique ID
 **/
+(NSString *)uniqueID;

@end
