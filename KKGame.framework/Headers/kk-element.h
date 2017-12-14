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
    DEF_CLASS(Element)
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
        
        virtual void change(Property * property);
        
        //(Document * document ,int id,CString name)
        virtual void init();
        
        virtual Event * defaultEvent(CString name);
        virtual void emit(CString name,Event * event);
        
        static Int64Property Property_id;
        static ObjectProperty Property_parent;
        static ObjectProperty Property_firstChild;
        static ObjectProperty Property_lastChild;
        static ObjectProperty Property_nextSibling;
        static ObjectProperty Property_prevSibling;
        static ObjectProperty Property_document;
        
        static Property *Propertys[];
        
    protected:
        Int64 _id;
        Weak<Element*> _parent;
        Strong<Element*> _firstChild;
        Strong<Element*> _lastChild;
        Strong<Element*> _nextSibling;
        Weak<Element*> _prevSibling;
        Weak<Object*> _document;
        virtual void setParent(Element * v);
        virtual void setFirstChild(Element * v);
        virtual void setLastChild(Element * v);
        virtual void setNextSibling(Element * v);
        virtual void setPrevSibling(Element * v);
        virtual void setDocument(Element * v);
    };

    class ElementEvent : public Event {
    DEF_CLASS(ElementEvent)
    public:
        virtual Element * element();
        virtual void setElement(Element * element);
        virtual Boolean isCancelBubble();
        virtual void setCancelBubble(Boolean value);
        
        static ObjectProperty Property_element;
        static BooleanProperty Property_cancelBubble;
        static Property *Propertys[];
        
    protected:
        Strong<Element*> _element;
        Boolean _cancelBubble;
    };
    
    enum {
        ElementActionTypeProperty
        ,ElementActionTypeAdd
        ,ElementActionTypeRemove
        ,ElementActionTypeNew
    };
    
    typedef Int ElementActionType;
    
    class ElementActionEvent : public ElementEvent {
    DEF_CLASS(ElementActionEvent)
    public:
        virtual Element * asElement();
        virtual void setAsElement(Element * element);
        virtual Int actionType();
        virtual void setActionType(Int value);
        virtual Property * property();
        virtual void setProperty(Property * value);
        virtual CString name();
        
        static ObjectProperty Property_asElement;
        static IntProperty Property_actionType;
        static StringProperty Property_name;
        static Property *Propertys[];
    protected:
        Strong<Element*> _asElement;
        Int _actionType;
        Property * _property;
    };
    
}

#endif /* kk_element_h */
