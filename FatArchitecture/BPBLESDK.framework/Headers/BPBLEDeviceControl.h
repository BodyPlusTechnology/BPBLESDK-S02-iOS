//
//  BPBLEDeviceControl.h
//  BPToolBox
//
//  Created by GrayLand on 2017/10/18.
//  Copyright © 2017年 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BPBLEBaseDevice.h"
#import "BPDeviceControllerTypeDef.h"

typedef void (^BPDeviceConnectHandler)(BOOL isSuccessful, NSString *errorStr);

@class BPBLEDeviceControl;
@protocol BPBLEDeviceControlDelegate <NSObject>
@optional
//- (void)deviceConnectSuccess:(BPBLEDeviceControl *)device;
//- (void)deviceConnectFailed:(BPBLEDeviceControl *)device error:(NSError *)error;
//- (void)deviceWillReconnect:(BPBLEDeviceControl *)device;
- (void)device:(BPBLEDeviceControl *)device disconnectWithError:(NSError *)error;
- (void)device:(BPBLEDeviceControl *)device didUpdatedBattery:(CGFloat)battery;
@end

@interface BPBLEDeviceControl : BPBLEBaseDevice
{
    // Public
    // 提供给派生类直接调用
    CBUUID *_Battery_Service_UUID;
    CBUUID *_Battery_Level_Characteristic_UUID;
    
    // 指令操作
    CBUUID *_serviceCmdProfileUUID;
    CBUUID *_characteristicCMDReadUUID;
    CBUUID *_characteristicCMDWriteUUID;
    CBUUID *_Uart1_DFU_WX_Characteristic_UUID;
    CBUUID *_uart1DfuRxCharacteristicUUID;
    CBUUID *_characteristicLogReadUUID;
    
    // 数据传输
    CBUUID *_serviceDataProfileUUID;
    CBUUID *_characteristicDataReadUUID;
    CBUUID *_characteristicDataWriteUUID;
    CBUUID *_characteristicOfflineReadUUID;
    CBUUID *_characteristicOfflineWriteUUID;
    
    // 其他
    CBUUID *_Device_Information_Service_UUID;
    CBUUID *_Hardware_Revision_Characteristic_UUID;
    
    
    int             _errorECGCount;      // ECG脱落次数
    NSMutableData   *_reciveData;        // 一条完整的数据(包含CRC8校验)
    NSUInteger      _reciveLength;
    uint32_t        _reciveCount;
    BOOL            _isReceivingData;
    
    NSDate          *_reciveTime;
    
    int             _retryCount;
    int _framCount;
    NSMutableArray *_sendCommandLogs;
    dispatch_queue_t _sendCommandQueue;
    dispatch_semaphore_t _sendCommandSemaphore;
    
    BOOL _isUart1Respond;
}

@property (nonatomic, strong) CBUUID *Battery_Service_UUID;
@property (nonatomic, strong) CBUUID *Battery_Level_Characteristic_UUID;

// 指令操作
@property (nonatomic, strong) CBUUID *serviceCmdProfileUUID;
@property (nonatomic, strong) CBUUID *characteristicCMDReadUUID;
@property (nonatomic, strong) CBUUID *characteristicCMDWriteUUID;
@property (nonatomic, strong) CBUUID *characteristicLogReadUUID;
@property (nonatomic, strong) CBUUID *Uart1_DFU_WX_Characteristic_UUID;
@property (nonatomic, strong) CBUUID *Uart1_DFU_RX_Characteristic_UUID;

// 数据传输
@property (nonatomic, strong) CBUUID *serviceDataProfileUUID;
@property (nonatomic, strong) CBUUID *characteristicDataReadUUID;
@property (nonatomic, strong) CBUUID *characteristicDataWriteUUID;
@property (nonatomic, strong) CBUUID *characteristicOfflineReadUUID;
@property (nonatomic, strong) CBUUID *characteristicOfflineWriteUUID;

// 其他
@property (nonatomic, strong) CBUUID *Device_Information_Service_UUID;
@property (nonatomic, strong) CBUUID *Hardware_Revision_Characteristic_UUID;

// 指令通道
@property (nonatomic, strong) CBService        *cmdProfileService;
@property (nonatomic, strong) CBCharacteristic *cmdReadCharacteristic;
@property (nonatomic, strong) CBCharacteristic *cmdWriteCharacteristic;
@property (nonatomic, strong) CBCharacteristic *dfuWxCharacteristic;
@property (nonatomic, strong) CBCharacteristic *dfuRxCharacteristic;
@property (nonatomic, strong) CBCharacteristic *logCharacteristic;

@property (nonatomic, strong) CBService *batteryService;
@property (nonatomic, strong) CBCharacteristic *batteryCharacteristic;

// 数据通道
@property (nonatomic, strong) CBService        *dataProfileService;
@property (nonatomic, strong) CBCharacteristic *dataReadCharacteristic;
@property (nonatomic, strong) CBCharacteristic *dataWriteCharacteristic;
@property (nonatomic, strong) CBCharacteristic *offlineReadCharacteristic;
@property (nonatomic, strong) CBCharacteristic *offlineWriteCharacteristic;

@property (nonatomic, assign          ) BOOL     isAutoReconnect;
@property (nonatomic, assign, readonly) BOOL     isConnected;
@property (nonatomic, strong, readonly) NSString *channelName;///<多设备通道标识

@property (nonatomic, weak) id <BPBLEDeviceControlDelegate> delegate;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral centralManager:(CBCentralManager *)centralManger;
- (void)initUUIDs;


#pragma mark - Virtual

- (void)handleDiscoverServicesWithChannel:(NSString *)channel peripheral:(CBPeripheral *)peripheral error:(NSError *)error;
- (void)handleDiscoverCharacteristicsWithChannel:(NSString *)channel peripheral:(CBPeripheral *)peripheral service:(CBService *)service error:(NSError *)error;

- (void)handleDiscoverCMDCharacteristics:(CBCharacteristic *)characteristics;
- (void)handleDiscoverDataCharacteristics:(CBCharacteristic *)characteristic;

- (BOOL)handleDidUpdateValueForCharacteristicWithPeripheral:(CBPeripheral *)peripheral characteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

- (void)processRecvCmdReadResponseWithCommand:(uint16_t)command value:(NSData *)value isError:(BOOL)isError;
- (BOOL)processOfflineDataCharacteristic :(CBCharacteristic *)characteristic;
/**
 Body Data Frame Processing
 */
- (void)processDataFrameWithBytes:(const uint8_t *)bytes length:(NSUInteger)length;

/**
 解析收到的完整数据帧
 
 @reciveCompleteData 处理去掉CRC校验位的数据, 即数据长度=原数据-1
 @reciveDate 接收头帧时间
 */
- (void)processFullDataFrame:(NSData *)reciveCompleteData withTime:(NSDate *)reciveDate;


//- (void)connect;
//- (void)connecteWithCompletion:(void (^)(BPBLEDeviceControl *device, BOOL bSuccess, NSString *error))completion;
//- (void)disconnet;

- (void)scanServicesWithCompletion:(void (^)(void))completion;

#pragma mark - Base Command
- (void)readFirmwareVersionWithCompletion:(void (^)(BOOL bSuccessm, NSString *version))completion;
- (void)excuteCommandWithPermission:(BPCommandPermission)permission command:(uint16_t)command playloadLength:(uint8_t)playloadLength playload:(NSData *)playload needRespond:(BOOL)needRespond;

- (BOOL)crcWithBytes:(const uint8_t *)bytes length:(NSUInteger)length;
@end
