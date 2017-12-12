//
//  kk-event.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-event.h"

namespace kk {
    
    
    Event::Event(ScriptContext context,ScriptPtr ptr):kk::Object(context,ptr) {
        
    }
    
    class EventCaller {
    public:
        EventCaller(CString name,Object * object,OnEventFunction func);
        EventCaller(CString name,EventFunction func,void * context);
        EventCaller(CString name,ScriptPtr ptr);
        virtual ~EventCaller();
        virtual Boolean has(CString name);
        virtual Boolean is(CString name,Object * object,OnEventFunction func);
        virtual Boolean is(CString name,EventFunction func,void * context);
        virtual Boolean is(CString name,ScriptPtr ptr);
        virtual void release(EventEmitter * emitter);
        virtual void call(EventEmitter * emitter,Event * event);
    private:
        Object * _object;
        OnEventFunction _onFunction;
        EventFunction _func;
        void * _context;
        ScriptPtr _ptr;
        String _name;
    };
    
    EventCaller::EventCaller(CString name,Object * object,OnEventFunction func):_object(object),_onFunction(func),_func(NULL),_ptr(0),_context(NULL),_name(name) {
        object->weak(&_object);
    }
    
    EventCaller::EventCaller(CString name,EventFunction func,void * context):_object(NULL),_onFunction(NULL),_func(func),_context(context),_ptr(0),_name(name) {
        
    }
    
    EventCaller::EventCaller(CString name,ScriptPtr ptr):_object(NULL),_onFunction(NULL),_func(NULL),_ptr(ptr),_context(NULL),_name(name) {
        
    }
    
    EventCaller::~EventCaller() {
        
    }
    
    Boolean EventCaller::has(CString name) {
        return CStringHasPrefix(_name.c_str(), name);
    }
    
    Boolean EventCaller::is(CString name,Object * object,OnEventFunction func) {
        return ((name == NULL ||CStringEqual(_name.c_str(), name) ) && (object == NULL || object == _object) && (func == NULL || func == _onFunction));
    }
    
    Boolean EventCaller::is(CString name,EventFunction func,void * context) {
        return ((name == NULL ||CStringEqual(_name.c_str(), name) ) && (func == NULL || func == _func) && (context == NULL || context == _context));
    }
    
    Boolean EventCaller::is(CString name,ScriptPtr ptr) {
        return ((name == NULL || CStringEqual(_name.c_str(), name) ) && (ptr == NULL || ptr == _ptr));
    }
    
    void EventCaller::release(EventEmitter * emitter) {
        
        if(_ptr) {
            
            ScriptContext ctx = emitter->context();
            
            ScriptPushObject(ctx, emitter);
            
            duk_push_string(ctx, "_events");
            duk_get_prop(ctx, -2);
            
            duk_push_pointer(ctx, _ptr);
            duk_del_prop(ctx, -2);
            
            duk_pop_n(ctx, 2);
            
        }
        
        if(_object != NULL) {
            _object->unweak(&_object);
        }
        
        delete this;
    }
    
    void EventCaller::call(EventEmitter * emitter,Event * event) {
        
        if(_object && _onFunction) {
            (_object->*_onFunction)(event);
        }
        
        if(_func) {
            (*_func)(event,_context);
        }
        
        if(_ptr) {
            
            ScriptContext ctx = emitter->context();
            
            duk_push_heapptr(ctx, _ptr);
            
            ScriptPushObject(ctx, event);
            
            if(duk_pcall(ctx, 1) != DUK_EXEC_SUCCESS) {
                Log("%s", duk_to_string(ctx, -1));
            }
            
            duk_pop(ctx);
        }
        
    }
    
    void EventEmitter::on(CString name,Object * object,OnEventFunction func) {
        _callers.push_back(new EventCaller(name,object,func));
    }
    
    void EventEmitter::off(CString name,Object * object,OnEventFunction func) {
        std::list<EventCaller *>::iterator i = _callers.begin();
        while(i != _callers.end()) {
            EventCaller * v = * i;
            if(v->is(name, object, func)) {
                v->release(this);
                i = _callers.erase(i);
            } else {
                i ++;
            }
        }
    }
    
    void EventEmitter::on(CString name,EventFunction func,void * context) {
        _callers.push_back(new EventCaller(name,func,context));
    }
    
    void EventEmitter::off(CString name,EventFunction func,void * context) {
        std::list<EventCaller *>::iterator i = _callers.begin();
        while(i != _callers.end()) {
            EventCaller * v = * i;
            if(v->is(name, func, context)) {
                v->release(this);
                i = _callers.erase(i);
            } else {
                i ++;
            }
        }
    }
    
    void EventEmitter::on(CString name,ScriptPtr fnptr) {
        
        ScriptContext ctx = context();
        
        ScriptPushObject(ctx, this);
        
        duk_push_string(ctx, "_events");
        duk_get_prop(ctx, -2);
        
        duk_push_pointer(ctx, fnptr);
        duk_push_heapptr(ctx, fnptr);
        duk_put_prop(ctx, -3);
        
        duk_pop_n(ctx, 2);
        
        _callers.push_back(new EventCaller(name,fnptr));
        
    }
    
    void EventEmitter::off(CString name,ScriptPtr fnptr) {
        std::list<EventCaller *>::iterator i = _callers.begin();
        while(i != _callers.end()) {
            EventCaller * v = * i;
            if(v->is(name, fnptr)) {
                v->release(this);
                i = _callers.erase(i);
            } else {
                i ++;
            }
        }
    }
    
    void EventEmitter::emit(CString name,Event * event) {
        std::list<EventCaller *> vs;
        std::list<EventCaller *>::iterator i = _callers.begin();
        while(i != _callers.end()) {
            EventCaller * v = * i;
            if(v->has(name)) {
                vs.push_back(v);
            } else {
                i ++;
            }
        }
        
        i = vs.begin();
        
        while(i != vs.end()) {
            
            EventCaller * v = * i;
            
            v->call(this, event);
            
            i ++;
        }
    }
    
    EventEmitter::EventEmitter(ScriptContext context,ScriptPtr ptr) : kk::Object(context,ptr) {
        
    }
    
    static ScriptResult EventEmitterOnFunc(ScriptContext ctx) {
        
        int nargs = duk_get_top(ctx);
        
        if(nargs > 1 && duk_is_string(ctx, -nargs) && duk_is_function(ctx, -nargs + 1)) {
            
            CString name = duk_to_string(ctx, -nargs);
            ScriptPtr ptr = duk_get_heapptr(ctx, -nargs + 1);
            
            duk_push_this(ctx);
            
            EventEmitter * v = dynamic_cast<EventEmitter *>(ScriptGetObject(ctx, -1));

            duk_pop(ctx);
            
            if(v) {
                v->on(name, ptr);
            }
            
        }
        
        return 0;
    }
    
    static ScriptResult EventEmitterOffFunc(ScriptContext ctx) {
        
        CString name = NULL;
        ScriptPtr ptr = NULL;
        
        int nargs = duk_get_top(ctx);
        
        if(nargs > 0 && duk_is_string(ctx, -nargs)) {
            name = duk_to_string(ctx, -nargs);
        }
        
        if(nargs > 1 && duk_is_function(ctx, -nargs +1)) {
            ptr = duk_get_heapptr(ctx, -nargs + 1);
        }
        
        duk_push_this(ctx);
        
        EventEmitter * v = dynamic_cast<EventEmitter *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            v->off(name, ptr);
        }
        
        return 0;
    }
    
    static ScriptResult EventEmitterEmitFunc(ScriptContext ctx) {
        
        CString name = NULL;
        Event * event = NULL;
        
        int nargs = duk_get_top(ctx);
        
        if(nargs > 0 && duk_is_string(ctx, -nargs)) {
            name = duk_to_string(ctx, -nargs);
        }
        
        if(nargs > 1 && duk_is_object(ctx, -nargs + 1)) {
            event = dynamic_cast<Event *>(ScriptGetObject(ctx, -nargs + 1));
        }
        
        duk_push_this(ctx);
        
        EventEmitter * v = dynamic_cast<EventEmitter *>(ScriptGetObject(ctx, -1));
        
        duk_pop(ctx);
        
        if(v) {
            if(event) {
                v->emit(name, event);
            } else {
                event = v->defaultEvent(name);
                v->emit(name, event);
                duk_pop(ctx);
            }
        }
        
        return 0;
    }
    
    void EventEmitter::init() {
        Object::init();
        
        ScriptContext ctx = context();
        
        duk_push_this(ctx);
        
        duk_push_string(ctx, "_events");
        duk_push_object(ctx);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "on");
        duk_push_c_function(ctx, EventEmitterOnFunc, 2);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "off");
        duk_push_c_function(ctx, EventEmitterOffFunc, 2);
        duk_put_prop(ctx, -3);
        
        duk_push_string(ctx, "emit");
        duk_push_c_function(ctx, EventEmitterEmitFunc, 2);
        duk_put_prop(ctx, -3);
        
        duk_pop(ctx);
        
    }
    
    Event * EventEmitter::defaultEvent(CString name) {
        return ScriptNewObject<Event>(context(), 0);
    }
    
}

