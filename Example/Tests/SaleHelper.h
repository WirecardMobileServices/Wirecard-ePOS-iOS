//
//  SaleHelper.h
//  DemoEPOS
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WDePOS/WDePOS.h>
#import "Constants.h"

@interface SaleHelper : NSObject
+ (SaleHelper *)sharedInstance;
-(WDSaleRequest *)currentSale;
-(WDSaleRequest *)newSale;
-(void)saleToSaveIdFrom:(WDSaleResponse*)sale;
-(NSString*)saleIdSaved;
-(WDReceipt*)receiptForDatecsFromReceiptData:(WDReceiptData*)receiptData;
@end
