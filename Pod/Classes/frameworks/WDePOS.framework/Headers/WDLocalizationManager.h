//
//  WDLocalizationManager.h
//  WDePOS
//
//  Created by Danko, Radoslav on 28/11/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

extern const int64_t kWDLANGUAGE_BUNDLE_KEY;

/**
 *  @class WDLocalizationManager
 *  @brief Localize Receipt and Z-Reports produced from SDK
 **/
@interface WDLocalizationManager : NSObject

/// List of supported languages - for Receipt | Z-Report  localization
- (NSArray<NSString *> *)supportedLanguages;
/// Set the required language - for Receipt | Z-Report  localization
- (void)setLanguage:(NSString *)language;
@end


NSString* WDLocalizedString(NSString *key);

