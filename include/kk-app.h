//
//  kk-app.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_app_h
#define kk_app_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-object.h>
#endif

namespace kk {
    
    class Application : public kk::Object {
    DEF_CLASS(Application)
    public:
        virtual kk::Boolean has(CString path);
        virtual CString getString(CString path); /** duk_pop(ctx) **/
        virtual kk::Uint8 * getBytes(CString path,kk::Uint * size); /** duk_pop(ctx) **/
        virtual kk::CString basePath();
        virtual void setBasePath(kk::CString basePath);
    protected:
        kk::String _basePath;
    };
    
    
}

#endif /* kk_app_h */
