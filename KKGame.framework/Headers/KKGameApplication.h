//
//  KKGameApplication.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <KKGame/kk-script.h>

@interface KKGameApplication : NSObject

@property(nonatomic,strong,readonly) NSBundle * bundle;
@property(nonatomic,assign,readonly) kk::ScriptContext jsContext;

-(instancetype) initWithBundle:(NSBundle *) bundle;

+(instancetype) main;

@end
