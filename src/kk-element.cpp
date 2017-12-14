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
    

    Element::~Element() {
        
    }
    
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
        
        ScriptContext ctx = context();
        ElementActionEvent * e = NULL;
        
        Element * p = parent();
        Element * prev = prevSibling();
        Element * next = nextSibling();
        
        if(prev) {
            e = ScriptNewObject<ElementActionEvent>(ctx, 0);
            e->setElement(this);
            prev->setNextSibling(next);
            if(next) {
                next->setPrevSibling(prev);
            } else {
                p->setLastChild( prev);
            }
        } else if(p) {
            e = ScriptNewObject<ElementActionEvent>(ctx, 0);
            e->setElement(this);
            p->setFirstChild( next);
            if(next) {
                next->setPrevSibling(NULL);
            } else {
                p->setLastChild(NULL);
            }
        }
        
        if(e) {
            
            e->setActionType((Int) ElementActionTypeRemove);
            
            emit("element", e);
            
            duk_pop(ctx);
            
        }
    }
    
    void Element::append(Element * e) {
        
        e->remove();
        
        Element * last = lastChild();
        
        if(last) {
            last->setNextSibling(e);
            e->setPrevSibling( last);
            setLastChild(e);
            e->setParent(this);
        } else {
            setFirstChild(e);
            setLastChild(e);
            e->setParent(this);
        }
        
        ScriptContext ctx = context();
        
        ElementActionEvent * event = ScriptNewObject<ElementActionEvent>(ctx, 0);
        
        event->setElement( this);
        event->setAsElement(e);
        event->setActionType( ElementActionTypeAdd);
        
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
            prev->_nextSibling.set(this, e);
            e->_prevSibling.set( prev);
            e->_nextSibling.set(this,this);
            e->setParent(p);
        } else if(p) {
            e->setNextSibling(this);
            this->setPrevSibling( e);
            p->setFirstChild( e);
            e->setParent(p);
        }
        
        if(p) {
            
            ScriptContext ctx = context();
            
            ElementActionEvent * event = ScriptNewObject<ElementActionEvent>(ctx, 0);
            
            event->setElement(p);
            event->setAsElement(e);
            event->setActionType(ElementActionTypeAdd);
            
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
            e->setNextSibling( next);
            next->_prevSibling.set( e);
            setNextSibling( e);
            e->setPrevSibling( this);
            e->setParent(p);
        } else if(p) {
            setNextSibling( e);
            e->setPrevSibling( this);
            p->setLastChild( e);
            e->setParent(p);
        }
        
        if(p) {
            
            ScriptContext ctx = context();
            
            ElementActionEvent * event = ScriptNewObject<ElementActionEvent>(ctx, 0);
            
            event->setElement(p);
            event->setAsElement(e);
            event->setActionType(ElementActionTypeAdd);
            
            p->emit("element", event);
            
            duk_pop(ctx);
        }
        
    }
    
    void Element::afterTo(Element * e) {
        e->after(this);
    }
    
    Int64 Element::id() {
        return _id;
    }
    
    void Element::setId(Int64 v) {
        if(_id == 0) {
            _id = v;
        }
    }
    
    void Element::setParent(Element * v){
        _parent.set(v);
    }
    
    void Element::setFirstChild(Element * v) {
        _firstChild.set(this, v);
    }
    
    void Element::setLastChild(Element * v) {
        _lastChild.set(this,v);
    }
    
    void Element::setNextSibling(Element * v) {
        _nextSibling.set(this, v);
    }
    
    void Element::setPrevSibling(Element * v) {
        _prevSibling.set(v);
    }
    
    void Element::setDocument(Element * v) {
        _document.set(v);
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
            _document.set(ScriptGetObject(ctx, -nargs));
        }
    }
    
    Document * Element::document() {
        return dynamic_cast<Document *>(_document.get());
    }
    
    void Element::change(Property * property) {
        EventEmitter::change(property);
        
        ScriptContext ctx = context();
        
        ElementActionEvent * e = ScriptNewObject<ElementActionEvent>(ctx, 0);
        
        e->setElement(this);
        e->setActionType(ElementActionTypeProperty);
        e->setProperty( property);
        
        emit("element", e);
        
        duk_pop(ctx);
    }
    
    Event * Element::defaultEvent(CString name) {
        ScriptContext ctx = context();
        ElementEvent * e = ScriptNewObject<ElementEvent>(ctx, 0);
        e->setElement(this);
        return e;
    }
    
    void Element::emit(CString name,Event * event) {
        EventEmitter::emit(name, event);
        
        ElementEvent * e = dynamic_cast<ElementEvent *>(event);
        
        if(e != NULL && !e->isCancelBubble()) {
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
   
    Int64Property Element::Property_id(&kk::named::id,(Int64Property::Getter) &Element::id, NULL);
    ObjectProperty Element::Property_parent(&kk::named::parent,(ObjectProperty::Getter)&Element::parent,NULL);
    ObjectProperty Element::Property_firstChild(&kk::named::firstChild,(ObjectProperty::Getter)&Element::firstChild,NULL);
    ObjectProperty Element::Property_lastChild(&kk::named::lastChild,(ObjectProperty::Getter)&Element::lastChild,NULL);
    ObjectProperty Element::Property_nextSibling(&kk::named::nextSibling,(ObjectProperty::Getter)&Element::nextSibling,NULL);
    ObjectProperty Element::Property_prevSibling(&kk::named::prevSibling,(ObjectProperty::Getter)&Element::prevSibling,NULL);
    ObjectProperty Element::Property_document(&kk::named::document,(ObjectProperty::Getter)&Element::document,NULL);
    
    Property *Element::Propertys[] = {
        &Element::Property_id,
        &Element::Property_parent,
        &Element::Property_firstChild,
        &Element::Property_lastChild,
        &Element::Property_nextSibling,
        &Element::Property_prevSibling,
        &Element::Property_document,
        NULL
    };
    
    static ScriptResult ElementPrototypeFunc(ScriptContext ctx) {
        
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
        
        return 0;
    }
    
    IMP_CLASS(Element, EventEmitter, Element::Propertys, ElementPrototypeFunc);
    
    ObjectProperty ElementEvent::Property_element(&kk::named::element,(ObjectProperty::Getter)&ElementEvent::element,(ObjectProperty::Setter)&ElementEvent::setElement);
    BooleanProperty ElementEvent::Property_cancelBubble(&kk::named::cancelBubble,(BooleanProperty::Getter)&ElementEvent::isCancelBubble,(BooleanProperty::Setter)&ElementEvent::setCancelBubble);
    
    Property *ElementEvent::Propertys[] ={
        &ElementEvent::Property_element,
        &ElementEvent::Property_cancelBubble,
        NULL
    };
    
    Element * ElementEvent::element(){
        return _element.get();
    }
    
    void ElementEvent::setElement(Element * element) {
        _element.set(this, element);
    }
    
    Boolean ElementEvent::isCancelBubble() {
        return _cancelBubble;
    }
    
    void ElementEvent::setCancelBubble(Boolean value) {
        _cancelBubble = value;
    }
    
    IMP_CLASS(ElementEvent, Event, ElementEvent::Propertys, NULL)
    
    Element * ElementActionEvent::asElement() {
        return _asElement.get();
    }
    
    void ElementActionEvent::setAsElement(Element * element) {
        _asElement.set(this, element);
    }
    
    Int ElementActionEvent::actionType() {
        return _actionType;
    }
    
    void ElementActionEvent::setActionType(Int value) {
        _actionType = value;
    }
    
    Property * ElementActionEvent::property() {
        return _property;
    }
    
    void ElementActionEvent::setProperty(Property * value) {
        _property = value;
    }
    
    CString ElementActionEvent::name() {
        return _property ? _property->name()->name() : NULL;
    }
    
    ObjectProperty ElementActionEvent::Property_asElement(&kk::named::asElement,(ObjectProperty::Getter)&ElementActionEvent::asElement,(ObjectProperty::Setter)&ElementActionEvent::setAsElement);
    IntProperty ElementActionEvent::Property_actionType(&kk::named::actionType,(IntProperty::Getter)&ElementActionEvent::actionType,(IntProperty::Setter)&ElementActionEvent::setActionType);
    StringProperty ElementActionEvent::Property_name(&kk::named::name,(StringProperty::Getter)&ElementActionEvent::name,NULL);
    
    Property *ElementActionEvent::Propertys[] = {
        &ElementActionEvent::Property_asElement,
        &ElementActionEvent::Property_actionType,
        &ElementActionEvent::Property_name,
        NULL
    };
    
    IMP_CLASS(ElementActionEvent, ElementEvent, ElementActionEvent::Propertys, NULL)
    
}
