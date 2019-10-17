//
//  WDFileManager.h
//  acceptSDK
//
//  Created by Pulik, Jaroslav on 22/08/2019.
//  Copyright © 2019 Wirecard. All rights reserved.
//

#import "WDDataTypes.h"

@protocol WDPaymentDelegate;
NS_ASSUME_NONNULL_BEGIN

/**
 *  @class WDFileManager
 *  @brief File Management
 */
@interface WDFileManager : NSObject

#pragma mark  ⎿ File management

/**
 *  @brief Get the list of files of specified category
 *  @param merchantId Merchant ID for which to get available files
 *  @param category Category name for which to get available files
 *  @param completion Block that will return file list
 **/
- (void)files:(NSString *)merchantId category:(NSString *)category completion:(FileFilesCompletion)completion;

/**
 *  @brief Get the file download for specified file ID
 *  @param fileId File ID for which file will be downloaded
 *  @param completion Block that will return downloaded file
 **/
- (void)downloadFile:(NSString *)fileId completion:(FileDownloadCompletion)completion;

@end

NS_ASSUME_NONNULL_END
