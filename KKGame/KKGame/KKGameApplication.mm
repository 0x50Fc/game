//
//  KKGameApplication.m
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk.h"
#include "kk-game.h"
#import "KKGameApplication.h"

#include <strstream>

static void KKGameApplication_fatal_function (void *udata, const char *msg) {
    kk::Log("Fail %s",msg);
}

@interface KKGameApplication() {
}

@end

@implementation KKGameApplication

-(instancetype) init {
    return [self initWithBundle:[NSBundle mainBundle]];
}

-(instancetype) initWithBundle:(NSBundle *) bundle {
    if((self = [super init])) {
        
        _bundle = bundle;
        
        _jsContext = duk_create_heap(NULL, NULL, NULL, NULL, KKGameApplication_fatal_function);
        
        kk::game::openlibs(_jsContext);
        
        duk_push_global_object(_jsContext);
        
        duk_push_string(_jsContext, "app");
        
        _app = kk::ScriptNewObject<kk::Application>(_jsContext, 0);
        
        _app->setBasePath([[bundle bundlePath] UTF8String]);
        
        duk_put_prop(_jsContext, -3);
        
        duk_pop(_jsContext);
    }
    return self;
}

-(void) dealloc {
    duk_destroy_heap(_jsContext);
}

-(void) run {
    
    kk::CString path = "/main.js";
    
    if(_app->has(path)) {
        
        std::strstream ss;
        
        ss << "(function(){";
        ss << _app->getString(path);
        ss << "})";
        ss << std::ends;
        
        duk_pop(_jsContext);
        
        const char * s = ss.str();
        
        duk_eval_string(_jsContext, s);
        
        if(duk_is_function(_jsContext, -1)) {
            
            if( duk_pcall(_jsContext, 0) == DUK_EXEC_SUCCESS ) {
                kk::Log("[OK] %s",path);
            } else {
                kk::Log("[Fail] %s Error: %s",path,duk_to_string(_jsContext, -1));
            }
            
            duk_pop(_jsContext);
            
        } else {
            duk_pop(_jsContext);
        }
    }
    
}

+(instancetype) main{
    static KKGameApplication * v = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        v = [[KKGameApplication alloc] initWithBundle:[NSBundle mainBundle]];
    });
    return v;
}
@end
