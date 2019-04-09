![Platform-iOS-blue.svg](https://img.shields.io/badge/Platform-iOS-blue.svg) ![Tag](https://img.shields.io/badge/Support-9.0-green.svg) ![Tag](https://img.shields.io/badge/Language-Objc-light.svg)

# Introduce

A BLE SDK of Aerobic(S02).

SDK provides these major functions blow:

* Scan and Connect Aerobic Core.
* Query Aerobic info, e.g. Battery/Name/SN Code/FirmwareVersion/HardwareVersion etc..
* Rename the Core.
* Start/Stop Online Monitor Heart rate and Breath rate.
* Start/Stop/Sync Offline Monitor Heart rate and Breath rate.
* Firmware upgrade.
* Boost loader upgrade.
* Auto-Reconnect Aerobic Core.

# Install 

building...

# API Preview

In `BPBLEManagerS02.h`:

```objc
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
                
```

In `BPBLEDeviceS02.h`:

```objc

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

- (void)renameWithName:(NSString *)name completion:(void (^)(BOOL bSuccess))completion;

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
- (void)eraseAllOfflineDataWithCompletion:(void (^)(BOOL bSuccess))completion;
```
# How to use

See Details in Demo.

Demo building...

 