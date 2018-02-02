//
//  kk-document.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_document_h
#define kk_document_h

#if defined(__APPLE__) && !defined(KK_SIMULATOR)
#include <KKGame/kk.h>
#include <KKGame/kk-element.h>
#include <KKGame/kk-app.h>
#else
#include "kk.h"
#include "kk-element.h"
#include "kk-app.h"
#endif

namespace kk {
    
    class Document : public EventEmitter {
    DEF_CLASS(Document)
    public:
        
        virtual Element * rootElement();
        
        virtual void setRootElement(Element * element);

        virtual Element * createElement(kk::Class * isa);
        
        virtual Element * createElement(CString name);
        
        virtual Element * element(Int64 id);
        
        virtual void emit(CString name,Event * event);
        
        virtual void init();
        
        virtual Application * app();
        
        virtual void setApp(Application * app);
        
        static ObjectProperty RootElement;
        static ObjectProperty App;
        static Property *Propertys[];
    protected:
        Strong<Element*> _rootElement;
        Weak<Application*> _app;
        virtual void setElementId(Element * e,Int64 id);
    };
    
    
}

#endif /* kk_document_h */
