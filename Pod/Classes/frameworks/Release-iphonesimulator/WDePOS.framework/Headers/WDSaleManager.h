//
//  WDSaleManager.h
//   WDePOS
//
//  Created by Timko, Marek on 02/03/2017.
//  Copyright © 2020 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDDataTypes.h"

@protocol WDPaymentDelegate;
NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDSaleManager
 *  @brief Sale Management
 */
@interface WDSaleManager : NSObject

- (void)pay:(WDPaymentConfig* )saleConfiguration
   delegate:(id<WDPaymentDelegate>)delegate __deprecated_msg("Please use pay:withDelegate:");
/**
 @brief Start the payment process
 
 The delegate will be able to receive the below events:
 
 @b progress @@b  bearing the information about the payment process progress
 
 @b collectSignature @@b  that needs to execute the option to capture a signature and return the signature data
 
 @b confirm @@b  that informs that e.g. signature needs to be verified or WeChat/Alipay password to be entered by customer. This is done after the transaction has been already send to background, but the final approval depends on the merchant.
 
 @b cardApplication @@b  informs that an application selection is needed with the chip card inserted.
 
 @b completion @@b that will be called at the very end of payment flow. It provides an Saleobject (that may be nil if unauthorised) or a descriptive error
 @param saleRequestConfiguration Configuration to be used to perform this Sale
 @param delegate to receive the events from the payment flow
 **/
- (void)pay:(WDSaleRequestConfiguration* )saleRequestConfiguration
   withDelegate:(id<WDPaymentDelegate>)delegate;

/**
 *  @brief Cancel the payment flow ONLY if the situation/terminal allows it. For Miura terminals, this function works anytime. For other terminals (ie Spire ones), it ONLY works when waiting signature input -- the call will be IGNORED by the hardware otherwise, as they are designed to accept only cancellation through keypad.
 **/
- (void) cancelPay;

#pragma mark - Transaction history and statistics

/**
 *  @brief Retrieve the sales statistics based on the search criteria
 *  @param query Statistics query parameters
 *  @param completion Block executed at the end of the login method - provides Array of one element EMAIL or SMS to confirm which method for sending the Receipt was used
 */
-(void)salesStatistics:(WDStatisticsQuery*)query
            completion:(SaleStatisticsCompletion _Nonnull)completion;

/**
 *  @brief Retrieve the sales for the merchant user based on the search criteria
 *  @param searchCriteria Definition of search criteria in WDSaleQuery instance
 *  @param completion SaleQueryResponse block executed at the end of the method - provides Array of WDSales
 */
-(void)querySales:(WDSalesQuery*)searchCriteria
       completion:(SaleQueryResponse)completion;

/**
 *  @brief Retrieve the specified sale
 *  @param internalId transaction Id
 *  @param completion TransactionsQueryResponse block executed at the end of the method -  provides Array of WDSales
 */
-(void)getSale:(NSString*)internalId
    completion:(SaleQueryResponse )completion;

#pragma mark - Transaction management

/**
 *  @brief Reverse the sale
 *  @param internalId unique sale id - internal
 *  @param cashRegisterId cash register id - if exist and is needed for the merchant
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)reverseSale:(NSString * _Nonnull)internalId
    cashRegisterId:(NSString * _Nullable)cashRegisterId
           message:(NSString *_Nullable)message
        completion:(SaleUpdateCompletion _Nonnull)completion __deprecated_msg("Please use reverseSale:message:completion:");



/**
 *  @brief Reverse the Sale - All payments will be Reversed and Sale will be flagged as Cancelled
 *  @param internalId  Sale id - internal identificator of the original Sale
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)reverseSale:(NSString * _Nonnull)internalId
           message:(NSString *_Nullable)message
        completion:(SaleUpdateCompletion _Nonnull)completion ;

/**
 *  @brief Reverse the Sale - The specific payment will be Reversed.
 *         After all Payments are Reversed the Sale can be cancelled by using cancelSale:message:completion
 *  @param internalId unique sale id - internal identificator
 *  @param message detailed information to be set for this action
 *  @param externalId The Reversal ID as known by the external system
 *  @param payment Payment to Reverse
 *  @param completion Block executed at the end of the  method
 */
-(void)reverseSale:(NSString * _Nonnull)internalId
           message:(NSString *_Nullable)message
        externalId:(NSString *_Nullable)externalId
           payment:(WDPaymentReverse *)payment
        completion:(SaleUpdateCompletion _Nonnull)completion ;

/**
 *  @brief Cancel the Sale where all payments were Reversed previously by using reverseSale:message:externalId:payment:completion
 *  @param internalId unique sale id - internal
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)cancelSale:(NSString * _Nonnull)internalId
          message:(NSString *_Nullable)message
        completion:(SaleUpdateCompletion _Nonnull)completion ;

/**
 *  @brief Refund the Sale - For multitender may need to be called multiple times for each Payment and related items list you wish to return
 *  @param sale The Original sale to refund
 *  @param message Detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)refundSale:(WDSaleRequest * )sale
          message:(NSString *)message
       completion:(SaleUpdateCompletion )completion;

/**
 *  @brief Refund the Sale - The specific payment will be Refunded.
 *         Applicable for Sale in Unconfirmed or Failed Intervene state
 *  @param internalId The Original Sale id - internal identificator
 *  @param message detailed information to be set for this action
 *  @param externalId The Refund ID as known by the external system
 *  @param payment Payment to Refund
 *  @param completion Block executed at the end of the  method
 */
-(void)refundSale:(NSString * _Nonnull)internalId
           message:(NSString *_Nullable)message
        externalId:(NSString *_Nullable)externalId
           payment:(WDPaymentRefund *)payment
        completion:(SaleUpdateCompletion _Nonnull)completion ;

/**
 *  @brief Return content from a sale
 *  @param sale original sale to return rom
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)returnSale:(WDSaleRequest * )sale
          message:(NSString *)message
       completion:(SaleUpdateCompletion )completion;

/**
 *  @brief Fail the Sale
 *  @param internalId original sale Id to Fail
 *  @param message detailed information to be set for this action
 *  @param completion Block executed at the end of the  method
 */
-(void)failSale:(NSString * )internalId
          message:(NSString *)message
       completion:(SaleUpdateCompletion )completion;

/**
 *  @brief Send Receipt to Email  or Phone
 *  @param saleId Sale id for which the Receipt should be sent
 *  @param saleState state (WDSaleStateCompleted, WDSaleStateReturned, WDSaleStateCancelled, ...)
 *  @param emailOrPhone Email address or Phone number to which to send the Receipt
 *  @param completion Block executed at the end of the login method - provides Array of one element EMAIL or SMS to confirm which method for sending the Receipt was used
 */
-(void)sendReceiptForSale:(NSString *)saleId
            saleState:(WDSaleState)saleState
                  byEmailOrPhone:(NSString *)emailOrPhone
                      completion:(SendReceiptCompletion)completion;

/**
 *  @brief Maintain a sale
 *  @param maintainSale It includes the original sale id we want to maintain, and editable properties such as items, total amount, tax mode, description, etc.
 *  @param completion Block executed at the end of the  method
 */
-(void)maintainSale:(WDSaleMaintain * )maintainSale
         completion:(SaleUpdateCompletion )completion;

@end

NS_ASSUME_NONNULL_END
