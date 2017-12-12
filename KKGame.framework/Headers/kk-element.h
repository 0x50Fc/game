//
//  kk-element.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_element_h
#define kk_element_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-event.h>
#endif

namespace kk {
    
    class Document;
    
    class Element : public EventEmitter {
    public:
        
        virtual Document * document();
        virtual Element * parent();
        virtual Element * firstChild();
        virtual Element * lastChild();
        virtual Element * nextSibling();
        virtual Element * prevSibling();
        
        virtual void remove();
        virtual void append(Element * e);
        virtual void appendTo(Element * e);
        virtual void before(Element * e);
        virtual void beforeTo(Element *e);
        virtual void after(Element * e);
        virtual void afterTo(Element * e);
        virtual Int64 id();
        virtual void setId(Int64 v);
        
        virtual void onChangeProperty(VProperty * property);
        
        //(Document * document ,int id,CString name)
        virtual void init();
        
        virtual Event * defaultEvent(CString name);
        virtual void emit(CString name,Event * event);
        
        DEF_CLASS(Element)
        
    protected:
        Element(ScriptContext context,ScriptPtr ptr);
        Int64Property _id;
        WeakProperty _parent;
        StrongProperty _firstChild;
        StrongProperty _lastChild;
        StrongProperty _nextSibling;
        WeakProperty _prevSibling;
        WeakProperty _document;
    };

    class ElementEvent : public Event {
    public:
        DEF_CLASS(ElementEvent)
        StrongProperty element;
        BooleanProperty cancelBubble;
    protected:
        ElementEvent(ScriptContext context,ScriptPtr ptr);
    };
    
    enum {
        ElementActionTypeProperty
        ,ElementActionTypeAppend
        ,ElementActionTypeAfter
        ,ElementActionTypeBefore
        ,ElementActionTypeRemove
        ,ElementActionTypeNew
    };
    
    typedef Int ElementActionType;
    
    class ElementActionEvent : public ElementEvent {
    public:
        DEF_CLASS(ElementActionEvent)
        StrongProperty asElement;
        IntProperty actionType;
        StringProperty name;
        VProperty * property;
    protected:
        ElementActionEvent(ScriptContext context,ScriptPtr ptr);
    };
    
}

#endif /* kk_element_h */
