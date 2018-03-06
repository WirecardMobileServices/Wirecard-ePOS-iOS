//
//  AppDelegate.m
//  ePos Demo
//
//  Created by Fortes, Francisco on 10/27/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import "AppDelegate.h"
#import <INTULocationManager/INTULocationManager.h>

@interface AppDelegate ()

@end

@implementation AppDelegate
{
    CLLocation *userLocation;
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

#pragma mark - Location

//WARNING: "Scheme Edit/Run(debug)/Options/Allow Location Simulation" can overwrite the values for the app even when not debugging (even in distributed IPAs!!). It must be disabled and the iPad must restart to clean that flag up
//https://discussions.apple.com/thread/4763274?start=0&tstart=0
-(void)getLocation{
    dispatch_async(dispatch_get_main_queue(), ^{
        INTULocationManager *locMgr = [INTULocationManager sharedInstance];
        [locMgr requestLocationWithDesiredAccuracy:INTULocationAccuracyHouse
                                           timeout:15 //Only values obtained under <=15 sec are valid for AccuracyHouse. Previous timeout of 30 was producing an error status
                              delayUntilAuthorized:YES
                                             block:^(CLLocation *currentLocation, INTULocationAccuracy achievedAccuracy, INTULocationStatus status) {
                                                 if (status == INTULocationStatusSuccess) {
                                                     // Request succeeded, meaning achievedAccuracy is at least the requested accuracy, and
                                                     // currentLocation contains the device's current location.
                                                     userLocation = currentLocation;
                                                 }
                                                 else if (status == INTULocationStatusTimedOut) {
                                                     // Wasn't able to locate the user with the requested accuracy within the timeout interval.
                                                     // However, currentLocation contains the best location available (if any) as of right now,
                                                     // and achievedAccuracy has info on the accuracy/recency of the location in currentLocation.
                                                     userLocation = currentLocation;
                                                 }
                                             }];
    });
    
}

-(CLLocation *)currentLocation{
    return userLocation;
}

@end
