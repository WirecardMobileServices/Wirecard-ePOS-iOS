//
//  WDLocalizationManager.h
//  WDePOS
//
//  Created by Danko, Radoslav on 28/11/2017.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

extern const int64_t kWDLANGUAGE_BUNDLE_KEY;

/**
 *  @class WDLocalizationManager
 *  @brief Localize Receipt and Z-Reports produced from SDK
 **/
@interface WDLocalizationManager : NSObject

/// List of supported languages - for Receipt | Z-Report  localization
- (NSArray<NSString *> *_Nonnull)supportedLanguages;
/// Set the required language - for Receipt | Z-Report  localization
- (void)setLanguage:(NSString *_Nonnull)language;
/// Set the default language upon initialisation - for Receipt | Z-Report  localization
- (void)setDefaultLanguageFromLocale:(NSString*_Nonnull)localeCode;
/// Get the current locale/language
+ (NSString*_Nonnull)getLocaleCode;
@end


NSString* _Nonnull WDLocalizedString(NSString * _Nonnull key);

