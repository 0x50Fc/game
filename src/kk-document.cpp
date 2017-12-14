//
//  kk-document.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-document.h"
#include "kk-element.h"

namespace kk {
    
    Element * Document::rootElement() {
        return _rootElement.get();
    }
    
    void Document::setRootElement(Element * element) {
        _rootElement.set(this,element);
    }
    
    Element * Document::createElement(kk::Class * isa) {
        
        ScriptContext ctx = context();
        ScriptPushObject(ctx, this);
        return dynamic_cast<Element *>(ScriptNewObject(ctx, isa, 1));
    }
    

    Element * Document::createElement(CString name) {
        
        ScriptContext ctx = context();
        
        duk_push_global_object(ctx);
        
        duk_push_string(ctx, name);
        duk_get_prop(ctx, -2);
        
        if(duk_is_c_function(ctx, -1)) {
            ScriptPushObject(ctx, this);
            duk_new(ctx, 1);
            duk_remove(ctx, -2);
            return dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        } else {
            duk_pop_n(ctx, 2);
        }
        
        kk::Log("Not Found Element Class %s",name);
        
        return createElement(&Element::Class);
    }
    
    Element * Document::element(Int64 id) {
        
        Element * e = NULL;
        
        ScriptContext ctx = context();
        
        ScriptPushObject(ctx, this);
        
        duk_push_string(ctx, "_elements");
        duk_get_prop(ctx, -2);
        
        if(duk_is_object(ctx, -1)) {
            
            duk_push_sprintf(ctx, "%lld", id);
            duk_get_prop(ctx, -2);
            
            e = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
            
            duk_pop(ctx);
            
        }
        
        duk_pop_n(ctx, 2);
        
        return e;
    }
    
    void Document::init() {
        
        ScriptContext ctx = context();
        
        int nargs = duk_get_top(ctx);
        
        if(nargs >0 && duk_is_object(ctx, -nargs)) {
            setApp(dynamic_cast<Application *>( ScriptGetObject(ctx, - nargs)));
        }
        
        duk_push_this(ctx);
        
        duk_push_string(ctx, "_elements");
        duk_push_object(ctx);
        duk_def_prop(ctx, -3, DUK_DEFPROP_HAVE_VALUE);
        
        duk_pop(ctx);
        
    }
    
    void Document::setElementId(Element * e,Int64 id) {
       
        ScriptContext ctx = context();
        
        ScriptPushObject(ctx, this);
        
        duk_push_string(ctx, "_elements");
        duk_get_prop(ctx, -2);
        
        duk_push_sprintf(ctx, "%lld", id);
        
        if(e) {
            ScriptPushObject(ctx, e);
            duk_put_prop(ctx, -3);
        } else {
            duk_del_prop(ctx, -2);
        }
        
        duk_pop_n(ctx, 2);
    }
    
    void Document::emit(CString name,Event * event) {
        EventEmitter::emit(name, event);
        ElementActionEvent * e = dynamic_cast<ElementActionEvent *>(event);
        
        if(e && e->actionType() == ElementActionTypeRemove) {
            
            Element * element = dynamic_cast<Element *>( e->element() );
            
            if(element) {
                
                Int64 id = element->id();
                
                if(id) {
                    setElementId(NULL, id);
                }
            }
        } else if(e &&
                (e->actionType() == ElementActionTypeAdd)) {
            
            Element * element = dynamic_cast<Element *>( e->asElement() );
            
            if(element) {
                
                Int64 id = element->id();
                
                if(id) {
                    
                    setElementId(element, id);
                    
                }
            }
        } else if(e && e->actionType() == ElementActionTypeProperty && e->property()->name() == &kk::named::id) {
            
            Element * element = dynamic_cast<Element *>( e->asElement() );
            
            if(element) {
                
                Int64 id = element->id();
                
                if(id) {
                    
                    setElementId(element, id);
                    
                }
            }
            
        }
    }
    
    Application * Document::app() {
        return dynamic_cast<Application *>( _app.get() );
    }
    
    void Document::setApp(Application * app) {
        _app.set(app);
    }
    
    ObjectProperty Document::RootElement(&kk::named::rootElement, (ObjectProperty::Getter)&Document::rootElement,(ObjectProperty::Setter)&Document::setRootElement);
    ObjectProperty Document::App(&kk::named::app,(ObjectProperty::Getter)&Document::app,(ObjectProperty::Setter)&Document::setApp);
    
    Property *Document::Propertys[] = {
        &Document::RootElement,
        &Document::App,
        NULL
    };
    
    
    IMP_CLASS(Document, EventEmitter, Document::Propertys, NULL);
    

}

