//
//  WDSError.h
//   WDePOS
//
//  Created by Danko, Radoslav on 18/10/15.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorUserInfoKey const WDAErrorStatusCode;

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
    WDErrorForgotExternalIdNotFound, //60            // there is no user/merchant with given email address. ( HTTP 422 )
    
    WDErrorConfigFilesInfoTimeout,
    WDErrorConfigFilesZipDownload,
    WDErrorTerminalDisconnected,
    WDErrorConfigFilesTerminalMayNotBeSet,
    WDErrorConfigFilesTerminalCancelledFileDownload,
    WDErrorConfigFilesProductionFirmwareOnDevelopmentTerminal,
    WDErrorConfigFilesDevelopmentFirmwareOnProductionTerminal,
    WDErrorConfigFilesTerminalUnsupported,
    WDErrorConfigFilesTokenExpired,
    WDErrorInventoryNoData,//70
    WDErrorTerminalFirmwareDoesNotExist,
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
    WDErrorExtensionDoesNotSupportMethod,// 90
    WDErrorInvalidParameter,
    WDErrorDeviceRooted,
    
    WDErrorActiveTerminalNotSet,
    WDErrorActiveScanPistolNotSet,
    WDErrorActivePrinterNotSet,
    WDErrorPinLocked,
    WDErrorPinInvalid,
    WDErrorGeneral,
    WDErrorServerSSLCertificateExpired,
    WDErrorFailedTerminalBluetoothConnectionNotInPayment,//100
    
    WDErrorMissingMerchant, //This happens when a System Admin, Partner or any role without merchant tries to log in
    WDErrorAnotherTransactionIsInProgress,
    WDErrorTerminalApplicationDoesNotExist,
    WDErrorPaymentFailed,
    WDErrorTransactionContactlessNotPermitted,
    // Keep it the last:
    WDErrorCounter
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
+(NSError *)error:(WDError)errorCode withDescription:(nullable NSString*)description andReason:(nullable NSString *)reason andUnderlyingError:(nullable NSError *)underlyingError;

/**
 *  @brief Error constructor
 *  @param errorCode Error code
 *  @param description Error description
 *  @param reason Error reason
 *  @param underlyingError underlying error
  * @param customUserInfo additional custom user info dictionary items
 *  @return Error object
 **/
+(NSError *)error:(WDError)errorCode withDescription:(nullable NSString*)description andReason:(nullable NSString *)reason andUnderlyingError:(nullable NSError *)underlyingError andCustomUserInfo:(nullable NSDictionary *)customUserInfo;
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

NS_ASSUME_NONNULL_END

