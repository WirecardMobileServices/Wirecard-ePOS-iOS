//
//  StartViewController.h
//  DemoEPOS
//
//  Created by Fortes, Francisco on 3/8/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface StartViewController : UIViewController
@property (nonatomic, weak) IBOutlet UILabel *infoLabel;

-(void)showProgressOnApp:(NSString*)progress withColor:(UIColor*)color;
@end
