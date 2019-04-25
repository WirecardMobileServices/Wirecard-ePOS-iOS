//
//  TestUtils.h
//  WDePOS
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WDePOS/WDePOS.h>
#import <UIKit/UIKit.h>


@interface TestUtils : NSObject
+(NSString *)uniqueID;
+ (UIImage *) signatureImageFromText:(NSString *)signatureText;
+ (UIImage *) signatureImageFromText:(NSString *)signatureText withSize:(CGSize)imageSize;

@end
