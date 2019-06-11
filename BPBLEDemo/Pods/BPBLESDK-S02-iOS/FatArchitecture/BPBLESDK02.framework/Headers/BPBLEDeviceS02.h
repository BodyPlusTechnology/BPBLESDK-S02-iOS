//
//  BPDevice.h
//  BPToolBox
//
//  Created by GrayLand on 2017/10/18.
//  Copyright © 2017年 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BPBLEDeviceControl.h"
#import "BPS02OfflineDataModel.h"

typedef NS_ENUM(NSUInteger, CoreS02Position) {
    CoreS02PositionChargingBase = 0x00,
    CoreS02PositionCoat         = 0x01,
    CoreS02PositionPants        = 0x10,
    CoreS02PositionIsolate      = 0x11,
    CoreS02PositionUnknow
};

typedef NS_ENUM(NSUInteger, CoreS02PowerState) {
    CoreS02PowerStateNormal      = 0x00,
    CoreS02PowerStateCharging    = 0x01,
    CoreS02PowerStateBatteryFull = 0x02,
    CoreS02PowerStateBatteryLow  = 0x03,
    CoreS02PowerStateExhaust     = 0x04,
    CoreS02PowerStateUnknow,
};

typedef NS_ENUM(NSUInteger, CoreS02MonitorMode) {
    CoreS02MonitorModeNone        = 0x00,
    CoreS02MonitorModeMonitorHRBR = 0x01,
    CoreS02MonitorModeOffline     = 0x02,
    CoreS02MonitorModeUnknow
};

@class BPBLEDeviceS02;
@protocol BPBLEDeviceS02Delegate <BPBLEDeviceControlDelegate>
@optional
- (void)device:(BPBLEDeviceS02 *)device didUpdateHeartRate:(NSInteger)heartRate breathRate:(NSInteger)breathRate;
//- (void)device:(BPBLEDeviceS02 *)device didReceiveRawHRData:(NSArray <NSNumber *> *)rawData filterHRData:(NSArray <NSNumber *> *)filterData;
- (void)device:(BPBLEDeviceS02 *)device didGetHardwareVersion:(NSString *)version;
- (void)device:(BPBLEDeviceS02 *)device didGetSoftwareVersion:(NSString *)version;
- (void)devicePositionDidChanged:(BPBLEDeviceS02 *)device;
- (void)devicePowerStateDidChanged:(BPBLEDeviceS02 *)device;

@end

@interface BPBLEDeviceS02 : BPBLEDeviceControl

@property (nonatomic, assign, readonly) BOOL isMonitoringHRBRMode;
@property (nonatomic, assign, readonly) BOOL isOfflineMode;
@property (nonatomic, assign, readonly) NSInteger curHR;
@property (nonatomic, assign, readonly) NSInteger curBR;
@property (nonatomic, assign, readonly) CoreS02MonitorMode monitorMode;
@property (nonatomic, assign, readonly) CoreS02Position currentPosition;
@property (nonatomic, assign, readonly) CoreS02PowerState currentPowerState;
@property (nonatomic, assign, readonly) BOOL isECGStateOK;///< ECG是否脱落
@property (nonatomic, assign, readonly) NSInteger ecgComeOffTimce;///< ECG脱落次数

@property (nonatomic, weak) id <BPBLEDeviceS02Delegate> delegate;

@property (nonatomic, assign) NSInteger offlineDataNum;
@property (nonatomic, assign) NSInteger hrOfflineDataAllFrameRecvLength;///< 总接收长度
@property (nonatomic, assign) NSInteger hrOfflineDataAllFrameTotalLength;///< 总长度

- (instancetype)initWithBaseDevice:(BPBLEBaseDevice *)baseDevice centralManager:(CBCentralManager *)centralManger;

/**
 Start monitoring
 */
- (void)startMonitorHRBR;

/**
 Stop monitoring
 */
- (void)stopMonitorHRBR;

- (void)queryHardwareVersionWithCompletion:(void (^)(BOOL bSuccess, NSInteger version))completion;
- (void)queryFirmwareVersionWithCompletion:(void (^)(BOOL bSuccess, NSInteger version))completion;
- (void)queryBoostloaderVersionWithCompletion:(void (^)(BOOL bSuccess, NSInteger version))completion;

/**
 Get core's current mode, in the callback block can read property isMonitoringHRBR/isOfflineMode.

 @param completion callback block
 */
- (void)queryCoreModeWithCompletion:(void (^)(BOOL bSuccess, CoreS02MonitorMode mode))completion;

/**
 * Sync core's time with your phone.
 */
- (void)syncTimeWithCompletion:(void (^)(BOOL bSuccess))completion;

#pragma mark - Command Rename

- (void)renameWithName:(NSString *)name completion:(void (^)(BOOL bSuccess))completion;

#pragma mark - DFU

- (void)changeToDFUModeWithCompletion:(void (^)(BOOL bSuccess, NSString *error))completion;

#pragma mark - Offline

/**
 Start offline monitoring
 */
- (void)startOfflineMonitoring;

/**
 Stop offline monitoring
 */
- (void)stopOfflineMonitoring;

/**
 Query Offline Datas Num.
 
 @param completion callback block
 */
- (void)queryOfflineDataNumWithCompletion:(void (^)(NSInteger totalLength, NSInteger dataNum))completion;

/**
 * Query if has offline datas, respond timestamp/length
 */
- (void)queryOfflineDataInfoWithCompletion:(void (^)(NSInteger timestamp, NSInteger length))completion;

/**
 Sync offline datas, when finish synchronizing process, core won't delete the datas, you should call <eraseAllOfflineDataWithCompletion:> after sync offline datas to erase.
 */
- (void)syncOfflineDataWithProgressHandler:(void (^)(CGFloat progress))progressHandler
                             finishHandler:(void (^)(NSInteger timestamp, NSArray <NSNumber *> *hrDatas, NSArray <NSNumber *> *brDatas))finishHandler;

/**
 * Erase all offline Data. Before do this, pls make sure your datas have been archiving successful.
 */
- (void)eraseAllOfflineDataWithCompletion:(void (^)(BOOL bSuccess, NSString *error))completion;

/**
 * Erase current offline Data. Before do this, pls make sure your datas have been archiving successful.
 */
- (void)eraseCurrentOfflineDataWithCompletion:(void (^)(BOOL bSuccess, NSString *error))completion;

@end
