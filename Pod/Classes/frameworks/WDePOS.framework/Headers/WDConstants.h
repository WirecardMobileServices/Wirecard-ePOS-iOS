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

//Payments and transactions types
#define kWDCASH_PURCHASE @"CASH_PURCHASE"
#define kWDCASH_REFUND @"CASH_REFUND"
#define kWDCASH_REVERSAL @"CASH_REVERSAL"
#define kWDCARD_PURCHASE @"CARD_PURCHASE"
#define kWDCARD_TERMINAL_AUTHORIZATION @"CARD_TERMINAL_AUTHORIZATION"
#define kWDCARD_TERMINAL_PREAUTHORIZATION @"CARD_TERMINAL_PREAUTHORIZATION"
#define kWDCARD_TERMINAL_PREAUTHORIZATION_SUPPLEMENT @"CARD_TERMINAL_PREAUTHORIZATION_SUPPLEMENT"
#define kWDEFT_CARD @"EFT_CARD"
#define kWDEFT_CARD_PURCHASE @"EFT_CARD_PURCHASE"
#define kWDEFT_CARD_REFUND @"EFT_CARD_REFUND"
#define kWDEFT_CARD_REVERSAL @"EFT_CARD_REVERSAL"
#define kWDCARD_AUTO_RESOLVE @"CARD_AUTO_RESOLVE"
#define kWDCARD_CAPTURE @"CARD_CAPTURE"
#define kWDCARD_REFUND @"CARD_REFUND"
#define kWDCARD_REVERSAL @"CARD_REVERSAL"
#define kWDCOUPON_PURCHASE @"COUPON_PURCHASE"
#define kWDCOUPON_REVERSAL @"COUPON_REVERSAL"
#define kWDCOUPON_REFUND @"COUPON_REFUND"
#define kWDALIPAY_PURCHASE @"ALIPAY_PURCHASE"
#define kWDALIPAY_REVERSAL @"ALIPAY_REVERSAL"
#define kWDALIPAY_REFUND @"ALIPAY_REFUND"
#define kWDALIPAY_AUTO_RESOLVE @"ALIPAY_AUTO_RESOLVE"
#define kWDWECHAT_PURCHASE @"WECHAT_PURCHASE"
#define kWDWECHAT_REVERSAL @"WECHAT_REVERSAL"
#define kWDWECHAT_REFUND @"WECHAT_REFUND"
#define kWDWECHAT_AUTO_RESOLVE @"WECHAT_AUTO_RESOLVE"
#define kWDUNKNOWN @"UNKNOWN"

//Payment and transaction statuses
#define kWDIN_PROGRESS @"IN_PROGRESS"
#define kWDUNCONFIRMED @"UNCONFIRMED"
#define kWDCOMPLETED @"COMPLETED"
#define kWDRETURNED @"RETURNED"
#define kWDPARTIALLY_RETURNED @"PARTIALLY_RETURNED"
#define kWDCANCELED @"CANCELED"
#define kWDFAILED @"FAILED"
#define kWDFAILED_INTERVENE @"FAILED_INTERVENE"
#define kWDREVERSED @"REVERSED"
#define kWDREFUNDED @"REFUNDED"
#define kWDREFERENCE_REFUND @"REFERENCE_REFUND"
#define kWDREFUND @"REFUND"
#define kWDINITIALIZED @"INITIALIZED"
#define kWDINCOMPLETE @"INCOMPLETE"
#define kWDREJECTED @"REJECTED"
#define kWDAPPROVED @"APPROVED"
#define kWDAPPROVED_BY_GATEWAY @"APPROVED_BY_GATEWAY"
#define kWDUSERPAYING @"USERPAYING"
#define kWDCAPTURED @"CAPTURED"
#define kWDAUTO_RESOLVE @"AUTO_RESOLVE"
#define kWDUNDEFINED @"UNDEFINED"
#define kWDAUTHORIZED @"AUTHORIZED"

//Payment methods
#define kWDCASH @"CASH"
#define kWDCARD @"CARD"
#define kWDCARD_AUTHORIZATION @"CARD_AUTHORIZATION"
#define kWDCARD_PREAUTHORIZATION @"CARD_PREAUTHORIZATION"
#define kWDCARD_PREAUTHORIZATION_SUPPLEMENT @"CARD_PREAUTHORIZATION_SUPPLEMENT"
#define kWDSEPA @"SEPA"
#define kWDALIPAY @"ALIPAY"
#define kWDWECHAT @"WECHAT"

//Payment items
#define kWDPURCHASE @"PURCHASE"
#define kWDSERVICE_CHARGE @"SERVICE_CHARGE"
#define kWDCOUPON @"COUPON"
#define kWDDISCOUNT @"DISCOUNT"
#define kWDTIP @"TIP"
#define kWDGIFT_CARD @"GIFT_CARD"

#endif /* WDConstants_h */
