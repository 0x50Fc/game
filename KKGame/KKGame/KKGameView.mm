//
//  KKGameView.m
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#import "KKGameView.h"

@interface KKGameView() {
    struct {
        GLuint frame;
        GLuint render;
        GLuint depth;
    } _data;
}

-(void) setup;

@end

@implementation KKGameView

@synthesize GLContext = _GLContext;

-(void) initGLContext {
    
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
    
    eaglLayer.contentsScale = [[UIScreen mainScreen] scale];
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
    
    
    _GLContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!_GLContext || ![EAGLContext setCurrentContext:_GLContext]) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }

    glGenFramebuffers(1, &_data.frame);
    glGenRenderbuffers(1, &_data.render);
    glGenRenderbuffers(1, &_data.depth);
    
    [self setup];
}

-(instancetype) initWithFrame:(CGRect)frame {
    if((self = [super initWithFrame:frame])) {
        
        [self initGLContext];
        
    }
    return self;
}

-(instancetype) initWithCoder:(NSCoder *) aDecoder{
    if((self = [super initWithCoder:aDecoder])) {
        
        [self initGLContext];
        
    }
    return self;
}

-(void) dealloc {
    if(_data.frame) {
        glDeleteFramebuffers(1,&_data.frame);
    }
    if(_data.render) {
        glDeleteFramebuffers(1,&_data.render);
    }
    if(_data.depth) {
        glDeleteFramebuffers(1,&_data.depth);
    }
}

-(void) setFrame:(CGRect)frame {
    CGRect r = self.frame;
    [super setFrame:frame];
    if(!CGSizeEqualToSize(r.size, frame.size)) {
        [self setup];
    }
}

-(void) setBounds:(CGRect)bounds {
    CGRect r = self.bounds;
    [super setBounds:bounds];
    if(!CGSizeEqualToSize(r.size, bounds.size)) {
        [self setup];
    }
}

-(void) setup {
 
    [EAGLContext setCurrentContext:_GLContext];
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.render);
    
    [_GLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*) self.layer];

    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_height);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16
                          , _width, _height);
    
    glBindFramebuffer(GL_FRAMEBUFFER, _data.frame);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _data.render);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _data.depth);
    
    glViewport(0,0,_width,_height);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.render);;
    
    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_BLEND);
    
    glEnable(GL_DEPTH_TEST);
    
}

-(void) display:(kk::gl::GLDrawable *) drawable context:(kk::gl::GLContext *) context {
    
    [EAGLContext setCurrentContext:_GLContext];
    
    CGFloat r = 0.0,g = 0.0,b = 0.0,a = 1.0;
    
    if(self.backgroundColor){
        UIColor * color = self.backgroundColor;
        [color getRed:&r green:&g blue:&b alpha:&a];
    }
    
    glClearColor(r, g, b, a);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    CGFloat scale = self.layer.contentsScale;
    
    context->setScale(scale);
    context->setWidth(_width / scale);
    context->setHeight(_height / scale);
    
    drawable->draw(context);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.render);
    
    [_GLContext presentRenderbuffer:GL_RENDERBUFFER]; // 渲染到设备
    
}

+(Class) layerClass {
    return [CAEAGLLayer class];
}

@end
