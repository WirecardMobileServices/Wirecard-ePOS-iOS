//
//  WDDataTypes.h
//   WDePOS
//
//  Created by Danko, Radoslav on 22/10/15.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#ifndef WDA_DATA_TYPES
#define WDA_DATA_TYPES

#import <UIKit/UIKit.h>
#import "WDProductCatalogue.h"
#import "WDPaymentRequestCoupon.h"
#import "WDPaymentRequestCard.h"
#import "WDPaymentRequestCash.h"
#import "WDPaymentRequestAlipay.h"
#import "WDPaymentRequestWeChat.h"
#import "WDPaymentDetailCard.h"
#import "WDPaymentDetailCoupon.h"
#import "WDPaymentDetailWeChat.h"
#import "WDPaymentDetailAlipay.h"
#import "WDPaymentDetail.h"
#import "WDObject.h"


@class WDSaleRequest, WDSale, WDSaleResponse;

@class WDCashRegister;

#define kStarMicronicsModelName @"CB2002" //This is the actual model name of the Star Micronics drawer with no printer within

#define WDAVariableName(arg) (@""#arg)
#define kWDAMissingInputText @"Missing input: %@ variable cannot be nil."
#define WDAOptionsHasValue(options, value) (((options) & (value)) == (value))

#define WDAOBJC_STRINGIFY(x) @#x

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Enumerations

/**
 *  @typedef WDUpdateSeverity
 *  @brief Enumerator of severities for a update to be applied to a terminal
 **/
typedef NS_ENUM(NSInteger, WDUpdateSeverity ) {
    /// Mandatory firmware update to be applied asap (Miura) "A"
    WDUpdateSeverityMandatory,
    /// Mandatory firmware update that allows only one more transaction before forcing it (Miura) "B"
    WDUpdateSeverityNextMandatory,
    /// Non mandatory firmware, or no new firmware at all. No need to inform or trigger the update (Miura and Spire) "C"
    WDUpdateSeverityOptional,
    /// Firmware update to be applied at user's earliest convenience - client application should prompt for a manual installation repeatedly (Spire) "D"
    WDUpdateSeverityNotifyMandatory
};

/**
 *  @typedef WDExtensionTypeUUID
 *  @brief Enumerator of supported terminal extensions
 **/
typedef NS_ENUM(NSInteger, WDExtensionTypeUUID ) {
        WDExtensionNoneUUID = -1,
        WDExtensionUUID = 0,
        WDPosMateExtensionUUID,
        WDEmvSwipeExtensionUUID,
        WDUnimagExtensionUUID,
        WDDatecsExtensionUUID,
        WDAirPrintExtensionUUID,
        WDDatecsPrinterExtensionUUID,
        WDMPOPExtensionUUID,
        WDStarMicronicsExtensionUUID,
        WDMiuraExtensionUUID,
        WDPaxExtensionUUID,
        WDSocketExtensionUUID,
        WDWisepadExtensionUUID
};


/**
 *  @typedef WDStateUpdate
 *  @brief Enumerator of statuses for informing the flow status or asking feedback to the user, received in the progress block of Pay function.
 **/
typedef NS_ENUM(NSInteger, WDStateUpdate ) {
    WDStateConfigurationProgressTerminalNotReady = -1,
    WDStateWaitingForPlugIn = 0,
    WDStateWaitingForSwipe,
    WDStateDamagedChipAndWaitingForSwipe,
    WDStateProcessingData,
    WDStateOnlineProcessingData,
    WDStateFollowTerminalInstructions,
    WDStateInitialize,
    WDStateTerminalConfigOngoing,
    WDStateInsertOrSwipeCard,
    WDStateTapOrInsertOrSwipeCard,
    WDStateWaitingForInsertCard, //10
    WDStateCheckingCard,
    WDStateRemoveCard,
    WDStateCardRemoved,
    WDStateConfirmAmount,
    WDStateAmountConfirmed,
    WDStatePINEntered,
    WDStateCorrectPIN, //deprecated
    WDStatePINEntryLastTry,
    WDStateAskingForPIN,
    WDStatePinEntryWrong, //deprecated //20
    WDStateCardholderSignatureCheck,
    WDStateTerminalRestarting,
    WDStateGratuityEntryStarted,
    WDStateApplicationSelectionStarted,
    WDStateApplicationSelectionFinished,
    WDStateFollowInstructionsOnConsumerDevice, //on device CVM for contactless
    WDStateScanInitialisation,
    WDStateScanBarcode,
    WDStateScanFinished,
    
    WDStateConfigurationProgressUpdateWillStart=1000,//the below matches with WDUpdateConfigurationProgressUpdate enum
    WDStateConfigurationProgressDownloading,
    WDStateConfigurationProgressUnzipping,
    WDStateConfigurationProgressUploading,
    WDStateConfigurationProgressDeferredInstall
};


/**
 *  @typedef WDTaxationType
 *  @brief Enumerator with the taxation types.
 **/
typedef NS_ENUM(NSInteger, WDTaxationType ) {
    WDTaxationTypeGross = 0,
    WDTaxationTypeNet = 1
};

/**
 *  @typedef WDCashierPinValidationResult
 *  @brief Enumerator with the Pin validation results.
 **/
typedef NS_ENUM(NSInteger, WDCashierPinValidationResult ) {
    WDCashierPinValidationResultInvalid,
    WDCashierPinValidationResultValid,
    WDCashierPinValidationResultLocked,
    WDCashierPinValidationResultUnknown
};

/**
 *  @typedef WDSaleCompletionOperation
 *  @brief Enumerator with the Sale completion operation types.
 **/
typedef NS_ENUM(NSInteger, WDSaleCompletionOperation ) {
    WDSaleCompletionOperationConfirm,
    WDSaleCompletionOperationCancel
};

/**
 *  @typedef WDReversalReason
 *  @brief Enumerator with the reversal reasons
 **/
typedef NS_ENUM(NSInteger, WDReversalReason)
{   WDReversalReasonUndefined = -1,
    WDReversalReasonSignatureDeclined = 0,
    WDReversalReasonAdviceUnsupported = 1,
    WDReversalReasonCardDeclined=2,
    WDReversalReasonCaptureUnsupported=4,
    WDReversalReasonNoEFTResponse = 6,
    WDReversalReasonTerminalTerminated=7,
    WDReversalReasonSignatureVerificationTimeout = 10,
    WDReversalReasonOfflineDeclined = 11,
    WDReversalReasonUserCanceled = 12,
    WDReversalReasonSignatureEnterTimeout = 13,
//    WDReversalReasonGatewayDeclined = 14
};

/**
 *  @typedef WDExtensionConnectionStatus
 *  @brief The terminal connection status enumerator
 **/
typedef NS_ENUM(NSInteger, WDExtensionConnectionStatus){
    WDExtensionConnectionStatusDisconnected,
    WDExtensionConnectionStatusConnected,
    WDExtensionConnectionStatusUnknown,
    WDExtensionConnectionStatusConnecting
};

/**
 *  @typedef WDPrinterStateUpdate
 *  @brief Enumerator with the statuses of the printing flow, received in progress block of print.
 **/
typedef NS_ENUM(NSInteger, WDPrinterStateUpdate ) {
    WDPrinterStateInitialize = 0,
    WDPrinterStateConnecting,
    WDPrinterStateConnected,
    WDPrinterStatePrint,
    WDPrinterStateFinish
};

/**
 *  @typedef WDPrinterPaperStatus
 *  @brief Enumerator with the status of the paper amount.
 **/
typedef NS_ENUM(NSInteger, WDPrinterPaperStatus ) {
    WDPrinterStatusUnknown = 0,
    WDPrinterStatusNotSupported,
    WDPrinterStatusReady,
    WDPrinterStatusNearEmpty,
    WDPrinterStatusEmpty
};

/**
 *  @typedef WDUpdateConfigurationProgressUpdate
 *  @brief Enumerator with the progress during the terminal config file update
 **/
typedef NS_ENUM(NSInteger, WDUpdateConfigurationProgressUpdate) {
    WDUpdateConfigurationProgressTerminalNotReady = -1,
    WDUpdateConfigurationProgressUpdateWillStart=1000,
    WDUpdateConfigurationProgressDownloading,
    WDUpdateConfigurationProgressUnzipping,
    WDUpdateConfigurationProgressUploading,
    WDUpdateConfigurationProgressDeferredInstall
} ;

/**
 *  @typedef WDUpdateConfigurationStatus
 *  @brief Enumerator with the status during the terminal config file update
 **/
typedef NS_ENUM(NSInteger, WDUpdateConfigurationStatus) {
    WDUpdateConfigurationStatusTerminalDoesNotSupportUpdates,
    WDUpdateConfigurationStatusSuccess,
    WDUpdateConfigurationStatusUnnecessary,
    WDUpdateConfigurationStatusConfigurationDoesNotExist,
    WDUpdateConfigurationStatusFailure
} ;

/**
 *  @typedef WDPaymentConfirmationType
 *  @brief Enumerator with the type of the merchant payment confirmation
 **/
typedef NS_ENUM(NSInteger, WDPaymentConfirmationType)
{
    WDPaymentConfirmationTypeSignature = 0,
    WDPaymentConfirmationTypeAlipayPassword = 1,
    WDPaymentConfirmationTypeWeChatPassword = 2
};

/**
 *  @typedef WDPaymentConfirmationResult
 *  @brief Enumerator with the result of the merchant payment confirmation
 **/
typedef NS_ENUM(NSInteger, WDPaymentConfirmationResult)
{
    WDPaymentConfirmationResultRejected = 0,
    WDPaymentConfirmationResultApproved,
    WDPaymentConfirmationResultUnconfirmed
};


/**
 *  @typedef WDTerminalUpdateType
 *  @brief Enumerator of terminal update types
 **/
typedef NS_ENUM(NSInteger, WDTerminalUpdateType ) {
    WDTerminalUpdateTypeConfiguration,
    WDTerminalUpdateTypeFirmware,
    WDTerminalUpdateTypeApplication,
    WDTerminalUpdateTypeCAKeys
};

/**
 *  @typedef WDTerminalUpdateTypeMask
 *  @brief These constants are mask bits for specifying the terminal update type
 **/
typedef enum WDTerminalUpdateTypeMask : NSUInteger {
    WDTerminalUpdateTypeMaskConfiguration = (1 << WDTerminalUpdateTypeConfiguration),
    WDTerminalUpdateTypeMaskFirmware = (1 << WDTerminalUpdateTypeFirmware),
    WDTerminalUpdateTypeMaskApplication = (1 << WDTerminalUpdateTypeApplication),
    WDTerminalUpdateTypeMaskCAKeys = (1 << WDTerminalUpdateTypeCAKeys),
    WDTerminalUpdateTypeMaskSoftware = (WDTerminalUpdateTypeMaskFirmware | WDTerminalUpdateTypeMaskApplication),
    WDTerminalUpdateTypeMaskAll = (WDTerminalUpdateTypeMaskFirmware | WDTerminalUpdateTypeMaskApplication | WDTerminalUpdateTypeMaskConfiguration)
} WDTerminalUpdateTypeMask;

/**
 *  @typedef WDResultStatus
 *  @brief Enumerator with common response statuses
 **/
typedef NS_ENUM(NSInteger, WDResultStatus)
{
    WDResultStatusUnknown =0,
    WDResultStatusOK = 200,
    WDResultStatusCreated = 201,
    WDResultStatusUnauthorized = 401,
    WDResultStatusForbidden = 403,
    WDResultStatusNotFound = 404,
    WDResultStatusPasswordValidationFailure = 5000,
    WDResultStatusPasswordCriteriaNotMet = 5435
};



/**
 *  @typedef WDExtensionBatteryStatus
 *  @brief Enumerator with the battery status.
 **/
typedef NS_ENUM(NSInteger, WDExtensionBatteryStatus ) {
    WDExtensionBatteryStatusCharging = -3,
    WDExtensionBatteryStatusNoResponse = -2,
    WDExtensionBatteryStatusUnsupported = -1
};

/** 
 * @typedef WDQuerySort
 *  @brief Enumerator with the order by for sort.
 */
typedef NS_ENUM(NSUInteger, WDQuerySort) {
    /**
     */
    WDQuerySortDescending=0,
    /**
     */
    WDQuerySortAscending=1

};

/** 
 * @typedef WDSaleQueryOrderBy
 *  @brief Enumerator with order by for transaction queries
 */
typedef  NS_ENUM(NSUInteger,WDSaleQueryOrderBy) {
    /**
     */
    WDSaleQueryOrderByCreatedAt=0,
    /**
     */
    WDSaleQueryOrderByAmount,
    /**
     */
    //WDSaleQueryOrderByName //Switch does not support cardholdername sorting
} ;

/**
 * @typedef WDShiftQueryOrderBy
 *  @brief Enumerator with order by for Shift queries
 */
typedef  NS_ENUM(NSUInteger,WDShiftQueryOrderBy) {
    WDShiftQueryOrderByOpenTime=0,
    WDShiftQueryOrderByOpeningAmount
} ;


/**
 *  @typedef WDStatisticPeriod
 *  @brief Enumerator with the Statistic reporting Period
 **/
typedef NS_ENUM(NSUInteger, WDStatisticPeriod){
    WDStatisticPeriodUndefined,
    WDStatisticPeriodDay,
    WDStatisticPeriodWeek,
    WDStatisticPeriodMonth,
    WDStatisticPeriodQuarter,
    WDStatisticPeriodYear
};

/**
 *  @typedef WDStatisticGroupBy
 *  @brief Enumerator with the Statistic Grouping criteria
 **/
typedef NS_ENUM(NSUInteger, WDStatisticGroupBy){
    WDStatisticGroupByUndefined,
    WDStatisticGroupByType,
    WDStatisticGroupByStatus,
    WDStatisticGroupByCardBrand
};

/**
 *  @typedef WDStatisticStatuses
 *  @brief Enumerator with the Statistic Grouping criteria
 **/
typedef NS_ENUM(NSUInteger, WDStatisticStatus)
{
    WDStatisticStatusUndefined,
    WDStatisticStatusCompleted,
    WDStatisticStatusReturned,
    WDStatisticStatusCanceled
};

/**
 *  @typedef WDPrintFormat
 *  @brief Enumerator with the WD Print format
 **/
typedef NS_ENUM(NSUInteger, WDPrintFormat)
{
    WDPrintFormatHTML,
    WDPrintFormatPDF,
    WDPrintFormatUIImage,
    WDPrintFormatDatecs,
    WDPrintFormatWisepad
};

/**
 *  @typedef WDPrintDpi
 *  @brief Enumerator with the WD Print DPI
 **/
typedef NS_ENUM(NSUInteger, WDPrintDpi)
{
    WDPrintDpiDefault=306, 
    WDPrintDpiMpop=384,
    WDPrintDpiStarMicronics=576
};

/**
 *  @typedef WDSaleType
 *  @brief Enumerator with the Sale types.
 **/
typedef NS_ENUM(NSInteger, WDSaleType ) {
    WDSaleTypePurchase,
    WDSaleTypeReturn,
    WDSaleTypeUnknown
};

/**
 *  @typedef WDSaleState
 *  @brief Sale Status enumeration
 **/
typedef NS_ENUM(NSUInteger, WDSaleState) {
    WDSaleStateUnknown = 0,
    WDSaleStateInProgress,
    WDSaleStateOpen,
    WDSaleStateCompleted,
    WDSaleStateCanceled,
    WDSaleStatePartiallyReturned,
    WDSaleStateReturned,
    WDSaleStateFailedIntervene,
    WDSaleStateFailed
};

/**
 *  @typedef WDBarcodeSymbology
 *  @brief Barcode symbologies (standards) enumeration
 **/
typedef NS_ENUM(NSUInteger, WDBarcodeSymbology) {
    WDBarcodeSymbologyUnknown = 0,
    WDBarcodeSymbologyUPCE,
    WDBarcodeSymbologyUPCA,
    WDBarcodeSymbologyEAN8,
    WDBarcodeSymbologyEAN13,
    WDBarcodeSymbologyCode39,
    WDBarcodeSymbologyITF,
    WDBarcodeSymbologyCode128,
    WDBarcodeSymbologyCode93,
    WDBarcodeSymbologyCodabar,
    WDBarcodeSymbologyAztec,
    WDBarcodeSymbologyDataMatrix,
    WDBarcodeSymbologyPDF417,
    WDBarcodeSymbologyQRCode
};

#pragma mark - Response Callbacks
@class WDTransaction,WDExtendedProcessingInfo;

/**
 *  @typedef SignatureCollectedResponse
 *  @brief Callback to return collected signature back to the payment process
 *  @param collectedSignature signature image
 **/
typedef void (^SignatureCollectedResponse)(UIImage* _Nullable collectedSignature, NSError* _Nullable error);

/**
 *  @typedef PaymentCardApplicationSelectionResponse
 *  @brief Callback to return collected signature back to the payment process
 *  @param selectedApplication index of the selected card application
 **/
typedef void(^PaymentCardApplicationSelectionResponse)(NSUInteger selectedApplication);

/**
 *  @typedef SaleQueryResponse
 *  @brief Callback to return sales
 *  @param sales sales response block
 **/
typedef void(^SaleQueryResponse)(NSArray <WDSaleResponse *>* _Nullable sales, NSError* _Nullable error);

/**
 *  @typedef DeviceConnectionStatusCompletion
 *  @brief The callback to report the device connections status
 *  @param connectionStatus the connection status
 **/
typedef void (^DeviceConnectionStatusCompletion)(WDExtensionConnectionStatus connectionStatus);

/**
 *  @typedef BatteryLevelCallback
 *  @brief The callback to report the battery level
 **/
typedef void (^BatteryLevelCallback)(NSInteger);

/**
 *  @typedef ExtensionCommandCompletion
 *  @brief The callback to report the extension command status
 *  @param commandCompletionStatus the extension command SUCCESS
 *  @param error the extension command error
 **/
typedef void (^ExtensionCommandCompletion)(BOOL commandCompletionStatus,  NSError * _Nullable error);

/**
 *  @typedef ZReportCompletion
 *  @brief Callback to return created Z-Report
 *  @param report created report
 *  @param error error when creating report
 **/
typedef void(^ZReportCompletion)(id _Nullable report, NSError* _Nullable error);

/**
 *  @typedef ReceiptCompletion
 *  @brief Callback to return created receipt
 *  @param receipts array of created receipts - in the case of WDHtmlReceipt printing of All receipts (e.g. Original + Refunds) there can be multiple of receipts to be printed
 *  @param error error when creating receipt
 **/
typedef void(^ReceiptCompletion)(NSArray* _Nullable receipts, NSError* _Nullable error);


#pragma mark - Classes
/**
 *  @class WDVendor
 *  @brief Vendor information
 **/
@interface WDVendor : WDObject <NSCoding, NSCopying>
/**
 */
@property (nonatomic) WDExtensionTypeUUID  vendorUUID;
/**
 */
@property (nonatomic, copy) NSString * _Nonnull displayName;
/**
 */
@property (nonatomic, copy) NSString * _Nullable alternativeDisplayName;
@end
/**
 *  @class WDTerminal
 *  @brief Terminal information
 **/
@interface WDTerminal : WDObject <NSCoding, NSCopying>
/**     
 */
@property (nonatomic, copy) WDVendor * _Nonnull terminalVendor;
/**
 */
@property (nonatomic, copy) NSString * _Nonnull terminalModel;
/**
 * @brief terminal model as reported by EAAccessory
 */
@property (nonatomic, copy) NSString * _Nonnull eaAccessoryModel;
/**
 */
@property (nonatomic, copy) NSString * _Nonnull terminalUUID;
/**
 * @brief configurable through paymentMethods.xml
 */
@property (nonatomic, copy) NSString * _Nonnull displayName;
/**
 */
@property (nonatomic, copy) NSString * _Nonnull firmwareVersion;
/**
 */
@property (nonatomic) BOOL  connected;
@end

/**
 *  @class WDPaymentConfig
 *  @brief Payment configuration class. Content required to execute the payment flow
 **/
@interface WDPaymentConfig : NSObject
/**
 *  @brief Payment Configuration
 *  @param sale Sale Request
 *  @param allowGratuity Terminal to ask for gratuity during the payment flow
 *  @return Payment configuration - to be used in Sale Manager to perform the payment
 **/
-(instancetype)initWithSaleRequest:(WDSaleRequest *)sale
              allowGratuity:(BOOL)allowGratuity;
@property (nonatomic, strong) WDSaleRequest * _Nonnull sale;
@property (nonatomic) BOOL allowGratuity;
@end


/**
 *  @class WDSignatureRequest
 *  @brief Used by extension to notify the Payment Flow that the Signature needs to be collected.
 *              Extension supplies card holder information to be displayed if necessary
 **/
@interface WDSignatureRequest: NSObject
/**
 */
@property (nonatomic, strong) NSString * _Nullable cardHolderName;
/**
 */
@property (nonatomic, strong) NSString * _Nullable cardNumber;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable cardType;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable issuer;
/**
 */
@property (nonatomic, strong) NSString * _Nullable maskedPAN;
/**
 */
@property (nonatomic) NSNumber *gratuityAmount;
/**
 *@discussion sendCollectedSignature - callback to Extension once the Payment Flow signalls the Approval/Rejection of the signature
 *                                It is used on the client side to confirm the signature validity
 *                                *If nil* then extension awaits the confirmation of the signature - e.g. by pressing the terminal buttons
 *                                *If NOT nil* then terminal does not have buttons and confirmation must be handled by the client application
 *                                  (presenting the OK/Cancel buttons to confirm the signature validity)
 */
@property (nonatomic, copy) SignatureCollectedResponse  _Nonnull sendCollectedSignature;
@end

/**
 *  @class WDAppSelectionRequest
 *  @brief Used by the extension to notify the Payment Flow that the ICC application selection is to be performed by the client app
 *
 **/
@interface WDAppSelectionRequest: NSObject
/**
 * @brief ICC applications list as retrieved from the card chip
 */
@property (nonatomic, strong) NSArray * _Nullable appsArray;
/**
 * @brief callback to be performed by the client app once ICC application is selected
 */
@property (nonatomic, copy) PaymentCardApplicationSelectionResponse _Nonnull selectCardApplication;
@end

/**
 *  @class WDPrinterConfig
 *  @brief Printer configuration class. Receipt Content or Receipt Image required to execute the printing flow
 **/
@interface WDPrinterConfig : NSObject
/**
 *  @brief Printer configuration to perform the printing
 *  @param printer Printer to use for printing
 *  @param printJobs Printing jobs
 *  @return Printer configuration
 **/
-(instancetype)initWithPrinter:(WDTerminal *)printer
                     printJobs:(NSArray *)printJobs;
///Device to print the receipt on
@property (nonatomic, strong) WDTerminal *  _Nonnull printer;
/// printJobs to print where its type is one of WDReceipt | WDZReport | UIImage
@property (nonatomic, strong) NSArray * printJobs;
@end

/**
 *  @class WDProductImage
 *  @brief Product Image information
 **/
@interface WDProductImage : NSObject
/**
 */
@property (nonatomic, strong) NSString *  _Nonnull productId;
/**
 */
@property (nonatomic, strong) NSError * _Nullable error;
/**
 */
@property (nonatomic, strong) NSString * _Nullable imagePath;
@end

/**
 *  @class WDSaleItem
 *  @brief  Payment item info
 **/
//@interface WDSaleItem : NSObject
///**
// */
//@property (nonatomic, strong) NSString * _Nullable itemDescription;
///**
// */
//@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitPrice;
///**
// */
//@property (nonatomic) NSInteger quantity;
///**
// */
//@property (nonatomic, strong) NSDecimalNumber * _Nonnull unitTax;
///**
// */
//@property (nonatomic, strong) NSDecimalNumber * _Nonnull itemTotal;
///**
// */
//@property (nonatomic) WDSaleItemType itemType;
///**
// */
//-(NSDecimalNumber *)totalUnitPrice;
//@end

/**
 *  @class WDSaleStatistics
 *  @brief  Transaction Statistics
 **/
@interface WDSaleStatistics : NSObject
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *avgAmount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *maxAmount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *minAmount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *transactionCount;
/**
 */
@property (nullable, nonatomic, strong) NSDecimalNumber *turnover;
/**
 */
@property (nullable, nonatomic, strong) NSString *cardBrand;
/**
 */
@property (nullable, nonatomic, strong) NSString *period;
/**
 */
@property (nonatomic) WDTransactionType type;
/**
 */
@property (nonatomic) WDSaleState status;

-(NSDate *)date;
@end

/**
 *  @class WDRemindUsername
 *  @brief  Remind username object to be used with credential management API
 **/
@interface WDRemindUsername : NSObject
/**
 *  @brief Remind Username by Email
 *  @param email Email address to which to send the Username reminder
 *  @return new Remind Username
 **/
-(instancetype)initWithEmail:(NSString *)email;
/**
 */
@property (nullable, nonatomic, retain) NSString *email;
/**
 */
@property (nullable, nonatomic, retain) NSString *phone;
@end

/**
 *  @class WDRequestPasswordReset
 *  @brief  Request Reset Password object to be used with credential management API
 **/
@interface WDRequestPasswordReset : WDRemindUsername
/**
 *  @brief Reset Password for a user
 *  @param username Username for which to send the Password reset instructions
 *  @return new Reset Password
 **/
-(instancetype)initWithUsername:(NSString *)username;
/**
 */
@property (nullable, nonatomic, retain) NSString *username;
@end

/**
 *  @class WDChangePassword
 *  @brief  Change Password object to be used with credential management API
 **/
@interface WDChangePassword : NSObject
/**
 *  @brief Change Password for a current user
 *  @param oldPassword Current user password
 *  @param newPassword New user password
 *  @return new Change Password
 **/
-(instancetype)initWithOldPassword:(NSString *)oldPassword
                       newPassword:(NSString *)newPassword;
/**
 */
@property (nullable, nonatomic, retain) NSString *currentPassword;
/**
 */
@property (nullable, nonatomic, retain) NSString *theNewPassword;
@end

/**
 *  @class WDQuery
 *  @brief  Generic Query attributes
 **/
@interface WDQuery : NSObject
/**
 *  @brief Basic WD Query attributes used for query request
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @return new WD Query
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize;
/// Page to retrieve
@property (nonatomic) NSUInteger page;
/// Page size
@property (nonatomic) NSUInteger pageSize;
@end

/**
 *  @class WDSalesQuery
 *  @brief Transaction query class used in payment searches
 **/
@interface WDSalesQuery : WDQuery
/**
 *  @brief Sales Query attributes used for query request
 *  @param page Page to obtain from sorted results
 *  @param orderBy results ordered by
 *  @param orderSort results sorted ascending/descending
 *  @param statuses Sale Statuses to query for
 *  @param saleTypes Sale Types to query for
 *  @return new Sales Query
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                    orderBy:(WDSaleQueryOrderBy)orderBy
                  orderSort:(WDQuerySort)orderSort
                   statuses:(NSArray <NSNumber*>*)statuses
                  saleTypes:(NSArray <NSNumber*>*)saleTypes
             paymentMethods:(NSArray <NSNumber*>*)paymentMethods;
/**
 * If not specified then current merchant Sale query  is performed
 * System Admin can perform Sale query on any merchant
 **/
@property (nonatomic, strong) NSString * _Nullable merchantId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable fullTextSearch;
/**
 */
@property (nonatomic, strong) NSDecimalNumber *  _Nullable amount;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable cardNumber;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable receiptId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable gatewayReference;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable saleId;
/**
 */
@property (nonatomic, strong) NSString *  _Nullable originalSaleId;
/**
 * @brief saleTypes is an array of one or many of WDSaleType enumeration
 */
@property (nonatomic, strong) NSArray <NSNumber*>* _Nullable saleTypes;
/**
 * start interval for sale initialisation date
 */
@property (nonatomic, strong) NSDate *  _Nullable initializedFrom;
/**
 * end interval for sale initialisation date 
 */
@property (nonatomic, strong) NSDate *  _Nullable initializedTo;
/**
 * @brief statuses is an array of one or many of WDSaleState enumeration
 */
@property (nonatomic, strong) NSArray <NSNumber*>*  _Nullable statuses;
/**
 * @brief paymentMethods is an array of one or many of WDPaymentMethod enumeration
 */
@property (nonatomic, strong) NSArray <NSNumber*>*  _Nullable paymentMethods;
/**
 */
@property (nonatomic) WDQuerySort orderSort;
/**
 */
@property (nonatomic) WDSaleQueryOrderBy orderBy;
@end

/**
 *  @class WDStatisticsQuery
 *  @brief Transaction query class used in payment searches
 **/
@interface WDStatisticsQuery : NSObject
/**
 *  @brief Statistics Query attributes used for query request
 *  @param merchantId Merchant for whom to obtain the statistics
 *  @param from Date from - Sale processed date
 *  @param to Date to - Sale processed date
 *  @param status Sale Status
 *  @param period Statistics period
 *  @param currency Sales Currency
 *  @return new Statistics Query
 **/
-(instancetype)initWithMerchantId:(NSString *)merchantId
                            from:(NSDate *)from
                              to:(NSDate *)to
                           status:(WDStatisticStatus)status
                           period:(WDStatisticPeriod)period
                         currency:(NSString *)currency;
/**
 * The merchant for whom to perform the Sale statistics
 **/
@property (nonatomic, strong) NSString * _Nonnull merchantId;
/// Sale Statuses - grouping criteria
@property (nonatomic) WDStatisticStatus status;
/// Statistics Period
@property (nonatomic) WDStatisticPeriod period;
/**
 * start interval for transaction processing date
 */
@property (nonatomic, strong) NSDate * _Nonnull processedFrom;
/**
 * start interval for transaction processing date
 */
@property (nonatomic, strong) NSDate * _Nonnull processedTo;
/// Sales currency code
@property (nonatomic, strong) NSString * _Nonnull currency;
@end

/**
 *  @class WDProductsQuery
 *  @brief Products query class used in product searches
 **/
@interface WDProductsQuery : WDQuery
/**
 *  @brief Product Query attributes used for generic query request
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @param catalogueId Product Catalogue Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                catalogueId:(NSString *)catalogueId;
/**
 *  @brief Product Query attributes used to query specific Product
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param productId Product Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                catalogueId:(NSString *)catalogueId
                  productId:(NSString *)productId;

/**
 *  @brief Product Query attributes used to query specific Product
 *  @param page Page to obtain from sorted results
 *  @param pageSize Size of the Page from sorted results
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param categoryId Category Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                catalogueId:(NSString *)catalogueId
                  categoryId:(NSString *)categoryId;

/**
 *  @brief Product Query attributes used for Product Changes query request
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param date get Product Changes since this date
 *  @return new Product Query attributes
 **/
-(instancetype)initWithCatalogueId:(NSString *)catalogueId
                              date:(NSDate *)date;

/**
 *  @brief Product Query attributes used to query specific Product Image
 *  @param catalogueId Product Catalogue Id to be queried
 *  @param productId Product Id to be queried
 *  @return new Product Query attributes
 **/
-(instancetype)initWithCatalogueId:(NSString *)catalogueId
                         productId:(NSString *)productId;
/**
 */
@property (nonatomic, strong, nonnull) NSString * productCatalogueId;
/**
 */
@property (nonatomic, strong,nullable) NSString * productId;
/**
 */
@property (nonatomic, strong,nullable) NSString * externalId;
/**
 */
@property (nonatomic, strong,nullable) NSString * productName;
/**
 */
@property (nonatomic, strong,nullable) NSString * barcodeValue;
/**
 */
@property (nonatomic, strong,nullable) NSString * productCategoryName;
/**
 */
@property (nonatomic, strong,nullable) NSString * productCategoryId;
/**
 */
@property (nonatomic, strong,nullable) NSDate * dateToLookForChanges;
/**
 */
@property (nonatomic) BOOL sortAscending;
@end

/**
 *  @class WDTerminalHardwareInformation
 *  @brief Terminal Hardware information - firmware version, configuration version, serial number
 **/
@interface WDTerminalHardwareInformation : WDObject <NSCoding>
/**
 * terminal serial number
 */
@property (nonatomic, strong, nullable) NSString * serial;
/**
 * firmware version - OS
 */
@property (nonatomic, strong, nullable) NSString * firmwareVersion;
/**
 * application version - MPI
 */
@property (nonatomic, strong, nullable) NSString * applicationVersion;
/**
 * in the case the configuration was uploaded to the terminal the configuration version will be appended later by SDK
 */
@property (nonatomic, strong, nullable) NSString * configVersion;
@end

/**
 *  @class WDResult
 *  @brief  Result object for credential management API
 **/
@interface WDResult : NSObject
@property (nullable, nonatomic, retain) NSString *detail;
@property (nullable, nonatomic, retain) NSString *message;
@property (nonatomic ) WDResultStatus status;
@property (nullable, nonatomic, retain) NSNumber *code;
@end

/**
 *  @class WDPasswordPolicyResult
 *  @brief  Result object for password policy
 **/
@interface WDPasswordPolicyResult : NSObject
@property (nullable, nonatomic, retain) NSNumber *expirationPeriod;
@property (nullable, nonatomic, retain) NSNumber *expiresNotificationDays;
@property (nullable, nonatomic, retain) NSNumber *minDigits;
@property (nullable, nonatomic, retain) NSNumber *minLength;
@property (nullable, nonatomic, retain) NSNumber *minLowerCase;
@property (nullable, nonatomic, retain) NSNumber *minSpecialCharacters;
@property (nullable, nonatomic, retain) NSNumber *minUpperCase;
@property (nullable, nonatomic, retain) NSString *specialCharacters;
@property (nullable, nonatomic, retain) NSNumber *whitespaceAllowed;
@property (nullable, nonatomic, retain) NSNumber *passwordHistory;
@end

/**
 *  @class WDCurrencyCore
 *  @brief  Currency core object
 **/
@interface WDCurrencyCore : WDObject <NSCoding>
/**
 *  @brief Currency
 *  @param code Currency Code
 *  @return new Currency
 **/
-(instancetype)initWithCurrencyCode:(NSString *)code;
@property (nullable, nonatomic, strong) NSString *code;
@end

/**
 *  @class WDCurrency
 *  @brief  Currency object
 **/
@interface WDCurrency : WDCurrencyCore
@property (nullable, nonatomic, strong) NSNumber *minorUnit;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSNumber *number;
@end

/**
 *  @class WDCountry
 *  @brief  Country object
 **/
@interface WDCountry : WDObject <NSCoding, NSCopying>

@property (nullable, nonatomic, strong) NSString *alpha2code;
@property (nullable, nonatomic, strong) NSString *alpha3code;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSNumber *numericCode;
@end

/**
 *  @class WDAddress
 *  @brief  Address object
 **/
@interface WDAddress : WDObject <NSCoding, NSCopying>
@property (nullable, nonatomic, strong) NSString *city;
@property (nullable, nonatomic, strong) NSString *postalCode;
@property (nullable, nonatomic, strong) NSString *stateOrProvince;
@property (nullable, nonatomic, strong) NSString *street1;
@property (nullable, nonatomic, strong) NSString *street2;
@property (nullable, nonatomic, strong) WDCountry *country;
-(NSString *)formattedAddress;
-(id _Nullable)castTo:(Class _Nonnull)targetClass;
@end

/**
 *  @class WDShop
 *  @brief  Shop object
 **/
@interface WDShop : WDObject <NSCoding>
@property (nullable, nonatomic, strong) NSString *internalId;
@property (nullable, nonatomic, strong) NSString *externalId;
@property (nullable, nonatomic, strong) NSString *siteId;
@property (nullable, nonatomic, strong) WDAddress *address;
@property (nullable, nonatomic, strong) NSString *status;
@end

/**
 *  @class WDTaxRate
 *  @brief  Tax rate object
 **/
@interface WDTaxRate : WDObject<NSCoding>
@property (nullable, nonatomic, strong) NSDate *validFrom;
@property (nullable, nonatomic, strong) NSDecimalNumber *value;
@end

/**
 *  @class WDTaxCategory
 *  @brief  Tax category object
 **/
@interface WDTaxCategory : WDObject<NSCoding>
@property (nullable, nonatomic, retain) NSString *taxCategoryId;
@property (nullable, nonatomic, strong) NSDecimalNumber *currentValue;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) WDCountry *country;
@property (nullable, nonatomic, strong) NSArray<WDTaxRate *> *taxRates;
@end

/**
 *  @class WDPartner
 *  @brief  Partner category object
 **/
@interface WDPartner : WDObject <NSCoding>
@property (nullable, nonatomic, retain) NSString *partnerId;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) NSArray *paymentConstraints;
@end

/**
 *  @class WDMerchant
 *  @brief  Merchant object
 **/
@interface WDMerchant : WDObject <NSCoding>
@property (nullable, nonatomic, strong) NSNumber *defaultNetTaxation;
@property (nullable, nonatomic, strong) NSString *merchantId;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSString *notifyCallbackUrl;
@property (nullable, nonatomic, strong) NSString *phone;
@property (nullable, nonatomic, strong) NSNumber *receiptIncludedSaleItems;
@property (nullable, nonatomic, strong) NSNumber *smsSendingAllowed;
@property (nullable, nonatomic, strong) NSString *status;
@property (nullable, nonatomic, strong) WDAddress *address;
@property (nullable, nonatomic, strong) NSArray<WDCurrency *> *configuredCurrencies;
@property (nullable, nonatomic, strong) WDCurrency *defaultCurrency;
@property (nullable, nonatomic, strong) NSNumber *mccCode;
@property (nullable, nonatomic, strong) NSArray <WDTaxCategory *>* taxCategories;
@property (nullable, nonatomic, strong) NSDate *created;
@property (nullable, nonatomic, strong) NSString *supportEmail;
@property (nullable, nonatomic, strong) NSString *taxNumber;
@property (nullable, nonatomic, strong) NSString *supportPhone;
@property (nullable, nonatomic, strong) NSNumber *serviceChargeRate;
@property (nullable, nonatomic, strong) NSNumber *serviceChargeTaxRate;
@property (nullable, nonatomic, strong) NSNumber *tipTaxRate;
@property (nullable, nonatomic, strong) WDPartner *partner;
@property (nullable, nonatomic, strong) NSArray<WDShop *> *shops;
@property (nullable, nonatomic, strong) NSNumber *flatDiscount;
@property (nullable, nonatomic, strong) NSNumber *cashRegistersRequired;
@property (nullable, nonatomic, strong) NSString *erpSystemType;
/// Distinct Union of configured currencies and default currency
-(NSArray *)availableCurrencies;
@end



/**
 *  @class WDMerchantUser
 *  @brief  Merchant user object
 **/
@interface WDMerchantUser : WDObject<NSCoding>
@property (nullable, nonatomic, strong) NSDate *accountExpirationReference;
@property (nullable, nonatomic, strong) NSString *email;
@property (nullable, nonatomic, strong) NSNumber *failedLoginCount;
@property (nullable, nonatomic, strong) NSString *merchantUserId;
@property (nullable, nonatomic, strong) NSString *name;
@property (nullable, nonatomic, strong) NSString *phone;
@property (nullable, nonatomic, strong) NSNumber *requestPasswordChange;
@property (nullable, nonatomic, strong) NSDate *lastPasswordChanged;
@property (nullable, nonatomic, strong) NSString *status;
@property (nullable, nonatomic, strong) NSString *username;
@property (nullable, nonatomic, strong) WDMerchant *merchant;
@property (nullable, nonatomic, strong) NSArray<NSString *> *roles;
@property (nullable, nonatomic, strong) NSString *timeZone;
@property (nullable, nonatomic, strong) NSDate *created;
@property (nullable, nonatomic, strong) NSArray<WDShop *> *merchantShops;
@end

/**
 *  @class WDShiftReportCategoryItem
 *  @brief Item of a category received in the Cash Shift Report
 **/
@interface WDShiftReportCategoryItem : WDObject<NSCoding>
///**
// */
@property (nullable, nonatomic, copy) NSString *itemType;
///**
// */
@property (nonnull, nonatomic, copy) NSString *name;
///**
// */
@property (nullable, nonatomic, copy) NSDecimalNumber *netAmount;
///**
// */
@property (nullable, nonatomic, copy) NSDecimalNumber *taxAmount;
///**
// */
@property (nullable, nonatomic, copy) NSDecimalNumber *grossAmount;
///**
// */
-(instancetype)initWithShiftReportCategoryItem:(id)shiftReportCategoryItem;
@end

/**
 *  @class WDShiftReportCategory
 *  @brief Category received in the Cash Shift Report
 **/
@interface WDShiftReportCategory : WDObject<NSCoding>
///**
// */
@property (nullable, nonatomic, copy) NSString *categoryType;
///**
// */
@property (nonnull, nonatomic, copy) NSString *name;
///**
// */
@property (nullable, nonatomic, retain) NSArray <WDShiftReportCategoryItem *>*categoryItems;
///**
// */
-(instancetype)initWithShiftReportCategory:(id)shiftReportCategory;
@end

/**
 *  @class WDShiftReport
 *  @brief Report for a Cash Shift
 **/
@interface WDShiftReport : WDObject<NSCoding>
///**
// */
@property (nullable, nonatomic, strong) NSString *reportNumber;
///**
// */
@property (nullable, nonatomic, strong) WDMerchant *merchant;
///**
// */
@property (nullable, nonatomic, strong) WDShop *shop;
///**
// */
@property (nullable, nonatomic, strong) NSArray <WDShiftReportCategory *>*reportCategories;
///**
// */
-(instancetype)initWithShiftReport:(id)shiftReport;
@end

/**
 *  @class WDMerchantCashier
 *  @brief Merchant Cashier object
 **/
@interface WDMerchantCashier : WDObject<NSCoding>
/// Switch Cashier ID
@property (nullable, nonatomic, retain) NSString *internalId;
/// ERP Cashier ID
@property (nullable, nonatomic, retain) NSString *externalId;
/**
 */
@property (nonatomic, retain) NSNumber *version;
/**
 */
@property (nullable, nonatomic, retain) NSString *firstName;
/**
 */
@property (nullable, nonatomic, retain) NSString *lastName;
/// Pin Hash
@property (nullable, nonatomic, retain) NSString *pin;
/**
 */
@property (nullable, nonatomic, retain) NSArray<NSString *> *roles;
/**
 */
@property (nullable, nonatomic, retain) NSString *merchantId;
/**
 */
@property (nullable, nonatomic, retain) NSString *userId;
///**
// */
-(instancetype)initWithMerchantCashier:(id)mercCashier;
@end

/**
 *  @class WDCashShift
 *  @brief Cash Register object - Cash/Drawer Management
 **/
@interface WDCashShift : WDObject<NSCoding>
///**
// */
@property (nullable, nonatomic, retain) NSString *internalId;
///**
// */
@property (nullable, nonatomic, retain) NSDate *openTime;
///**
// */
@property (nullable, nonatomic, retain) NSDate *closeTime;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *openingAmount;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *closingAmount;
///**
// */
@property (nullable, nonatomic, retain) NSString *openingNote;
///**
// */
@property (nullable, nonatomic, retain) NSString *closingNote;
///**
// */
@property (nullable, nonatomic, retain) NSString *shiftStatus;
///**
// */
@property (nullable, nonatomic, retain) WDMerchantCashier *openedBy;
///**
// */
@property (nullable, nonatomic, retain) WDMerchantCashier *closedBy;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *cashPurchases;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *cashRefunds;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *cashOperationsBalance;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *cashBalance;
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *currentValue;
///**
// */
@property (nullable, nonatomic, retain) WDShiftReport *shiftReport;
///
@property (nullable, nonatomic, retain) WDCashRegister *cashRegister;
///
-(instancetype)initWithMerchantShift:(id)merchantShift;
/**
 * @brief Default Design of the Z-Report
 * @param format Format of the report
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param completion Report in the requested format
 */
-(void)zReport:(WDPrintFormat)format
           dpi:(WDPrintDpi)dpi
    completion:(ZReportCompletion)completion;

/**
 * @brief Default Design of the Z-Report
 * @param format Format of the report
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param language to use for translating the Z-Report labels (current NSLocale is used for date formats)
 * @param completion Report in the requested format
 */
-(void)zReport:(WDPrintFormat)format
           dpi:(WDPrintDpi)dpi
      language:(NSString *)language
    completion:(ZReportCompletion)completion;

/**
 * @brief Default Design of the Z-Report
 * @param format Format of the report
 * @param dpi dots per width of the receipt to be printed - not used for HTML or Datecs native format
 * @param locale to use for translating the Z-Report labels (language) and formatting the dates (country)
 * @param completion Report in the requested format
 */
-(void)zReport:(WDPrintFormat)format
           dpi:(WDPrintDpi)dpi
        locale:(NSLocale *)locale
    completion:(ZReportCompletion)completion;
@end

/**
 *  @class WDCashActivity
 *  @brief Cash Register object - Cash/Drawer Management
 **/
@interface WDCashActivity : WDObject<NSCoding>
///**
// */
@property (nullable, nonatomic, retain) NSDecimalNumber *amount;
///**
// */
@property (nullable, nonatomic, retain) NSDate *timestamp;
///**
// */
@property (nullable, nonatomic, retain) NSString *operationType;
///**
// */
@property (nullable, nonatomic, retain) NSString *firstname;
///**
// */
@property (nullable, nonatomic, retain) NSString *lastname;
///**
// */
@property (nullable, nonatomic, retain) NSString *note;
///**
// */
@property (nullable, nonatomic, retain) NSString *internalId;
///**
// */
-(instancetype)initWithShiftActivity:(id)shiftActivity;

@end

/**
 *  @class WDCashDrawerType
 *  @brief Cash Drawer Type
 **/
@interface WDCashDrawerType : WDObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *internalId;
/**
 */
@property (nullable, nonatomic, strong) NSNumber *version;
/**
 */
@property (nullable, nonatomic, strong) NSString *vendor;
/**
 */
@property (nullable, nonatomic, strong) NSString *model;
@end

/**
 *  @class WDCashRegister
 *  @brief Cash Register object - Cash/Drawer Management
 **/
@interface WDCashRegister : WDObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *internalId;
/**
 */
@property (nullable, nonatomic, retain) NSString *externalId;
/**
 */
@property (nonatomic, retain) NSNumber *version;
/**
 */
@property (nullable, nonatomic, retain) NSString *registerName;
/**
 */
@property (nullable, nonatomic, retain) NSString *serialNumber;
/**
 */
@property (nullable, nonatomic, retain) NSString *drawerStatus;
///**
// */
@property (nullable, nonatomic, retain) WDMerchantCashier *openedBy;
///**
// */
@property (nullable, nonatomic, retain) WDMerchantCashier *closedBy;
///**
// */
@property (nullable, nonatomic, retain) WDMerchant *merchant;
///**
// */
@property (nullable, nonatomic, retain) WDShop *shop;
///**
// */
@property (nullable, nonatomic, retain) WDCashShift *lastShift;
///**
// */
@property (nullable, nonatomic, retain) WDCurrency *currency;
///**
// */
@property (nullable, nonatomic, retain) WDCashDrawerType *cashDrawerType;
@end


/**
 *  @class WDUnitPrice
 *  @brief  Unit Price object
 **/
@interface WDUnitPrice : WDObject <NSCoding>
/**
 *  @brief Unit Price
 *  @param currency Currency
 *  @param unitValue Unit Price value
 *  @return new Unit Price
 **/
-(instancetype)initWithCurrency:(WDCurrencyCore *)currency unitValue:(NSNumber  *)unitValue;

@property (nonatomic, strong) WDCurrencyCore  *currency;
@property (nonatomic, strong) NSNumber  *unitValue;
@end

/**
 *  @class WDProductCatalogue
 *  @brief  Product Catalogue object
 **/
//@interface WDProductCatalogue : NSObject
//@property (nullable, nonatomic, retain) NSString *productCatalogueId;
//@property (nullable, nonatomic, retain) NSString *merchantId;
//@property (nullable, nonatomic, retain) NSString *productCatalogueName;
//@property (nullable, nonatomic, retain) NSString *productCatalogueDescription;
//@property (nullable, nonatomic, retain) NSNumber *version;
//@property (nullable, nonatomic, retain) NSString *lastUpdated;
//@end

/**
 *  @class WDTerminalCapabilities
 *  @brief  Terminal Capabilities template
 **/
@interface WDTerminalCapabilities : WDObject
@property (nullable, nonatomic, retain) NSString *terminalCapabilitiesId;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) NSString *emvTerminalType;
@property (nullable, nonatomic, retain) NSString *emvTransactionCategoryCode;
@property (nullable, nonatomic, retain) NSString *capabilities;
@property (nullable, nonatomic, retain) NSString *additionalCapabilities;
@end

/**
 *  @class WDICCApplication
 *  @brief  ICC Application template
 **/
@interface WDICCApplication : WDObject
@property (nullable, nonatomic, retain) NSString *iccApplicationId;
@property (nullable, nonatomic, retain) NSString *aid;
@property (nullable, nonatomic, retain) NSString *version;
@property (nullable, nonatomic, retain) NSString *product;
@property (nullable, nonatomic, retain) NSString *networkId;
@end

/**
 *  @class WDAID
 *  @brief  AID template
 **/
@interface WDAID : WDObject
@property (nullable, nonatomic, retain) NSString *aid;
@property (nullable, nonatomic, retain) NSString *ddol;
@property (nullable, nonatomic, retain) NSString *targetPercentage;
@property (nullable, nonatomic, retain) NSString *tacOnline;
@property (nullable, nonatomic, retain) NSString *terminalFloorLimit;
@property (nullable, nonatomic, retain) NSString *thresholdValue;
@property (nullable, nonatomic, retain) NSString *maxTargetPercentage;
@property (nullable, nonatomic, retain) NSString *tacDenial;
@property (nullable, nonatomic, retain) NSString *preferredApplicationName;
@property (nullable, nonatomic, retain) NSString *tdol;
@property (nullable, nonatomic, retain) NSString *applicationVersionNumber;
@property (nullable, nonatomic, retain) NSString *tacDefault;
@property (nullable, nonatomic, retain) NSString *acquirerIdentifier;
@property (nullable, nonatomic, retain) NSString *forceOnline;
@property (nullable, nonatomic, retain) NSString *transactionType;
@end

/**
 *  @class WDAIDConfiguration
 *  @brief  AID Configuration
 **/
@interface WDAIDConfiguration : WDObject
@property (nullable, nonatomic, retain) NSString *aidConfigurationId;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) WDICCApplication *chipApplication;
@property (nullable, nonatomic, retain) WDAID *items;
@end

/**
 *  @class WDNetwork
 *  @brief  Issuer Network detail
 **/
@interface WDNetwork : WDObject
@property (nullable, nonatomic, retain) NSString *networkId;
@property (nullable, nonatomic, retain) NSString *networkIssuerName;
@end

/**
 *  @class WDTerminalProfile
 *  @brief  Terminal Profile
 **/
@interface WDTerminalProfile : WDObject
@property (nullable, nonatomic, retain) NSString *terminalProfileId;
@property (nullable, nonatomic, retain) NSString *tid;
@property (nullable, nonatomic, retain) NSString *mid;
@property (nullable, nonatomic, retain) WDCurrency *currency;
@property (nullable, nonatomic, retain) WDNetwork *network;
-(NSString*)getNetworkName;
@end

/**
 *  @class WDTerminalAIDConfiguration
 *  @brief Terminal AID Configuration
 **/
@interface WDTerminalAIDConfiguration : WDObject
@property (nullable, nonatomic, retain) NSString *merchantName;
@property (nullable, nonatomic, retain) NSNumber *mcc;
@property (nullable, nonatomic, retain) NSString *terminalCountryCode;
@property (nullable, nonatomic, retain) NSArray<WDAIDConfiguration *> *aidConfigurations;
@property (nullable, nonatomic, retain) WDTerminalCapabilities *terminalCapabilitiesTemplate;
@property (nullable, nonatomic, retain) NSArray<WDTerminalProfile *> *terminalProfiles;

#pragma mark  Helpers
-(WDAIDConfiguration *)getTerminalAIDConfigurationForAID:(NSString *)aid;
-(WDAIDConfiguration *)getTerminalAIDChipAppConfigurationForAID:(NSString *)aid;
-(WDTerminalProfile *)getTerminalProfileForCurrency:(NSString *)currencyCode andNetwork:(NSString *)networkId;
@end


/**
 *  @class WDShiftQuery
 *  @brief  Query the shifts
 **/
@interface WDShiftQuery : WDQuery
/**
 *  @brief Shift Query attributes used for query request
 *  @param page Page to obtain from sorted results
 *  @param orderBy results ordered by
 *  @param orderSort results sorted ascending/descending
 *  @return new WD Query
 **/
-(instancetype)initWithPage:(NSUInteger)page
                   pageSize:(NSUInteger)pageSize
                    orderBy:(WDShiftQueryOrderBy)orderBy
                  orderSort:(WDQuerySort)orderSort;
@property (nonatomic) WDShiftQueryOrderBy orderBy;
@property (nonatomic) WDQuerySort orderSort;
@end

/**
 *  @class WDEncryptionParameters
 *  @brief Encryption parameters
 **/
@interface WDEncryptionParameters : NSObject
/**
 */
@property (nullable, nonatomic, retain) NSString *encoding;
/**
 */
@property (nullable, nonatomic, retain) NSString *format;
/**
 */
@property (nullable, nonatomic, retain) NSString *ksn;
/**
 */
@property (nullable, nonatomic, retain) NSString *name;
/**
 */
@property (nullable, nonatomic, retain) NSString *padding;
/**
 */
@property (nullable, nonatomic, retain) NSString *version;
@end

/**
 *  @class WDTerminalRKIRequest
 *  @brief Terminal Remote Key Injection values
 **/
@interface WDTerminalRKIRequest : WDObject
/**
 */
@property (nullable, nonatomic, retain) NSString *vendor;
/**
 */
@property (nullable, nonatomic, retain) NSString *model;
/**
 */
@property (nullable, nonatomic, retain) NSString *serialNo;
/**
 */
@property (nullable, nonatomic, retain) NSString *prodSignCrt;
/**
 */
@property (nullable, nonatomic, retain) NSString *terminalCrt;
/**
 */
@property (nullable, nonatomic, retain) NSString *tempKeyCrt;
/**
 */
@property (nullable, nonatomic, retain) NSString *suggestedIksn;

@end

/**
 *  @class WDTerminalRKI
 *  @brief Terminal Remote Key Injection values
 **/
@interface WDTerminalRKI : WDObject
/**
 */
@property (nullable, nonatomic, retain) NSString *hsmCertificate;
/**
 */
@property (nullable, nonatomic, retain) NSString *iksnPin;
/**
 */
@property (nullable, nonatomic, retain) NSString *iksnSred;
/**
 */
@property (nullable, nonatomic, retain) NSString *initialDukptPin;
/**
 */
@property (nullable, nonatomic, retain) NSString *initialDukptSred;
/**
 */
@property (nullable, nonatomic, retain) NSString *tmk;
/**
 */
@property (nullable, nonatomic, retain) NSString *tmkSignature;

@end

/**
 *  @class WDMember
 *  @brief ERP Members information
 **/
@interface WDMember : WDObject<NSCoding>
/**
 */
@property (nullable, nonatomic, retain) NSString *memberId;
/**
 */
@property (nullable, nonatomic, retain) NSString *accountId;
/**
 */
@property (nullable, nonatomic, retain) NSString *lifeCycleStatusCode;
/**
 */
@property (nullable, nonatomic, retain) NSString *birthDate;
/**
 */
@property (nullable, nonatomic, retain) NSString *email;
/**
 */
@property (nullable, nonatomic, retain) NSString *surname;
/**
 */
@property (nullable, nonatomic, retain) NSString *firstName;
@end

/**
 *  @class WDTerminalUpdate
 *  @brief Update information for the terminal
 **/
@interface WDTerminalUpdate : WDObject<NSCoding>
///
@property (nullable, nonatomic, retain) NSString *version;
///
@property (nullable, nonatomic, retain) NSNumber *size;
///
@property (nullable, nonatomic, retain) NSString *terminalUpdateId;
///
@property (nullable, nonatomic, retain) NSString *checksum;
///
@property (nullable, nonatomic, retain) NSString *updateDescription;
///
@property (nonatomic) WDUpdateSeverity severity;
///
@property (nullable, nonatomic, retain) NSString *downloadURL;
@end

/**
 *  @class WDTerminalUpdates
 *  @brief Set of updates information for the terminal APPLICATION + CONFIGURATION + FIRMWARE
 **/
@interface WDTerminalUpdates : WDObject<NSCoding>

@property (nullable, nonatomic, retain) WDTerminalUpdate *assignedApplication;
@property (nullable, nonatomic, retain) WDTerminalUpdate *assignedConfiguration;
@property (nullable, nonatomic, retain) WDTerminalUpdate *assignedFirmware;

@end

/**
 *  @class WDReceiptAddress
 *  @brief Merchant Address
 *  @discussion Receipt Merchant Address
 **/
@interface WDReceiptAddress : NSObject
@property (nullable, nonatomic, strong) NSString *city;
@property (nullable, nonatomic, strong) NSString *postalCode;
@property (nullable, nonatomic, strong) NSString *stateOrProvince;
@property (nullable, nonatomic, strong) NSString *street1;
@property (nullable, nonatomic, strong) NSString *street2;
@property (nullable, nonatomic, strong) NSString *country;

- (nonnull instancetype)init __attribute__((unavailable("use initWithWDAddress:")));
+ (nonnull instancetype)new __attribute__((unavailable("use initWithWDAddress:")));
- (nonnull instancetype)initWithWDAddress:(WDAddress *)address;
@end

#pragma mark - Request Callbacks
/**
 *  @typedef PaymentProgress
 *  @brief Callback to be executed upon payment process stage change
 *  @param paymentProgress Coded payment progress
 **/
typedef void (^PaymentProgress)(WDStateUpdate paymentProgress);

/**
 *  @typedef PaymentCardApplicationSelection
 *  @brief Used by extension to notify the Payment Flow to ask for the Card application selection
 *  @param appSelectionRequest  WDAppSelectionRequest to be sent to the client application
 *  @see WDAppSelectionRequest
 **/
typedef void (^PaymentCardApplicationSelectionRequest)(WDAppSelectionRequest * _Nullable appSelectionRequest);

/**
 *  @typedef PrintCompletion
 *  @brief Callback to be executed in the case the printing is complete
 **/
typedef void (^PrintCompletion)(BOOL printStatusOK, NSError* _Nullable printError);

/**
 *  @typedef PrinterStateUpdate
 *  @brief Callback to be executed upon print process stage change
 **/
typedef void (^PrinterStateUpdate)(WDPrinterStateUpdate printProgress);

/**
 *  @typedef DeviceDiscoveryCompletion
 *  @brief Callback to be executed upon completion of device discovery
 *  @param devices of WDTerminal
 **/
typedef void (^DeviceDiscoveryCompletion)(NSArray <WDTerminal *>* _Nullable devices, NSError* _Nullable devicesError);
/**
 *  @typedef VendorDiscoveryCompletion
 *  @brief Callback to be executed upon completion of vendor discovery
 *  @param vendors of WDVendor
 **/
typedef void (^VendorDiscoveryCompletion)(NSArray <WDVendor *> * _Nullable vendors);
/**
 *  @typedef WDUpdateConfigurationProgress
 *  @brief Callback to be executed at each progress update of the terminal configuration update process
 *  @param configurationUpdate progress status
 **/
typedef void (^UpdateConfigurationProgress)(WDUpdateConfigurationProgressUpdate configurationUpdate);

/**
 *  @typedef UpdateTerminalCompletion
 *  @brief Callback to be executed at the end of the terminal configuration update process
 *  @param updateStatus terminal update result
 **/
typedef void (^UpdateTerminalCompletion)(WDUpdateConfigurationStatus updateStatus, NSError* _Nullable updateError);

/**
 *  @typedef TerminalUpdatesCompletion
 *  @brief Callback to be executed at the end of the available terminal updates process
 *  @param availableUpdates the details of the available updates (Configuration, Terminal Application, Firmware)
 **/
typedef void (^TerminalUpdatesCompletion)(WDTerminalUpdates *_Nullable availableUpdates, NSError* _Nullable availableUpdatesError);

/**
 *  @typedef PaymentConfirmationResult
 *  @brief The callback to pass to startPay function with the result of Customer confirmation - either Signature confirmation or Password entry completed confirmation (In the case of WeChat)
 *  @param paymentConfirmationResult the result of the Merchant veryfying the customer signature or confirming Password was entered by customer (WeChat customer)
 **/
typedef void (^PaymentConfirmationResult)(WDPaymentConfirmationResult paymentConfirmationResult);

/**
 *  @typedef SignatureRequest
 *  @brief Callback to be executed if the signature is required during the payment process
 *  @param signatureRequest signature request block
 **/
typedef void (^SignatureRequiredRequest)(WDSignatureRequest* _Nonnull signatureRequest);

/**
 *  @typedef MerchantDetailCompletion
 *  @brief The callback upon the merchant detail method completion
 *  @param merchantUser the result of the login method - available if correct user credentials used
 **/
typedef void(^MerchantDetailCompletion)(WDMerchantUser * _Nullable merchantUser, NSError * _Nullable merchantUserError);

/**
 *  @typedef MerchantCashierCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param merchantCashiers the result of the getMerchantCashiers method - available if correctly logged in
 **/
typedef void(^MerchantCashierCompletion)( NSArray <WDMerchantCashier *>* _Nullable merchantCashiers, NSError * _Nullable merchantCashiersError);

/**
 *  @typedef CurrentUserCompletion
 *  @brief The callback upon the current user method completion
 *  @param currentUser Current user - as per credentials used when initializing the SDK
 *  @param cashier Cashier record if exists for the Current user
 *  @error Error from the current user process
 **/
typedef void(^CurrentUserCompletion)( WDMerchantUser * _Nullable currentUser, WDMerchantCashier * _Nullable cashier, NSError * _Nullable error);

/**
 *  @typedef MerchantCashierPinValidationCompletion
 *  @brief The callback upon the merchant cashier PIN validation method completion
 *  @param pinValidationResult shows the result of the PIN validation
 **/
typedef void(^MerchantCashierPinValidationCompletion)( WDCashierPinValidationResult pinValidationResult, NSError * _Nullable merchantCashierValidationError);

/**
 *  @typedef CashRegisterCompletion
 *  @brief The callback upon the cash registers method completion
 *  @param cashRegisters the result of the cashRegisters:shopId:cashDrawerVendor: method - available if correctly logged in
 **/
typedef void(^CashRegisterCompletion)( NSArray <WDCashRegister *>* _Nullable cashRegisters, NSError * _Nullable cashRegistersError);

/**
 *  @typedef CashRegisterDetailsCompletion
 *  @brief The callback upon the cash register method completion
 *  @param cashRegister the result of the cashRegisters:shopId:cashDrawerVendor: method - available if correctly logged in
 **/
typedef void(^CashRegisterDetailsCompletion)( WDCashRegister * _Nullable cashRegister, NSError * _Nullable cashRegisterError);

/**
 *  @typedef CashRegisterShiftCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param cashShifts the result of the getMerchantCashiers method - available if correctly logged in
 **/
typedef void(^CashRegisterShiftCompletion)( NSArray <WDCashShift *>* _Nullable cashShifts, NSError * _Nullable cashShiftsError);

/**
 *  @typedef CashRegisterShiftCompletion
 *  @brief The callback upon the merchant cashier method completion
 *  @param cashShifts shifts for this merchant
 *  @param cashShiftsError error obtaining shifts
 **/
typedef void(^CashRegisterShiftDetailsCompletion)( WDCashShift * _Nullable cashShifts, NSError * _Nullable cashShiftsError);

/**
 *  @typedef CashRegisterActivityCompletion
 *  @brief The callback upon the cash register activity completion
 *  @param cashActivities cash activities of this cashier
 *  @param cashActivitiesError  error obtaining the cash activities
 **/
typedef void(^CashRegisterActivityCompletion)( NSArray <WDCashActivity *>* _Nullable cashActivities, NSError * _Nullable cashActivitiesError);

/**
 *  @typedef SaleCompletion
 *  @brief Callback to be executed at the end of the payment process
 *  @param saleResponse transaction object
 *  @param saleResponseError if encountered during the paymnet process
 **/
typedef void (^SaleCompletion)(WDSaleResponse* _Nullable saleResponse, NSError* _Nullable saleResponseError);

/**
 *  @typedef SendReceiptCompletion
 *  @brief Callback to be executed at the end of the send receipt process
 *  @param recepients recepient email addresses
 **/
typedef void (^SendReceiptCompletion)(NSArray <NSString*>* _Nullable recepients, NSError* _Nullable error);

/**
 *  @typedef CredentialManagementCompletion
 *  @brief Callback to be executed at the end of the credential management action
 *  @param result the credential management result
 **/
typedef void (^CredentialManagementCompletion)(WDResult * _Nullable result, NSError* _Nullable error);

/**
 *  @typedef PasswordPolicyCompletion
 *  @brief Callback to be executed at the end of the credential management action
 *  @param policy the password policy result object
 *  @param error if encountered during the process
 **/
typedef void (^PasswordPolicyCompletion)(WDPasswordPolicyResult * _Nullable policy, NSError* _Nullable error);

/**
 *  @typedef SaleStatisticsCompletion
 *  @brief Callback to be executed at the end of the get transaction statistics
 *  @param statistics array of transaction statistics objects
 **/
typedef void (^SaleStatisticsCompletion)(NSArray  <WDSaleStatistics *>* _Nullable statistics, NSError* _Nullable error);

/**
 *  @typedef SaleUpdateCompletion
 *  @brief Callback to be executed at the end of the transaction update process
 *  @param sale updated sale
 **/
typedef void (^SaleUpdateCompletion)(WDSaleResponse* _Nullable sale, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueCompletion
 *  @brief Callback to be executed at the end of the product catalogue maintenance or query process
 *  @param productCatalogues available product catalogues
 **/
typedef void (^ProductCatalogueCompletion)(NSArray <WDProductCatalogue *>*_Nullable productCatalogues, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueCategoryCompletion
 *  @brief Callback to be executed at the end of the product catalogue category maintenance or query process
 *  @param productCategories product categories
 **/
typedef void (^ProductCatalogueCategoryCompletion)(NSArray <WDProductCatalogueCategory *>*_Nullable productCategories, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueProductCompletion
 *  @brief Callback to be executed at the end of the product catalogue maintenance or query process
 *  @param products Products
 **/
typedef void (^ProductCatalogueProductCompletion)(NSArray <WDProductCatalogueProduct *>*_Nullable products,NSNumber * _Nullable totalCount, NSError* _Nullable error);

/**
 *  @typedef ProductStockCompletion
 *  @brief Callback to be executed at the end of the product stock query process
 *  @param stocks Stock availability
 **/
typedef void (^ProductStocksCompletion)(NSArray <WDProductStock *>*_Nullable stocks, NSError* _Nullable error);

/**
 *  @typedef MembersCompletion
 *  @brief Callback to be executed at the end of the members  query process
 *  @param members Members list
 **/
typedef void (^MembersCompletion)(NSArray <WDMember *>*_Nullable members, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueProductChangeCompletion
 *  @brief Callback to be executed at the end of the product catalogue maintenance or query process
 *  @param updatedProducts updated products
 *  @param deletedProducts of strings with the ids of the products that were removed
 **/
typedef void (^ProductCatalogueProductChangeCompletion)(NSArray <WDProductCatalogueProduct *>*_Nullable updatedProducts, NSArray <NSString *>*_Nullable deletedProducts, NSError* _Nullable error);

/**
 *  @typedef ProductCatalogueImageCompletion
 *  @brief Callback to get the image of a catalogue product
 *  @param productsImage  producs image
 **/
typedef void (^ProductCatalogueImageCompletion)(NSArray <WDProductImage *>*_Nullable productsImage, NSError* _Nullable error);

/**
 *  @typedef ProductPricesCompletion
 *  @brief Callback to be executed at the end of the member's products prices query process
 *  @param productPrices Products prices list
 **/
typedef void (^ProductPricesCompletion)(NSArray <WDProductPrice *>*_Nullable productPrices, NSError* _Nullable error);

/**
 *  @typedef WDTerminalRKICompletion
 *  @brief Callback after the terminal RKI were retrieved from backend
 *  @param terminalRKI  terminal RKI details
 **/
typedef void(^WDTerminalRKICompletion)(WDTerminalRKI * _Nullable terminalRKI, NSError * _Nullable error);


#pragma mark - Helper Functions
/**
 *  @brief Get the  Transaction State  from WD Transaction State code
 *  @param WDState WD Transaction Status code
 *  @return  Transaction State as string
 **/
NSString *const _Nullable PaymentStateFromWDState(WDPaymentState WDState);

/**
 *  @brief Get the Payment Method from WD Payment Method code
 *  @param paymentMethod WD Payment Method code
 *  @return Array of the Payment methods as an Array of the strings
 **/
NSArray<NSString*> *const PaymentMethodsFromWDPaymentMethod(WDPaymentMethod paymentMethod);

/**
 *  @brief Get the Payment Method code from WD Payment Method and Transaction Type string
 *  @param paymentMethod WD Payment Method and Transaction Type string (e.g: @"CARD_CAPTURE")
 *  @return Payment Method code
 **/
WDPaymentMethod WDPaymentMethodFromPaymentMethod(NSString *paymentMethod);

/**
 *  @brief get the Switch transaction types as dictionary
 **/
NSDictionary *  WDATransactionTypes(void);

/**
 *  @brief get the Switch payment methods as dictionary
 **/
NSDictionary *  WDAPaymentMethods(void);

/**
 *  @brief Get the WD Extensions as dictionary of code and names
 *  @return WD Extensions dictionary
 **/
NSDictionary * WDExtensionNames(void);

/**
 *  @brief Get the WD Extension name from Vendor UUID
 *  @return WD Extension name
 **/
NSString * WDExtensionNameFromWDVendorUUID(WDExtensionTypeUUID vendorUUID);

/**
 *  @brief Get the WD Vendor UUID from Extension name
 *  @return WD vendor UUID
 **/
WDExtensionTypeUUID WDVendorUUIDFromWDExtensionName(NSString *extensionName);

/**
 *  @brief get the Internal transaction statuses as dictionary
 *  @return Dictionary of mapping internal Switch Payment statuses to external WD Payment statuses
 **/
NSDictionary *  WDAPaymentStatuses(void);

/**
 *  @brief get the Internal sale statuses as dictionary
 *  @return Dictionary of mapping internal Switch Sale statuses to external WD sale statuses
 **/
NSDictionary *  WDASaleStatuses(void);


/**
 *  @brief get the WD Sale status from Switch Sale status
 *  @return WD Sale Status
 **/
WDSaleState WDSaleStatusFromSaleStatus(NSString *saleStatus);
/**
 *  @brief Get the Sale Status from WD Sale Status code
 *  @param saleStatus WD Sale Status code
 *  @return Sale State as string
 **/
NSString *const SaleStatusFromWDSaleStatus(WDSaleState saleStatus);

/**
 *  @brief get the Switch Payment Method and Transaction Type from WD Payment Method and Transaction type
 *  @return Switch Payment Method and Transaction Type
 **/

NSString *const WDPaymentMethodAndTransactionTypeFromWDPaymentMethodAndTransactionType(WDPaymentMethod paymentMethod, WDTransactionType transactionType);

/**
 *  @typedef BarCodeTypeCompletion
 *  @brief Callback to be executed at the end of the barcode type maintenance or query process
 *  @param barCodeTypes Supported BarCode types
 **/
typedef void (^BarCodeTypeCompletion)(NSArray <WDBarCodeType *>*_Nullable barCodeTypes, NSError* _Nullable error);

/**
 *  @typedef TaxCategoryCompletion
 *  @brief Callback to be executed at the end of the tax category maintenance or query process
 *  @param taxCategories Array of queried Tax Categories
 **/
typedef void (^TaxCategoryCompletion)(NSArray <WDTaxCategory *>*_Nullable taxCategories, NSError* _Nullable error);

NS_ASSUME_NONNULL_END

#endif // WDA_DATA_TYPES
