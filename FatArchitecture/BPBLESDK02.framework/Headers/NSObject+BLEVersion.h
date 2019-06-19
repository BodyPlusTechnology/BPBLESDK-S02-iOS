//
//  NSObject+BLEVersion.h
//  BPStudentClient
//
//  Created by GrayLand on 2019/6/4.
//  Copyright © 2019 BodyPlus. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (BLEVersion)

- (NSString *)displayVersionWithInt:(NSInteger)iValue;

@end

NS_ASSUME_NONNULL_END
