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
    
    namespace named {
     
        kk::Named parent(1,"parent");
        kk::Named firstChild(2,"firstChild");
        kk::Named lastChild(3,"lastChild");
        kk::Named nextSibling(4,"nextSibling");
        kk::Named prevSibling(5,"prevSibling");
        kk::Named name(6,"name");
        kk::Named id(7,"id");
        kk::Named document(8,"document");
        kk::Named rootElement(9,"rootElement");
        kk::Named element(10,"element");
        kk::Named cancelBubble(11,"cancelBubble");
        kk::Named asElement(12,"asElement");
        kk::Named actionType(13,"actionType");
        kk::Named size(14,"size");
        kk::Named position(15,"position");
        kk::Named transform(16,"transform");
        kk::Named opacity(17,"opacity");
        kk::Named current(18,"current");
        kk::Named speed(19,"speed");
        kk::Named count(20,"count");
        kk::Named paused(21,"paused");
        kk::Named duration(22,"duration");
        kk::Named app(23,"app");
        kk::Named path(24,"path");
        kk::Named anchor(25,"anchor");
        kk::Named width(26,"width");
        kk::Named height(27,"height");
        kk::Named startTime(28,"startTime");
        kk::Named scale(29,"scale");
        kk::Named maxWidth(30,"maxWidth");
        kk::Named text(31,"text");
        kk::Named fontFamily(32,"fontFamily");
        kk::Named color(33,"color");
        kk::Named fontSize(34,"fontSize");
        kk::Named layout(35,"layout");
        kk::Named contentSize(36,"contentSize");
        kk::Named left(37,"left");
        kk::Named top(38,"top");
        kk::Named right(39,"right");
        kk::Named bottom(40,"bottom");
        kk::Named margin(41,"margin");
        kk::Named padding(42,"padding");
        kk::Named minWidth(43,"minWidth");
        kk::Named minHeight(44,"minHeight");
        kk::Named maxHeight(45,"maxHeight");
        
        static kk::Named *_list[]={
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
            &current,
            &speed,
            &count,
            &paused,
            &duration,
            &app,
            &path,
            &anchor,
            &width,
            &height,
            &startTime,
            &scale,
            &maxWidth,
            &text,
            &fontFamily,
            &color,
            &fontSize,
            &layout,
            &contentSize,
            &left,
            &top,
            &right,
            &bottom,
            &margin,
            &padding,
            &minWidth,
            &minHeight,
            &maxHeight,
            NULL};
        
        static std::map<std::string,kk::Named*> _map;
        
        kk::Named * get(kk::CString name) {
            if(_map.size() == 0) {
                kk::Named ** p = _list;
                while(p && *p) {
                    _map[(*p)->name()] = *p;
                    p ++;
                }
            }
            std::map<std::string,kk::Named*>::iterator i = _map.find(name);
            if(i != _map.end()) {
                return i->second;
            }
            return NULL;
        }
        
        kk::Named ** list(kk::Int * length) {
            return _list;
        }
    }
    
    Named::Named(Id id,CString name):_id(id),_name(name) {
        
    }
    
    Id Named::id() {
        return _id;
    }
    
    CString Named::name() {
        return _name;
    }
    
    Property::Property(Named * name) :_name(name),_title(NULL) {
        
    }
    
    Property::Property(Named * name,CString title) :_name(name),_title(title) {
        
    }
    
    Named * Property::name() {
        return _name;
    }
    
    CString Property::title() {
        return _title;
    }
    
    void Property::change(Object * object) {
        object->change(this);
    }
    
    IntProperty::IntProperty(Named * name, Getter getter, Setter setter):TProperty<Int>(name,getter,setter) {
        
    }
    
    IntProperty::IntProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<Int>(name,getter,setter,title) {
        
    }
    
    static ScriptResult IntPropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        IntProperty * p = (IntProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_int(ctx, p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult IntPropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        IntProperty * p = (IntProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    p->set(v, duk_to_int(ctx, -nargs));
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs));
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, atoi(duk_to_string(ctx, -nargs)));
                }
            } else {
                p->set(v, 0);
            }
        }
        
        return 0;
    }
    
    void IntProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, IntPropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, IntPropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
    UintProperty::UintProperty(Named * name, Getter getter, Setter setter):TProperty<Uint>(name,getter,setter) {
        
    }
    
    UintProperty::UintProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<Uint>(name,getter,setter,title) {
        
    }
    
    static ScriptResult UintPropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        UintProperty * p = (UintProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_uint(ctx, p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult UintPropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        UintProperty * p = (UintProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    p->set(v, duk_to_int(ctx, -nargs));
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs));
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, atoi(duk_to_string(ctx, -nargs)));
                }
            } else {
                p->set(v, 0);
            }
        }
        
        return 0;
    }
    
    void UintProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, UintPropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, UintPropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
    Int64Property::Int64Property(Named * name, Getter getter, Setter setter):TProperty<Int64>(name,getter,setter) {
        
    }
    
    Int64Property::Int64Property(Named * name, Getter getter, Setter setter,CString title):TProperty<Int64>(name,getter,setter,title) {
        
    }
    
    static ScriptResult Int64PropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        Int64Property * p = (Int64Property *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_sprintf(ctx,"%lld", p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult Int64PropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        Int64Property * p = (Int64Property *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    p->set(v, duk_to_int(ctx, -nargs));
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs));
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, atoll(duk_to_string(ctx, -nargs)));
                }
            } else {
                p->set(v, 0);
            }
        }
        
        return 0;
    }
    
    void Int64Property::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, Int64PropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, Int64PropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
    BooleanProperty::BooleanProperty(Named * name, Getter getter, Setter setter):TProperty<Boolean>(name,getter,setter) {
        
    }
    
    BooleanProperty::BooleanProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<Boolean>(name,getter,setter,title) {
        
    }
    
    static ScriptResult BooleanPropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        BooleanProperty * p = (BooleanProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_boolean(ctx,p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult BooleanPropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        BooleanProperty * p = (BooleanProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    p->set(v, duk_to_number(ctx, -nargs) != 0);
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs));
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, strcmp(duk_to_string(ctx, -nargs),"true") == 0);
                }
            } else {
                p->set(v, false);
            }
        }
        
        return 0;
    }
    
    void BooleanProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, BooleanPropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, BooleanPropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
    FloatProperty::FloatProperty(Named * name, Getter getter, Setter setter):TProperty<Float>(name,getter,setter) {
        
    }
    
    FloatProperty::FloatProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<Float>(name,getter,setter,title) {
        
    }
    
    static ScriptResult FloatPropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        FloatProperty * p = (FloatProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_number(ctx,p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult FloatPropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        FloatProperty * p = (FloatProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    p->set(v, duk_to_number(ctx, -nargs));
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs));
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, atof(duk_to_string(ctx, -nargs)));
                }
            } else {
                p->set(v, false);
            }
        }
        
        return 0;
    }
    
    void FloatProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, FloatPropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        if(_setter != NULL) {
            duk_push_c_function(ctx, FloatPropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        } else {
            duk_def_prop(ctx,
                         -3,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        }
    }
    
    DoubleProperty::DoubleProperty(Named * name, Getter getter, Setter setter):TProperty<Double>(name,getter,setter) {
        
    }
    
    DoubleProperty::DoubleProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<Double>(name,getter,setter,title) {
        
    }
    
    static ScriptResult DoublePropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        DoubleProperty * p = (DoubleProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_number(ctx,p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult DoublePropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        DoubleProperty * p = (DoubleProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    p->set(v, duk_to_number(ctx, -nargs));
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs));
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, atof(duk_to_string(ctx, -nargs)));
                }
            } else {
                p->set(v, false);
            }
        }
        
        return 0;
    }
    
    void DoubleProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, DoublePropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, DoublePropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
    StringProperty::StringProperty(Named * name, Getter getter, Setter setter):TProperty<CString>(name,getter,setter) {
        
    }
    
    StringProperty::StringProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<CString>(name,getter,setter,title) {
        
    }
    
    static ScriptResult StringPropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        StringProperty * p = (StringProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            duk_push_string(ctx,p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult StringPropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        StringProperty * p = (StringProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 ) {
                if(duk_is_number(ctx, -nargs)) {
                    char b[255];
                    snprintf(b, sizeof(b), "%g",duk_to_number(ctx, -nargs));
                    p->set(v, b);
                } else if(duk_is_boolean(ctx, -nargs)) {
                    p->set(v, duk_to_boolean(ctx, -nargs) ? "true":"false");
                } else if(duk_is_string(ctx, -nargs)) {
                    p->set(v, duk_to_string(ctx, -nargs));
                }
            } else {
                p->set(v, "");
            }
        }
        
        return 0;
    }
    
    void StringProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, StringPropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, StringPropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
    ObjectProperty::ObjectProperty(Named * name, Getter getter, Setter setter):TProperty<Object *>(name,getter,setter) {
        
    }
    
    ObjectProperty::ObjectProperty(Named * name, Getter getter, Setter setter,CString title):TProperty<Object *>(name,getter,setter,title) {
        
    }
    
    static ScriptResult ObjectPropertyGetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        ObjectProperty * p = (ObjectProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p){
            ScriptPushObject(ctx, p->get(v));
        } else {
            duk_push_undefined(ctx);
        }
        
        return 1;
    }
    
    static ScriptResult ObjectPropertySetFunc(ScriptContext ctx) {
        
        duk_push_this(ctx);
        
        Object * v = ScriptGetObject(ctx, -1);
        
        duk_pop(ctx);
        
        duk_push_current_function(ctx);
        
        duk_get_prop_string(ctx, -1, "property");
        
        ObjectProperty * p = (ObjectProperty *) duk_get_pointer(ctx, -1);
        
        duk_pop_n(ctx, 2);
        
        if(v && p) {
            
            int nargs = duk_get_top(ctx);
            
            if(nargs >0 && duk_is_object(ctx, -nargs)) {
                p->set(v, ScriptGetObject(ctx, -nargs));
            } else {
                p->set(v, NULL);
            }
        }
        
        return 0;
    }
    
    void ObjectProperty::def(ScriptContext ctx) {
        
        duk_push_string(ctx, _name->name());
        
        duk_push_c_function(ctx, ObjectPropertyGetFunc, 0);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_push_c_function(ctx, ObjectPropertySetFunc, 1);
        duk_push_string(ctx, "property");
        duk_push_pointer(ctx, this);
        duk_put_prop(ctx, -3);
        
        duk_def_prop(ctx,
                     -4,
                     DUK_DEFPROP_HAVE_GETTER |
                     DUK_DEFPROP_HAVE_SETTER |
                     DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
        
    }
    
}
