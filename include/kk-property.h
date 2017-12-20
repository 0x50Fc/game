//
//  kk-property.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_property_h
#define kk_property_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-script.h>
#endif


namespace kk {
    
    class Object;
    
    typedef Uint32 Id;
    
    class Named {
    public:
        Named(Id id,CString name);
        virtual Id id();
        virtual CString name();
    protected:
        CString _name;
        Id _id;
    };
    
    namespace named {
        extern kk::Named id;
        extern kk::Named name;
        extern kk::Named parent;
        extern kk::Named firstChild;
        extern kk::Named lastChild;
        extern kk::Named nextSibling;
        extern kk::Named prevSibling;
        extern kk::Named document;
        extern kk::Named rootElement;
        extern kk::Named element;
        extern kk::Named cancelBubble;
        extern kk::Named asElement;
        extern kk::Named actionType;
        extern kk::Named size;
        extern kk::Named position;
        extern kk::Named transform;
        extern kk::Named opacity;
        extern kk::Named current;
        extern kk::Named speed;
        extern kk::Named count;
        extern kk::Named paused;
        extern kk::Named duration;
        extern kk::Named app;
        extern kk::Named path;
        extern kk::Named anchor;
        extern kk::Named width;
        extern kk::Named height;
        extern kk::Named startTime;
        extern kk::Named scale;
        extern kk::Named maxWidth;
        extern kk::Named text;
        extern kk::Named fontFamily;
        extern kk::Named color;
        extern kk::Named fontSize;
        extern kk::Named layout;
        extern kk::Named contentSize;
        extern kk::Named left;
        extern kk::Named top;
        extern kk::Named right;
        extern kk::Named bottom;
        extern kk::Named margin;
        extern kk::Named padding;
        extern kk::Named minWidth;
        extern kk::Named minHeight;
        extern kk::Named maxHeight;
        
        kk::Named * get(kk::CString name);
        kk::Named ** list();
    }
    
    
    class Property {
    public:
        Property(Named * name,CString title);
        Property(Named * name);
        virtual Named * name();
        virtual CString title();
        virtual void change(Object * object);
        virtual void def(ScriptContext ctx) = 0;
    protected:
        Named * _name;
        CString _title;
    };
    
    template<typename T>
    class TProperty : public Property {
    public:
        typedef T (Object::*Getter)();
        typedef void (Object::*Setter)(T value);
        TProperty(Named * name, Getter getter, Setter setter): Property(name),_getter(getter),_setter(setter) {};
        TProperty(Named * name, Getter getter, Setter setter,CString title): Property(name,title),_getter(getter),_setter(setter) {};
        virtual T get(Object * object) { return (object->*_getter)(); };
        virtual void set(Object * object,T value) { if(_setter) { (object->*_setter)(value); change(object); } };
    protected:
        Getter _getter;
        Setter _setter;
    };
    
    class IntProperty : public TProperty<Int> {
    public:
        IntProperty(Named * name, Getter getter, Setter setter);
        IntProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class UintProperty : public TProperty<Uint> {
    public:
        UintProperty(Named * name, Getter getter, Setter setter);
        UintProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class Int64Property : public TProperty<Int64> {
    public:
        Int64Property(Named * name, Getter getter, Setter setter);
        Int64Property(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class BooleanProperty : public TProperty<Boolean> {
    public:
        BooleanProperty(Named * name, Getter getter, Setter setter);
        BooleanProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class FloatProperty : public TProperty<Float> {
    public:
        FloatProperty(Named * name, Getter getter, Setter setter);
        FloatProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class DoubleProperty : public TProperty<Double> {
    public:
        DoubleProperty(Named * name, Getter getter, Setter setter);
        DoubleProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class StringProperty : public TProperty<CString> {
    public:
        StringProperty(Named * name, Getter getter, Setter setter);
        StringProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    class ObjectProperty : public TProperty<Object*> {
    public:
        ObjectProperty(Named * name, Getter getter, Setter setter);
        ObjectProperty(Named * name, Getter getter, Setter setter,CString title);
        virtual void def(ScriptContext ctx);
    };
    
    
}

#endif /* kk_property_h */
