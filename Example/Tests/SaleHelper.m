//
//  SaleHelper.m
//  DemoEPOS
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "SaleHelper.h"
#import "AppDelegate.h"
#import "UserHelper.h"
#import "TestUtils.h"
#import <WDePOS/NSString+WDExtras.h>

@implementation SaleHelper
{
    WDSaleRequest *_currentSale;
    WDSaleResponse *_currentSaleResponse;
    NSString *_cashRegisterId, *_shopId, *_cashierId, *_customerId;
    NSString *_selectedCurrencyCode, *_loginCredentials;
    WDSaleRequestConfiguration *_paymentConfiguration;
    NSDecimalNumber *_gratuityTaxRate;
    NSUserDefaults *userDefaults;
    NSDateFormatter *_dateFormatter;
}

static SaleHelper *sharedInstance = nil;

- (instancetype)initPrivate
{
    self = [super init];
    userDefaults = [[NSUserDefaults alloc] initWithSuiteName:@"ePosDemo"];
    _dateFormatter = [[NSDateFormatter alloc] init];
    [_dateFormatter setLocale:[NSLocale currentLocale]];
    [_dateFormatter setDateFormat:@"yyyyMMddHHmmss"];
    return self;
}

+ (SaleHelper *)sharedInstance
{
    static dispatch_once_t pred;
    dispatch_once(&pred, ^{
        sharedInstance = [[SaleHelper alloc] initPrivate];
    });
    
    return sharedInstance;
}

-(NSString *)formatNumberToCurrency:(NSDecimalNumber *)number withCurrencySymbol:(BOOL)withCurrencySymbol
{
    if (!number || [number isEqualToNumber:[NSNumber numberWithInt:0]]) {
        number = [NSDecimalNumber decimalNumberWithString:@"0.00"];
    }
    NSNumberFormatter *numFormatter = [[NSNumberFormatter alloc] init];
    
    [numFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    
    NSLocale *lcl = [NSLocale currentLocale];
    
    //IMPORTANT: you may encounter currencies with 0, 1 or 3 decimal places around the world
    int minorUnits = 2;
    
    [numFormatter setLocale:lcl];
    [numFormatter setCurrencyCode:_selectedCurrencyCode? _selectedCurrencyCode : @"EUR"];
    [numFormatter setMinimumIntegerDigits:1];
    [numFormatter setMinimumFractionDigits:minorUnits];
    [numFormatter setMaximumFractionDigits:minorUnits];
    //    [numFormatter setPositiveFormat:@"0.00"];
    
    if (minorUnits == 0) {
        [numFormatter setAlwaysShowsDecimalSeparator:NO];
    }
    else{
        [numFormatter setAlwaysShowsDecimalSeparator:YES];
    }
    [numFormatter setRoundingMode:NSNumberFormatterRoundHalfUp];
    [numFormatter setUsesGroupingSeparator:NO];
    
    if(!withCurrencySymbol){
        [numFormatter setCurrencySymbol:@""];
    }
    NSString *strNumber = [numFormatter stringFromNumber:number];
    
    return strNumber;
}

-(NSString*)formatDate:(NSDate *)date withFormat:(NSString*)withFormat
{
    NSString *oldFormat = _dateFormatter.dateFormat;
    [_dateFormatter setDateFormat:withFormat];
    NSString *ret = [_dateFormatter stringFromDate: date];
    [_dateFormatter setDateFormat:oldFormat];
    
    return ret;
}

-(WDSaleRequest *)newSale
{
    _currentSale = nil;
    
    NSString *transactionUniqueId = [TestUtils uniqueID];
    
    //Note: having a location in your sale is totally optional - it will expose the coordinates where the transaction was done.
    CLLocation *terminalLocation = [(AppDelegate *)[[UIApplication sharedApplication] delegate] currentLocation];
    
    _currentSale = [[WDSaleRequest alloc] initWithUniqueId:transactionUniqueId
                                                                        location:terminalLocation
                                                                  inclusiveTaxes:KTAX_INCLUSIVE_ENABLED
                                                                        currency:@"EUR"
                                                                            note:KSALE_DESCRIPTION
                                                                 gratuityTaxRate:_gratuityTaxRate];
    _currentSale.shopId = _shopId;
    _currentSale.customerId = _customerId;
    
    return _currentSale;
}

-(WDSaleRequest *)currentSale
{
    if (!_currentSale)
    {
        
        return [self newSale];
    }
    
    return _currentSale;
}

-(void)saleToSaveIdFrom:(WDSaleResponse*)sale
{
    [userDefaults setObject:sale.saleId forKey:@"saleToSaveIdFrom"];
}

-(NSString*)saleIdSaved
{
    return [userDefaults objectForKey:@"saleToSaveIdFrom"];
}

@end
