//
//  AppDelegate.h
//  ePos Demo
//
//  Created by Fortes, Francisco on 10/27/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

-(CLLocation *)currentLocation;

@property (strong, nonatomic) UIWindow *window;


@end

