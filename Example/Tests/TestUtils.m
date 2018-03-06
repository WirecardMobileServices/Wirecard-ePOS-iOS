//
//  TestUtils.m
//  WDePOS
//
//  Created by Danko, Radoslav on 17/10/15.
//  Copyright © 2015 Wirecard. All rights reserved.
//

#import "TestUtils.h"


@implementation TestUtils
//+(NSString *)basicAuthenticationFromConfig{
//    
//    NSData *dataAuthorisation = [K_SWITCH_DEV_USERNAME_PASSWORD dataUsingEncoding:NSUTF8StringEncoding];
//    
//    NSString * strAuthorisation = [NSString stringWithFormat:@"Basic %@",[dataAuthorisation base64EncodedStringWithOptions:(NSDataBase64EncodingOptions)0]];
//    
//    return strAuthorisation;
//}
//
//+(NSDictionary *)publicTestEnvironment{
//    return @{@"environment":@(WDEnvironmentPublicTestPublicTest),
//             @"credentials":K_SWITCH_PUBLICTEST_USERNAME_PASSWORD};
//}
//
//+(NSDictionary *)devEnvironment{
//    return @{@"environment":@(WDEnvironmentPublicTestPublicTest),
//             @"credentials":K_SWITCH_DEV_USERNAME_PASSWORD};
//}

//
//+(NSDictionary *)defaultWDEnvironmentPublicTest{
//    return [[self class] devEnvironment];
//
//}


+(NSString *)uniqueID{
   return [[[NSUUID UUID] UUIDString] stringByReplacingOccurrencesOfString:@"-" withString:@""];
}

+ (UIImage *) signatureImageFromText:(NSString *)signatureText{
   return [TestUtils signatureImageFromText:signatureText withSize:CGSizeMake(240, 100)];
}

+ (UIImage *) signatureImageFromText:(NSString *)signatureText withSize:(CGSize)imageSize
{
    UILabel *signatureLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, imageSize.width, imageSize.height)];
    
    signatureLabel.backgroundColor = [UIColor whiteColor];
    signatureLabel.textColor = [UIColor blackColor];
    signatureLabel.text = signatureText;
    signatureLabel.minimumScaleFactor = 0.5;
    signatureLabel.font = [UIFont fontWithName:@"Zapfino" size:20];
    
    UIGraphicsBeginImageContextWithOptions(signatureLabel.bounds.size, signatureLabel.opaque, 0.0);
    [signatureLabel.layer renderInContext:UIGraphicsGetCurrentContext()];
    
    UIImage * img = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    return img;
}

@end
