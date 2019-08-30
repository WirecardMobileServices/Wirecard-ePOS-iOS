//
//  MerchantHelper.m
//  DemoEPOS
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "UserHelper.h"

@implementation UserHelper
{
    NSUserDefaults *userDefaults;
    WDMerchantUser *currentUser;
}

static UserHelper *sharedInstance = nil;

- (instancetype)initPrivate
{
    self = [super init];
    userDefaults = [[NSUserDefaults alloc] initWithSuiteName:@"ePosDemo"];
    return self;
}

+ (UserHelper *)sharedInstance
{
    static dispatch_once_t pred;
    dispatch_once(&pred, ^{
        sharedInstance = [[UserHelper alloc] initPrivate];
    });
    
    return sharedInstance;
}

-(void)setUser:(WDMerchantUser*)merchantUser
{
    currentUser = merchantUser;
}

-(const WDMerchantUser*)getCurrentUser
{
    return currentUser;
}

-(NSDecimalNumber*)preferredSaleItemTax
{
    //You are free to select the tax from the avalilables in taxCategories and taxRates, that will depend on the country of your merchant
    return currentUser.merchant.taxCategories.count > 0 && [[currentUser.merchant.taxCategories firstObject] currentValue] != nil ? 
        [[currentUser.merchant.taxCategories firstObject] currentValue] : NSDecimalNumber.zero;
}

-(NSDecimalNumber*)tipTax
{
    //You are free to select
    return [NSDecimalNumber decimalNumberWithString: [[currentUser.merchant tipTaxRate] stringValue] ?: @"0"];
}

-(NSDecimalNumber*)serviceChargeRate 
{
    //You are free to select
    return [NSDecimalNumber decimalNumberWithString: [[currentUser.merchant serviceChargeRate] stringValue] ?: @"0"];
}

-(NSDecimalNumber*)serviceChargeTax
{
    //You are free to select
    return [NSDecimalNumber decimalNumberWithString:  [[currentUser.merchant serviceChargeTaxRate] stringValue] ?: @"0"];
}

-(void)storeOpenShiftId:(NSString*)shiftId
{
    [userDefaults setObject:shiftId forKey:@"shiftId"];
}

-(NSString*)lastShiftId
{
    return [userDefaults objectForKey:@"shiftId"];
}

-(void)storeCashRegisterId:(NSString*)cashRegisterId
{
    [userDefaults setObject:cashRegisterId forKey:@"cashRegisterId"];
}

-(NSString*)selectedCashRegisterId
{
    return [userDefaults objectForKey:@"cashRegisterId"]? [userDefaults objectForKey:@"cashRegisterId"] : @"";
}

@end
