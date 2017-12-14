//
//  KKGLTexture.m
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import <CoreImage/CoreImage.h>

#include "kk-config.h"
#include "kk-gl.h"


namespace kk {
    
    namespace gl {
        
        GLTexture * GLCreateTexture(kk::Application * app,kk::CString path) {
            
            GLTexture * v = NULL;
            kk::ScriptContext ctx = app->context();
            
            kk::Uint size = 0;
            kk::Uint8 * data = app->getBytes(path, & size);
            
            if(data && size) {
                if(kk::CStringHasSuffix(path, ".pvr")) {
                    v = new GLTexture(data, size, 0, 0, GLTextureTypePVR);
                } else {
                    
                    CFDataRef vdata = CFDataCreateWithBytesNoCopy(NULL, data, size, NULL);
                    
                    CGImageSourceRef imageSource =  CGImageSourceCreateWithData(vdata, NULL);
                    
                    CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                    
                    size_t c = CGImageSourceGetCount(imageSource);
                    
                    if(c > 0) {
                        
                        CGImageRef imageRef = CGImageSourceCreateImageAtIndex(imageSource, 0, nil);
                        
                        size_t width = CGImageGetWidth(imageRef);
                        size_t height = CGImageGetHeight(imageRef);
                        
                        CGContextRef ctx = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                        
                        CGContextDrawImage(ctx, CGRectMake(0, 0, width, height), imageRef);
                        
                        v = new GLTexture(CGBitmapContextGetData(ctx), kk::Uint(width * height * 4), kk::Int(width),kk::Int(height),GLTextureTypeRGBA);
                        
                        CGContextRelease(ctx);
                        
                        CFRelease(imageRef);
                        
                    }
                    
                    CGColorSpaceRelease(rgbSpace);
                    
                    CFRelease(imageSource);
                    
                    
                }
            }
            
            duk_pop(ctx);
            
            return v;
        }
        
    }
    
}


