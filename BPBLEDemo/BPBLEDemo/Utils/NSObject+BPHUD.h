//
//  NSObject+BPHUD.h
//  BPCoachClient
//
//  Created by GrayLand on 2018/7/4.
//  Copyright © 2018 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MBProgressHUD.h"

@interface NSObject (BPHUD)

- (void)showWaittingHud;
- (void)showWaittingHudWithMessage:(NSString *)message;
- (void)hideHud;

- (void)showHudWithMessage:(NSString *)message;
- (void)showHudWithMessage:(NSString *)message duration:(NSTimeInterval)duration;

- (void)showWaittingHudWithMessage:(NSString *)message progress:(CGFloat)progress;

@end
