//
//  WDCashManager.h
//   WDePOS
//
//  Created by Danko, Radoslav on 19/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Cashier management
/**
 *  @class WDCashManager
 *  @brief Cash Management
 */
@interface WDCashManager : NSObject

/**
 *  @brief Validate supplied PIN
 *  @param pin PIN as set by cashier
 *  @param cashierId cashier internal id
 *  @param completion Block executed at the end of the get merchant cashier method having pin validation result
 */
-(void)validatePin:(NSString *)pin
         cashierId:(NSString *)cashierId
        completion:(MerchantCashierPinValidationCompletion)completion;

/**
 *  @brief Get cashiers for a merchant
 *  @param completion Block executed at the end of the get cash register method method
 */
-(void)cashiers:(MerchantCashierCompletion)completion;

/**
 *  @brief Update the cashier of the current merchant (based on the currently logged in merchant user)
 *  @param completion Block executed at the end of the update merchant cashier method
 */
-(void)updateCashier:(WDMerchantCashier *)cashier
    completion:(MerchantCashierCompletion)completion;

/**
 *  @brief Get cash registers for a merchant, so we get the connection between registers IDs and Cash Drawer serial numbers for Cash Management
 *  @param merchantId NSString id of the merchant we are requesting registers
 *  @param shopId NSString id of the merchant's shop we are requesting registers(cash registers without assigned shopId are NOT excluded)
 *  @param vendor NSString Cash register's vendor name(No filter if nil)
 *  @param completion Block executed at the end of the get cash register method
 */
-(void)cashRegisters:(NSString* _Nonnull)merchantId shopId:(NSString * _Nullable)shopId cashDrawerVendor:(nullable NSString*)vendor completion:(CashRegisterCompletion)completion;

/**
 *  @brief Get cash registers shifts for a merchant
 *  @param cashRegisterInternalId NSString id of the cash register we are requesting shifts
 *  @param query params for the request, including page, page size, sorting, order, etc
 *  @param completion Block executed at the end of the get cash register shifts method
 */
-(void)shifts:(NSString*)cashRegisterInternalId query:(WDShiftQuery* _Nonnull)query completion:(CashRegisterShiftCompletion)completion;

/**
 *  @brief Get details of a specific cash registers shift
 *  @param shiftId NSString id of the cash register shift we want the details from
 *  @param cashRegisterInternalId NSString id of the cash register we are requesting shifts
 *  @param completion Block executed at the end of the get cash register shifts method
 */
-(void)shiftDetails:(NSString*)shiftId cashRegister:(NSString*)cashRegisterInternalId completion:(CashRegisterShiftDetailsCompletion)completion;

/**
 *  @brief Pay In /Out as cash operation for a cash register
 *  @param cashRegisterInternalId cash register we are requesting to pay/in operation for
 *  @param note NSString note is an optional note for paying in or out
 *  @param amount NSString amount is the cash to be paid IN (set Positive value) or OUT (set Negative value)
 *  @param currency NSString currency code of the cash paying in/out
 *  @param completion Block executed at the end of the open cash  shift method
 */
-(void)cashOperation:(NSString*)cashRegisterInternalId note:(NSString*)note amount:(NSDecimalNumber*)amount currency:(NSString*)currency completion:(void (^)(BOOL success, NSError *error))completion;

/**
 *  @brief Open cash shift for a cash register
 *  @param cashRegisterInternalId NSString id of the cash register we are requesting to open a shift
 *  @param note NSString note is an optional note for opening the shift
 *  @param amount NSString amount is the cash in the drawer when closing the shift
 *  @param completion Block executed at the end of the open cash shift method
 */
-(void)openShift:(NSString*)cashRegisterInternalId note:(NSString*)note amount:(NSDecimalNumber*)amount completion:(void (^)(BOOL success, NSError *error))completion;

/**
 *  @brief Close cash shift for a cash register
 *  @param cashRegisterInternalId NSString id of the cash register we are requesting to opeen a shift
 *  @param note NSString note is an optional note for closing the shift
 *  @param amount NSString amount is the cash in the drawer when closing the shift
 *  @param completion Block executed at the end of the close cash shift method
 */
-(void)closeShift:(NSString*)cashRegisterInternalId note:(NSString*)note amount:(NSDecimalNumber*)amount completion:(void (^)(BOOL success, NSError *error))completion;

/**
 *  @brief Do put a drawer serial number into a register
 *  @param cashRegister Cash Register to update
 *  @param terminal Device to update the Cash Register with
 *  @param completion Block executed at the end of the execution
 */
-(void)updateCashRegister:(WDCashRegister*)cashRegister withSerialNumberFromTerminal:(WDTerminal*)terminal completion:(void (^)(BOOL success, WDCashRegister*updatedRegister, NSError *error))completion;

/**
 *  @brief Get cash registers activities for a merchant's shift
 *  @param shiftId NSString id of the cash shift we are requesting activities
 *  @param query additional Query attributes page, page size 
 *  @param cashRegisterId NSString id of the cash register we are requesting shifts's activities
 *  @param completion Block executed at the end of the get cash register shifts activities method
 */
-(void)getOperationsForShift:(NSString* _Nonnull)shiftId query:(WDQuery*)query belongingToCashRegister:(NSString* _Nonnull)cashRegisterId completion:(CashRegisterActivityCompletion)completion;


@end


NS_ASSUME_NONNULL_END
