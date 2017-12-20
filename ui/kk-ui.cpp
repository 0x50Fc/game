//
//  kk-ui.cpp
//  KKGame
//
//  Created by hailong11 on 2017/12/18.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-ui.h"

namespace kk {
    
    namespace ui {
        
        PixelProperty::PixelProperty(Named * name, Getter getter, Setter setter)
            :kk::TProperty<Pixel&>(name,getter,setter){
            
        }
        
        static ScriptResult PixelPropertyGetFunc(ScriptContext ctx) {
            
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
        
        static ScriptResult PixelPropertySetFunc(ScriptContext ctx) {
            
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
        
        void PixelProperty::def(ScriptContext ctx) {
            
            duk_push_string(ctx, _name->name());
            
            duk_push_c_function(ctx, PixelPropertyGetFunc, 0);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_push_c_function(ctx, PixelPropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
            
        }
        
        
        EdgeProperty::EdgeProperty(Named * name, Getter getter, Setter setter)
            :kk::TProperty<Edge&>(name,getter,setter){
            
        }
        
        static ScriptResult EdgePropertyGetFunc(ScriptContext ctx) {
            
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
        
        static ScriptResult EdgePropertySetFunc(ScriptContext ctx) {
            
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
        
        void EdgeProperty::def(ScriptContext ctx) {
            
            duk_push_string(ctx, _name->name());
            
            duk_push_c_function(ctx, EdgePropertyGetFunc, 0);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_push_c_function(ctx, EdgePropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
            
        }
        
        
        
        kk::Float UIDocument::pixel(Pixel& v,kk::Float baseValue,kk::Float defaultValue) {
            switch (v.type) {
                case PixelTypeAuto:
                    break;
                case PixelTypePercent:
                    return v.value * baseValue * 0.01;
                default:
                    std::map<PixelType,kk::Float>::iterator i = _pixelTypeScales.find(v.type);
                    if(i != _pixelTypeScales.end()) {
                        return v.value * i->second;
                    }
                    return v.value;
                    break;
            }
            return defaultValue;
        }
        
        void UIDocument::setPixelScale(PixelType type,kk::Float scale) {
            _pixelTypeScales[type] = scale;
        }
        
        void UIDocument::init() {
            kk::Document::init();
        }
        
        IMP_CLASS(UIDocument, kk::Document, NULL, NULL);
        
        void UIElement::begin(UITouch * touch) {
            
        }
        
        void UIElement::moved(UITouch * touch) {
            
        }
        
        void UIElement::end(UITouch * touch) {
            
        }
        
        void UIElement::canceled(UITouch * touch) {
            
        }
        
        kk::Float UIElement::pixel(Pixel& v,kk::Float baseValue,kk::Float defaultValue) {
            UIDocument * doc = dynamic_cast<UIDocument* >(document());
            if(doc) {
                return doc->pixel(v, baseValue, defaultValue);
            }
            switch (v.type) {
                case PixelTypeAuto:
                    break;
                case PixelTypePercent:
                    return v.value * baseValue * 0.01;
                default:
                    return v.value;
                    break;
            }
            return defaultValue;
        }
        
        kk::CString UIElement::layout() {
//            if(_layout == UILayoutRelative) {
//                return "relative";
//            }
//            if(_layout == UILayoutFlex) {
//                return "flex";
//            }
//            if(_layout == UILayoutHorizontal) {
//                return "horizontal";
//            }
            return "";
        }
        
        void UIElement::setLayout(kk::CString name) {
//            if(kk::CStringEqual(name, "relative")) {
//                _layout = UILayoutRelative;
//            } else if(kk::CStringEqual(name, "flex")) {
//                _layout = UILayoutFlex;
//            } else if(kk::CStringEqual(name, "horizontal")) {
//                _layout = UILayoutHorizontal;
//            } else {
//                _layout = NULL;
//            }
        }
        
        void UIElement::setLayout(UILayout layout) {
            _layout = layout;
        }
        
        void UIElement::init() {
            kk::gl::GLElement::init();
            _layout = NULL;
            _size = kk::gl::vec2(0);
            _contentSize = kk::gl::vec2(0);
            _anchor = kk::gl::vec2(0.5,0.5);
            
        }
        
        kk::gl::vec2& UIElement::size() {
            return _size;
        }
        
        void UIElement::setSize(kk::gl::vec2& v) {
            _size = v;
        }
        
        kk::gl::vec2& UIElement::contentSize() {
            return _contentSize;
        }
        
        void UIElement::setContentSize(kk::gl::vec2& v) {
            _contentSize = v;
        }
        
        Pixel& UIElement::width() {
            return _width;
        }
        
        void UIElement::setWidth(Pixel&v) {
            _width = v;
        }
        
        Pixel& UIElement::height() {
            return _height;
        }
        
        void UIElement::setHeight(Pixel&v) {
            _height = v;
        }
        
        Pixel& UIElement::minWidth() {
            return _minWidth;
        }
        
        void UIElement::setMinWidth(Pixel&v) {
            _minWidth = v;
        }
        
        Pixel& UIElement::maxWidth() {
            return _maxWidth;
        }
        
        void UIElement::setMaxWidth(Pixel&v) {
            _maxWidth = v;
        }
        
        Pixel& UIElement::minHeight() {
            return _minHeight;
        }
        
        void UIElement::setMinHeight(Pixel&v) {
            _minHeight = v;
        }
        
        Pixel& UIElement::maxHeight() {
            return _maxHeight;
        }
        
        void UIElement::setMaxHeight(Pixel&v) {
            _maxHeight = v;
        }
        
        kk::gl::vec2& UIElement::anchor() {
            return _anchor;
        }
        
        void UIElement::setAnchor(kk::gl::vec2& v) {
            _anchor = v;
        }
        
        Edge& UIElement::margin(){
            return _margin;
        }
        
        void UIElement::setMargin(Edge&v) {
            _margin = v;
        }
        
        Edge& UIElement::padding() {
            return _padding;
        }
        
        void UIElement::setPadding(Edge&v) {
            _padding = v;
        }
        
        Pixel& UIElement::left() {
            return _left;
        }
        
        void UIElement::setLeft(Pixel&v) {
            _left = v;
        }
        
        Pixel& UIElement::top() {
            return _top;
        }
        
        void UIElement::setTop(Pixel&v) {
            _top = v;
        }
        
        Pixel& UIElement::right() {
            return _right;
        }
        
        void UIElement::setRight(Pixel&v) {
            _right = v;
        }
        
        Pixel& UIElement::bottom() {
            return _bottom;
        }
        
        void UIElement::setBottom(Pixel&v) {
            _bottom = v;
        }
        
        void UIElement::layoutChildren() {
            if(_layout) {
                _contentSize = _layout(this);
            } else {
                _contentSize = _size;
            }
        }
        
        kk::StringProperty UIElement::Property_layout(&kk::named::layout,(kk::StringProperty::Getter) &UIElement::layout,(kk::StringProperty::Setter) &UIElement::setLayout);
        
        kk::gl::Vec2Property UIElement::Property_size(&kk::named::size,(kk::gl::Vec2Property::Getter) &UIElement::size,(kk::gl::Vec2Property::Setter) &UIElement::setSize);
        
        kk::gl::Vec2Property UIElement::Property_contentSize(&kk::named::contentSize,(kk::gl::Vec2Property::Getter) &UIElement::contentSize,(kk::gl::Vec2Property::Setter) &UIElement::setContentSize);
        
        PixelProperty UIElement::Property_left(&kk::named::left,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        PixelProperty UIElement::Property_top(&kk::named::top,(PixelProperty::Getter) &UIElement::top,(PixelProperty::Setter) &UIElement::setTop);
        PixelProperty UIElement::Property_right(&kk::named::right,(PixelProperty::Getter) &UIElement::right,(PixelProperty::Setter) &UIElement::setRight);
        PixelProperty UIElement::Property_bottom(&kk::named::bottom,(PixelProperty::Getter) &UIElement::bottom,(PixelProperty::Setter) &UIElement::setBottom);
        EdgeProperty UIElement::Property_margin(&kk::named::margin,(EdgeProperty::Getter) &UIElement::margin,(EdgeProperty::Setter) &UIElement::setMargin);
        EdgeProperty UIElement::Property_padding(&kk::named::padding,(EdgeProperty::Getter) &UIElement::padding,(EdgeProperty::Setter) &UIElement::setPadding);
        
        PixelProperty Property_width(&kk::named::width,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        PixelProperty Property_height(&kk::named::height,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        PixelProperty Property_minWidth(&kk::named::minWidth,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        PixelProperty Property_maxWidth(&kk::named::left,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        PixelProperty Property_minHeight(&kk::named::left,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        PixelProperty Property_maxHeight(&kk::named::left,(PixelProperty::Getter) &UIElement::left,(PixelProperty::Setter) &UIElement::setLeft);
        
        kk::Property *UIElement::Propertys[] = {
            &UIElement::Property_layout,
            &UIElement::Property_size,
            &UIElement::Property_contentSize,
            &UIElement::Property_left,
            &UIElement::Property_top,
            &UIElement::Property_right,
            &UIElement::Property_bottom,
            &UIElement::Property_margin,
            &UIElement::Property_padding,
            NULL
        };
        
        void UIElement::onDraw(kk::gl::GLContext * ctx) {
            kk::gl::GLElement::onDraw(ctx);
        }
        
        /**
         * 相对布局 "relative"
         */
        /*
        kk::gl::vec2 UILayoutRelative(UIElement * element) {
            
            kk::gl::vec2 size = element->size();
            Edge &padding = element->padding();
            kk::Float paddingLeft = element->pixel(padding.left, size.x, 0);
            kk::Float paddingRight = element->pixel(padding.right, size.x, 0);
            kk::Float paddingTop = element->pixel(padding.top, size.y, 0);
            kk::Float paddingBottom = element->pixel(padding.bottom, size.y, 0);
            kk::gl::vec2 inSize(size.x - paddingLeft - paddingRight,size.y - paddingTop - paddingBottom);
            
            kk::gl::vec2 contentSize(0);
            
            kk::Element * p = element->firstChild();
            
            while(p) {
                
                UIElement * e = dynamic_cast<UIElement *>(p);
                
                if(e) {
                    
                    kk::Float width = e->pixel(e->width(), inSize.x, FLOAT_MAX);
                    kk::Float height = e->pixel(e->height(), inSize.y, FLOAT_MAX);
                    
                    if(width == FLOAT_MAX || height == FLOAT_MAX) {
                        
                        kk::gl::vec2 &v = e->size();
                        
                        v.x = width;
                        v.y = height;
                        
                        e->layoutChildren();
                        
                        if(width == FLOAT_MAX) {
                            width = v.x = e->contentSize().x;
                            kk::Float min = e->pixel(e->minWidth(), inSize.x, 0);
                            kk::Float max = e->pixel(e->maxWidth(), inSize.y, FLOAT_MAX);
                            if(v.x < min) {
                                width = v.x = min;
                            }
                            if(v.x > max) {
                                width = v.x = max;
                            }
                        }
                        
                        if(height == FLOAT_MAX) {
                            height = v.y = e->contentSize().y;
                            kk::Float min = e->pixel(e->minHeight(), inSize.x, 0);
                            kk::Float max = e->pixel(e->maxHeight(), inSize.y, FLOAT_MAX);
                            if(v.y < min) {
                                height = v.y = min;
                            }
                            if(v.y > max) {
                                height = v.y = max;
                            }
                        }
                    }
                
                    kk::Float left = e->pixel(e->left(), inSize.x, FLOAT_MAX);
                    kk::Float right = e->pixel(e->right(), inSize.x, FLOAT_MAX);
                    kk::Float top = e->pixel(e->top(), inSize.y, FLOAT_MAX);
                    kk::Float bottom = e->pixel(e->bottom(), inSize.y, FLOAT_MAX);
                    
                    kk::Float mleft = e->pixel(e->margin().left, inSize.x, FLOAT_MAX);
                    kk::Float mright = e->pixel(e->margin().right, inSize.x, FLOAT_MAX);
                    kk::Float mtop = e->pixel(e->margin().top, inSize.y, FLOAT_MAX);
                    kk::Float mbottom = e->pixel(e->margin().bottom, inSize.y, FLOAT_MAX);
                    
                    if(left == FLOAT_MAX) {
                        
                        if(right == FLOAT_MAX) {
                            left = paddingLeft + mleft + (inSize.x - width - mleft - mright) * 0.5f;
                        } else {
                            left = paddingLeft + (inSize.x - right - mright);
                        }
                        
                    }
                    
                    if(top == FLOAT_MAX) {
                        
                        if(bottom == FLOAT_MAX) {
                            top = paddingTop + mtop + (inSize.y - height - mtop - mbottom) * 0.5f;
                        } else {
                            top = paddingTop + (inSize.y - height - mbottom);
                        }
                        
                    }
                    
                    kk::gl::vec3 &loc = e->position();
                    kk::gl::vec2 &anchor = e->anchor();
                    
                    loc.x = left + anchor.x * width;
                    loc.y = top + anchor.y * height;
                    
                    if(left + paddingRight + mright > contentSize.x) {
                        contentSize.x = left + paddingRight + mright;
                    }
                    
                    if(top + paddingBottom + mbottom > contentSize.y) {
                        contentSize.y = top + paddingBottom + mbottom;
                    }
                }
                
                p = p->nextSibling();
            }
            
            return contentSize;
        }
        */
        
        /**
         * 流式布局 "flex" 左到右 上到下
         */
        /*
        kk::gl::vec2 UILayoutFlex(UIElement * element) {
            
            kk::gl::vec2 size = element->size();
            Edge &padding = element->padding();
            kk::Float paddingLeft = element->pixel(padding.left, size.x, 0);
            kk::Float paddingRight = element->pixel(padding.right, size.x, 0);
            kk::Float paddingTop = element->pixel(padding.top, size.y, 0);
            kk::Float paddingBottom = element->pixel(padding.bottom, size.y, 0);
            kk::gl::vec2 inSize(size.x - paddingLeft - paddingRight,size.y - paddingTop - paddingBottom);
            
            kk::gl::vec2 contentSize(0);
            
            kk::Float y = paddingTop;
            kk::Float x = paddingLeft;
            kk::Float maxWidth = paddingLeft + paddingRight;
            kk::Float lineHeight = 0;
            
            kk::Element * p = element->firstChild();
            
            while(p) {
                
                UIElement * e = dynamic_cast<UIElement *>(p);
                
                if(e) {
                    
                    kk::Float width = e->pixel(e->width(), inSize.x, FLOAT_MAX);
                    kk::Float height = e->pixel(e->height(), inSize.y, FLOAT_MAX);
                    
                    if(width == FLOAT_MAX || height == FLOAT_MAX) {
                        
                        kk::gl::vec2 &v = e->size();
                        
                        v.x = width;
                        v.y = height;
                        
                        e->layoutChildren();
                        
                        if(width == FLOAT_MAX) {
                            width = v.x = e->contentSize().x;
                            kk::Float min = e->pixel(e->minWidth(), inSize.x, 0);
                            kk::Float max = e->pixel(e->maxWidth(), inSize.y, FLOAT_MAX);
                            if(v.x < min) {
                                width = v.x = min;
                            }
                            if(v.x > max) {
                                width = v.x = max;
                            }
                        }
                        
                        if(height == FLOAT_MAX) {
                            height = v.y = e->contentSize().y;
                            kk::Float min = e->pixel(e->minHeight(), inSize.x, 0);
                            kk::Float max = e->pixel(e->maxHeight(), inSize.y, FLOAT_MAX);
                            if(v.y < min) {
                                height = v.y = min;
                            }
                            if(v.y > max) {
                                height = v.y = max;
                            }
                        }
                    }
                    
                    kk::Float mleft = e->pixel(e->margin().left, inSize.x, FLOAT_MAX);
                    kk::Float mright = e->pixel(e->margin().right, inSize.x, FLOAT_MAX);
                    kk::Float mtop = e->pixel(e->margin().top, inSize.y, FLOAT_MAX);
                    kk::Float mbottom = e->pixel(e->margin().bottom, inSize.y, FLOAT_MAX);
                    
                    if(x + mleft + mright + paddingRight > size.x) {
                        y += lineHeight;
                        lineHeight = 0;
                        x = paddingLeft;
                    }
                    
                    kk::Float left = x + mleft;
                    kk::Float top = y + mtop;
                    
                    x += width + mleft + mright;
                    
                    if(lineHeight < height + mtop + mbottom) {
                        lineHeight = height + mtop + mbottom;
                    }
                    
                    kk::gl::vec3 &loc = e->position();
                    kk::gl::vec2 &anchor = e->anchor();
                    
                    loc.x = left + anchor.x * width;
                    loc.y = top + anchor.y * height;
                    
                    if(left + paddingRight + mright > maxWidth) {
                        maxWidth = left + paddingRight + mright;
                    }
                    
                }
                
                p = p->nextSibling();
            }
            
            return kk::gl::vec2(maxWidth,y + lineHeight + paddingBottom);
        }
        */
        
        /**
         * 水平布局 "horizontal" 左到右
         */
        /*
        kk::gl::vec2 UILayoutHorizontal(UIElement * element) {
            kk::gl::vec2 size = element->size();
            Edge &padding = element->padding();
            kk::Float paddingLeft = element->pixel(padding.left, size.x, 0);
            kk::Float paddingRight = element->pixel(padding.right, size.x, 0);
            kk::Float paddingTop = element->pixel(padding.top, size.y, 0);
            kk::Float paddingBottom = element->pixel(padding.bottom, size.y, 0);
            kk::gl::vec2 inSize(size.x - paddingLeft - paddingRight,size.y - paddingTop - paddingBottom);
            
            kk::gl::vec2 contentSize(0);
            
            kk::Float y = paddingTop;
            kk::Float x = paddingLeft;
            kk::Float maxWidth = paddingLeft + paddingRight;
            kk::Float lineHeight = 0;
            
            kk::Element * p = element->firstChild();
            
            while(p) {
                
                UIElement * e = dynamic_cast<UIElement *>(p);
                
                if(e) {
                    
                    kk::Float width = e->pixel(e->width(), inSize.x, FLOAT_MAX);
                    kk::Float height = e->pixel(e->height(), inSize.y, FLOAT_MAX);
                    
                    if(width == FLOAT_MAX || height == FLOAT_MAX) {
                        
                        kk::gl::vec2 &v = e->size();
                        
                        v.x = width;
                        v.y = height;
                        
                        e->layoutChildren();
                        
                        if(width == FLOAT_MAX) {
                            width = v.x = e->contentSize().x;
                            kk::Float min = e->pixel(e->minWidth(), inSize.x, 0);
                            kk::Float max = e->pixel(e->maxWidth(), inSize.y, FLOAT_MAX);
                            if(v.x < min) {
                                width = v.x = min;
                            }
                            if(v.x > max) {
                                width = v.x = max;
                            }
                        }
                        
                        if(height == FLOAT_MAX) {
                            height = v.y = e->contentSize().y;
                            kk::Float min = e->pixel(e->minHeight(), inSize.x, 0);
                            kk::Float max = e->pixel(e->maxHeight(), inSize.y, FLOAT_MAX);
                            if(v.y < min) {
                                height = v.y = min;
                            }
                            if(v.y > max) {
                                height = v.y = max;
                            }
                        }
                    }
                    
                    kk::Float mleft = e->pixel(e->margin().left, inSize.x, FLOAT_MAX);
                    kk::Float mright = e->pixel(e->margin().right, inSize.x, FLOAT_MAX);
                    kk::Float mtop = e->pixel(e->margin().top, inSize.y, FLOAT_MAX);
                    kk::Float mbottom = e->pixel(e->margin().bottom, inSize.y, FLOAT_MAX);
                    
                    kk::Float left = x + mleft;
                    kk::Float top = y + mtop;
                    
                    x += width + mleft + mright;
                    
                    if(lineHeight < height + mtop + mbottom) {
                        lineHeight = height + mtop + mbottom;
                    }
                    
                    kk::gl::vec3 &loc = e->position();
                    kk::gl::vec2 &anchor = e->anchor();
                    
                    loc.x = left + anchor.x * width;
                    loc.y = top + anchor.y * height;
                    
                    if(left + paddingRight + mright > maxWidth) {
                        maxWidth = left + paddingRight + mright;
                    }
                    
                }
                
                p = p->nextSibling();
            }
            
            return kk::gl::vec2(maxWidth,y + lineHeight + paddingBottom);
        }
         */
    }
    
}
