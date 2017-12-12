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
    
    typedef Uint32 PropertyId;
    
    class Property {
    public:
        Property(PropertyId pid,CString name);
        virtual PropertyId pid();
        virtual CString name();
    protected:
        CString _name;
        PropertyId _pid;
    };
    
    class VProperty {
    public:
        VProperty(Object * object,Property * property);
        virtual Property * property();
        virtual Object * object();
        virtual void change();
        virtual ScriptResult getScript() = 0;
        virtual ScriptResult setScript() = 0;
        virtual String toString() ;
        virtual void set(CString value) ;
    protected:
        Property * _property;
        Object * _object;
    };
    
    template<typename T>
    class TProperty : public VProperty {
    public:
        TProperty(Object * object,Property * property): VProperty(object,property) {};
        virtual T get() { return _value;};
    protected:
        T _value;
    };
    
    class IntProperty : public TProperty<Int> {
    public:
        IntProperty(Object * object,Property * property);
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual String toString();
        virtual void set(Int value) { _value = value; change(); };
        virtual void set(CString value);
    };
    
    class Int64Property : public TProperty<Int64> {
    public:
        Int64Property(Object * object,Property * property);
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual String toString();
        virtual void set(Int64 value) { _value = value; change(); };
        virtual void set(CString value);
    };
    
    class BooleanProperty : public TProperty<Boolean> {
    public:
        BooleanProperty(Object * object,Property * property);
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual String toString();
        virtual void set(Boolean value) { _value = value; change(); };
        virtual void set(CString value);
    };
    
    class DoubleProperty : public TProperty<Double> {
    public:
        DoubleProperty(Object * object,Property * property);
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual String toString();
        virtual void set(Double value) { _value = value; change(); };
        virtual void set(CString value);
    };
    
    class FloatProperty : public TProperty<Float> {
    public:
        FloatProperty(Object * object,Property * property);
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual String toString();
        virtual void set(Float value) { _value = value; change(); };
        virtual void set(CString value);
    };
    
    class StringProperty : public VProperty {
    public:
        StringProperty(Object * object,Property * property);
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual String& get() { return _value;};
        virtual void set(String value){ _value = value; change(); };
        virtual void set(CString value){ _value = value; change(); };
        virtual void set(String &value){ _value = value; change(); };
        virtual String toString();
    protected:
        String _value;
    };
    
    class StrongProperty : public TProperty<Object*> {
    public:
        StrongProperty(Object * object,Property * property);
        virtual ~StrongProperty();
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual void set(Object * value);
        virtual String toString();
        virtual void set(CString value);
    };
    
    class WeakProperty : public TProperty<Object*> {
    public:
        WeakProperty(Object * object,Property * property);
        virtual ~WeakProperty();
        virtual ScriptResult getScript();
        virtual ScriptResult setScript();
        virtual void set(Object * value);
        virtual String toString();
        virtual void set(CString value);
    };
    
    
    namespace P {
        extern kk::Property id;
        extern kk::Property name;
        extern kk::Property parent;
        extern kk::Property firstChild;
        extern kk::Property lastChild;
        extern kk::Property nextSibling;
        extern kk::Property prevSibling;
        extern kk::Property document;
        extern kk::Property rootElement;
        extern kk::Property element;
        extern kk::Property cancelBubble;
        extern kk::Property asElement;
        extern kk::Property actionType;
        extern kk::Property size;
        extern kk::Property position;
        extern kk::Property transform;
        extern kk::Property opacity;
        extern kk::Property current;
        extern kk::Property speed;
        extern kk::Property count;
        extern kk::Property paused;
        extern kk::Property duration;
        extern kk::Property app;
        extern kk::Property path;
        
        kk::Property * get(kk::CString name);
        kk::Property ** list();
    }
    
}

#endif /* kk_property_h */
