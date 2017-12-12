//
//  kk.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/6.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_h
#define kk_h

#include <string>

namespace kk {
    
    typedef int Int;
    typedef unsigned int Uint;
    typedef int Int32;
    typedef unsigned int Uint32;
    typedef long long Int64;
    typedef unsigned long long Uint64;
    typedef bool Boolean;
    typedef double Double;
    typedef float Float;
    typedef std::string String;
    typedef const char * CString;
    typedef long Intptr;
    typedef char Int8;
    typedef unsigned char Uint8;
    
    Boolean CStringHasPrefix(CString string,CString prefix);
    Boolean CStringHasSuffix(CString string,CString suffix);
    Boolean CStringEqual(CString string,CString value);
    size_t CStringLength(CString string);
    void CStringSplit(CString string,CString delim, std::vector<String>& items);
    String CStringJoin(std::vector<String>& items,CString delim);
    
    template<typename T>
    T Max(T a,T b) {
        return a > b ? a : b;
    }
    
    template<typename T>
    T Min(T a,T b) {
        return a < b ? a : b;
    }

    void Log(CString format,...);
    void LogV(CString format,va_list va);
    
}

#endif /* kk_h */
