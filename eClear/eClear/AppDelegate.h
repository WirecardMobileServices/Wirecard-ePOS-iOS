//
//  AppDelegate.h
//  eClear
//
//  Created by Danko, Radoslav on 15/12/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WDePOS/WDePOS.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) WDePOS *sdk;
@property (strong, nonatomic) NSArray *backends;
@property (strong, nonatomic, readonly) NSString *language;

-(void)showError:(NSString *)title text:(NSString *)text;
-(void)showInfo:(NSString *)title text:(NSString *)text;
-(void)showSuccess:(NSString *)title text:(NSString *)text;
-(void)loginUser:(NSString *)username
        password:(NSString *)password
         backend:(NSString *)backend
      completion:(void(^)(BOOL))completion;

@end
