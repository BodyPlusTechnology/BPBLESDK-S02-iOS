//
//  BPBLEDemoVC.m
//  BPBLEDemo
//
//  Created by GrayLand on 2019/3/26.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import "BPBLEDemoVC.h"
#import "BPScanningVC.h"

//#import "BPBLESDKLiteS02.h"
#import <BPBLESDK/BPBLESDKLiteS02.h>
#import <Masonry/Masonry.h>

@interface BPBLEDemoVC ()
<UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, strong) UITableView *tableView;
@end

@implementation BPBLEDemoVC

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = @"BPBLEDemo";
    
    [self setupViews];
    [self setupLayouts];
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
    [self.navigationController.navigationBar setBackgroundImage:[UIImage imageWithColor:FONT_COLOR1] forBarMetrics:UIBarMetricsDefault];
}

#pragma mark - Custom delegate

#pragma mark - UITableViewDelegate, UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 50;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UITableViewCell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:(UITableViewCellStyleValue1) reuseIdentifier:@"UITableViewCell"];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    switch (indexPath.row) {
        case 0:
            cell.textLabel.text = @"Scan Core - S02(Aerobic)";
            break;
            
        default:
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    if (indexPath.row == 0) {
        if (!BPBLEManagerS02.defaultManager.isBLEPowerOn) {
            [self showHudWithMessage:@"BLE is powered Off"];
            return;
        }
        
        BPScanningVC *vc = [BPScanningVC new];
        [self.navigationController pushViewController:vc animated:YES];
        return;
    }
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
