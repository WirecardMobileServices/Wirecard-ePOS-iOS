//
//  ViewController.m
//  eClear
//
//  Created by Danko, Radoslav on 15/12/2017.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import "ViewController.h"
#import "eClear-Swift.h"
#import <WDePOS/WDePOS.h>
#import <WDePOSUI/WDePOSUI-Swift.h>

typedef NS_ENUM(NSUInteger, PaymentType) {
    PaymentTypeAmountCash = 1,
    PaymentTypeAmountCard,
    PaymentTypeNoAmountCardAndCash,
    PaymentTypeNoAmountQRCode,
    PaymentTypeNoAmountNoPaymentMethod
};

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIButton *btnPayCashCard;
@property (strong, nonatomic) AppDelegate* app;
@property (strong, nonatomic) WDSaleResponse* sale;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.app = (AppDelegate*)[[UIApplication sharedApplication] delegate];
    self.btnPayCashCard.titleLabel.lineBreakMode = NSLineBreakByWordWrapping;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    if (!self.app.sdk) {
        [self showLogin];
    }
    self.sale = nil;
}

-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
//    [self.navigationController setNavigationBarHidden:YES animated:YES];
}

#pragma mark - Custom Methods

-(void)showLogin {
   LoginVC *loginVC = (LoginVC*)[[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"LoginVC"];
    [self.navigationController presentViewController:loginVC animated:YES completion:nil];
}

-(void)pay:(NSDecimalNumber *)amount paymentMethod:(WDPaymentMethodMask*)paymentMethod {
    
    WDSaleManagerUI *ui = [WDSaleManagerUI sharedInstance];
    
    WDSaleConfiguration *config = [[WDSaleConfiguration alloc]
                                         initWithAmount:amount
                                         currency: (paymentMethod == WDPaymentMethodMask.qr ) ? @"USD" : @"EUR"
                                         taxRate:[NSDecimalNumber decimalNumberWithString:@"0.19"]
                                         paymentMethods:paymentMethod];
    
    //set the Localisation for the UI component [en, de, es] defaults to en if not set
    config.language = ((AppDelegate *)[UIApplication sharedApplication].delegate).language;
    
    [ui pay:config progress:^(WDStateUpdate paymentProgress) {
       NSLog(@"progress =%ld", (long)paymentProgress);
    } completion:^(WDSaleResponse * _Nullable saleResponse, NSError * _Nullable saleResponseError) {
        if (saleResponseError) {
           NSLog(@"saleResponseError:%@",saleResponseError);
           [self.app showError:@"Sale" text:saleResponseError.localizedDescription];
        }
        else {
           if ([saleResponse allPaymentsApproved]) {
               [self.app showSuccess:@"Sale" text:@"Payment processed successfully"];
           }
           else{
               [self.app showInfo:@"Sale" text:@"Payment failed" ] ;
           }
           [self showReceipt:saleResponse];
        }
        NSLog(@"saleResponse:%@",saleResponse);
    }];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    ReceiptVC *receiptVC = (ReceiptVC*) segue.destinationViewController;
    receiptVC.sale = self.sale;
}

-(void)showReceipt:(WDSaleResponse *)sale {
    self.sale = sale;
//    ReceiptVC *receiptVC = (ReceiptVC*)[[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:@"ReceiptVC"];
//    receiptVC.sale = sale;
//    [self.navigationController showViewController:receiptVC sender:nil];
//    [self.navigationController setNavigationBarHidden:NO animated:YES];
    [self performSegueWithIdentifier:@"receiptSeque" sender:nil];
}

#pragma mark - Custom Actions
- (IBAction)onTapPay:(id)sender {
    
    long tag = 0;
    
    if ([sender isKindOfClass:[UITapGestureRecognizer class]]) {
        tag = [[sender view] tag];
    }
    else {
        UIButton *btn = (UIButton *) sender;
        tag = btn.tag;
    }
    switch (tag) {
        case PaymentTypeAmountCash:
            [self pay:[NSDecimalNumber decimalNumberWithString:@"10"] paymentMethod:WDPaymentMethodMask.cashOnly];
            break;
        case PaymentTypeAmountCard:
            [self pay:[NSDecimalNumber decimalNumberWithString:@"10"] paymentMethod:WDPaymentMethodMask.cardOnly];
            break;
        case PaymentTypeNoAmountCardAndCash:
            [self pay:nil paymentMethod:WDPaymentMethodMask.standard];
            break;
        case PaymentTypeNoAmountQRCode:
            [self pay:nil paymentMethod:WDPaymentMethodMask.qr];
            break;
        case PaymentTypeNoAmountNoPaymentMethod:
            [self pay:nil paymentMethod:WDPaymentMethodMask.all];
            break;

        default:
            break;
    }
}
- (IBAction)onTapLogout:(id)sender {
    [self showLogin];
}
@end
