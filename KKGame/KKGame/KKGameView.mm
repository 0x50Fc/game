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

-(instancetype) initWithFrame:(CGRect)frame {
    if((self = [super initWithFrame:frame])) {
        
        _GLContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        if(_GLContext == nil) {
            _GLContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        }
        
        glGenFramebuffers(1, &_data.frame);
        glGenRenderbuffers(1, &_data.render);
        glGenRenderbuffers(1, &_data.depth);

        [self setup];
        
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
 
    GLsizei width = self.bounds.size.width * self.layer.contentsScale;
    GLsizei height = self.bounds.size.height * self.layer.contentsScale;;
    
    [EAGLContext setCurrentContext:_GLContext];
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.render);
    
    [_GLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*) self];
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16
                          , width, height);
    
    glBindFramebuffer(GL_FRAMEBUFFER, _data.frame);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _data.render);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _data.render);
    
    glViewport(0,0,width,height);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.render);;
    
}

-(void) display:(kk::gl::GLDrawable *) drawable context:(kk::gl::GLContext *) context {
    
    [EAGLContext setCurrentContext:_GLContext];
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawable->draw(context);
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.render);
    
    [_GLContext presentRenderbuffer:GL_RENDERBUFFER]; // 渲染到设备
    
}

+(Class) layerClass {
    return [CAEAGLLayer class];
}

@end
