//
//  kk-script.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/6.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_script_h
#define kk_script_h

#if defined(__APPLE__) && !defined(KK_SIMULATOR)

#include <KKDuktape/KKDuktape.h>

#else

#include "duktape.h"

#endif

namespace kk {
    
    typedef duk_context * ScriptContext;
    
    typedef duk_ret_t ScriptResult;
    
    typedef duk_c_function ScriptFunction;
    
    typedef void * ScriptPtr;
    
}

#endif /* kk_script_h */
