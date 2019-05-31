//
//  BPBLEManagerS02.h
//  BPBLEDemo
//
//  Created by GrayLand on 2019/3/26.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BPBLEDeviceS02.h"
#import "BPBLEDFUDevice.h"
#import "BPS02DFUConfig.h"

NS_ASSUME_NONNULL_BEGIN

@class BPBLEManagerS02;
@protocol BPBLEManagerS02Delegate <NSObject>
@optional

/**
 Turn the BLE off will trigger this method, and if device is connected before turn the BLE off, it will trigger <deviceS02DidDisconnected:> method simultaneous.
 */
- (void)blePermissionPoweredOff;
- (void)blePermissionPoweredOn;

- (void)deviceS02DidConnected:(BPBLEDeviceS02 *)deviceS02;
- (void)deviceS02DidDisconnected:(BPBLEDeviceS02 *)deviceS02;

- (void)deviceS02:(BPBLEDeviceS02 *)deviceS02 batteryDidChange:(CGFloat)battery;
- (void)deviceS02:(BPBLEDeviceS02 *)deviceS02 valueDidChangeWithHeartRate:(NSInteger)hr breathRate:(NSInteger)br;
- (void)deviceS02PositionDidChange:(BPBLEDeviceS02 *)deviceS02;
- (void)deviceS02PowerStateDidChange:(BPBLEDeviceS02 *)deviceS02;

- (void)deviceS02WillReconnect:(BPBLEDeviceS02 *)deviceS02;

//- (void)dfuDeviceS02DidConnected:(BPBLEDFUDevice *)dfuDeviceS02;

@end

typedef void (^BPBLECommonSuccessHandler)(BOOL bSuccess, BPBLEDeviceControl * _Nullable device, NSError * _Nullable error);
typedef void (^BPBLECommonFailureHandler)(BOOL isTimeout, NSString * _Nullable error);
typedef void (^BPBLEConnectDFUDeviceSuccessHandler)(BOOL bSuccess, BPBLEDFUDevice * _Nullable device, NSError * _Nullable error);


typedef NS_ENUM(NSUInteger, UpgradeState) {
    UpgradeStateNone                     = 0,
    UpgradeStateUnzipPackage             = 1,
    UpgradeStateChangeToDFUMode          = 2,
    UpgradeStateScanningDFUDevice        = 3,
    UpgradeStateConnectingDFUDevice      = 4,
    UpgradeStateBoostloaderUpgrading     = 5,
    UpgradeStateBoostloaderUpgradeFinish = 6,
    UpgradeStateFirmwareUpgrading        = 7,
    UpgradeStateFirmwareUpgradeFinish    = 8,
    UpgradeStateReconnectingDevice       = 9,
    UpgradeStateUpgradeAllFinish         = 10,
    UpgradeStateUnknow
};



@interface BPBLEManagerS02 : NSObject

@property (nonatomic, assign, readonly) BOOL isBLEPowerOn; ///< Has permission to access bluetooth.
@property (nonatomic, assign, readonly) BOOL isReady; ///< Is ready to send command.
@property (nonatomic, assign, readonly) BOOL isWaitingForDFU; ///< Core is waiting for firmware upgrade.
@property (nonatomic, assign, readonly) BOOL isDuringDFU;///< Core is during firmware upgrading.
@property (nonatomic, assign, readonly) BOOL isScanning;///< BLE is scanning.
@property (nonatomic, assign, readonly) BOOL isFinishSyncData;///< BLE is finish sync offline data.
@property (nonatomic, assign, readonly) BOOL isConnected;///< BLE is connected a S02 device.

/**
 autoConnectSN is the deivce's identifier, using in reconnecting process, default is current core's SN,
 if haven't connect any devices, default is nil.
 */
@property (nonatomic, strong) NSString * _Nullable autoConnectSN;
@property (nonatomic, assign) BOOL autoConnectEnable;///< default is YES

/**
 If connected, this property is current connected device,
 if disconnected, this property is nil.
 */
@property (nonatomic, strong, readonly) BPBLEDeviceS02 * _Nullable currentDevice;
@property (nonatomic, strong, readonly) BPBLEDFUDevice * _Nullable dfuDevice;

+ (instancetype)defaultManager;

/**
 Have batter setup in appdelegate didFinishLaunch. otherwise read property <isBLEPowerOn> may get the incorrect state at the first time.
 @param key The key of yours, determin if you can use the height level SDK.
 */
- (void)setupWithKey:(NSString * _Nullable)key;

/*===============================================================
 Multi-Delegate
 ===============================================================*/
- (void)addDelegate:(id<BPBLEManagerS02Delegate>)delegate;
- (void)removeDelegate:(id<BPBLEManagerS02Delegate>)delegate;
- (void)removeAllDelegates;

/*===============================================================
 Scan and Connect
 ===============================================================*/
/**
 Scan All S02 devices.

 @param interval The time interval(Second) between twice updateHandler, recommend 2.0.
 @param sortByRSSI If sort discovered devices by RSSI in updateHandler
 @param updateHandler the callback block, contains all discovered deivces.
 */
- (void)scanAllDeviceS02WithUpdateInterval:(NSTimeInterval)interval
                                sortByRSSI:(BOOL)sortByRSSI
                             updateHandler:(void (^)(NSArray <BPBLEBaseDevice *> *devices))updateHandler;

/**
 Scan and connect device with the SN.

 @param deviceSN deviceSN
 @param timeout timeout(Seconds), recommend 15.0
 @param successHandler Connect successful will trigger this callback
 @param failureHandler Timeout in this process will trigger this callback
 */
- (void)scanAndConnectDeviceS02WithSN:(NSString *)deviceSN
                              timeout:(NSTimeInterval)timeout
                       successHandler:(BPBLECommonSuccessHandler)successHandler
                       failureHandler:(BPBLECommonFailureHandler)failureHandler;


/**
 During scan and connect process, using this method to cancel reconnect.
 */
- (void)cancelReconnecting;

/**
 Connect device, it will trigger the delegate method.

 @param device The device discover in scan callback handler.
 */
- (void)connectDevice:(BPBLEBaseDevice *)device
          withTimeout:(NSTimeInterval)timeout
       successHandler:(BPBLECommonSuccessHandler)successHandler
       failureHandler:(BPBLECommonFailureHandler)failureHandler;

/**
 Stop scanning devices.
 */
- (void)stopScanning;

/**
 Disconnect current connected devices.
 */
- (void)disconnectCurrentDevice;

/*===============================================================
 Device Firmware Upgrade - DFU
 ===============================================================*/
- (void)scanAndConnectDFUDeviceWithSN:(NSString *)deviceSN
                              timeout:(NSTimeInterval)timeout
                      callBackHandler:(BPBLEConnectDFUDeviceSuccessHandler)callBackHandler;

/**
 Auto upgrade device boostloader and firmware, all of the params must be nonull.
 
 @param device A device type of BPBaseDevice.
 @param config Can use [BPS02DFUConfig defaultConfig].
 @param stateChangedHandler The state in upgrade processing flow.
 @param progressHandler progress callback.
 @param successHandler Upgrade finish callback.
 @param failureHandler ErrorCode, 1-device or config is nil/2-pacakge not found/3-unzip error/4-package content missing
 */
- (void)startUpgradeWithDevice:(BPBLEDeviceS02 *)device
                        config:(BPS02DFUConfig *)config
           stateChangedHandler:(void(^)(UpgradeState state))stateChangedHandler
               progressHandler:(void(^)(CGFloat progress))progressHandler
                successHandler:(void(^)(BPBLEDeviceS02 *reconnectedDevice))successHandler
                failureHandler:(void(^)(NSInteger errorCode, NSString *msg))failureHandler;
@end

NS_ASSUME_NONNULL_END
