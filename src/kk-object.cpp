    //
    //  kk-object.cpp
    //  KKGame
    //
    //  Created by 张海龙 on 2017/12/6.
    //  Copyright © 2017年 kkmofang.cn. All rights reserved.
    //

    #include "kk-config.h"
    #include "kk-object.h"

    namespace kk {


        Class::Class(Class * isa,Property ** propertys,ClassPrototypeFunc prototype,ClassAllocFunc alloc): isa(isa),propertys(propertys),prototype(prototype),alloc(alloc){
        }
        
        Property * Class::getProperty(kk::Id id){
            
            if(_propertys.empty() && propertys) {
                Property ** p = propertys;
                while(p && *p) {
                    _propertys[(*p)->name()->id()] = *p;
                    p++;
                }
            }
            
            std::map<kk::Id,Property *>::iterator i = _propertys.find(id);
            
            if(i != _propertys.end()) {
                return i->second;
            }
            
            if(isa) {
                return isa->getProperty(id);
            }
            
            return NULL;
        }
        
        ScriptResult Object::Alloc(kk::ScriptContext context) {
            duk_push_this(context);
            Object * v = new Object(context,duk_get_heapptr(context,-1));
            ScriptInitObject(context,v);
            duk_pop(context);
            v->init();
            return 0;
        }
        
        Class Object::Class = {NULL,NULL,NULL,Object::Alloc};
        
        kk::Class * Object::getClass() {
            return & Object::Class;
        }
        
        Object::Object(ScriptContext context,ScriptPtr ptr): _ptr(ptr),_context(context) {
            
        }
        
        Object::~Object() {
            std::set<Object **>::iterator i = _weaks.begin();
            while(i != _weaks.end()) {
                Object ** v = *i;
                *v = NULL;
                i ++;
            }
        }
        
        void Object::init() {
            
        }
        
        void Object::deinit() {
            
        }
        
        String Object::toString() {
            return "[Object]";
        }
        
        ScriptPtr Object::ptr() {
            return _ptr;
        }
        
        ScriptContext Object::context() {
            return _context;
        }
        
        void Object::weak(Object ** value) {
            _weaks.insert(value);
        }
        
        void Object::unweak(Object ** value) {
            std::set<Object **>::iterator i = _weaks.find(value);
            if(i != _weaks.end()) {
                _weaks.erase(i);
            }
        }
        
        void Object::change(Property * property) {
            
        }
        
        void ScriptGetPrototype(ScriptContext context,  Class * isa) {
            
            duk_push_global_object(context);
            
            duk_push_sprintf(context, "__class_%lx",(unsigned long) isa);
            duk_get_prop(context, -2);
            
            if(duk_is_object(context, -1)) {
                duk_remove(context, -2);
            } else {
                duk_pop(context);
                
                duk_push_object(context);
                duk_push_sprintf(context, "__class_%lx",(unsigned long) isa);
                duk_dup(context, -2);
                
                if(isa) {
                    
                    Property **p = isa->propertys;
                    
                    while(p && *p) {
                        (*p)->def(context);
                        p ++;
                    }
                    
                    if(isa->prototype) {
                        (*isa->prototype)(context);
                    }
                }
                
                if(isa->isa) {
                    ScriptGetPrototype(context, isa->isa);
                    duk_set_prototype(context, -2);
                }
                
                duk_put_prop(context, -4);
                duk_remove(context, -2);
            }
        }
        
        void ScriptOpenClass(ScriptContext context, CString name, Class * isa) {
            
            duk_push_global_object(context);
            
            duk_push_string(context, name);
            duk_push_c_function(context, isa->alloc, DUK_VARARGS);
            duk_put_prop(context, -3);
            
            duk_pop(context);
            
        }
        
        static ScriptResult ScriptObjectDealloc(ScriptContext context) {
            
            Object * v = ScriptGetObject(context,-1);
            
            if(v) {
                v->deinit();
                delete v;
            }

            return 0;
        }
        
        
        void ScriptInitObject(ScriptContext ctx,Object * object) {
            
            duk_push_string(ctx, "__object");
            duk_push_pointer(ctx, object);
            duk_def_prop(ctx,
                         -3,
                         DUK_DEFPROP_HAVE_VALUE );
            
            ScriptGetPrototype(ctx, object->getClass());
            duk_set_prototype(ctx, -2);
            
            duk_push_c_function(ctx, ScriptObjectDealloc, 1);
            duk_set_finalizer(ctx, -2);
        }
        
        void ScriptPushObject(ScriptContext context,Object * object) {
            if(object == NULL || object->ptr() == 0) {
                duk_push_undefined(context);
            } else {
                duk_push_heapptr(context, object->ptr());
            }
        }
        
        Object * ScriptGetObject(ScriptContext context, int idx) {
            Object * v = NULL;
            if(duk_is_object(context, idx)){
                duk_push_string(context, "__object");
                duk_get_prop(context, idx -1);
                if(duk_is_pointer(context, -1)) {
                    v = (Object *) duk_to_pointer(context, -1);
                }
                duk_pop(context);
            }
            return v;
        }
        
        Object * ScriptNewObject(ScriptContext context, Class * isa , int nargs){
            
            duk_push_c_function(context, isa->alloc, DUK_VARARGS);
            
            if(nargs > 0) {
                duk_insert(context, - nargs - 1);
            }
            
            duk_new(context, nargs);
            
            return ScriptGetObject(context,-1);
        }
        
        void ScriptNewGlobalObject(ScriptContext context,Object * object) {
            duk_push_global_object(context);
            duk_push_sprintf(context, "__strong_%lx",(unsigned long) object->ptr());
            ScriptPushObject(context, object);
            duk_put_prop(context,-3);
            duk_pop(context);
        }
        
        void ScriptDeleteGlobalObject(ScriptContext context,Object * object) {
            duk_push_global_object(context);
            duk_push_sprintf(context, "__strong_%lx",(unsigned long) object->ptr());
            duk_del_prop(context,-2);
            duk_pop(context);
        }
    }
