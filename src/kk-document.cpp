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
        return dynamic_cast<Element *>(_rootElement.get());
    }
    
    void Document::setRootElement(Element * element) {
        _rootElement.set(element);
    }
    
    Document::Document(ScriptContext context,ScriptPtr ptr)
        :kk::EventEmitter(context,ptr)
            ,_rootElement(this,&P::rootElement)
            ,_app(this,&P::app){
        
    }
    
    Element * Document::createElement(kk::Class isa) {
        
        ScriptContext ctx = context();
        ScriptPushObject(ctx, this);
        return dynamic_cast<Element *>(ScriptNewObject(ctx, isa, 1));
    }
    

    Element * Document::createElement(CString name) {
        
        kk::Class isa = NULL;
        ScriptContext ctx = context();
        
        duk_push_global_object(ctx);
        
        duk_push_string(ctx, name);
        duk_get_prop(ctx, -2);
        
        if(duk_is_c_function(ctx, -1)) {
            isa = duk_get_c_function(ctx, -1);
        }
        
        duk_pop_n(ctx, 2);
        
        if(isa) {
            return createElement(isa);
        }
        
        kk::Log("Not Found Element Class %s",name);
        
        return createElement(Element::Class);
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
        duk_put_prop(ctx, -3);
        
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
        
        if(e && e->actionType.get() == ElementActionTypeRemove) {
            
            Element * element = dynamic_cast<Element *>( e->element.get() );
            
            if(element) {
                
                Int64 id = element->id();
                
                if(id) {
                    setElementId(NULL, id);
                }
            }
        } else if(e &&
                (e->actionType.get() == ElementActionTypeAdd)) {
            
            Element * element = dynamic_cast<Element *>( e->asElement.get() );
            
            if(element) {
                
                Int64 id = element->id();
                
                if(id) {
                    
                    setElementId(element, id);
                    
                }
            }
        } else if(e && e->actionType.get() == ElementActionTypeProperty && e->property->property() == &kk::P::id) {
            
            Element * element = dynamic_cast<Element *>( e->asElement.get() );
            
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

}

