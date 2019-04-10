//
//  BPBLEDeviceControl.h
//  BPToolBox
//
//  Created by GrayLand on 2017/10/18.
//  Copyright © 2017年 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BPBLEBaseDevice.h"

@class BPBLEDeviceControl;
@protocol BPBLEDeviceControlDelegate <NSObject>
@optional
- (void)device:(BPBLEDeviceControl *)device disconnectWithError:(NSError *)error;
- (void)device:(BPBLEDeviceControl *)device didUpdatedBattery:(CGFloat)battery;
@end

@interface BPBLEDeviceControl : BPBLEBaseDevice

@property (nonatomic, assign          ) BOOL     isAutoReconnect;
@property (nonatomic, assign, readonly) BOOL     isConnected;
@property (nonatomic, strong, readonly) NSString *channelName;///<多设备通道标识

@end
