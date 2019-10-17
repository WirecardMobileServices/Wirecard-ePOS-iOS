//
//  WDConstants.h
//   WDePOS
//
//  Created by Danko, Radoslav on 26/06/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#ifndef WDConstants_h
#define WDConstants_h

extern const char kWDLanguageBundles;

#define kWDDateSeparatorDash @"%@ - %@"
#define kWDDateSeparatorParentheses @"%@ (%@)"
#define kWDDateSeparatorBlank @"%@ %@"
#define kWDDateSeparatorEmpty @""
#define kWDDateSeparatorComma @","
#define kWDDateFormatEU @"dd.LLL.yyyy"
#define kWDDateFormatChina @"yyyy/LLL/dd"
#define kWDDateFormatUSA @"LLL/dd/yyyy"
#define kWDDateFormatCommaEU @"dd LLL, yyyy"
#define kWDDateFormatCommaChina @"yyyy, LLL dd"
#define kWDDateFormatCommaUSA @"LLL dd, yyyy"
#define kWDTimeFormat24Hours @"HH:mm:ss"
#define kWDTimeFormatShort @"HH:mm"
#define kWDA4WidthInPoints 595.0
#define kWDA4HeightInPoints 841.0
#define kWDPaperSizeA4 CGSizeMake(kA4WidthInPoints, kA4HeightInPoints)
#define kWDDPP250DotsPerWidth 600.0
#define kWDmPOPDotsPerWidth 384.0
#define kWDStarMicronicsDotsPerWidth 576.0

#define kWDMID @"MID:"
#define kWDARC @"ARC:"
#define kWDAOSA @"AOSA:"
#define kWDAID @"AID:"
#define kWDTC @"TC:"
#define WDLocaleFormat(key) [[WDePOSUtils sharedInstance] formatDateWithCurrentLocale:key]

#endif /* WDConstants_h */
