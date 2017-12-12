//
//  kk.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/6.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk.h"

#include <vector>
#include <strstream>

namespace kk {
    
    Boolean CStringHasPrefix(CString string,CString prefix) {
        
        if(string == prefix) {
            return true;
        }
        
        if(prefix == NULL) {
            return true;
        }
        
        if(string == NULL) {
            return false;
        }
        
        size_t n1 = strlen(string);
        size_t n2 = strlen(prefix);
        
        return n1 >= n2 && strncmp(string, prefix, n2) == 0;
    }
    
    Boolean CStringHasSuffix(CString string,CString suffix) {
        
        if(string == suffix) {
            return true;
        }
        
        if(suffix == NULL) {
            return true;
        }
        
        if(string == NULL) {
            return false;
        }
        
        size_t n1 = strlen(string);
        size_t n2 = strlen(suffix);
        
        return n1 >= n2 && strncmp(string + n1 - n2, suffix, n2) == 0;
    }
    
    size_t CStringLength(CString string){
        if(string == NULL) {
            return 0;
        }
        return strlen(string);
    }
    
    Boolean CStringEqual(CString string,CString value) {
        
        if(string == value) {
            return true;
        }
        
        if(value == NULL || string == NULL ) {
            return false;
        }
        
        return strcmp(string, value) == 0;
    }
    
    void CStringSplit(CString string,CString delim, std::vector<String>& items) {
        
        if(string == NULL || delim == NULL) {
            return ;
        }
        
        char * p = (char *) string;
        char * b = p;
        size_t n= strlen(delim);
        
        while(*b != 0) {
            if(strncmp(b, delim, n) == 0) {
                items.push_back(String(p,b-p));
                b += n;
                p = b;
            } else {
                b ++;
            }
        }
        
        if(b != p) {
            items.push_back(String(p,b-p));
        }
        
    }
    
    String CStringJoin(std::vector<String>& items,CString delim){
        std::strstream ss;
        std::vector<String>::iterator i = items.begin();
        
        while(i !=items.end()){
            if(i !=items.begin()){
                ss<< delim;
            }
            ss << * i;
            i ++;
        }
        
        ss << std::ends;
        
        return ss.str();
    }
    
    void Log(CString format,...) {
        va_list va;
        va_start(va, format);
        LogV(format,va);
        va_end(va);
    }
    
    void LogV(CString format,va_list va) {
        
        printf("[KK] ");
        
        vprintf(format, va);
        
        printf("\n");
    }
}
