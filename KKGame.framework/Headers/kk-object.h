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
    
#define DEF_CLASS(name) \
static ScriptResult Class(ScriptContext context){ \
    duk_push_this(context); \
    kk::ScriptPtr ptr = duk_get_heapptr(context,-1); \
    name * v = new name (context,ptr); \
    kk::ScriptInitObject(context, v); \
    duk_pop(context); \
    v->init(); \
    return 0; \
}
    
    void ScriptInitObject(ScriptContext context,Object * object);
    
    typedef ScriptFunction Class;
    
    class Object {
    public:
        virtual ~Object();
        virtual void init();
        virtual void deinit();
        virtual ScriptPtr ptr();
        virtual std::map<PropertyId,VProperty *>::iterator begin();
        virtual std::map<PropertyId,VProperty *>::iterator end();
        virtual void weak(Object ** value);
        virtual void unweak(Object ** value);
        virtual VProperty * getProperty(PropertyId pid);
        virtual String toString();
        
        template<typename T>
        T * getProperty(PropertyId pid) { return dynamic_cast<T*>( getProperty(pid) ); }
        
        template<typename TProperty,typename TValue>
        void setProperty(PropertyId pid, TValue value) { TProperty * p = dynamic_cast<TProperty*>( getProperty(pid) ); if(p) { p->set(context(),value); } }
        
        virtual ScriptContext context();
        
        virtual void onChangeProperty(VProperty * property);
        
        DEF_CLASS(Object)
        
        static Object * Null;
        
    protected:
        Object(ScriptContext context,ScriptPtr ptr);
    private:
        ScriptContext _context;
        ScriptPtr _ptr;
        std::set<Object **> _weaks;
        std::map<PropertyId,VProperty *> _propertys;
        void addProperty(VProperty * property);
        friend class VProperty;
    };
    
    
    void ScriptOpenClass(ScriptContext context, CString name, Class isa);
    
    Object * ScriptNewObject(ScriptContext context, Class isa, int nargs);
    
    void ScriptPushObject(ScriptContext context,Object * object);
    
    Object * ScriptGetObject(ScriptContext context, int idx);
    
    void ScriptNewGlobalObject(ScriptContext context,Object * object);
    
    void ScriptDeleteGlobalObject(ScriptContext context,Object * object);
    
    template<typename T>
    T * ScriptNewObject(ScriptContext context,int nargs) {
        return dynamic_cast<T *>(ScriptNewObject(context,T::Class,nargs));
    }
 
}

#endif /* kk_object_h */
