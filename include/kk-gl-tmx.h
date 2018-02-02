//
//  kk-gl-tmx.h
//  KKGame
//
//  Created by hailong11 on 2017/12/18.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_gl_tmx_h
#define kk_gl_tmx_h


#if defined(__APPLE__) && !defined(KK_SIMULATOR)
#include <KKGame/kk-gl.h>
#endif

#include <string>

#ifdef __cplusplus
extern "C" {
#endif
    
struct _tmx_map;

#ifdef __cplusplus
}
#endif

namespace kk {
    
    namespace gl {
        
        class GLTMXElement : public GLElement {
            DEF_CLASS(GLTMXElement)
        public:
            
            virtual ~GLTMXElement();
            
            virtual CString path();
            virtual void setPath(CString path);
            
            virtual void init();
            
            static kk::StringProperty Property_path;
            static kk::Property * Propertys[];
            
            
        protected:
            virtual void onDraw(GLContext * ctx);
            virtual void loadMap();
            struct _tmx_map * _map;
            std::string _path;
        };
        
    }
    
}


#endif /* kk_gl_tmx_h */
