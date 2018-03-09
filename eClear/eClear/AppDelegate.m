//
//  AppDelegate.m
//  eClear
//
//  Created by Danko, Radoslav on 15/12/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "AppDelegate.h"
#import <TWMessageBarManager/TWMessageBarManager.h>
@interface AppDelegate ()

@end

@implementation AppDelegate
@dynamic language;

- (NSString *)language {
    return @"en"; //change this to de for German localized UI component
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    if (!self.backends) {
        [self getAllBackendURLs];    
    }
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

-(void)showError:(NSString *)title text:(NSString *)text{
    [[TWMessageBarManager sharedInstance] showMessageWithTitle:title
                                                   description:text
                                                          type:TWMessageBarMessageTypeError];
}
-(void)showInfo:(NSString *)title text:(NSString *)text{
    [[TWMessageBarManager sharedInstance] showMessageWithTitle:title
                                                   description:text
                                                          type:TWMessageBarMessageTypeInfo];
}

-(void)showSuccess:(NSString *)title text:(NSString *)text{
    [[TWMessageBarManager sharedInstance] showMessageWithTitle:title
                                                   description:text
                                                          type:TWMessageBarMessageTypeSuccess];
}

-(void)getAllBackendURLs
{
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"switchBE" ofType:@"json"];
    if (!filePath) {
        filePath = [[NSBundle bundleForClass:[self class]] pathForResource:@"switchBE" ofType:@"json"];
    }
    NSData *data = [NSData dataWithContentsOfFile:filePath];
    
    if (data)
    {
        
        if (data) {
            NSError *err;
            NSDictionary *dictBackends = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&err];
            self.backends = [dictBackends objectForKey:@"backends"];
        }
        
    }
}

-(void)loginUser:(NSString *)username
        password:(NSString *)password
         backend:(NSString *)backend
      completion:(void(^)(BOOL))completion{
    
    __weak AppDelegate * wself = self;
    self.sdk = [WDePOS sharedInstance];
    [self.sdk setupWithEnvironment:WDEnvironmentFromUrl(backend)
                                            username:username
                                            password:password
                                          completion:^(WDMerchantUser * _Nullable currentUser, WDMerchantCashier * _Nullable cashier, NSError * _Nullable error) {
                                              
                                              if (error) {
                                                  [wself showError:@"Login" text:error.localizedDescription];
                                              }
                                              
                                              completion( (currentUser != nil && error == nil) );
                                              
                                          }];
    
}
@end
