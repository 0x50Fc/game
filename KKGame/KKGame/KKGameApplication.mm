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

static kk::ScriptResult KKGameApplication_print_func(kk::ScriptContext ctx) {
    
    int nargs = duk_get_top(ctx);
    
    printf("[KK]");
    
    for(int i=0;i<nargs;i++) {
        duk_int_t type =  duk_get_type(ctx, -nargs + i);
        switch (type) {
            case DUK_TYPE_NUMBER:
                printf(" %g", duk_to_number(ctx, -nargs + i));
                break;
            case DUK_TYPE_STRING:
                printf(" %s", duk_to_string(ctx, -nargs + i));
                break;
            case DUK_TYPE_BOOLEAN:
                printf(" %s", duk_to_boolean(ctx, -nargs + i) ? "true":"false" );
                break;
            case DUK_TYPE_OBJECT:
                printf(" [object]");
                break;
            case DUK_TYPE_POINTER:
                printf(" [0x%lx]",(unsigned long) duk_to_pointer(ctx, -nargs + i));
                break;
            case DUK_TYPE_UNDEFINED:
                printf(" undefined");
                break;
            case DUK_TYPE_NULL:
                printf(" null");
                break;
            default:
                break;
        }
    }
    
    printf("\n");
    
    return 0;
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
        
        duk_push_global_object(_jsContext);
        
        duk_push_string(_jsContext, "print");
        duk_push_c_function(_jsContext, KKGameApplication_print_func, DUK_VARARGS);
        duk_put_prop(_jsContext, -3);
        
        duk_push_string(_jsContext, "app");
        
        _app = kk::ScriptNewObject<kk::Application>(_jsContext, 0);
        
        _app->setBasePath([[bundle bundlePath] UTF8String]);
        
        duk_put_prop(_jsContext, -3);
        
        duk_pop(_jsContext);
        
        ScriptOpenClass(_jsContext, "Document", &kk::Document::Class);
        ScriptOpenClass(_jsContext, "Element", &kk::Element::Class);
        ScriptOpenClass(_jsContext, "ElementEvent", &kk::ElementEvent::Class);
        ScriptOpenClass(_jsContext, "ElementActionEvent", &kk::ElementActionEvent::Class);
        
        ScriptOpenClass(_jsContext, "GLElement", &kk::gl::GLElement::Class);
        ScriptOpenClass(_jsContext, "GLImageElement", &kk::gl::GLImageElement::Class);
        
        ScriptOpenClass(_jsContext, "GMSceneElement", &kk::game::GMSceneElement::Class);
        ScriptOpenClass(_jsContext, "GMTextureElement", &kk::game::GMTextureElement::Class);
        
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
