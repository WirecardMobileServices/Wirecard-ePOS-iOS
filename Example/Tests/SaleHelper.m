//
//  SaleHelper.m
//  DemoEPOS
//
//  Created by Fortes, Francisco on 3/9/17.
//  Copyright © 2017 Wirecard. All rights reserved.
//

#import "SaleHelper.h"
#import "AppDelegate.h"
#import "UserHelper.h"
#import "TestUtils.h"
#import <WDePOS/NSString+WDExtras.h>

@implementation SaleHelper
{
    WDSaleRequest *_currentSale;
    WDSaleResponse *_currentSaleResponse;
    NSString *_cashRegisterId, *_shopId, *_cashierId, *_customerId;
    NSString *_selectedCurrencyCode, *_loginCredentials;
    WDPaymentConfig *_paymentConfiguration;
    NSDecimalNumber *_gratuityTaxRate;
    NSUserDefaults *userDefaults;
    NSDateFormatter *_dateFormatter;
}

static SaleHelper *sharedInstance = nil;

- (instancetype)initPrivate
{
    self = [super init];
    userDefaults = [[NSUserDefaults alloc] initWithSuiteName:@"ePosDemo"];
    _dateFormatter = [[NSDateFormatter alloc] init];
    [_dateFormatter setLocale:[NSLocale currentLocale]];
    [_dateFormatter setDateFormat:@"yyyyMMddHHmmss"];
    return self;
}

+ (SaleHelper *)sharedInstance
{
    static dispatch_once_t pred;
    dispatch_once(&pred, ^{
        sharedInstance = [[SaleHelper alloc] initPrivate];
    });
    
    return sharedInstance;
}

-(NSString *)formatNumberToCurrency:(NSDecimalNumber *)number withCurrencySymbol:(BOOL)withCurrencySymbol
{
    if (!number || [number isEqualToNumber:[NSNumber numberWithInt:0]]) {
        number = [NSDecimalNumber decimalNumberWithString:@"0.00"];
    }
    NSNumberFormatter *numFormatter = [[NSNumberFormatter alloc] init];
    
    [numFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    
    NSLocale *lcl = [NSLocale currentLocale];
    
    //IMPORTANT: you may encounter currencies with 0, 1 or 3 decimal places around the world
    int minorUnits = 2;
    
    [numFormatter setLocale:lcl];
    [numFormatter setCurrencyCode:_selectedCurrencyCode? _selectedCurrencyCode : @"EUR"];
    [numFormatter setMinimumIntegerDigits:1];
    [numFormatter setMinimumFractionDigits:minorUnits];
    [numFormatter setMaximumFractionDigits:minorUnits];
    //    [numFormatter setPositiveFormat:@"0.00"];
    
    if (minorUnits == 0) {
        [numFormatter setAlwaysShowsDecimalSeparator:NO];
    }
    else{
        [numFormatter setAlwaysShowsDecimalSeparator:YES];
    }
    [numFormatter setRoundingMode:NSNumberFormatterRoundHalfUp];
    [numFormatter setUsesGroupingSeparator:NO];
    
    if(!withCurrencySymbol){
        [numFormatter setCurrencySymbol:@""];
    }
    NSString *strNumber = [numFormatter stringFromNumber:number];
    
    return strNumber;
}

-(NSString*)formatDate:(NSDate *)date withFormat:(NSString*)withFormat
{
    NSString *oldFormat = _dateFormatter.dateFormat;
    [_dateFormatter setDateFormat:withFormat];
    NSString *ret = [_dateFormatter stringFromDate: date];
    [_dateFormatter setDateFormat:oldFormat];
    
    return ret;
}

-(WDSaleRequest *)newSale
{
    _currentSale = nil;
    
    NSString *transactionUniqueId = [TestUtils uniqueID];
    
    //Note: having a location in your sale is totally optional - it will expose the coordinates where the transaction was done.
    CLLocation *terminalLocation = [(AppDelegate *)[[UIApplication sharedApplication] delegate] currentLocation];
    
    _currentSale = [[WDSaleRequest alloc] initWithUniqueId:transactionUniqueId
                                                                        location:terminalLocation
                                                                  inclusiveTaxes:KTAX_INCLUSIVE_ENABLED
                                                                        currency:_selectedCurrencyCode
                                                                            note:KSALE_DESCRIPTION
                                                                 gratuityTaxRate:_gratuityTaxRate];
    _currentSale.shopId = _shopId;
    _currentSale.cashierId = _cashierId;
    _currentSale.customerId = _customerId;
    _currentSale.currency = [[[[[UserHelper sharedInstance] getCurrentUser] merchant] defaultCurrency] code];
    
    return _currentSale;
}

-(WDSaleRequest *)currentSale
{
    if (!_currentSale)
    {
        
        return [self newSale];
    }
    
    return _currentSale;
}

-(void)saleToSaveIdFrom:(WDSaleResponse*)sale
{
    [userDefaults setObject:sale.internalId forKey:@"saleToSaveIdFrom"];
}

-(NSString*)saleIdSaved
{
    return [userDefaults objectForKey:@"saleToSaveIdFrom"];
}

-(WDReceipt*)receiptForDatecsFromReceiptData:(WDReceiptData*)receiptData
{
    //Note: this long function is an example of how to build a complete, certification friendly receipt for
    //the Datecs printer. But you are free to fill the values as you want
    WDReceipt *receipt = [WDReceipt new];
    if (!receiptData)
    {
        return receipt;
    }
    receipt.header = NSLocalizedString(@"Customer Receipt", @"Customer Receipt");
    receipt.merchantName = receiptData.merchantName;
    receipt.merchantAddressLine1 = receiptData.address.street1;
    receipt.merchantAddressLine2 = receiptData.address.street2;
    receipt.merchantAddressZipCode = receiptData.address.postalCode;
    receipt.merchantAddressCityAndCountry = [NSString stringWithFormat:@"%@, %@",receiptData.address.city, receiptData.address.country.name];
    //Note: you can include a logo in the header of the receipt with:
    //receipt.headerLogo = [UIImage imageWithData: imageData];
    receipt.localisedAOSAHeader = NSLocalizedString(@"AOSA:", @"AOSA:"); //Available Offline Spending Amount, a parameter for some contactless cards
    receipt.availableOfflineSpendingAmount = (receiptData.aosa)? [self formatNumberToCurrency:receiptData.aosa withCurrencySymbol:YES] : nil;
    receipt.verifiedOnDeviceCVM = receiptData.verifiedOnTerminalCVM;
    receipt.appCrypt = receiptData.applicationCryptogram;
    if (receiptData.technicalMessage.length)
    {
        receipt.declinedReason = receiptData.technicalMessage;
    }
    receipt.PINVerified = receiptData.PINVerified;
    receipt.merchantID = receiptData.emvMID;
    receipt.merchantIDHeader = @"MID:";
    receipt.aidHeader = @"AID:";
    receipt.aid = receiptData.emvAID;
    receipt.merchantPhone = receiptData.merchantPhone;
    receipt.localisedReceiptDateHeader = NSLocalizedString(@"Date", @"Date");
    receipt.localisedPaymentDateHeader = [NSLocalizedString(@"Payment Date", @"Payment Date") stringByAppendingString:@":"];
    receipt.localisedReceiptTimeHeader = NSLocalizedString(@"Time", @"Time");
    NSString *date = [self formatDate:receiptData.utcPaymentDate withFormat:@"dd.MM.yyyy"];
    NSString *time = [self formatDate:receiptData.utcPaymentDate withFormat:@"HH:mm:ss"];
    receipt.receiptDate = date;
    receipt.receiptTime = time;
    receipt.localisedReceiptIDHeader = [NSLocalizedString(@"Receipt #", @"Receipt #") stringByAppendingString:@":"];
    receipt.localisedReceiptNumberHeader = [NSLocalizedString(@"Receipt number", @"Receipt number") stringByAppendingString:@":"];
    receipt.receiptID = [NSString stringWithFormat:@"%u", (unsigned)receiptData.receiptID];
    receipt.localisedShopIDHeader = [NSLocalizedString(@"Shop", @"Shop") stringByAppendingString:@":"];
    receipt.localisedCashierIDHeader = [NSLocalizedString(@"Cashier ID", @"Cashier ID") stringByAppendingString:@":"];
    receipt.shopID = receiptData.shopId;
    receipt.cashierID = receiptData.cashierId;
    receipt.localisedCardTypeHeader = [NSLocalizedString(@"Card Type", @"Card Type") stringByAppendingString:@":"];
    receipt.cardType = receiptData.cardType;
    if (receiptData.saleType == WDSaleTypeReturn )
    {
        receipt.saleTypeAsText =  NSLocalizedString(@"REFUND",@"REFUND");
    }
    else if (receiptData.status ==  WDSaleStateCompleted || receiptData.status ==  WDSaleStateReturned)
    {
        receipt.saleTypeAsText =  NSLocalizedString(@"SALE",@"SALE");
    }
    else if (receiptData.status == WDSaleStateFailed ||
             receiptData.status == WDSaleStateFailedIntervene ||
             receiptData.status == WDSaleStateUnknown)
    {
        receipt.saleTypeAsText =  NSLocalizedString(@"DECLINED",@"DECLINED");
    }
    else if (receiptData.status == WDSaleStateInProgress)
    {
        receipt.saleTypeAsText =  NSLocalizedString(@"INCOMPLETE",@"INCOMPLETE");
    }
    else if (receiptData.status == WDSaleStateIncomplete)
    {
        //Incomplete will always end as declined on backend in a matter of seconds.
        receipt.saleTypeAsText =  NSLocalizedString(@"DECLINED",@"DECLINED");
    }
    else if (receiptData.status == WDSaleStateCanceled)
    {
        receipt.saleTypeAsText =  NSLocalizedString(@"REVERSED",@"REVERSED"); //REVERSED is canceled, REFUND is returned
        //in backend terminology
    }
    else
    {
        receipt.saleTypeAsText =  @"";
    }
    receipt.isContactless = receiptData.contactless;
    if  (!receipt.isContactless)
    {
        receipt.posEntryModeInterpreted = [receiptData posEntryModeDescriptionWithCardType:receiptData.cardType];
    }
    receipt.transactionTypeString = receiptData.emvTransactionType;
    receipt.localisedTransactionTypeHeader = [NSLocalizedString(@"Transaction type", @"Transaction type") stringByAppendingString:@":"];
    receipt.localisedCardNumberHeader = [NSLocalizedString(@"Card Number", @"Card Number") stringByAppendingString:@":"];
    NSString *cardNo = [receiptData.maskedCardNumber stringByReplacingOccurrencesOfString:@"(null)" withString:@""];
    if (cardNo.length > 0 && cardNo.length <= 4 && [cardNo instr:@"X"] < 0)
    {
        cardNo = [NSString stringWithFormat:@"XXXX-XXXX-XXXX-%@",cardNo];
    }
    receipt.cardNumber = cardNo;
    receipt.cardHolder = receiptData.cardholderName;
    receipt.localisedCardHolderHeader = [NSLocalizedString(@"Cardholder Name", @"Cardholder Name") stringByAppendingString:@":"];
    receipt.localisedExpiryDateHeader = NSLocalizedString(@"Expiry Date", @"Expiry Date");
    receipt.expiryDate = nil;
    receipt.localisedTerminalIDHeader =[ NSLocalizedString(@"Terminal ID", @"Terminal ID")  stringByAppendingString:@":"];
    receipt.terminalID = receiptData.emvTID;
    receipt.localisedApprovalCodeHeader = [NSLocalizedString(@"Approval Code", @"Approval Code")  stringByAppendingString:@":"];
    receipt.approvalCode = receiptData.approvalCode;
    receipt.localisedSubtotalHeader = [NSLocalizedString(@"Subtotal", @"Subtotal") stringByAppendingString:@":"];
    receipt.localisedTipHeader = [NSLocalizedString(@"Tip", @"Tip") stringByAppendingString:@":"];
    receipt.localisedServiceChargeHeader = [NSLocalizedString(@"Service charge", @"Service charge") stringByAppendingString:@":"];
    receipt.localisedServiceChargeWithTaxHeader = [NSLocalizedString(@"Service charge with Tax", @"Service charge with Tax") stringByAppendingString:@":"];
    receipt.localisedDiscountHeader = [NSLocalizedString(@"Discount", @"Discount") stringByAppendingString:@":"];
    receipt.localisedVoucherHeader = [NSLocalizedString(@"Voucher", @"Voucher") stringByAppendingString:@":"];
    receipt.localisedCustomerCardHeader = [NSLocalizedString(@"Customer card", @"Customer card") stringByAppendingString:@":"];
    receipt.localisedPaymentTypeHeader = [NSLocalizedString(@"Payment type", @"Payment type") stringByAppendingString:@":"];
    if (receiptData.serviceChargeItem)
    {
        receipt.serviceCharge = [self formatNumberToCurrency:[receiptData.serviceChargeItem totalBeforeTaxBeforeDiscount] withCurrencySymbol:YES];
        receipt.serviceChargeWithTax = [self formatNumberToCurrency:[receiptData.serviceChargeItem totalAfterTaxBeforeDiscount] withCurrencySymbol:YES];
    }
    if (receiptData.discountItem)
    {
        NSDecimalNumber *decDiscount = [[receiptData.discountItem total] decimalNumberByMultiplyingBy:[NSDecimalNumber decimalNumberWithString:@"-1"]];
        receipt.discount = [self formatNumberToCurrency:decDiscount withCurrencySymbol:YES];
    }
    if (receiptData.tipItem)
    {
        receipt.tip = [self formatNumberToCurrency:receiptData.tipItem.total withCurrencySymbol:YES];
    }
    NSMutableString *paymentTypeStr = [[NSMutableString alloc] init];
    for (NSNumber *i in receiptData.receiptPaymentTypes)
    {
        if (i.intValue == WDPaymentMethodCard)
        {
            if (paymentTypeStr.length > 1)
            {
                [paymentTypeStr appendString:@", "];
            }
            [paymentTypeStr appendString:NSLocalizedString(@"Card", @"Card")];
        }
        else if (i.intValue == WDPaymentMethodCoupon)
        {
            if (paymentTypeStr.length > 1)
            {
                [paymentTypeStr appendString:@", "];
            }
            [paymentTypeStr appendString:NSLocalizedString(@"Coupon", @"Coupon")];
        }
        else if (i.intValue == WDPaymentMethodCoupon)
        {
            if (paymentTypeStr.length > 1)
            {
                [paymentTypeStr appendString:@", "];
            }
            [paymentTypeStr appendString:NSLocalizedString(@"Alipay", @"Alipay")];
        }
        else
        {
            if (paymentTypeStr.length > 1)
            {
                [paymentTypeStr appendString:@", "];
            }
            [paymentTypeStr appendString:NSLocalizedString(@"Cash", @"Cash")];
        }
    }
        receipt.paymentType = paymentTypeStr;
    NSDecimalNumber *subtotalDec = [[receiptData totalAmount] decimalNumberBySubtracting:([receiptData.serviceChargeItem totalAfterTaxBeforeDiscount])? [receiptData.serviceChargeItem totalAfterTaxBeforeDiscount] : [NSDecimalNumber decimalNumberWithString:@"0"]];
    subtotalDec = [subtotalDec decimalNumberBySubtracting:(receiptData.tipItem.total)? receiptData.tipItem.total : [NSDecimalNumber decimalNumberWithString:@"0"]];
    receipt.subtotal = [self formatNumberToCurrency:subtotalDec withCurrencySymbol:YES];
    receipt.localisedAmountHeader = [NSLocalizedString(@"Total", @"Total")  stringByAppendingString:@":"];
    NSString *totalAmount = [self formatNumberToCurrency:[receiptData totalAmount] withCurrencySymbol:YES];
    receipt.amount = totalAmount;
    NSString *transactionStatus = [receiptData receiptSaleStatusDescription];
    transactionStatus = NSLocalizedString(transactionStatus, transactionStatus);
    receipt.localisedTransactionStatusHeader =[NSLocalizedString(@"Transaction Status", @"Transaction Status")  stringByAppendingString:@":"];
    receipt.transactionStatus = NSLocalizedString(transactionStatus, transactionStatus);
    receipt.footer = [NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Payment issued by", @"Payment issued by"), @"ePosDemo"];
    if (receipt.aid.length && [receipt.aid.uppercaseString instr:@"A000000025"] >= 0) //if it is AMEX
    {
        receipt.footer = [NSString stringWithFormat:@"%@\n%@", receipt.footer, NSLocalizedString(@"Please retain receipt for future reference.", @"Please retain receipt for future reference.")];
    }
    receipt.footerThankYou = NSLocalizedString(@"Thank you for your purchase", @"Thank you for your purchase");
    receipt.footerCopyright = @"\u00A9 WIRECARD GmBH 2014 Mobile Services";
    receipt.localisedPaymentDetailsHeader = NSLocalizedString(@"Details",@"Details");
    receipt.receiptStringToBarCode = [NSString stringWithFormat:@"%09lu", (unsigned long)receiptData.receiptID];
    NSMutableArray *itemsArray = [NSMutableArray new];
    for (WDSaleItem *item in receiptData.receiptItems)
    {
        if (item.itemType == WDSaleItemTypePurchase)
        {
            NSDecimalNumber *decTaxAmount = item.taxRate;
            NSString *desc = item.itemDescription;
            NSString *taxMode = receiptData.inclusiveTax? NSLocalizedString(@"Incl.", @"Incl.") : NSLocalizedString(@"Excl.", @"Excl.");
            NSString *strTaxAmount = [NSString stringWithFormat:@"%@ %@%% %@",taxMode, decTaxAmount, @"VAT"];
            if (desc.length == 0)
            {
                desc = NSLocalizedString(@"No description", @"No description");
            }

            //Datecs format exclusive
            [itemsArray addObject:[NSString stringWithFormat:@"{=F0}{+B}{=L}%@ {-B}{=R}%@\n{=F1}{=L}%ldx %@ {=R}%@\n"//@"{=F0}{+B}{=L}%@ {-B}{=R}%@\n{=F1}{=L}%ld x %@ {=R}%@\n"
                                    ,desc
                                    ,[self formatNumberToCurrency:[item itemTotal] withCurrencySymbol:YES]
                                    ,(long)item.quantity
                                    ,[self formatNumberToCurrency:item.unitPrice withCurrencySymbol:YES]
                                    ,strTaxAmount]];
        
        }
    }
    if(receiptData.inclusiveTax)
    {
        [itemsArray addObject:[NSString stringWithFormat:@"\n%@",NSLocalizedString(@"Prices inclusive of taxes", @"Prices inclusive of taxes")]];
    }
    else
    {
        [itemsArray addObject:[NSString stringWithFormat:@"\n%@",NSLocalizedString(@"Prices exclusive of taxes", @"Prices exclusive of taxes")]];
    }
    receipt.paymentItems = itemsArray;
    NSMutableString *strTaxSummary = [[NSMutableString alloc] initWithString:@""];
    for (WDSaleSummaryItem *item in receiptData.taxSummaryItems)
    {
        if (item.taxRate.floatValue >= 0)
        {
            NSString *taxMode = receiptData.inclusiveTax? NSLocalizedString(@"Tax incl.", @"Tax incl."): NSLocalizedString(@"Tax excl.", @"Tax excl.");
            [strTaxSummary appendString:[NSString stringWithFormat:@"{=F0}{+B}{=L}%@ %@%%\n"
                                         ,taxMode
                                         ,item.taxRate]];
            
            [strTaxSummary appendString:[NSString stringWithFormat:@"{=F0}{-B}{=L}%@ %@ + %@ %@\n"
                                         ,NSLocalizedString(@"Netto",@"Netto")
                                         ,[self formatNumberToCurrency: [item totalBeforeTaxBeforeDiscount] withCurrencySymbol:YES]
                                         ,NSLocalizedString(@"Tax",@"Tax")
                                         ,[self formatNumberToCurrency: item.taxAmount withCurrencySymbol:YES]]];
            
            [strTaxSummary appendString:[NSString stringWithFormat:@"{=F0}{-B}{=L}%@ %@\n"
                                         ,NSLocalizedString(@"Gross",@"Gross")
                                         ,[self formatNumberToCurrency: [item totalAfterTaxBeforeDiscount] withCurrencySymbol:YES]]];
        }
    }
    
    if (strTaxSummary.length)
    {
        receipt.taxSummary = [strTaxSummary substringToIndex:([strTaxSummary length] -1)]; //remove last newline character;
    }
    
    return receipt;
}

@end
