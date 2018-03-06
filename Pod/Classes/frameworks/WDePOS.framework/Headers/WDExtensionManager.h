//
//  WDExtensionManager.h
//   WDePOS
//
//  Created by Danko, Radoslav on 12/10/16.
//  Copyright © 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "WDDataTypes.h"
#import "WDProtocols.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDExtensionManager
 *  @brief Extension Manager (terminals | printers | scanners)
 */
@interface WDExtensionManager : NSObject
@property(nonatomic, readonly) BOOL isDevMode;

/**
 *  @brief Retrieve an array of supported  vendors
 *  @param completion The array of vendors found, returned with objects of class AcceptVendor
 **/
- (void)discoverVendors:(VendorDiscoveryCompletion)completion;

/**
 *  @brief Retrieve an array of supported devices for a vendor
 *  @param vendorUUID The terminal vendor identifier WDExtensionTypeUUID
 *  @param completion The array of vendors found, returned with objects of class AcceptTerminal
 **/
- (void)discoverDevices:(WDExtensionTypeUUID)vendorUUID completion:(DeviceDiscoveryCompletion)completion;

/**
 *  @brief Set the active device for communication
 *  @param device Device to direct all comunications to
 **/
-(void)setActive:(nullable WDTerminal *)device completion:(nullable dispatch_block_t)completion;

/**
 *  @brief Get the active device for communication
 *  @return current active device (last communicated to)
 **/
-(nullable WDTerminal *)activeDevice;

/**
 *  @brief Get the active device for communication
 *  @completion current active device (last communicated to) or first active device from the connected/active devices
 **/
-(void)activeDevice:(void (^)(WDTerminal * _Nullable))completion;

/**
 *  @brief Request the current device connection status.
 *  @param completion Block that will receive the device connection status.
 **/
- (void)connectionStatus:(DeviceConnectionStatusCompletion)completion;

/**
 *  @brief Request the battery level of the connected device. NOTE: this function should NOT be called if an operation in the device is ongoing (ie startPay has not finished)
 *  @param completion Block that will receive the battery level as a signed integer. If negative, then it indicates an error between three possible cases: "-1" for showing that the selected terminalID is wrong or that the device does not support battery level info. "-2" for indicating that the device does not respond (not ready or not connected). "-3" for indicating that the device is currently charging through a cable.
 **/
- (void)percentageBatteryRemaining:(BatteryLevelCallback)completion;

/**
 *  @brief Subscribe to device updates like connection status change, battery level change and so on. Manager holds weak reference.
 *  @param delegate Instance which conforms to WDManagerDelegate protocol
 *  @param device Device to subscribe to
 */

- (void)addManagerDelegate:(id<WDManagerDelegate>)delegate forDevice:(nonnull WDTerminal *)device;
/**
 *  @brief Unsubscribe to device updates.
 *  @param delegate Instance used in addManagerDelegate:forTerminal:
 *  @param device Device to unsubscribe from
 */
- (void)removeManagerDelegate:(id<WDManagerDelegate>)delegate forDevice:(nullable WDTerminal *)device;

@end

/**
 *  @class WDUpdateableExtensionManager
 *  @brief Extension Manager - updateable devices
 */
@interface WDUpdateableExtensionManager : WDExtensionManager
/**
 *  @brief Update terminals for a vendor. Chip compatible terminals receive config files from backend
 *  @param terminal The terminal for which to run configuration update
 *  @param updateType Update type can be one of Firmware or Configuration
 *  @param progress The block to receive the update process progress updates
 *  @param completion Block that receives the latest updated version or an error
 **/
- (void) update:(WDTerminal*)terminal
     updateType:(WDTerminalUpdateTypeMask)updateType
       progress:(nullable UpdateConfigurationProgress)progress
     completion:(UpdateTerminalCompletion)completion;

/**
 *  @discussion Obtain the Remote Key Injection details for the terminal
 *  @param completion Provides obtained terminal RKI - if the supplied RKI request contains all necessary information
 **/
-(void)terminalRKI:(WDTerminalRKIRequest*)rkiRequest
        completion:(WDTerminalRKICompletion)completion;

@end

/**
 *  @class WDTerminalManager
 *  @brief Terminal Manager
 */
@interface WDTerminalManager : WDUpdateableExtensionManager 

/**
 *  @brief Check the available updates for the terminal
 *  @param completion Block that receives the inforation about available updates for the terminal
 **/
-(void) availableUpdates:(TerminalUpdatesCompletion)completion;

/**
 *  @brief Clean the info about previous updates on all terminals. Function useful only in case the naming between terminal updates is not consistent during development. Not needed in production.
 **/
- (void)resetTerminalsCache;
@end

#pragma mark - Print manager

/**
 *  @class WDPrinterManager
 *  @brief Printer Manager
 */
@interface WDPrinterManager : WDExtensionManager

/**
 *  @brief Print the receipt
 *  @param config print configuration
 *  @param progress printing progress
 *  @param completion Block executed at the end of the  method
 */
- (void)print:(WDPrinterConfig*)config
     progress:(PrinterStateUpdate)progress
   completion:(PrintCompletion)completion;

/**
 *  @brief Subscribe to printer updates. Manager holds weak reference.
 *  @param delegate Instance which conforms to WDPrinting protocol
 *  @param printer Printer device to subscribe to
 */
- (void)addPrinterManagerDelegate:(id<WDPrinting>)delegate forPrinter:(WDTerminal*)printer;

/**
 *  @brief Unsubscribe to printer status updates.
 *  @param delegate Instance used in addPrintingDelegate:forPrinter:
 */
- (void)removePrinterManagerDelegate:(id<WDPrinting>)delegate forPrinter:(WDTerminal*)printer;

@end

#pragma mark - Scanner manager

/**
 *  @class WDScannerManager
 *  @brief Scanner Manager
 */
@interface WDScannerManager : WDExtensionManager

/**
 *  @brief Subscribe to scanner notifications. Manager holds weak reference.
 *  @param delegate Instance which conforms to WDScanning protocol
 *  @param scanner Scanner device to subscribe to
 */
- (void)addScannerManagerDelegate:(id<WDScanning>)delegate forScanner:(WDTerminal*)scanner;

/**
 *  @brief Unsubscribe to scanner notifications.
 *  @param delegate Instance used in addScannerDelegate:forScanner
 */
- (void)removeScannerManagerDelegate:(id<WDScanning>)delegate forScanner:(WDTerminal*)scanner;

@end

/**
 *  @class WDCashDrawerManager
 *  @brief Cash Drawer Manager
 */
@interface WDCashDrawerManager : WDExtensionManager

/**
 *  @brief Open the cash drawer of the extension that supports it
 *  @param terminal The terminal with barcode scanner to which to connect to
 *  @param completion Block that informs about the command status
 **/
- (void)openCashDrawer:(WDTerminal*)terminal completion:(ExtensionCommandCompletion)completion;

@end

NS_ASSUME_NONNULL_END
