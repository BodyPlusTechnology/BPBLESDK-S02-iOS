//
//  BPBLEManagerS02+Config.h
//  BPStudentClient
//
//  Created by GrayLand on 2019/6/4.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import "BPBLESDKLiteS02.h"

NS_ASSUME_NONNULL_BEGIN

@interface BPBLEManagerS02 (Config)

@property (nullable, nonatomic, strong) BPS02DFUConfig *dfuConfig;
@property (nonatomic, strong) NSString *blePackageDir;

- (BPS02DFUConfig *)defaultDfuConfig;
- (BPS02DFUConfig *)dfuConfigWithExtendBLEPackageDir:(NSString * _Nullable)blePackageDir;

- (BOOL)checkNeedUpgradeWithCurrentDeviceWithCache:(BOOL)useCache;
- (BOOL)checkNeedBLEUpgradeWithCurrentDevice;
- (BOOL)checkNeedFirmwareUpgradeWithCurrentDevice;

@end

NS_ASSUME_NONNULL_END
