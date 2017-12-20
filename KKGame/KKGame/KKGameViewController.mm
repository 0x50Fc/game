//
//  KKGameViewController.m
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import "KKGameViewController.h"
#import "KKGameApplication.h"

#include "GLSLTexture.h"
#include "kk-game.h"

#include <strstream>

@interface KKGameViewController () {
    kk::gl::GLDrawable * _drawable;
    kk::gl::GLContext * _glContext;
    
    kk::game::GMElement * _gameElement;
    kk::game::GMContext * _gameContext;
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
        _drawable = nil;
        _gameElement = nil;
    }

    if(_glContext != nil){
        kk::ScriptDeleteGlobalObject(_glContext->context(), _glContext);
        _glContext = nil;
    }
    
    if(_gameContext != nil){
        kk::ScriptDeleteGlobalObject(_gameContext->context(), _gameContext);
        _gameContext = nil;
    }
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if(_gameView == nil) {
        _gameView = [[KKGameView alloc] initWithFrame:self.view.bounds];
        [_gameView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
        [self.view addSubview:_gameView];
    }
    
    [EAGLContext setCurrentContext:[_gameView GLContext]];

    if(_document != nil) {
        kk::ScriptDeleteGlobalObject(_document->context(), _document);
        _document = nil;
        _drawable = nil;
        _gameElement = nil;
    }
    
    if(_glContext != nil){
        kk::ScriptDeleteGlobalObject(_glContext->context(), _glContext);
        _glContext = nil;
    }
    
    if(_gameContext != nil){
        kk::ScriptDeleteGlobalObject(_gameContext->context(), _gameContext);
        _gameContext = nil;
    }
    
    kk::Application * app = self.app.app;
    
    kk::ScriptContext ctx = self.app.jsContext;
    
    _glContext = kk::ScriptNewObject<kk::gl::GLContext>(ctx, 0);
    
    _glContext->set("GLSLTexture", kk::glsl::GLSLTextureCreate());
    
    kk::ScriptNewGlobalObject(ctx, _glContext);
    
    duk_pop(ctx);
    
    _gameContext = kk::ScriptNewObject<kk::game::GMContext>(ctx, 0);
    
    _gameContext->setSpeed(1000 / 60);
    
    kk::ScriptNewGlobalObject(ctx, _gameContext);
    
    duk_pop(ctx);
    
    _document = kk::ScriptNewObject<kk::ui::UIDocument>(ctx, 0);
    
    _document->setPixelScale(kk::ui::PixelTypeRPX, [[UIScreen mainScreen] bounds].size.width / 750.0f);
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
            
            if(_drawable == NULL) {
                _drawable = dynamic_cast<kk::gl::GLDrawable *>(p);
            }
            
            if(_gameElement == NULL) {
                _gameElement = dynamic_cast<kk::game::GMElement *>(p);
            }
            
            p = p->nextSibling();
        }
        
    }
    
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(onDrawDocument)];
    
    _glContext->setSpeed(1000 / 60);
    
    [_displayLink setFrameInterval:60];
    
    [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    
}

-(void) onDrawDocument {
    
    if(_gameContext){
        
        _gameContext->tick();
        
        if(_gameElement) {
            _gameElement->tick(_gameContext);
        }
        
    }

    if(_drawable && _glContext) {
        [_gameView display:_drawable context:_glContext];
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

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event {
    
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event {
    
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event {
    
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event {
    
}
@end
