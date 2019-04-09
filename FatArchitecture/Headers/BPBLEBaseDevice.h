//
//  BPBaseDevice.h
//  BPToolBox
//
//  Created by GrayLand on 2017/10/18.
//  Copyright © 2017年 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "BPDeviceTypeDef.h"


/*===============================================================
 底层 - 基础属性
 ===============================================================*/
@interface BPBLEBaseDevice : NSObject
{
    CBPeripheral     *_peripheral;
    NSDictionary     *_advertisementData;
    NSNumber         *_RSSI;
}
@property (nonatomic, weak) CBCentralManager *central;
@property (nonatomic, strong) CBPeripheral     *peripheral;
@property (nonatomic, strong) NSDictionary     *advertisementData;
@property (nonatomic, strong) NSNumber         *RSSI;
@property (nonatomic, assign) NSInteger signalIntensity;///<信号等级 0,1,2,3

@property (nonatomic, assign) CGFloat  battery;
@property (nonatomic, assign) BOOL isDFUMode;
@property (nonatomic, assign) NSInteger hardwareVersion;///< 硬件版本
@property (nonatomic, assign) NSInteger firmwareVersion;///< 固件号
@property (nonatomic, assign) NSInteger boostloaderVersion;
@property (nonatomic, strong) NSString *dispHWVersion;///< 硬件版本
@property (nonatomic, strong) NSString *dispFWVersion;///< 固件号
@property (nonatomic, assign) BOOL hasVersionInAdvertisementData;
@property (nonatomic, strong) NSString *localName;
@property (nonatomic, strong) NSString *SN;
@property (nonatomic, assign) NSInteger hwVersionInAD;

+ (NSString *)deviceSNWithAD:(NSDictionary *)advertisementData;
+ (BOOL)checkHasVersionInAD:(NSDictionary *)advertisementData;
+ (uint16_t)dfuDeviceHardwareVersionWithAD:(NSDictionary *)advertisementData;
+ (NSString *)deviceLocalNameWithAD:(NSDictionary *)advertisementData;
+ (NSArray *)deviceUUIDsWithAD:(NSDictionary *)advertisementData;
+ (BOOL)isDFUModeWithAD:(NSDictionary *)advertisementData;
+ (BOOL)isDFUModeWithService:(CBService *)service;
+ (NSArray *)bodyPlusService;
+ (CBUUID *)uuidWithMode:(BPUUIDType)type;
+ (NSInteger)hardwareVersionWithSN:(NSString *)snCode;
//+ (NSString *)bluetoothNameWithType:(BPDeviceNameType)type;

- (NSInteger)hwVersinWithSN:(NSString *)sn;
- (void)setAdvertisementData:(NSDictionary *)advertisementData withAutoSet:(BOOL)autoSet;

#pragma mark - Helper

- (uint32_t)getInt32WithBytes:(const uint8_t *)bytes;

- (uint16_t)getInt16WithBytes:(const uint8_t *)bytes;

@end
