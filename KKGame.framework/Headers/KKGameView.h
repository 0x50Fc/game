//
//  KKGameView.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <KKGame/kk-gl.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface KKGameView : UIView

@property(nonatomic,strong,readonly) EAGLContext * GLContext;
@property(nonatomic,assign,readonly) GLsizei width;
@property(nonatomic,assign,readonly) GLsizei height;

-(instancetype) initWithFrame:(CGRect)frame;

-(void) display:(kk::gl::GLDrawable *) drawable context:(kk::gl::GLContext *) context;

@end
