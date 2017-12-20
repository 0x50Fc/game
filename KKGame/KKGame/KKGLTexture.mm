//
//  KKGLTexture.m
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreImage/CoreImage.h>

#include "kk-config.h"
#include "kk-gl.h"


namespace kk {
    
    namespace gl {
        
        static UIFont * GLFont(kk::CString fontFamily,kk::Float fontSize) {
            if(CStringEqual(fontFamily, "bold")) {
                return [UIFont boldSystemFontOfSize:fontSize];
            }
            if(CStringEqual(fontFamily, "italic")) {
                return [UIFont italicSystemFontOfSize:fontSize];
            }
            if(fontFamily && * fontFamily != 0) {
                UIFont * v = [UIFont fontWithName:[NSString stringWithCString:fontFamily encoding:NSUTF8StringEncoding] size:fontSize];
                if(v) {
                    return v;
                }
            }
            return [UIFont systemFontOfSize:fontSize];
        }
        
        vec2 GLStringSize(kk::CString string,kk::CString fontFamily,kk::Float fontSize,kk::Float maxWidth) {
            vec2 v(0,0);
            
            if(string) {
                UIFont * font = GLFont(fontFamily,fontSize);
                NSAttributedString * s = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:string encoding:NSUTF8StringEncoding] attributes:@{NSFontAttributeName: font}];
                CGRect r = [s boundingRectWithSize:CGSizeMake(maxWidth, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                v.x = r.size.width;
                v.y = r.size.height;
            }
            
            return v;
        }
        
        GLTexture * GLCreateStringTexture(kk::CString string,kk::CString fontFamily,kk::Float fontSize,vec4 textColor,kk::Float maxWidth) {
            
            GLTexture * v = NULL;
            
            if(string) {
                
                UIFont * font = GLFont(fontFamily,fontSize);
 
                UIColor * color = [UIColor colorWithRed:textColor.r green:textColor.g blue:textColor.b alpha:textColor.a];
                
                NSAttributedString * s = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:string encoding:NSUTF8StringEncoding] attributes:@{NSFontAttributeName: font,NSForegroundColorAttributeName:color,NSBackgroundColorAttributeName:[UIColor clearColor]}];
                
                CGRect bounds = [s boundingRectWithSize:CGSizeMake(maxWidth, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                
                size_t width = (size_t) ceil(bounds.size.width);
                size_t height = (size_t) ceil(bounds.size.height);
                
                CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                
                CGContextRef ctx = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
              

                CGContextTranslateCTM(ctx, 0, height);
                CGContextScaleCTM(ctx, 1, -1);
        
                UIGraphicsPushContext(ctx);
                
                [s drawInRect:CGRectMake(0, 0, width,  height)];
    
                UIGraphicsPopContext();
                
                v = new GLTexture(CGBitmapContextGetData(ctx), kk::Uint(width * height * 4), kk::Int(width),kk::Int(height),GLTextureTypeRGBA);
                
                CGContextRelease(ctx);
                
                CGColorSpaceRelease(rgbSpace);
                
            }
            
            return v;
        }
        
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


