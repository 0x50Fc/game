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
        
        Object * Object::Null = NULL;
        
        String Object::toString() {
            return "[Object]";
        }
        
        ScriptPtr Object::ptr() {
            return _ptr;
        }
        
        ScriptContext Object::context() {
            return _context;
        }
        
        std::map<PropertyId,VProperty *>::iterator Object::begin() {
            return _propertys.begin();
        }
        
        std::map<PropertyId,VProperty *>::iterator Object::end() {
            return _propertys.end();
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
        
        VProperty * Object::getProperty(PropertyId pid) {
            std::map<PropertyId,VProperty *>::iterator i = _propertys.find(pid);
            if(i != _propertys.end()) {
                return i->second;
            }
            return NULL;
        }
        
        void Object::addProperty(VProperty * property) {
            _propertys[property->property()->pid()] = property;
        }
        
        void Object::onChangeProperty(VProperty * property) {
            
        }
        
        void ScriptOpenClass(ScriptContext context, CString name, Class isa) {
            
            duk_push_global_object(context);
            
            duk_push_string(context, name);
            duk_push_c_function(context, isa, DUK_VARARGS);
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
        
        static ScriptResult ScriptObjectGetProperty(ScriptContext context) {
            
            VProperty * v = NULL;
            
            duk_push_current_function(context);
            
            duk_push_string(context, "property");
            duk_get_prop(context, -2);
            
            if(duk_is_pointer(context, -1)) {
                v = (VProperty *) duk_to_pointer(context, -1);
            }
            
            duk_pop_n(context, 2);
            
            if(v) {
                return v->getScript();
            }
            
            return 0;
        }
        
        static ScriptResult ScriptObjectSetProperty(ScriptContext context) {
            
            VProperty * v = NULL;
            
            duk_push_current_function(context);
            
            duk_push_string(context, "property");
            duk_get_prop(context, -2);
            
            if(duk_is_pointer(context, -1)) {
                v = (VProperty *) duk_to_pointer(context, -1);
            }
            
            duk_pop_n(context, 2);
            
            if(v) {
                return v->setScript();
            }
            
            return 0;
        }
        
        void ScriptInitObject(ScriptContext context,Object * object) {
            
            duk_push_string(context, "__object");
            duk_push_pointer(context, (void*) object);
            duk_put_prop(context, -3);
            
            std::map<PropertyId,VProperty *>::iterator i = object->begin();

            while(i != object->end()) {
                
                VProperty * v = i->second;
             
                duk_push_string(context, v->property()->name());
                duk_push_c_function(context, ScriptObjectGetProperty, 0);
                
                duk_push_string(context, "property");
                duk_push_pointer(context, v);
                duk_put_prop(context, -3);
                
                duk_push_c_function(context, ScriptObjectSetProperty, 1);
                
                duk_push_string(context, "property");
                duk_push_pointer(context, v);
                duk_put_prop(context, -3);
                
                duk_def_prop(context,
                             -4,
                             DUK_DEFPROP_HAVE_GETTER |
                             DUK_DEFPROP_HAVE_SETTER |
                             DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
                
                i++;
            }
            
            duk_push_c_function(context, ScriptObjectDealloc, 1);
            duk_set_finalizer(context, -2);
            
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
        
        Object * ScriptNewObject(ScriptContext context, Class isa , int nargs){
            
            duk_push_c_function(context, isa, DUK_VARARGS);
            
            if(nargs > 0) {
                duk_insert(context, - nargs - 1);
            }
            
            duk_new(context, nargs);
            
            return ScriptGetObject(context,-1);
        }
        
        void ScriptNewGlobalObject(ScriptContext context,Object * object) {
            duk_push_global_object(context);
            duk_push_sprintf(context, "_G_%lx",(unsigned long) object->ptr());
            ScriptPushObject(context, object);
            duk_put_prop(context,-3);
            duk_pop(context);
        }
        
        void ScriptDeleteGlobalObject(ScriptContext context,Object * object) {
            duk_push_global_object(context);
            duk_push_sprintf(context, "_G_%lx",(unsigned long) object->ptr());
            duk_del_prop(context,-2);
            duk_pop(context);
        }
    }
