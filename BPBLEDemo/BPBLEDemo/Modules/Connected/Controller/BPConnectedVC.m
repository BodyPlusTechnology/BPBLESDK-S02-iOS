//
//  BPConnectedVC.m
//  BPBLEDemo
//
//  Created by GrayLand on 2019/3/27.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import "BPConnectedVC.h"
#import <BPBLESDK02/BPBLESDKLiteS02.h>
#import <iOSDFULibrary-Swift.h>
#import <Masonry/Masonry.h>

typedef NS_ENUM(NSUInteger, CellType) {
    CellTypeDeviceInfo = 0,
    CellTypeBattery,
    CellTypeHardwareVersion,
    CellTypeFirmwareVersion,
    CellTypeECGState,
    CellTypeCorePositionAndPowerState,
    CellTypeHRBRValue,
    CellTypeMonitorHRBR,
    CellTypeGetOfflineMode,
    CellTypeGetOfflineDataInfo,
    CellTypeGetOfflineSync,
    CellTypeEraseCurrentOfflineData,
    CellTypeEraseOfflineData,
    CellTypeBoostloaderVersion,
    CellTypeRename,
    CellTypeStartFirmwareUpgrade,
    CellTypeStartBoostloaderUpgrade,
    CellTypeEnd
};

@interface BPConnectedVC ()
<UITableViewDelegate, UITableViewDataSource, BPBLEManagerS02Delegate>

@property (nonatomic, strong) UITableView *tableView;

@end

@implementation BPConnectedVC

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setupViews];
    [self setupLayouts];
    
    [BPBLEManagerS02.defaultManager addDelegate:self];
    
    [_tableView reloadData];
}

- (void)dealloc {
    [BPBLEManagerS02.defaultManager removeDelegate:self];
}

- (void)setupViews {
    UIButton *disconnetBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    [disconnetBtn setTitle:@"Disconnet" forState:UIControlStateNormal];
    UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithCustomView:disconnetBtn];
    [disconnetBtn addTarget:self action:@selector(onDisconnetBtn) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.leftBarButtonItem = item;
    
    [self.view addSubview:self.tableView];
}

- (void)setupLayouts {
    [_tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.mas_equalTo(0);
        if (@available(iOS 11.0, *)) {
            make.top.mas_equalTo(self.view.mas_safeAreaLayoutGuideTop);
        } else {
            make.top.mas_equalTo(self.view).offset(STATUS_AND_NAVIGATION_HEIGHT);
        }
    }];
}

#pragma mark - Custom delegate
#pragma mark - UITableViewDelegate, UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return CellTypeEnd;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return UITableViewAutomaticDimension;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ActionCell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"ActionCell"];
        cell.detailTextLabel.numberOfLines = 0;
    }
    BPBLEDeviceS02 *device = BPBLEManagerS02.defaultManager.currentDevice;
    if (!device.isConnected) {
        cell.textLabel.text = @"--";
        cell.detailTextLabel.text = @"--";
        cell.accessoryType = UITableViewCellAccessoryNone;
        return cell;
    }
    
    switch (indexPath.row) {
        case CellTypeDeviceInfo: {
            cell.textLabel.text = [NSString stringWithFormat:@"Name:%@", device.localName];
            cell.detailTextLabel.text = [NSString stringWithFormat:@"SN:%@", device.SN];
            cell.accessoryType = UITableViewCellAccessoryNone;
        }break;
        case CellTypeBattery: {
            cell.textLabel.text = @"Battery:";
            cell.detailTextLabel.text = [NSString stringWithFormat:@"%.0f%%", device.battery];
            cell.accessoryType = UITableViewCellAccessoryNone;
        }break;
        case CellTypeHardwareVersion: {
            cell.textLabel.text = @"Hardware Version:";
            cell.detailTextLabel.text = device.dispHWVersion;
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeFirmwareVersion: {
            cell.textLabel.text = @"Firmware Version:";
            cell.detailTextLabel.text = device.dispFWVersion;
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeECGState: {
            cell.textLabel.text = @"ECGState:";
            cell.detailTextLabel.text = device.isECGStateOK?@"OK":@"Come Off";
            cell.accessoryType = UITableViewCellAccessoryNone;
        }break;
        case CellTypeCorePositionAndPowerState: {
            cell.textLabel.text = @"Core Position/Power State:";
            NSMutableString *str = [[NSMutableString alloc] init];
            switch (device.currentPosition) {
                case CoreS02PositionCoat:[str appendString:@"Coat"];break;
                case CoreS02PositionPants:[str appendString:@"Pants"];break;
                case CoreS02PositionIsolate:[str appendString:@"Isolate"];break;
                case CoreS02PositionChargingBase:[str appendString:@"On charging base"];break;
                default:[str appendString:@"Unknow Position"];break;
            }
            [str appendString:@"/"];
            switch (device.currentPowerState) {
                case CoreS02PowerStateNormal:[str appendString:@"Normal"];break;
                case CoreS02PowerStateCharging:[str appendString:@"Charging"];break;
                case CoreS02PowerStateBatteryFull:[str appendString:@"BatteryFull"];break;
                case CoreS02PowerStateBatteryLow:[str appendString:@"BatteryLow"];break;
                case CoreS02PowerStateExhaust:[str appendString:@"Exhaust"];break;
                default:[str appendString:@"Unknow"];break;
            }
            cell.detailTextLabel.text = str;
            cell.accessoryType = UITableViewCellAccessoryNone;
        }break;
        case CellTypeMonitorHRBR: {
            cell.textLabel.text = @"Monitor HRBR:";
            cell.detailTextLabel.text = device.isMonitoringHRBRMode?@"Working - Tap to stop monitoring":@"Doesn't working yet - Tap to start monitoring";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeHRBRValue: {
            cell.textLabel.text = @"HRBR Value:";
            cell.detailTextLabel.text = [NSString stringWithFormat:@"HR:%ld\nBR:%ld", device.curHR, device.curBR];
            cell.accessoryType = UITableViewCellAccessoryNone;
        }break;
        case CellTypeGetOfflineMode: {
            cell.textLabel.text = @"Offline Mode:";
            cell.detailTextLabel.text = device.isOfflineMode?@"On - Tap to turn offline mode off":@"Off - Tap to turn offline mode On";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeGetOfflineDataInfo: {
            cell.textLabel.text = @"Offline Data Info:";
            cell.detailTextLabel.text = [NSString stringWithFormat:@"Data Num:%ld",
                                         device.offlineDataNum];
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeGetOfflineSync: {
            cell.textLabel.text = @"Sync Offline Data:";
            cell.detailTextLabel.text = @"Tap to sync data";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeEraseCurrentOfflineData: {
            cell.textLabel.text = @"Erase Current Offline Data:";
            cell.detailTextLabel.text = @"Tap to erase curData";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeEraseOfflineData: {
            cell.textLabel.text = @"Erase Offline Data:";
            cell.detailTextLabel.text = @"Tap to erase data";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeBoostloaderVersion: {
            cell.textLabel.text = @"Boostloader version:";
            cell.detailTextLabel.text = [NSString stringWithFormat:@"%ld", device.boostloaderVersion];
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeRename: {
            cell.textLabel.text = @"Tap to rename";
            cell.detailTextLabel.text = @"";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeStartFirmwareUpgrade: {
            cell.textLabel.text = @"Tap to start firmware upgrading";
            cell.detailTextLabel.text = @"";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
        case CellTypeStartBoostloaderUpgrade: {
            cell.textLabel.text = @"Tap tp start boostloader Upgrading";
            cell.detailTextLabel.text = @"";
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }break;
            
        default:
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    BPBLEDeviceS02 *device = BPBLEManagerS02.defaultManager.currentDevice;
    switch (indexPath.row) {
        case CellTypeMonitorHRBR: {
            if (device.isMonitoringHRBRMode) {
                // to stop monitor
                [device stopMonitorHRBR];
                
                [tableView beginUpdates];
                [tableView reloadRow:CellTypeMonitorHRBR inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView reloadRow:CellTypeHRBRValue inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView endUpdates];
            }else {
                // to start monitor
                [device startMonitorHRBR];
                
                [tableView beginUpdates];
                [tableView reloadRow:CellTypeMonitorHRBR inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView endUpdates];
            }
        }break;
            
        case CellTypeHardwareVersion: {
            [device queryHardwareVersionWithCompletion:^(BOOL bSuccess, NSInteger version) {
                if (bSuccess) {
                    NSLog(@"Hardware Version : 0x%lx - %ld", (long)version, version);
                }
            }];
        }break;
            
        case CellTypeFirmwareVersion: {
            [device queryFirmwareVersionWithCompletion:^(BOOL bSuccess, NSInteger version) {
                if (bSuccess) {
                    NSLog(@"Firmware Version : 0x%lx - %ld", (long)version, version);
                }
            }];
        }break;
            
        case CellTypeGetOfflineMode: {
            if (device.isOfflineMode) {
                [device stopOfflineMonitoring];
            }else {
                [device startOfflineMonitoring];
            }
            [tableView beginUpdates];
            [tableView reloadRow:CellTypeMonitorHRBR inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
            [tableView reloadRow:CellTypeGetOfflineMode inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
            [tableView endUpdates];
            
            //            [device queryCoreModeWithCompletion:^(BOOL bSuccess, CoreS02MonitorMode mode) {
            //                [tableView beginUpdates];
            //                [tableView reloadRow:CellTypeGetOfflineMode inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
            //                [tableView reloadRow:CellTypeMonitorHRBR inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
            //                [tableView endUpdates];
            //            }];
        }break;
            
        case CellTypeGetOfflineDataInfo: {
            [device queryOfflineDataNumWithCompletion:^(NSInteger totalLength, NSInteger dataNum) {
                [tableView beginUpdates];
                [tableView reloadRow:CellTypeGetOfflineDataInfo inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView endUpdates];
            }];
        }break;
        case CellTypeGetOfflineSync: {
            if (device.offlineDataNum == 0) {
                [self showHudWithMessage:@"Have not offline datas."];
                return;
            }
            [self showWaittingHudWithMessage:@"sychronizing" progress:0.0];
            [device syncOfflineDataWithProgressHandler:^(CGFloat progress) {
                [self showWaittingHudWithMessage:@"sychronizing" progress:progress];
            } finishHandler:^(NSInteger timestamp, NSArray<NSNumber *> *hrDatas, NSArray<NSNumber *> *brDatas) {
                [self hideHud];
                NSString *dirPath = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject;
                dirPath = [dirPath stringByAppendingPathComponent:@"offline"];
                NSInteger timeSec = floor(NSDate.date.timeIntervalSince1970);
                NSString *hrPath = [dirPath stringByAppendingPathComponent:[NSString stringWithFormat:@"hrDatas-%ld.dat", timeSec]];
                NSString *brPath = [dirPath stringByAppendingPathComponent:[NSString stringWithFormat:@"brDatas-%ld.dat", timeSec]];
                
                [hrDatas writeToFile:hrPath atomically:YES];
                [brDatas writeToFile:brPath atomically:YES];
                [self showHudWithMessage:[NSString stringWithFormat:@"Count: HR:%ld,BR:%ld",
                                          hrDatas.count,
                                          brDatas.count]];
            }];
            
        }break;
        case CellTypeEraseCurrentOfflineData: {
            [BPBLEManagerS02.defaultManager.currentDevice eraseCurrentOfflineDataWithCompletion:^(BOOL bSuccess, NSString *error) {
                [tableView beginUpdates];
                [tableView reloadRow:CellTypeGetOfflineDataInfo inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView reloadRow:CellTypeEraseCurrentOfflineData inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView endUpdates];
            }];
        }break;
        case CellTypeEraseOfflineData: {
            [self showWaittingHudWithMessage:@"Erasing"];
            [device eraseAllOfflineDataWithCompletion:^(BOOL bSuccess, NSString *error) {
                [self hideHud];
                if (!bSuccess) {
                    [self showHudWithMessage:error];
                    return;
                }
                [tableView beginUpdates];
                [tableView reloadRow:CellTypeGetOfflineDataInfo inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView endUpdates];
            }];
            
        }break;
        case CellTypeBoostloaderVersion: {
            [device queryBoostloaderVersionWithCompletion:^(BOOL bSuccess, NSInteger version) {
                [tableView beginUpdates];
                [tableView reloadRow:CellTypeBoostloaderVersion inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                [tableView endUpdates];
            }];
        }break;
        case CellTypeRename: {
            __block UITextField *editTF;
            UIAlertController* alertController = [UIAlertController alertControllerWithTitle:@"Rename" message:@"Input the new name this core(less than 12 bytes)" preferredStyle:UIAlertControllerStyleAlert];
            [alertController addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
            }]];
            [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
                editTF = textField;
            }];
            [alertController addAction:[UIAlertAction actionWithTitle:@"Rename" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                NSString *customName = editTF.text;
                NSData* nameData = [customName dataUsingEncoding:NSUTF8StringEncoding];
                if (customName.length == 0 || customName == nil) {
                    [self showHudWithMessage:@"New name can't be empty!"];
                    return;
                } else if(nameData.length > 12) {
                    [self showHudWithMessage:@"New name must be less than 12 bytes"];
                    return;
                }
                
                [self showWaittingHud];
                [device renameWithName:customName completion:^(BOOL bSuccess) {
                    [self hideHud];
                    if (bSuccess) {
                        [self showHudWithMessage:@"Rename Success!"];
                        [tableView beginUpdates];
                        [tableView reloadRow:CellTypeDeviceInfo inSection:0 withRowAnimation:(UITableViewRowAnimationAutomatic)];
                        [tableView endUpdates];
                    }else{
                        [self showHudWithMessage:@"Rename failure!"];
                    }
                }];
            }]];
            
            [self presentViewController:alertController animated:YES completion:nil];
        }break;
        case CellTypeStartFirmwareUpgrade: {
            [self showWaittingHudWithMessage:@"Upgrading" progress:0.01];
            BPS02DFUConfig *config = [BPS02DFUConfig defaultConfigWithPackageDir:nil];
            // In demo , for testing upgrade can set a big version num to always upgrading when tap, otherwise will notice 'Already leatest version' and skip upgrade.
            //            config.latestFirmwareVersion = 0xFFFF;
            //            config.latestBoostloaderVersion = 5;
            
            [BPBLEManagerS02.defaultManager startUpgradeWithDevice:device config:config stateChangedHandler:^(UpgradeState state) {
                NSLog(@"Upgrade State >>> %@", @(state));
            } progressHandler:^(CGFloat progress) {
                [self showWaittingHudWithMessage:@"Upgrading" progress:progress];
            } successHandler:^(BPBLEDeviceS02 * _Nonnull reconnectedDevice) {
                [self hideHud];
                if (reconnectedDevice) {
                    [self showHudWithMessage:@"Upgrading Success" duration:3.0];
                }else {
                    [self showHudWithMessage:@"Was latest version"];
                }
                [tableView reloadData];
            } failureHandler:^(NSInteger errorCode, NSString * _Nonnull msg) {
                [self hideHud];
                [self showHudWithMessage:msg duration:5.0];
            }];
        }break;
        case CellTypeStartBoostloaderUpgrade: {
            BOOL needUpgrade = NO;
            BPS02DFUConfig *dfuConfig = [BPS02DFUConfig defaultConfigWithPackageDir:nil];
            // In demo , for testing upgrade can set a big version num to always upgrading when tap, otherwise will notice 'Already leatest version' and skip upgrade.
            //            config.latestFirmwareVersion = 0xFFFF;
            //            config.latestBoostloaderVersion = 6;
            // or
            //#if DEBUG
            //    static BOOL hasDFU = NO;
            //    if (!hasDFU) {
            //        hasDFU = YES;
            //        dfuConfig.latestFirmwareVersion = 0xFFFF;
            //    }
            //#endif
            if (device.boostloaderVersion < dfuConfig.latestBoostloaderVersion) {
                needUpgrade = YES;
            }
            
            NSInteger hexVersion = [[NSString stringWithFormat:@"%lx", device.firmwareVersion] integerValue];
            if (hexVersion < dfuConfig.latestFirmwareVersion) {
                needUpgrade = YES;
            }
            
            if (!needUpgrade) {
                [self showHudWithMessage:@"Was latest version"];
                return;
            }
            
            [self showWaittingHudWithMessage:@"Upgrading" progress:0.01];
            
            [BPBLEManagerS02.defaultManager startUpgradeWithDevice:device config:dfuConfig stateChangedHandler:^(UpgradeState state) {
                NSLog(@"Upgrade State >>> %@", @(state));
            } progressHandler:^(CGFloat progress) {
                [self showWaittingHudWithMessage:@"Upgrading" progress:progress];
            } successHandler:^(BPBLEDeviceS02 * _Nonnull reconnectedDevice) {
                [self hideHud];
                if (reconnectedDevice) {
                    [self showHudWithMessage:@"Upgrading Success" duration:3.0];
                }else {
                    [self showHudWithMessage:@"Was latest version"];
                }
                [tableView reloadData];
            } failureHandler:^(NSInteger errorCode, NSString * _Nonnull msg) {
                [self hideHud];
                [self showHudWithMessage:msg duration:5.0];
            }];
        }break;
        default:
            break;
    }
    
}

#pragma mark - BPBLEManagerS02Delegate

- (void)deviceS02DidConnected:(BPBLEDeviceS02 *)deviceS02 {
    [self hideHud];
    [self showHudWithMessage:[NSString stringWithFormat:@"Device %@ connected", deviceS02.localName]];
    [_tableView reloadData];
}

- (void)deviceS02DidDisconnected:(BPBLEDeviceS02 *)deviceS02 {
    [_tableView reloadData];
}

- (void)blePermissionPoweredOff {
    [self showHudWithMessage:@"BLE Powered Off"];
    [_tableView reloadData];
}

- (void)blePermissionPoweredOn {
    [self showHudWithMessage:@"BLE Powered On"];
    [_tableView reloadData];
}

- (void)deviceS02:(BPBLEDeviceS02 *)deviceS02 valueDidChangeWithHeartRate:(NSInteger)hr breathRate:(NSInteger)br {
    [_tableView beginUpdates];
    [_tableView reloadRow:CellTypeHRBRValue inSection:0 withRowAnimation:UITableViewRowAnimationAutomatic];
    [_tableView endUpdates];
}

- (void)deviceS02:(BPBLEDeviceS02 *)deviceS02 batteryDidChange:(CGFloat)battery {
    [_tableView beginUpdates];
    [_tableView reloadRow:CellTypeBattery inSection:0 withRowAnimation:UITableViewRowAnimationAutomatic];
    [_tableView endUpdates];
}

- (void)deviceS02PowerStateDidChange:(BPBLEDeviceS02 *)deviceS02 {
    [_tableView beginUpdates];
    [_tableView reloadRow:CellTypeCorePositionAndPowerState inSection:0 withRowAnimation:UITableViewRowAnimationAutomatic];
    [_tableView endUpdates];
}

- (void)deviceS02PositionDidChange:(BPBLEDeviceS02 *)deviceS02 {
    [_tableView beginUpdates];
    [_tableView reloadRow:CellTypeCorePositionAndPowerState inSection:0 withRowAnimation:UITableViewRowAnimationAutomatic];
    [_tableView reloadRow:CellTypeECGState inSection:0 withRowAnimation:UITableViewRowAnimationAutomatic];
    [_tableView reloadRow:CellTypeMonitorHRBR inSection:0 withRowAnimation:UITableViewRowAnimationAutomatic];
    [_tableView endUpdates];
}

- (void)deviceS02WillReconnect:(BPBLEDeviceS02 *)deviceS02 {
    [self showWaittingHudWithMessage:@"Reconnecting"];
}

#pragma mark - Event response

- (void)onDisconnetBtn {
    [BPBLEManagerS02.defaultManager disconnectCurrentDevice];
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - Private methods

#pragma mark - Setter

#pragma mark - Getter

- (UITableView *)tableView {
    if (!_tableView) {
        _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStyleGrouped];
        _tableView.delegate = self;
        _tableView.dataSource = self;
    }
    return _tableView;
}

@end
