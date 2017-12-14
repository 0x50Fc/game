//
//  kk-object.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/6.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_object_h
#define kk_object_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-property.h>
#endif

#include <set>
#include <map>

namespace kk {
    
    class Object;
    
    void ScriptInitObject(ScriptContext context,Object * object);
    
    typedef ScriptFunction ClassPrototypeFunc;
    typedef ScriptFunction ClassAllocFunc;
    
    class Class {
    public:
        Class(Class * isa,Property ** propertys,ClassPrototypeFunc prototype,ClassAllocFunc alloc);
        Class * isa;
        Property ** propertys;
        ClassPrototypeFunc prototype;
        ClassAllocFunc alloc;
        virtual Property * getProperty(kk::Id id);
    private:
        std::map<kk::Id,Property *> _propertys;
    };
    
#define DEF_CLASS(name) \
protected: \
    name(kk::ScriptContext context,ScriptPtr ptr); \
public: \
    virtual kk::Class * getClass(); \
    static kk::ScriptResult Alloc(kk::ScriptContext context);\
    static kk::Class Class;


#define IMP_CLASS(name,super,propertys,prototype) \
name::name(kk::ScriptContext context,ScriptPtr ptr):super(context,ptr){};\
kk::Class * name::getClass() { \
    return & name::Class; \
} \
kk::ScriptResult name::Alloc(kk::ScriptContext context) { \
    duk_push_this(context); \
    name * v = new name(context,duk_get_heapptr(context,-1)); \
    ScriptInitObject(context,v);\
    duk_pop(context); \
    v->init(); \
    return 0; \
} \
Class name::Class(&super::Class,(propertys),(prototype),name::Alloc);
    
    class Object {
        
        DEF_CLASS(Object)
        
    public:
        virtual ~Object();
        virtual void init();
        virtual void deinit();
        virtual ScriptPtr ptr();
        virtual void weak(Object ** value);
        virtual void unweak(Object ** value);
        virtual String toString();
        virtual ScriptContext context();
        virtual void change(Property * property);

    private:
        ScriptContext _context;
        ScriptPtr _ptr;
        std::set<Object **> _weaks;
    };
    
    template<typename T>
    class Strong {
    public:
        Strong(): _object(NULL),_value(NULL) {}
        virtual ~Strong(){
            if(_value && _object) {
                _value->unweak((kk::Object**) &_value);
                ScriptContext ctx = _object->context();
                ScriptPushObject(ctx,_object);
                duk_push_sprintf(ctx,"__strong_%lx",(unsigned long) _value);
                duk_del_prop(ctx,-2);
                duk_pop(ctx);
            }
        }
        virtual T get() { return _value; }
        virtual void set(Object * object,T value) {
            if(_value != value) {
                if(_value && _object) {
                    _value->unweak((kk::Object**)&_value);
                    ScriptContext ctx = _object->context();
                    ScriptPushObject(ctx,_object);
                    duk_push_sprintf(ctx,"__strong_%lx",(unsigned long) _value);
                    duk_del_prop(ctx,-2);
                    duk_pop(ctx);
                }
                _value = value;
                _object = object;
                if(_value && _object) {
                    _value->weak((kk::Object**)&_value);
                    ScriptContext ctx = _object->context();
                    ScriptPushObject(ctx,_object);
                    duk_push_sprintf(ctx,"__strong_%lx",(unsigned long) _value);
                    ScriptPushObject(ctx,_value);
                    duk_def_prop(ctx, -3,
                                 DUK_DEFPROP_HAVE_VALUE |
                                 DUK_DEFPROP_HAVE_CONFIGURABLE | DUK_DEFPROP_CONFIGURABLE);
                    duk_pop(ctx);
                }
            }
        }
    protected:
        Object * _object;
        T _value;
    };
    
    template<typename T>
    class Weak {
    public:
        Weak(): _value(NULL) {}
        virtual ~Weak(){
            if(_value) {
                _value->unweak((kk::Object**)&_value);
            }
        }
        virtual T get() { return _value; }
        virtual void set(T value) {
            if(_value != value) {
                if(_value) {
                    _value->unweak((kk::Object**)&_value);
                }
                _value = value;
                if(_value) {
                    _value->weak((kk::Object**)&_value);
                }
            }
        }
    protected:
        T _value;
    };
    
    void ScriptGetPrototype(ScriptContext context,  Class * isa);
    
    void ScriptOpenClass(ScriptContext context, CString name, Class * isa);
    
    Object * ScriptNewObject(ScriptContext context, Class * isa, int nargs);
    
    void ScriptPushObject(ScriptContext context,Object * object);
    
    Object * ScriptGetObject(ScriptContext context, int idx);
    
    void ScriptNewGlobalObject(ScriptContext context,Object * object);
    
    void ScriptDeleteGlobalObject(ScriptContext context,Object * object);
    
    template<typename T>
    T * ScriptNewObject(ScriptContext context,int nargs) {
        return dynamic_cast<T *>(ScriptNewObject(context,&T::Class,nargs));
    }
 
}

#endif /* kk_object_h */
