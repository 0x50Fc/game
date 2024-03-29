//
//  kk-app.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/11.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-app.h"

#include <strstream>

namespace kk {
    
    kk::Boolean Application::has(CString path) {
        std::strstream spath;
        
        spath << _basePath << path << std::ends;
        
        struct stat st;
        
        if(-1 == stat(spath.str(), &st)) {
            return false;
        }
        
        return true;
    }
    
    CString Application::getString(CString path) {
        
        std::strstream spath;
        
        spath << _basePath << path << std::ends;
        
        struct stat st;
        
        if(-1 == stat(spath.str(), &st)) {
            kk::Log("Not Found File %s",path);
            return NULL;
        }
        
        ScriptContext ctx = context();
        
        kk::Uint8 * v = (kk::Uint8 *) duk_push_fixed_buffer(ctx, (duk_size_t) st.st_size + 1);
        
        v[st.st_size] = 0;
        
        FILE * fd = fopen(spath.str(), "r");
        
        if(fd != NULL) {
            
            if(fread(v, 1, (duk_size_t) st.st_size, fd) != st.st_size) {
                fclose(fd);
                duk_pop(ctx);
                kk::Log("File Read Fail %s",spath.str());
                return NULL;
            }
            
            fclose(fd);
            
        }
        
        return (CString) v;
    }
    
    kk::Uint8 * Application::getBytes(CString path,kk::Uint * size) {
        
        std::strstream spath;
        
        spath << _basePath << path << std::ends;
        
        struct stat st;
        
        if(-1 == stat(spath.str(), &st)) {
            kk::Log("Not Found File %s",path);
            return NULL;
        }
        
        ScriptContext ctx = context();
        
        kk::Uint8 * v = (kk::Uint8 *) duk_push_fixed_buffer(ctx, (duk_size_t) st.st_size);
        
        FILE * fd = fopen(spath.str(), "rb");
        
        if(fd != NULL) {
            
            if(fread(v, 1, (duk_size_t) st.st_size, fd) != st.st_size) {
                fclose(fd);
                duk_pop(ctx);
                kk::Log("File Read Fail %s",spath.str());
                return NULL;
            }
            
            fclose(fd);
            
        }
        
        if(size) {
            * size = (kk::Uint) st.st_size;
        }
        
        return v;
        
    }
    
    kk::CString Application::basePath() {
        return _basePath.c_str();
    }
    
    void Application::setBasePath(kk::CString basePath) {
        _basePath = basePath;
    }
    
    static ScriptResult ApplicationGetStringFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Application * v = dynamic_cast<Application *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_string(ctx, - nargs)) {
                v->getString(duk_to_string(ctx, - nargs));
                return 1;
            }
            
        }
        
        return 0;
    }
    
    static ScriptResult ApplicationPrototypeFunc(ScriptContext ctx) {
        
        duk_push_string(ctx, "getString");
        duk_push_c_function(ctx, ApplicationGetStringFunc, 1);
        duk_put_prop(ctx, -3);
        
        return 0;
    }
    
    IMP_CLASS(Application, Object, NULL, ApplicationPrototypeFunc)
    
}
