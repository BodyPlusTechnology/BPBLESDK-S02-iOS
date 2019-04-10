//
//  BPScanningVC.m
//  BPBLEDemo
//
//  Created by GrayLand on 2019/3/26.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import "BPScanningVC.h"
#import "BPConnectedVC.h"
#import <BPBLESDK02/BPBLESDKLiteS02.h>
#import <Masonry/Masonry.h>

@interface BPScanningVC ()
<UITableViewDelegate, UITableViewDataSource, BPBLEManagerS02Delegate>

@property (nonatomic, strong) UITableView *tableView;

@property (nonatomic, strong) NSArray <BPBLEBaseDevice *> * _Nonnull discoveredDevices;
@end

@implementation BPScanningVC

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setupViews];
    [self setupLayouts];
    
    [BPBLEManagerS02.defaultManager addDelegate:self];
}

- (void)dealloc {
    [BPBLEManagerS02.defaultManager removeDelegate:self];
}

- (void)setupViews {
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

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self startScanning];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self stopScanning];
}

- (void)startScanning {
    __weak __typeof(self) ws = self;
    [self showWaittingHudWithMessage:@"Scanning"];
    [BPBLEManagerS02.defaultManager scanAllDeviceS02WithUpdateInterval:2.0 sortByRSSI:YES updateHandler:^(NSArray<BPBLEBaseDevice *> * _Nonnull devices) {
        if (devices.count > 0) {
            [self hideHud];
        }else {
            [self showWaittingHudWithMessage:@"Scanning"];
        }
        ws.discoveredDevices = devices;
        [ws.tableView reloadData];
    }];
}

- (void)stopScanning {
    [self hideHud];
    [BPBLEManagerS02.defaultManager stopScanning];
}


#pragma mark - Custom delegate
#pragma mark - UITableViewDelegate, UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _discoveredDevices.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return UITableViewAutomaticDimension;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"DeviceCell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"DeviceCell"];
        cell.detailTextLabel.numberOfLines = 0;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    BPBLEBaseDevice *device = _discoveredDevices[indexPath.row];
    cell.textLabel.text = device.localName;
    cell.detailTextLabel.text = [NSString stringWithFormat:@"SN:%@\nRSSI:%@\nRSSI Level:%ld", device.SN, device.RSSI, device.signalIntensity];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    [self stopScanning];
    
    BPBLEBaseDevice *device = _discoveredDevices[indexPath.row];
    [self showWaittingHudWithMessage:@"Connecting"];
    [BPBLEManagerS02.defaultManager connectDevice:device withTimeout:7.0 successHandler:^(BOOL bSuccess, id device, NSError *error) {
        [self hideHud];
        BPConnectedVC *vc = [BPConnectedVC new];
        [self.navigationController pushViewController:vc animated:YES];
    } failureHandler:^(BOOL isTimeout, NSString *error) {
        [self hideHud];
        [self showHudWithMessage:[NSString stringWithFormat:@"Connect Failure %@", error]];
    }];
    
}

#pragma mark - BPBLEManagerS02Delegate

- (void)deviceS02DidConnected:(BPBLEDeviceS02 *)deviceS02 {
//    [self showHudWithMessage:[NSString stringWithFormat:@"Device %@ connected", deviceS02.localName]];
}

- (void)deviceS02DidDisconnected:(BPBLEDeviceS02 *)deviceS02 {
//    [self showHudWithMessage:[NSString stringWithFormat:@"Device %@ disconnected", deviceS02.localName]];
}

- (void)blePermissionPoweredOff {
    [self showHudWithMessage:@"BLE Powered Off"];
}

- (void)blePermissionPoweredOn {
    [self showHudWithMessage:@"BLE Powered On"];
}

#pragma mark - Event response

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
