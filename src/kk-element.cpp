//
//  kk-element.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-element.h"
#include "kk-document.h"

namespace kk {
    
    
    Element * Element::parent() {
        return dynamic_cast<Element *>(_parent.get());
    }
    
    Element * Element::firstChild() {
        return dynamic_cast<Element *>(_firstChild.get());
    }
    
    Element * Element::lastChild() {
        return dynamic_cast<Element *>(_lastChild.get());
    }
    
    Element * Element::nextSibling() {
        return dynamic_cast<Element *>(_nextSibling.get());
    }
    
    Element * Element::prevSibling() {
        return dynamic_cast<Element *>(_prevSibling.get());
    }
    
    void Element::remove() {
        
        Element * element = NULL;
        
        Element * p = parent();
        Element * prev = prevSibling();
        Element * next = nextSibling();
        
        if(prev) {
            prev->_nextSibling.set( next);
            if(next) {
                next->_prevSibling.set(prev);
            } else {
                p->_lastChild.set( prev);
            }
            element = this;
        } else if(p) {
            p->_firstChild.set( next);
            if(next) {
                next->_prevSibling.set(Object::Null);
            } else {
                p->_lastChild.set(Object::Null);
            }
            element = this;
        }
        
        if(element) {
            
            _parent.set( Object::Null);
            _nextSibling.set( Object::Null);
            _prevSibling.set( Object::Null);
            
            ScriptContext ctx = context();
            
            ElementActionEvent * e = ScriptNewObject<ElementActionEvent>(ctx, 0);
            
            e->element.set(element);
            e->actionType.set((Int) ElementActionTypeRemove);
            
            emit("element", e);
            
            duk_pop(ctx);
            
        }
    }
    
    void Element::append(Element * e) {
        
        e->remove();
        
        Element * last = lastChild();
        
        if(last) {
            last->_nextSibling.set( e);
            e->_prevSibling.set( last);
            _lastChild.set( e);
        } else {
            _firstChild.set( e);
            _lastChild.set( e);
        }
        
        ScriptContext ctx = context();
        
        ElementActionEvent * event = ScriptNewObject<ElementActionEvent>(ctx, 0);
        
        event->element.set( this);
        event->asElement.set(e);
        event->actionType.set( ElementActionTypeAdd);
        
        emit("element", event);
        
        duk_pop(ctx);
        
    }
    
    void Element::appendTo(Element * e) {
        e->append(this);
    }
    
    void Element::before(Element * e) {
        
        e->remove();
        
        Element * prev = prevSibling();
        Element * p = parent();
        
        if(prev) {
            prev->_nextSibling.set( e);
            e->_prevSibling.set( prev);
            e->_nextSibling.set(this);
        } else if(p) {
            e->_nextSibling.set( this);
            this->_prevSibling.set( e);
            p->_firstChild.set( e);
        }
        
        if(p) {
            
            ScriptContext ctx = context();
            
            ElementActionEvent * event = ScriptNewObject<ElementActionEvent>(ctx, 0);
            
            event->element.set(p);
            event->asElement.set(e);
            event->actionType.set(ElementActionTypeAdd);
            
            p->emit("element", event);
            
            duk_pop(ctx);
        }
    }
    
    void Element::beforeTo(Element *e) {
        e->before(this);
    }
    
    void Element::after(Element * e) {
        
        e->remove();
        
        Element * next = nextSibling();
        Element * p = parent();
        
        if(next) {
            e->_nextSibling.set( next);
            next->_prevSibling.set( e);
            _nextSibling.set( e);
            e->_prevSibling.set( this);
        } else if(p) {
            _nextSibling.set( e);
            e->_prevSibling.set( this);
            p->_lastChild.set( e);
        }
        
        if(p) {
            
            ScriptContext ctx = context();
            
            ElementActionEvent * event = ScriptNewObject<ElementActionEvent>(ctx, 0);
            
            event->element.set(p);
            event->asElement.set(e);
            event->actionType.set(ElementActionTypeAdd);
            
            p->emit("element", event);
            
            duk_pop(ctx);
        }
        
    }
    
    void Element::afterTo(Element * e) {
        e->after(this);
    }
    
    Int64 Element::id() {
        return _id.get();
    }
    
    void Element::setId(Int64 v) {
        if(_id.get() == 0) {
            _id.set(v);
        }
    }
    
    Element::Element(ScriptContext context,ScriptPtr ptr)
        :kk::EventEmitter(context,ptr)
            ,_parent(this,&P::parent)
            ,_firstChild(this,&P::firstChild)
            ,_lastChild(this,&P::lastChild)
            ,_nextSibling(this,&P::nextSibling)
            ,_prevSibling(this,&P::prevSibling)
            ,_id(this,&P::id)
            ,_document(this,&P::document){
        
    }
   
    static ScriptResult ElementAppendFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_object(ctx, -nargs)) {
                Element * e = dynamic_cast<Element *>(ScriptGetObject(ctx, -nargs));
                if(e) {
                    v->append(e);
                }
            }
        }
        
        
        return 0;
    }
    
    static ScriptResult ElementAppendToFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_object(ctx, -nargs)) {
                Element * e = dynamic_cast<Element *>(ScriptGetObject(ctx, -nargs));
                if(e) {
                    v->appendTo(e);
                }
            }
        }
        
        
        return 0;
    }
    
    static ScriptResult ElementBeforeFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_object(ctx, -nargs)) {
                Element * e = dynamic_cast<Element *>(ScriptGetObject(ctx, -nargs));
                if(e) {
                    v->before(e);
                }
            }
        }
        
        
        return 0;
    }
    
    static ScriptResult ElementBeforeToFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_object(ctx, -nargs)) {
                Element * e = dynamic_cast<Element *>(ScriptGetObject(ctx, -nargs));
                if(e) {
                    v->beforeTo(e);
                }
            }
        }
        
        
        return 0;
    }
    
    static ScriptResult ElementAfterFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_object(ctx, -nargs)) {
                Element * e = dynamic_cast<Element *>(ScriptGetObject(ctx, -nargs));
                if(e) {
                    v->after(e);
                }
            }
        }
        
        
        return 0;
    }
    
    static ScriptResult ElementAfterToFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs > 0 && duk_is_object(ctx, -nargs)) {
                Element * e = dynamic_cast<Element *>(ScriptGetObject(ctx, -nargs));
                if(e) {
                    v->afterTo(e);
                }
            }
        }
        
        
        return 0;
    }
    
    static ScriptResult ElementRemoveFunc(ScriptContext ctx) {
        
        Element * v = NULL;
        
        duk_push_this(ctx);
        
        v = dynamic_cast<Element *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            v->remove();
        }
        
        return 0;
    }
    
    void Element::init() {
        EventEmitter::init();
        
        ScriptContext ctx = context();
        
        int nargs = duk_get_top(ctx);
        
        if(nargs >0 && duk_is_object(ctx, -nargs)) {
            _document.set( ScriptGetObject(ctx, -nargs));
        }
        
        duk_push_this(ctx);
        
        duk_push_string(ctx, "append");
        duk_push_c_function(ctx, ElementAppendFunc, 1);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "appendTo");
        duk_push_c_function(ctx, ElementAppendToFunc, 1);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "before");
        duk_push_c_function(ctx, ElementBeforeFunc, 1);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "beforeTo");
        duk_push_c_function(ctx, ElementBeforeToFunc, 1);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "after");
        duk_push_c_function(ctx, ElementAfterFunc, 1);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "afterTo");
        duk_push_c_function(ctx, ElementAfterToFunc, 1);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "remove");
        duk_push_c_function(ctx, ElementRemoveFunc, 0);
        duk_put_prop(ctx, -3);
        
        duk_pop(ctx);
    }
    
    Document * Element::document() {
        return dynamic_cast<Document *>(_document.get());
    }
    
    void Element::onChangeProperty(VProperty * property) {
        Object::onChangeProperty(property);
        
        ScriptContext ctx = context();
        
        ElementActionEvent * e = ScriptNewObject<ElementActionEvent>(ctx, 0);
        
        e->element.set(this);
        e->actionType.set(ElementActionTypeProperty);
        e->property = property;
        
        emit("element", e);
        
        duk_pop(ctx);
    }
    
    Event * Element::defaultEvent(CString name) {
        ScriptContext ctx = context();
        ElementEvent * e = ScriptNewObject<ElementEvent>(ctx, 0);
        e->element.set(this);
        return e;
    }
    
    void Element::emit(CString name,Event * event) {
        EventEmitter::emit(name, event);
        
        ElementEvent * e = dynamic_cast<ElementEvent *>(event);
        
        if(e != NULL && !e->cancelBubble.get()) {
            Element * p = parent();
            if(p) {
                p->emit(name, event);
            } else {
                Document * doc = document();
                if(doc) {
                    doc->emit(name, event);
                }
            }
        }
    }
    
    ElementEvent::ElementEvent(ScriptContext context,ScriptPtr ptr)
        :kk::Event(context,ptr)
        ,element(this,&P::element)
        ,cancelBubble(this,&P::cancelBubble){
        
    }
    
    ElementActionEvent::ElementActionEvent(ScriptContext context,ScriptPtr ptr)
        :kk::ElementEvent(context,ptr)
        ,asElement(this,&P::asElement)
        ,actionType(this,&P::actionType)
        ,name(this,&P::name)
        ,property(NULL){
        
    }
    
}
