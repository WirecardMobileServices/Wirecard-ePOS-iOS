//
//  StartViewController.m
//  DemoEPOS
//
//  Created by Fortes, Francisco on 3/8/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "StartViewController.h"

@interface StartViewController ()

@end

@implementation StartViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

-(void)viewWillAppear:(BOOL)animated
{
    //We detect is the app is in normal execution or running unitests
    if ([[[NSProcessInfo processInfo] environment] objectForKey:@"XCTestConfigurationFilePath"])
    {
        [self.infoLabel setTextColor:[UIColor whiteColor]];
        [self.infoLabel setText:@"Unit test currently running, please check console logs."];
    }
    else
    {
        [self.infoLabel setTextColor:[UIColor whiteColor]];
        [self.infoLabel setText:@"This demo must be used running unit tests. Please check Xcode test section and run the tests from there."];
    }
}

-(void)showProgressOnApp:(NSString*)progress withColor:(UIColor*)color
{
    dispatch_queue_t mainQueue = dispatch_get_main_queue();
    dispatch_async(mainQueue, ^{
        [self.infoLabel setText:progress];
        [self.infoLabel setTextColor:color];
    });
}

@end
