//
//  WDePOSEnvironment.h
//   WDePOS
//
//  Created by Danko, Radoslav on 15/12/15.
//  Copyright © 2018 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
/**
 *  @brief WDePOS Environments enumerator
 **/
typedef NS_ENUM(NSUInteger, WDEnvironment) {
    WDEnvironmentProduction = 1,
    WDEnvironmentPublicTest = 2
};

/**
 *  @brief WDePOS Environment Types enumerator
 **/
typedef NS_ENUM(NSUInteger, WDEnvironmentType) {
    WDEnvironmentTypeUnknown = 0,
    WDEnvironmentTypeDEV = 1,
    WDEnvironmentTypeQA = 2,
    WDEnvironmentTypeTEST = 3,
    WDEnvironmentTypePUBLICTEST = 4,
    WDEnvironmentTypePROD = 5
};

/**
 *  @class WDEnvironmentConfiguration
 *  @brief Wirecard WDePOS Environment configuration 
 *  @discussion WDePOS Environment to be used for ReST services \n
 *  WDEnvironmentPublicTest to be used for Integration Tests and Development \n
 *  WDEnvironmentTypePROD to be used for Production application
 **/
@interface WDEnvironmentConfiguration : NSObject
/// Default NSObject init is unavailable
-(nonnull instancetype)init __attribute__((unavailable("use initWithUrl")));
/// environment as one of WDEnvironment
@property (nonatomic,readonly) WDEnvironment environment;
/// environmentType type as one of WDEnvironmentType
@property (nonatomic, readonly) WDEnvironmentType environmentType;
/// url of this environment
@property (nonatomic,strong,readonly) NSString *url;
/// Create the enironment from known URL
-(instancetype _Nullable)initWithUrl:(NSString *_Nonnull)url NS_DESIGNATED_INITIALIZER;
@end

/**
 *  @brief Get URL for the specified WDePOS Environment
 *  @param environment one of WDEnvironment environments
 **/
NSString *WDEnvironmentGetBackendUrl(WDEnvironment environment);

/**
 *  @brief Get WDEnvironment for the specified URL
 *  @param url of the WDePOS backend
 **/
WDEnvironment WDEnvironmentFromUrl(NSString *url);

/**
 *  @brief Get list of supported WDePOS Environments as array of WDEnvironmentConfiguration
 **/
NSArray <WDEnvironmentConfiguration *>* WDEnvironments(void);

NS_ASSUME_NONNULL_END
