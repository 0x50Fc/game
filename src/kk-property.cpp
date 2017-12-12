//
//  kk-property.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-property.h"
#include "kk-object.h"

#include <strstream>
#include <map>
#include <string>

namespace kk {
    
    namespace P {
     
        kk::Property parent(1,"parent");
        kk::Property firstChild(2,"firstChild");
        kk::Property lastChild(3,"lastChild");
        kk::Property nextSibling(4,"nextSibling");
        kk::Property prevSibling(5,"prevSibling");
        kk::Property name(6,"name");
        kk::Property id(7,"id");
        kk::Property document(8,"document");
        kk::Property rootElement(9,"rootElement");
        kk::Property element(10,"element");
        kk::Property cancelBubble(11,"cancelBubble");
        kk::Property asElement(12,"asElement");
        kk::Property actionType(13,"actionType");
        kk::Property size(14,"size");
        kk::Property position(15,"position");
        kk::Property transform(16,"transform");
        kk::Property opacity(17,"opacity");
        kk::Property current(18,"current");
        kk::Property speed(19,"speed");
        kk::Property count(20,"count");
        kk::Property paused(21,"paused");
        kk::Property duration(22,"duration");
        kk::Property app(23,"app");
        kk::Property path(24,"path");
        
        static kk::Property *_list[]={
            &parent,
            &firstChild,
            &lastChild,
            &nextSibling,
            &prevSibling,
            &name,
            &id,
            &document,
            &rootElement,
            &element,
            &cancelBubble,
            &asElement,
            &actionType,
            &size,
            &position,
            &transform,
            &opacity,
            NULL};
        
        static std::map<std::string,kk::Property*> _map;
        
        kk::Property * get(kk::CString name) {
            if(_map.size() == 0) {
                kk::Property ** p = _list;
                while(p && *p) {
                    _map[(*p)->name()] = *p;
                    p ++;
                }
            }
            std::map<std::string,kk::Property*>::iterator i = _map.find(name);
            if(i != _map.end()) {
                return i->second;
            }
            return NULL;
        }
        
        kk::Property ** list(kk::Int * length) {
            return _list;
        }
    }
    
    Property::Property(PropertyId pid,CString name):_name(name),_pid(pid) {
        
    }
    
    PropertyId Property::pid() {
        return _pid;
    }
    
    CString Property::name() {
        return _name;
    }
    
    VProperty::VProperty(Object * object,Property * property):_property(property),_object(object) {
        object->addProperty(this);
    }
    
    String VProperty::toString() {
        return "";
    }
    
    void VProperty::set(CString value) {
        
    }
    
    Property * VProperty::property() {
        return _property;
    }
    
    Object * VProperty::object() {
        return _object;
    }
    
    void VProperty::change() {
        _object->onChangeProperty(this);
    }
    
    IntProperty::IntProperty(Object * object,Property * property):TProperty<Int>(object,property) {
        _value = 0;
    }
    
    ScriptResult IntProperty::getScript() {
        ScriptContext context = _object->context();
        duk_push_int(context, TProperty<Int>::get());
        return 1;
    }
    
    ScriptResult IntProperty::setScript() {
        
        ScriptContext context = _object->context();
        
        if(duk_is_number(context, -1)) {
            set((Int) duk_to_number(context, -1));
        } else if(duk_is_boolean(context, -1)) {
            set((Int) duk_to_boolean(context, -1));
        } else if(duk_is_string(context, -1)) {
            set(atoi(duk_to_string(context, -1)));
        }
        
        return 0;
    }
    
    String IntProperty::toString() {
        std::strstream ss;
        ss << _value << std::ends;
        return ss.str();
    }
    
    void IntProperty::set(CString value) {
        _value = value ? atoi(value) : 0;
        change();
    }
    
    Int64Property::Int64Property(Object * object,Property * property):TProperty<Int64>(object,property) {
        _value = 0;
    }
    
    ScriptResult Int64Property::getScript() {
        ScriptContext context = _object->context();
        char b[255];
        snprintf(b, sizeof(b), "%lld",TProperty<Int64>::get());
        duk_push_string(context, b);
        return 1;
    }
    
    ScriptResult Int64Property::setScript() {
        
        ScriptContext context = _object->context();
        
        if(duk_is_number(context, -1)) {
            set((Int64) duk_to_number(context, -1));
        } else if(duk_is_boolean(context, -1)) {
            set((Int64) duk_to_boolean(context, -1));
        } else if(duk_is_string(context, -1)) {
            set(atoll(duk_to_string(context, -1)));
        }
        
        return 0;
    }
    
    String Int64Property::toString() {
        std::strstream ss;
        ss << _value << std::ends;
        return ss.str();
    }
    
    void Int64Property::set(CString value) {
        _value = value ? atoi(value) : 0;
        change();
    }
    
    BooleanProperty::BooleanProperty(Object * object,Property * property):TProperty<Boolean>(object,property) {
        _value = false;
    }
    
    ScriptResult BooleanProperty::getScript() {
        ScriptContext context = _object->context();
        duk_push_boolean(context, TProperty<Boolean>::get());
        return 1;
    }
    
    ScriptResult BooleanProperty::setScript() {
        
        ScriptContext context = _object->context();
        
        if(duk_is_number(context, -1)) {
            set(duk_to_number(context, -1)? true:false);
        } else if(duk_is_boolean(context, -1)) {
            set(duk_to_boolean(context, -1) ?true:false);
        } else if(duk_is_string(context, -1)) {
            CString v = duk_to_string(context, -1);
            if(strcmp(v, "true") == 0) {
                set(true);
            } else {
                set(false);
            }
        }
        
        return 0;
    }
    
    String BooleanProperty::toString() {
        return _value ? "true" : "false";
    }
    
    void BooleanProperty::set(CString value) {
        _value = CStringEqual(value, "true") ? true : false;
        change();
    }
    
    DoubleProperty::DoubleProperty(Object * object,Property * property):TProperty<Double>(object,property) {
        _value = 0.0;
    }
    
    ScriptResult DoubleProperty::getScript() {
        ScriptContext context = _object->context();
        duk_push_number(context, TProperty<Double>::get());
        return 1;
    }
    
    ScriptResult DoubleProperty::setScript() {
        
        ScriptContext context = _object->context();
        
        if(duk_is_number(context, -1)) {
            set((Double) duk_to_number(context, -1));
        } else if(duk_is_boolean(context, -1)) {
            set((Double) duk_to_boolean(context, -1));
        } else if(duk_is_string(context, -1)) {
            set(atof(duk_to_string(context, -1)));
        }
        
        return 0;
    }
    
    String DoubleProperty::toString() {
        std::strstream ss;
        ss << _value << std::ends;
        return ss.str();
    }
    
    void DoubleProperty::set(CString value) {
        _value = value ? atof(value) : 0;
        change();
    }
    
    FloatProperty::FloatProperty(Object * object,Property * property):TProperty<Float>(object,property) {
        _value = 0.0;
    }
    
    ScriptResult FloatProperty::getScript() {
        ScriptContext context = _object->context();
        duk_push_number(context, TProperty<Float>::get());
        return 1;
    }
    
    ScriptResult FloatProperty::setScript() {
        
        ScriptContext context = _object->context();
        
        if(duk_is_number(context, -1)) {
            set((Float) duk_to_number(context, -1));
        } else if(duk_is_boolean(context, -1)) {
            set((Float) duk_to_boolean(context, -1));
        } else if(duk_is_string(context, -1)) {
            set((Float) atof(duk_to_string(context, -1)));
        }
        
        return 0;
    }
    
    String FloatProperty::toString() {
        std::strstream ss;
        ss << _value << std::ends;
        return ss.str();
    }
    
    void FloatProperty::set(CString value) {
        _value = value ? atof(value) : 0;
        change();
    }
    
    StringProperty::StringProperty(Object * object,Property * property):VProperty(object,property) {
        
    }
    
    ScriptResult StringProperty::getScript() {
        ScriptContext context = _object->context();
        duk_push_string(context, _value.c_str());
        return 1;
    }
    
    ScriptResult StringProperty::setScript() {
        ScriptContext context = _object->context();
        if(duk_is_string(context, -1)) {
            _value = duk_to_string(context, -1);
        }
        return 0;
    }
    
    String StringProperty::toString() {
        return _value;
    }
    
    StrongProperty::StrongProperty(Object * object,Property * property):TProperty<kk::Object *>(object,property) {
        _value = NULL;
    }
    
    StrongProperty::~StrongProperty() {
        if(_value != NULL) {
            _value->unweak(&_value);
        }
    }
    
    ScriptResult StrongProperty::getScript() {
        ScriptContext context = _object->context();
        ScriptPushObject(context,TProperty<Object *>::get());
        return 1;
    }
    
    ScriptResult StrongProperty::setScript() {
        ScriptContext context = _object->context();
        set(ScriptGetObject(context, -1));
        return 0;
    }
    
    void StrongProperty::set(Object * value) {
        
        ScriptContext context = _object->context();
        
        if(_value != value) {
            
            if(_value != NULL) {
                _value->unweak(&_value);
            }
            
            _value = value;
            
            if(_value) {
                _value->weak(&_value);
            }
            
            ScriptPushObject(context, object());
            
            duk_push_sprintf(context, "_%s",property()->name());
            ScriptPushObject(context,value);
            duk_put_prop(context, -3);
            
            duk_pop(context);
            
        }
        
    }
    
    String StrongProperty::toString() {
        if(_value != NULL) {
            return _value->toString();
        }
        return "";
    }
    
    void StrongProperty::set(CString value) {

    }
    
    WeakProperty::WeakProperty(Object * object,Property * property):TProperty<kk::Object *>(object,property) {
        _value = NULL;
    }
    
    WeakProperty::~WeakProperty() {
        if(_value != NULL) {
            _value->unweak(&_value);
        }
    }
    
    ScriptResult WeakProperty::getScript() {
        ScriptContext context = _object->context();
        ScriptPushObject(context,TProperty<Object *>::get());
        return 1;
    }
    
    ScriptResult WeakProperty::setScript() {
        ScriptContext context = _object->context();
        set(ScriptGetObject(context, -1));
        return 0;
    }
    
    void WeakProperty::set(Object * value) {
        
        if(_value != value) {
            
            if(_value != NULL) {
                _value->unweak(&_value);
            }
            
            _value = value;
            
            if(_value) {
                _value->weak(&_value);
            }
        }
        
    }
    
    String WeakProperty::toString() {
        if(_value != NULL) {
            return _value->toString();
        }
        return "";
    }
    
    void WeakProperty::set(CString value) {
        
    }
    
}
