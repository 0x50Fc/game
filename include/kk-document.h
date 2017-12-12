//
//  kk-document.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_document_h
#define kk_document_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-element.h>
#include <KKGame/kk-app.h>
#endif

namespace kk {
    
    class Document : public EventEmitter {
    public:
        
        virtual Element * rootElement();
        
        virtual void setRootElement(Element * element);
  
        DEF_CLASS(Document)
        
        virtual Element * createElement(kk::Class isa);
        
        virtual Element * createElement(CString name);
        
        virtual Element * element(Int64 id);
        
        virtual void emit(CString name,Event * event);
        
        virtual void init();
        
        virtual Application * app();
        
        virtual void setApp(Application * app);
        
    protected:
        Document(ScriptContext context,ScriptPtr ptr);
        StrongProperty _rootElement;
        WeakProperty _app;
        virtual void setElementId(Element * e,Int64 id);
    };
    
    
}

#endif /* kk_document_h */
