//
//  BPS02DFUConfig.h
//  BPBLEDemo
//
//  Created by GrayLand on 2019/4/2.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BPS02DFUConfig : NSObject

/**
 If allow upgrade to lower version, default is NO.
 */
@property (nonatomic, assign) BOOL allowLowerVersion;

/**
 Contain the hardware version number. e.g. [0x102, 0x103, 0x131]
 */
@property (nonatomic, strong) NSArray <NSNumber *> *supportHWVersions;

/**
 Hardware package paths. e.g. @{@(hardwareVersion):@"..../S02_0103_0037.zip"}
 */
@property (nonatomic, strong) NSArray <NSDictionary <NSNumber *, NSString *> *> *swPackagePaths;

/**
 Boostloader package paths. e.g. @{@(hardwareVersion):@"..../s02_dfu_0004.zip"}
 */
@property (nonatomic, strong) NSArray <NSDictionary <NSNumber *, NSString *> *> *boostPackagePaths;

@property (nonatomic, assign) NSInteger latestFirmwareVersion;
@property (nonatomic, assign) NSInteger latestBoostloaderVersion;

+ (instancetype)defaultConfig;

@end

NS_ASSUME_NONNULL_END
