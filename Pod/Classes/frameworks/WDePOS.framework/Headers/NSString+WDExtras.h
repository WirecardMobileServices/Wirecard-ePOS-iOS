//
//  NSString+ToData.h
//  PwmAdk_RefApp
//
//  Created by Barrett Francis on 7/31/13.
//  Copyright (c) 2013 Barrett Francis. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (WDExtras)

- (NSData *)convertHexToData;
- (NSString *)stringByRemovingControlCharacters;
- (NSInteger)instr:(NSString*)substring;
- (NSString *)leftPadStringWithPadding:(NSString *)padding;
- (NSString *)leftPadStringToLength:(int)toLength;
- (NSString *)stringByEncodingHTMLEntities ;
- (BOOL)contains:(NSString*)string;

+ (NSString *)hexFromStr:(NSString*)str;
+ (NSString *)hexToString:(NSString *)string;
+ (NSString *)hexToASCII:(NSString *)hexString;
+ (NSString *)getMaskedPANForReceipt:(NSString *)PAN;

-(NSString *)wrapByLength:(NSUInteger)length;
-(NSArray *)splitByLength:(int)length;
@end
