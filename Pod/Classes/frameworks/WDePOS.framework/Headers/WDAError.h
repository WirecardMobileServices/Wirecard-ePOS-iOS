//
//  WDSError.h
//   WDePOS
//
//  Created by Danko, Radoslav on 18/10/15.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 *  @brief WDSError
 *  @discussion Enumerator of acceptSDK errors
 **/
typedef NS_ENUM(NSInteger, WDError) {
    WDErrorBackendReturnedJSONDoesNotMatchMappedClass = 0,
    WDErrorUnauthorizedUser,
    WDErrorUserPasswordExpired,
    WDErrorUserPasswordChangeRequired,
    WDErrorUserAccessForbidden,
    WDErrorResourceNotFound,
    WDErrorSessionExpired,
    WDErrorRequestTimeOut,
    WDErrorRequestNoProperResponse,
    WDErrorRequestParameterRequired,
    WDErrorRequestedResourceNotFound,//10
    WDErrorRequestFailedValidation,
    WDErrorPlugInTimeout ,
    WDErrorSignatureTimeout,
    WDErrorInitialization,
    WDErrorLowBatteryLevel,
    WDErrorSwipeTimeout,
    WDErrorBadSwipe,
    WDErrorNotSupportedCardType,
    WDErrorDataProcessing,
    WDErrorOnlineProcessing,//20
    WDErrorTransactionNotApproved,
    WDErrorHardwareAccessPermission,
    WDErrorTokenExpired,
    WDErrorConnection,
    WDErrorSignatureRequired,
    WDErrorCantLoadTerminalConfiguration,
    WDErrorTerminalDamaged,
    WDErrorNoDUKPT,
    WDErrorFailedToStartEMV,
    WDErrorFailedToSendOfflineEMV,//30
    WDErrorFailedToSendOnlineEMV,
    WDErrorTerminalNotSetInMerchant,
    WDErrorResponseLost,
    WDErrorTransactionTerminated,
    WDErrorTransactionDeclined,
    WDErrorTransactionFailure,
    WDErrorBlockedCardType,
    WDErrorFailedBluetoothConnection,
    WDErrorFailedPrinterBluetoothConnection,
    WDErrorFailedTerminalBluetoothConnection,//40
    WDErrorFailedDrawerBluetoothConnection,
    WDErrorFailedPistolBluetoothConnection,
    
    WDErrorTerminalNotReady,
    WDErrorTerminalCommunication,
    WDErrorTerminalTimeoutApplicationSelection,
    WDErrorTerminalFailedToGetICCApplicationsList,
    WDErrorTerminalFailedToTerminateCurrentTerminalPaymentFlow,
    WDErrorLowPowerInAudioJack,
    WDErrorMonoAudioEnabled,
    WDErrorTerminalCommandTimeOut,//50
    WDErrorTerminalTimeOut,
    WDErrorTerminalWaitingUserTimeOut,
    WDErrorTerminalCancelledFileUpload,

    WDErrorWrongUserNameOrPassword,
    WDErrorVendorNotFound,
    WDErrorExternalAccessoriesProtocolInvalid,          // some extensions requires additional configuration changes in host application .plist file.
    WDErrorExternalIdNotFound,                   // there is no user/merchant with given external id. ( HTTP 422 )
    WDErrorChangePasswordCriteriaNotMet,                  //password change criteria not met
    WDErrorQueryStatsTokenExpired,
    WDErrorForgotExternalIdNotFound,             // there is no user/merchant with given email address. ( HTTP 422 )
    
    WDErrorConfigFilesInfoTimeout,//60
    WDErrorConfigFilesZipDownload,
    WDErrorTerminalDisconnected,
    WDErrorConfigFilesTerminalMayNotBeSet,
    WDErrorConfigFilesTerminalCancelledFileDownload,
    WDErrorConfigFilesProductionFirmwareOnDevelopmentTerminal,
    WDErrorConfigFilesDevelopmentFirmwareOnProductionTerminal,
    WDErrorConfigFilesTerminalUnsupported,
    WDErrorConfigFilesTokenExpired,
    WDErrorInventoryNoData,
    WDErrorTerminalFirmwareDoesNotExist,//70
    WDErrorTerminalConfigDoesNotExist,
    
    WDErrorConfigFilesReading,
    
    WDErrorPrinterTimeout,
    WDErrorPrinterInitialization,
    WDErrorPrinterLowBatteryLevel,
    WDErrorPrinterNotConnected,
    WDErrorPrinterOperation,
    WDErrorPrinterUnsupportedDevice,
    WDErrorDeviceDoesNotSupportPrinting,//80
    WDErrorPrinterPaperLow,
    
    WDErrorSignatureRejectedFromTerminal,
    WDErrorInvalidPaymentConfiguration,
    WDErrorInvalidAIDConfiguration,
    
    WDErrorTransactionReversalRequired,
    WDErrorTransactionReversedByTerminal,
    WDErrorTransactionReversalFailed,
    WDErrorTransactionUpdateFailed,
    
    WDErrorExtensionClassDoesNotExist,
    WDErrorExtensionDoesNotSupportMethod,
    WDErrorInvalidParameter,// 90
    WDErrorDeviceRooted,
    
    WDErrorActiveTerminalNotSet,
    WDErrorActiveScanPistolNotSet,
    WDErrorActivePrinterNotSet,
    WDErrorPinLocked,
    WDErrorPinInvalid,
    WDErrorGeneral,
    WDErrorServerSSLCertificateExpired,
    WDErrorFailedTerminalBluetoothConnectionNotInPayment,
    
    WDErrorMissingMerchant, //100//This happens when a System Admin, Partner or any role without merchant tries to log in
    WDErrorAnotherTransactionIsInProgress
};


/**
 *  @class WDError
 *  @brief WDePOS Error object
 *  @discussion Error helper methods
 **/
@interface WDAError : NSObject

/**
 *  @brief Error constructor - uses the errorCode to add the default error code description
 *  @param errorCode Error code
 *  @return Error object
 **/
+(NSError *)error:(WDError)errorCode;

/**
 *  @brief Error constructor  - uses the errorCode to add the default error code description and appends the custom reason
 *  @param errorCode Error code
 *  @param reason Error reason
 *  @return Error object
 **/
+(NSError *)error:(WDError)errorCode andCustomReason:(NSString *)reason;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param description Error description
 *  @return Error object
 **/
+(NSError *)error:(WDError)errorCode withDescription:(NSString*)description;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param andUnderlyingError underlying Error
 *  @return Error object
 **/
+(NSError *)error:(WDError)errorCode andUnderlyingError:(NSError*)andUnderlyingError;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param description Error description
 *  @param reason Error reason
 *  @param underlyingError underlying error
 *  @return Error object
 **/
+(NSError *)error:(WDError)errorCode withDescription:(NSString*)description andReason:(NSString *)reason  andUnderlyingError:(NSError *)underlyingError;
    
/**
 *  @brief Get the default description linked to this error code
 *  @param errorCode Error code
 *  @return Error description
 **/
+(NSString *)defaultDescriptionOfErrorCode:(WDError)errorCode;

/**
 *  @brief Get the dictionary of error codes and their descriptions
 *  @return Dictionary of error codes and linked descriptions
 **/
+(NSDictionary *)errorCodesDescriptions;

/**
 *  @brief Collate underlying reasons into the array of strings
 *  @param reason add reason into the array of reason - recursively
 *  @param reasons array of reasons
 **/
+(void)underlyingReasons:(NSError *)reason reasons:(NSMutableArray *)reasons;
@end
