//
//  kk-event.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_event_h
#define kk_event_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-object.h>
#endif

#include <list>

namespace kk {
    
    class Event : public Object {
        DEF_CLASS(Event)
    };
    
    typedef void (Object::*OnEventFunction)(Event * event);
    typedef void (*EventFunction)(Event * event,void * context);
    
    class EventCaller;
    
    class EventEmitter : public Object {
    DEF_CLASS(EventEmitter)
    public:
        virtual void on(CString name,Object * object,OnEventFunction func);
        virtual void off(CString name,Object * object,OnEventFunction func);
        virtual void on(CString name,EventFunction func,void * context);
        virtual void off(CString name,EventFunction func,void * context);
        virtual void on(CString name,ScriptPtr fnptr);
        virtual void off(CString name,ScriptPtr fnptr);
        virtual void emit(CString name,Event * event);
        virtual void init();
        virtual Event * defaultEvent(CString name);
    private:
        std::list<EventCaller *> _callers;
    };
    
    CString EventFunctionGetName(ScriptContext context);
    
    void * EventFunctionGetContext(ScriptContext context);
    
}

#endif /* kk_event_h */
