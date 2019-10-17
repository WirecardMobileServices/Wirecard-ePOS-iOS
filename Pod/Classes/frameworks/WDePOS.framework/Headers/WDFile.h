//
//  WDFile.h
//  acceptSDK
//
//  Created by Pulik, Jaroslav on 22/08/2019.
//  Copyright © 2019 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WDObject.h"

#pragma mark - File

/**
 *  @class WDFileCategory
 *  @brief FileManager file category
 **/
@interface WDFile : WDObject <NSCoding>

/**
 */
@property (nullable, nonatomic, strong) NSString *internalId;

/**
 */
@property (nullable, nonatomic, strong) NSString *category;

/**
 */
@property (nullable, nonatomic, strong) NSString *downloadUrl;

/**
 */
@property (nullable, nonatomic, strong) NSString *merchantId;

/**
 */
@property (nullable, nonatomic, strong) NSString *originalFileName;

@end
