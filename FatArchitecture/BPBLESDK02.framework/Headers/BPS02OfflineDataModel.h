//
//  BPS02OfflineDataModel.h
//  BPBLEDemo
//
//  Created by GrayLand on 2019/3/27.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BPS02OfflineDataModel : NSObject
@property (nonatomic, assign) NSInteger itemID;
@property (nonatomic, assign) NSInteger timeOffset;
@property (nonatomic, assign) NSInteger data;
@end

NS_ASSUME_NONNULL_END
