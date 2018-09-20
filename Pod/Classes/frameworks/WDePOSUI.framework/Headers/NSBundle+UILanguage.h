//
//  NSBundle+WDBundle.h
//  WDePOSUI
//
//  Created by Pulik, Jaroslav on 31/08/2018.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSBundle (UILanguage)

    - (NSString*)ui_localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName;

    + (void)ui_setLanguage:(NSString*)language;

    + (void)ui_setLanguage:(NSString*)language sourceBundleName:(NSString *)sourceBundleName;

@end
