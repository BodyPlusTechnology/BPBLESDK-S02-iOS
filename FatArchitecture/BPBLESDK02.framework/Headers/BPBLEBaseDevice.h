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
@property (nonatomic, assign) NSInteger hardwareVersion;///< 硬件版本 Dec
@property (nonatomic, assign) NSInteger firmwareVersion;///< 固件号 Dec
@property (nonatomic, assign) NSInteger boostloaderVersion;
@property (nonatomic, strong) NSString *dispHWVersion;///< 硬件版本
@property (nonatomic, strong) NSString *dispFWVersion;///< 固件号
@property (nonatomic, assign) BOOL hasVersionInAdvertisementData;
@property (nonatomic, strong) NSString *localName;
@property (nonatomic, assign) NSInteger hwVersionInAD;

@property (nonatomic, strong, readonly) NSString *manufacturerID;///< 厂商信息
@property (nonatomic, strong, readonly) NSString *SN;

@property (nonatomic, assign, readonly) BOOL isZFDevice;
@property (nonatomic, assign, readonly) BOOL isS03;

@end
