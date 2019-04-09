//
//  NSObject+BPHUD.m
//  BPCoachClient
//
//  Created by GrayLand on 2018/7/4.
//  Copyright © 2018 BodyPlus. All rights reserved.
//

#import "NSObject+BPHUD.h"
#import <objc/runtime.h>
#import "pthread.h"

static void* kHUD                 = &"kHUD";

@implementation NSObject (BPHUD)

- (MBProgressHUD *)HUD{
    return objc_getAssociatedObject(self, kHUD);
}

- (void)setHUD:(MBProgressHUD *)HUD{
    objc_setAssociatedObject(self, kHUD, HUD, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)hideHud {
    __block MBProgressHUD *hudb = [self HUD];
    if (hudb) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [hudb hideAnimated:YES];
            hudb = nil;
            objc_setAssociatedObject(self, kHUD, hudb, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        });
    }
}

- (void)showWaittingHud {
    MBProgressHUD *hudb = [self HUD];
    if (hudb) [hudb removeFromSuperview];
    hudb = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];
    hudb.removeFromSuperViewOnHide = YES;
    [self setHUD:hudb];
}

- (void)showWaittingHudWithMessage:(NSString *)message {
    MBProgressHUD *hudb = [self HUD];
    if (hudb) [hudb removeFromSuperview];
    hudb = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];
    hudb.removeFromSuperViewOnHide = YES;
    hudb.label.numberOfLines = 0;
    hudb.label.text = message;
    hudb.label.font = [UIFont systemFontOfSize:12];
    [self setHUD:hudb];
}

- (void)showHudWithMessage:(NSString *)message {
    [self showHudWithMessage:message duration:2.0];
}

- (void)showHudWithMessage:(NSString *)message duration:(NSTimeInterval)duration {
    if (!pthread_main_np()) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self showHudWithMessage:message duration:duration];
        });
        return;
    }
    
    MBProgressHUD *hudb = [self HUD];
    if (hudb) [hudb removeFromSuperview];
    
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];
    hud.removeFromSuperViewOnHide = YES;
    hud.mode = MBProgressHUDModeText;
    hud.margin = 18.f;
    hud.detailsLabel.font = [UIFont systemFontOfSize:18];
    hud.detailsLabel.text = message;
    hud.detailsLabel.numberOfLines = 0;
    hud.contentColor = [UIColor colorWithWhite:0.0 alpha:0.9];
    //    [hud hide:YES afterDelay:2];
    [hud hideAnimated:YES afterDelay:duration];
    [self setHUD:hudb];
}

- (void)showWaittingHudWithMessage:(NSString *)message progress:(CGFloat)progress {
    [self showWaittingHudWithMessage:message progress:progress type:MBProgressHUDModeAnnularDeterminate];
}

- (void)showWaittingHudWithMessage:(NSString *)message progress:(CGFloat)progress type:(MBProgressHUDMode)type {
    MBProgressHUD *hudb = [self HUD];
    if (!hudb) {
        hudb = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];
        [self setHUD:hudb];
    }
    hudb.mode = type;
    hudb.progress = progress;
    
    hudb.removeFromSuperViewOnHide = YES;
    hudb.label.numberOfLines = 0;
    hudb.label.text = message;
    hudb.label.font = [UIFont systemFontOfSize:18];
    
    //    hudb.activityIndicatorColor = [UIColor lightGrayColor];
    //    [UIActivityIndicatorView appearanceWhenContainedIn:[MBProgressHUD class], nil].color = [UIColor lightGrayColor];
    //hudb.detailsLabelText = [NSString stringWithFormat:@"已下载 %.1f%%", progress * 100];
    hudb.square = NO;
    
    if (progress == 1.0) hudb.detailsLabel.text = nil;
}
@end
