//
//  BPBLEDFUDevice.h
//  BodyPlusECG
//
//  Created by GrayLand on 2018/1/4.
//  Copyright © 2018年 BodyPlus. All rights reserved.
//

#import "BPBLEDeviceControl.h"

//#define DFU_PACKAGE_NAME_6 @"s06_0006_0067"
//#define DFU_PACKAGE_NAME_4 @"s06_0004_0067"

// Boost Load
#define LATEST_BOOST_LOAD_HW_VERSION 0x01
#define DFU_BOOST_LOAD_PACKAGE_6 @"s06_0006_0093"
#define DFU_BOOST_LOAD_PACKAGE_4 @"s06_0004_0093"
// Hardware
#define HW_VERSION_SUPPORT_102 0x102 // 0x102 -> 258d -> bcd code -> 513d
#define HW_VERSION_SUPPORT_103 0x103 // 259
#define HW_VERSION_SUPPORT_131 0x131 // 305

//#define LATEST_HW_VERSION 0x37
#define LATEST_HW_VERSION 0x00

#define DFU_PACKAGE_NAME_2_3 @"M2_0103_0037"
#define DFU_PACKAGE_NAME_31 @"M2_0131_0037"
#define IS_FORCE_UPG        YES
#define SHOW_UPG_INFO       YES
#define CORE_UPG_INFO       @"发现新的固件版本"

@interface BPBLEDFUDevice : BPBLEDeviceControl

@property (nonatomic, copy) void (^changeToDFUModeHandler)(BOOL bSuccess);

- (instancetype)initWithBaseDevice:(BPBLEBaseDevice *)baseDevice centralManager:(CBCentralManager *)centralManger;

//- (void)firmwareUpgradeCurrentDeviceWithHardwareVersion:(NSInteger)hardwareVersion softwareVersion:(NSInteger)softwareVersion;

//- (void)changeToDFUModeWithCompletion:(void (^)(BOOL bSuccess))completion;

@end
