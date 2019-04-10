//
//  BPBLEDFUDevice.h
//  BodyPlusECG
//
//  Created by GrayLand on 2018/1/4.
//  Copyright © 2018年 BodyPlus. All rights reserved.
//

#import "BPBLEDeviceControl.h"

@interface BPBLEDFUDevice : BPBLEDeviceControl

@property (nonatomic, copy) void (^changeToDFUModeHandler)(BOOL bSuccess);

- (instancetype)initWithBaseDevice:(BPBLEBaseDevice *)baseDevice centralManager:(CBCentralManager *)centralManger;

@end
