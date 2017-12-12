//
//  KKGameViewController.m
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import "KKGameViewController.h"
#import "KKGameApplication.h"

#include <strstream>

@interface KKGameViewController () {
    kk::gl::GLDrawable * _drawable;
}

@property(nonatomic,strong) CADisplayLink * displayLink;

-(void) onDrawDocument;

@end

@implementation KKGameViewController

-(void) dealloc {
    
    [_displayLink removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    
    if(_document != nil) {
        kk::ScriptDeleteGlobalObject(_document->context(), _document);
        _document = nil;
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if(_document != nil) {
        kk::ScriptDeleteGlobalObject(_document->context(), _document);
        _document = nil;
        _drawable = nil;
    }
    
    kk::Application * app = self.app.app;
    
    kk::ScriptContext ctx = self.app.jsContext;
    
    _document = kk::ScriptNewObject<kk::Document>(ctx, 0);
    
    _document->setApp(app);
    
    kk::ScriptNewGlobalObject(ctx, _document);
    
    duk_pop(ctx);
    
    if([_path length] > 0 && app->has([_path UTF8String])) {
        
        std::strstream ss;
        
        ss << "(function(document){";
        ss << app->getString([_path UTF8String]);
        ss << "})" << std::ends;
        
        duk_pop(ctx);
        
        const char * s = ss.str();
        
        duk_eval_string(ctx, s);
        
        if(duk_is_function(ctx, -1)) {
            
            kk::ScriptPushObject(ctx, _document);
            
            if( duk_pcall(ctx, 1) == DUK_EXEC_SUCCESS ) {
                kk::Log("[OK] %s",[_path UTF8String]);
            } else {
                kk::Log("[Fail] %s Error: %s",[_path UTF8String],duk_to_string(ctx, -1));
            }
            
            duk_pop(ctx);
            
        } else {
            duk_pop(ctx);
        }
    }
    
    if(_document && _document->rootElement()) {
        
        kk::Element * p = _document->rootElement()->firstChild();
        
        while(p) {
            
            _drawable = dynamic_cast<kk::gl::GLDrawable *>(p);
            
            if(_drawable) {
                break;
            }
            
            p = p->nextSibling();
        }
        
    }
    
    if(_gameView == nil) {
        _gameView = [[KKGameView alloc] initWithFrame:self.view.bounds];
        [_gameView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        [self.view addSubview:_gameView];
    }
    
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(onDrawDocument)];
    
    [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    
}

-(void) onDrawDocument {
    
    if(_drawable) {
        
        kk::ScriptContext ctx = _document->context();
        kk::gl::GLContext * glContext = kk::ScriptNewObject<kk::gl::GLContext>(ctx, 0);
        
        [_gameView display:_drawable context:glContext];
        
        duk_pop(ctx);
        
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

-(KKGameApplication *) app {
    if(_app == nil) {
        _app = [KKGameApplication main];
    }
    return _app;
}

@end
