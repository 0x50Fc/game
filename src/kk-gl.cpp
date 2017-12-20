//
//  kk-gl.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-gl.h"

#ifdef __APPLE__

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#endif

namespace kk {
    
    namespace gl {
        
        Vec4Property::Vec4Property(Named * name, Getter getter, Setter setter):TProperty<vec4&>(name,getter,setter) {
            
        }
        
        static ScriptResult Vec4PropertyGetFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            Object * v = ScriptGetObject(ctx, -1);
            
            duk_pop(ctx);
            
            duk_push_current_function(ctx);
            
            duk_get_prop_string(ctx, -1, "property");
            
            Vec4Property * p = (Vec4Property *) duk_get_pointer(ctx, -1);
            
            duk_pop_n(ctx, 2);
            
            if(v && p){
                vec4& vv = p->get(v);
                duk_push_array(ctx);
                
                duk_push_number(ctx, vv.x);
                duk_put_prop_index(ctx, -3, 0);
                
                duk_push_number(ctx, vv.y);
                duk_put_prop_index(ctx, -3, 1);
                
                duk_push_number(ctx, vv.z);
                duk_put_prop_index(ctx, -3, 2);
                
                duk_push_number(ctx, vv.w);
                duk_put_prop_index(ctx, -3, 3);
                
            } else {
                duk_push_undefined(ctx);
            }
            
            return 1;
        }
        
        static ScriptResult Vec4PropertySetFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            Object * v = ScriptGetObject(ctx, -1);
            
            duk_pop(ctx);
            
            duk_push_current_function(ctx);
            
            duk_get_prop_string(ctx, -1, "property");
            
            Vec4Property * p = (Vec4Property *) duk_get_pointer(ctx, -1);
            
            duk_pop_n(ctx, 2);
            
            if(v && p) {
                
                int nargs = duk_get_top(ctx);
                
                if(nargs >0 && duk_is_array(ctx, -nargs) ) {
                    vec4 vv(0);
                    
                    duk_size_t n = duk_get_length(ctx, -nargs);
                    
                    if(n > 0) {
                        duk_get_prop_index(ctx, -nargs, 0);
                        vv.x = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    if(n > 1) {
                        duk_get_prop_index(ctx, -nargs, 1);
                        vv.y = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    if(n > 2) {
                        duk_get_prop_index(ctx, -nargs, 2);
                        vv.z = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    if(n > 3) {
                        duk_get_prop_index(ctx, -nargs, 3);
                        vv.w = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    p->set(v,vv);
                } else {
                    vec4 vv(0);
                    p->set(v, vv);
                }
            }
            
            return 0;
        }
        
        void Vec4Property::def(ScriptContext ctx) {
            
            duk_push_string(ctx, _name->name());
            
            duk_push_c_function(ctx, Vec4PropertyGetFunc, 0);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_push_c_function(ctx, Vec4PropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
            
        }
        
        Vec3Property::Vec3Property(Named * name, Getter getter, Setter setter):TProperty<vec3&>(name,getter,setter) {
            
        }
        
        static ScriptResult Vec3PropertyGetFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            Object * v = ScriptGetObject(ctx, -1);
            
            duk_pop(ctx);
            
            duk_push_current_function(ctx);
            
            duk_get_prop_string(ctx, -1, "property");
            
            Vec3Property * p = (Vec3Property *) duk_get_pointer(ctx, -1);
            
            duk_pop_n(ctx, 2);
            
            if(v && p){
                
                vec3& vv = p->get(v);
                
                duk_push_array(ctx);
                
                duk_push_number(ctx, vv.x);
                duk_put_prop_index(ctx, -3, 0);
                
                duk_push_number(ctx, vv.y);
                duk_put_prop_index(ctx, -3, 1);
                
                duk_push_number(ctx, vv.z);
                duk_put_prop_index(ctx, -3, 2);
                
                
            } else {
                duk_push_undefined(ctx);
            }
            
            return 1;
        }
        
        static ScriptResult Vec3PropertySetFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            Object * v = ScriptGetObject(ctx, -1);
            
            duk_pop(ctx);
            
            duk_push_current_function(ctx);
            
            duk_get_prop_string(ctx, -1, "property");
            
            Vec3Property * p = (Vec3Property *) duk_get_pointer(ctx, -1);
            
            duk_pop_n(ctx, 2);
            
            if(v && p) {
                
                int nargs = duk_get_top(ctx);
                
                if(nargs >0 && duk_is_array(ctx, -nargs) ) {
                    
                    vec3 vv(0);
                    
                    duk_size_t n = duk_get_length(ctx, -nargs);
                    
                    if(n > 0) {
                        duk_get_prop_index(ctx, -nargs, 0);
                        vv.x = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    if(n > 1) {
                        duk_get_prop_index(ctx, -nargs, 1);
                        vv.y = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                   
                    if(n > 2) {
                        duk_get_prop_index(ctx, -nargs, 2);
                        vv.z = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    p->set(v,vv);
                    
                } else {
                    vec3 vv(0);
                    p->set(v, vv);
                }
            }
            
            return 0;
        }
        
        void Vec3Property::def(ScriptContext ctx) {
            
            duk_push_string(ctx, _name->name());
            
            duk_push_c_function(ctx, Vec3PropertyGetFunc, 0);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_push_c_function(ctx, Vec3PropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
            
        }
        
        Vec2Property::Vec2Property(Named * name, Getter getter, Setter setter):TProperty<vec2&>(name,getter,setter) {
            
        }
        
        static ScriptResult Vec2PropertyGetFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            Object * v = ScriptGetObject(ctx, -1);
            
            duk_pop(ctx);
            
            duk_push_current_function(ctx);
            
            duk_get_prop_string(ctx, -1, "property");
            
            Vec2Property * p = (Vec2Property *) duk_get_pointer(ctx, -1);
            
            duk_pop_n(ctx, 2);
            
            if(v && p){
                
                vec2& vv = p->get(v);
                
                duk_push_array(ctx);
                
                duk_push_number(ctx, vv.x);
                duk_put_prop_index(ctx, -3, 0);
                
                duk_push_number(ctx, vv.y);
                duk_put_prop_index(ctx, -3, 1);
                
                
            } else {
                duk_push_undefined(ctx);
            }
            
            return 1;
        }
        
        static ScriptResult Vec2PropertySetFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            Object * v = ScriptGetObject(ctx, -1);
            
            duk_pop(ctx);
            
            duk_push_current_function(ctx);
            
            duk_get_prop_string(ctx, -1, "property");
            
            Vec2Property * p = (Vec2Property *) duk_get_pointer(ctx, -1);
            
            duk_pop_n(ctx, 2);
            
            if(v && p) {
                
                int nargs = duk_get_top(ctx);
                
                if(nargs >0 && duk_is_array(ctx, -nargs) ) {
                    
                    vec2 vv(0);
                    
                    duk_size_t n = duk_get_length(ctx, -nargs);
                    
                    if(n > 0) {
                        duk_get_prop_index(ctx, -nargs, 0);
                        vv.x = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    if(n > 1) {
                        duk_get_prop_index(ctx, -nargs, 1);
                        vv.y = duk_to_number(ctx, -1);
                        duk_pop(ctx);
                    }
                    
                    p->set(v,vv);
                    
                } else {
                    vec2 vv(0);
                    p->set(v, vv);
                }
            }
            
            return 0;
        }
        
        void Vec2Property::def(ScriptContext ctx) {
            
            duk_push_string(ctx, _name->name());
            
            duk_push_c_function(ctx, Vec2PropertyGetFunc, 0);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_push_c_function(ctx, Vec2PropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
            
        }
        
        Mat4Property::Mat4Property(Named * name, Getter getter, Setter setter):TProperty<mat4&>(name,getter,setter) {
            
        }
        
        static ScriptResult Mat4PropertyGetFunc(ScriptContext ctx) {
            
            return 0;
        }
        
        static ScriptResult Mat4PropertySetFunc(ScriptContext ctx) {
            
    
            return 0;
        }
        
        void Mat4Property::def(ScriptContext ctx) {
            
            duk_push_string(ctx, _name->name());
            
            duk_push_c_function(ctx, Mat4PropertyGetFunc, 0);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_push_c_function(ctx, Mat4PropertySetFunc, 1);
            duk_push_string(ctx, "property");
            duk_push_pointer(ctx, this);
            duk_put_prop(ctx, -3);
            
            duk_def_prop(ctx,
                         -4,
                         DUK_DEFPROP_HAVE_GETTER |
                         DUK_DEFPROP_HAVE_SETTER |
                         DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE);
            
        }
        
        GLContext::~GLContext() {
            std::map<std::string,GLProgram *>::iterator i = _programs.begin();
            while(i != _programs.end()) {
                delete i->second;
                i ++;
            }
        }
        
        void GLContext::set(kk::CString name,GLProgram * program) {
            GLProgram * v = get(name);
            if(v != program) {
                if(v){
                    delete v;
                }
                _programs[name] = program;
            }
        }
        
        GLProgram * GLContext::get(kk::CString name) {
            std::map<std::string,GLProgram *>::iterator i = _programs.find(name);
            if(i != _programs.end()) {
                return i->second;
            }
            return NULL;
        }
        
        GLContextState& GLContext::state() {
            return * _states.begin();
        }
        
        void GLContext::store() {
            GLContextState v = state();
            _states.insert(_states.begin(), v);
        }
        
        void GLContext::restore() {
            _states.erase(_states.begin());
        }
        
        void GLContext::init() {
            Object::init();
         
            _width = _height = 0;
            _speed = 0;
            _scale = 1.0f;
            
            GLContextState state;
            state.projection = glm::mat4(1.0f);
            state.view = glm::mat4(1.0f);
            state.opacity = 1.0;
            
            _states.push_back(state);
        }
        
        static ScriptResult GLContextStoreFunc(ScriptContext ctx) {
            
            GLContext * v = NULL;
            
            duk_push_this(ctx);
            
            v = dynamic_cast<GLContext *>(ScriptGetObject(ctx, -1));
            
            duk_pop(ctx);
            
            if(v) {
                v->store();
            }
            
            return 0;
        }
        
        static ScriptResult GLContextRestoreFunc(ScriptContext ctx) {
            
            GLContext * v = NULL;
            
            duk_push_this(ctx);
            
            v = dynamic_cast<GLContext *>(ScriptGetObject(ctx, -1));
            
            duk_pop(ctx);
            
            if(v) {
                v->restore();
            }
            
            return 0;
        }
        
        static ScriptResult GLContextPrototypeFunc(ScriptContext ctx) {
            
            duk_push_string(ctx, "store");
            duk_push_c_function(ctx, GLContextStoreFunc, 0);
            duk_put_prop(ctx, -3);
            
            duk_push_string(ctx, "restore");
            duk_push_c_function(ctx, GLContextRestoreFunc, 0);
            duk_put_prop(ctx, -3);
            
            return 0;
        }
        
        kk::Int GLContext::width() {
            return _width;
        }
        
        void GLContext::setWidth(kk::Int v) {
            _width = v;
        }
        
        kk::Int GLContext::height() {
            return _height;
        }
        
        void GLContext::setHeight(kk::Int v) {
            _height = v;
        }
        
        GLTimeInterval GLContext::speed(){
            return _speed;
        }
        
        void GLContext::setSpeed(GLTimeInterval v) {
            _speed = v;
        }
        
        kk::Float GLContext::scale() {
            return _scale;
        }
        
        void GLContext::setScale(kk::Float v) {
            _scale = v;
        }
        
        void GLContext::drawTexture(GLTexture * texture,vec4 dest,vec4 src) {
            
            GLProgram * program = this->get("GLSLTexture");
            
            if(texture && program) {
                
                GLContextState & state = this->state();
                
                kk::Int position = program->attrib("position");
                kk::Int texCoord = program->attrib("texCoord");
                kk::Int transfrom = program->uniform("transfrom");
                kk::Int textureId = program->uniform("texture");
                
                program->use();
                
                texture->active(GL_TEXTURE0);
                program->setUniform(textureId, kk::Int(0));
                
                mat4 v = state.projection * state.view;
                
                program->setUniform(transfrom, v );
                
                kk::Float top = dest.y;
                kk::Float bottom = dest.y + dest.w;
                kk::Float left = dest.x;
                kk::Float right = dest.x + dest.z;
                
                vec3 p[6] = {
                    {left,top,0},{right,top,0},{left,bottom,0},{left,bottom,0},{right,top,0},{right,bottom,0}};
                
                program->setAttrib(position, 3, p, sizeof(vec3));
                
                top = src.y / texture->height();
                bottom = top + src.w / texture->height();
                left = src.x / texture->width();
                right = left + src.z / texture->width();
                
                vec2 t[6] = {
                    {left,top},{right,top},{left,bottom},{left,bottom},{right,top},{right,bottom}};
                
                program->setAttrib(texCoord, 2, t, sizeof(vec2));
                
                glDrawArrays(GL_TRIANGLES, 0, 6);
                
            }
            
        }
    
        
        kk::IntProperty GLContext::Property_width(&kk::named::width,(kk::IntProperty::Getter) & GLContext::width,NULL);
        kk::IntProperty GLContext::Property_height(&kk::named::height,(kk::IntProperty::Getter) & GLContext::height,NULL);
        kk::Int64Property GLContext::Property_speed(&kk::named::speed,(kk::Int64Property::Getter) & GLContext::speed,NULL);
        kk::FloatProperty GLContext::Property_scale(&kk::named::scale,(kk::FloatProperty::Getter) & GLContext::scale,NULL);
        
        kk::Property *GLContext::Propertys[] = {
            &GLContext::Property_width,
            &GLContext::Property_height,
            &GLContext::Property_speed,
            &GLContext::Property_scale,
            NULL
        };
        
        IMP_CLASS(GLContext, kk::Object, GLContext::Propertys, GLContextPrototypeFunc)
        
        void GLElement::init(){
            Element::init();
            _position = vec3(0.0f);
            _transform = mat4(1.0f);
            _scale = vec3(1.0f,1.0f,1.0f);
            _opacity = 1.0;
        }
        
        vec3& GLElement::position(){
            return _position;
        }
        
        void GLElement::setPosition(vec3& v) {
            _position = v;
        }
        
        mat4& GLElement::transform() {
            return _transform;
        }
        
        void GLElement::setTransform(mat4& v) {
            _transform = v;
        }
        
        kk::Float GLElement::opacity() {
            return _opacity;
        }
        
        void GLElement::setOpacity(kk::Float v) {
            _opacity = v;
        }
        
        vec3& GLElement::scale() {
            return _scale;
        }
        
        void GLElement::setScale(vec3& v) {
            _scale = v;
        }
        
        void GLElement::onDraw(GLContext * ctx) {
        
        }
        
        void GLElement::draw(GLContext * ctx) {

            ctx->store();
            
            GLContextState & s = ctx->state() ;
            
            s.opacity = s.opacity * _opacity;
            s.view = glm::scale(glm::translate(s.view, _position),_scale);

            onDraw(ctx);
            
            Element * p = firstChild();
            
            while(p) {
                
                GLDrawable * v = dynamic_cast<GLDrawable *>(p);
                
                if(v) {
                    v->draw(ctx);
                }
                
                p  = p->nextSibling();
            }
            
            ctx->restore();
        }
        
        GLTexture * GLElement::getTexture(kk::CString name) {
            
            GLTexture * v = NULL;
            kk::Element * e = this;
            
            while(e) {
                
                GLTextureProvider * p = dynamic_cast<GLTextureProvider *>(e);
                
                if(p) {
                    v = p->getTexture(name);
                    if(v != NULL) {
                        break;
                    }
                }
                e = e->parent();
            }
            
            if(v == NULL) {
                
                GLTextureProvider * p = dynamic_cast<GLTextureProvider *>(document());
                
                if(p) {
                    v = p->getTexture(name);
                }
            }
            
            if(v == NULL) {
                
                Document * doc = document();
                
                if(doc) {
                    GLTextureProvider * tp = dynamic_cast<GLTextureProvider *>(doc->app());
                    if(tp) {
                        v = tp->getTexture(name);
                    }
                }
            }
            
            return v;
        }
        
        Vec3Property GLElement::Property_position(&kk::named::position,(Vec3Property::Getter)&GLElement::position,(Vec3Property::Setter)&GLElement::setPosition);
        Vec3Property GLElement::Property_scale(&kk::named::scale,(Vec3Property::Getter)&GLElement::scale,(Vec3Property::Setter)&GLElement::setScale);
        Mat4Property GLElement::Property_transform(&kk::named::transform,(Mat4Property::Getter)&GLElement::transform,(Mat4Property::Setter)&GLElement::setTransform);
        kk::FloatProperty GLElement::Property_opacity(&kk::named::opacity,(FloatProperty::Getter)&GLElement::opacity,(FloatProperty::Setter)&GLElement::setOpacity);
        kk::Property * GLElement::Propertys[] = {
            &GLElement::Property_position,
            &GLElement::Property_scale,
            &GLElement::Property_transform,
            &GLElement::Property_opacity,
            NULL
        };
        
        IMP_CLASS(GLElement, kk::Element, GLElement::Propertys, NULL)
        
        void GLImageElement::init() {
            GLElement::init();
            _size = vec2(0);
            _anchor = vec2(0.5,0.5);
            _texture = NULL;
        }
        
        CString GLImageElement::name() {
            return _name.c_str();
        }
        
        void GLImageElement::setName(CString name) {
            _name = name;
            _texture = NULL;
        }
        
        vec2& GLImageElement::size() {
            return _size;
        }
        
        void GLImageElement::setSize(vec2& size) {
            _size = size;
        }
        
        vec2& GLImageElement::anchor() {
            return _anchor;
        }
        
        void GLImageElement::setAnchor(vec2& anchor) {
            _anchor = anchor;
        }
        
        void GLImageElement::onDraw(GLContext * ctx) {
            
            if(_texture == NULL) {
                _texture = getTexture(name());
            }
            
            if(_texture) {
                
                if(_size.x == 0) {
                    _size.x = _texture->width();
                }
                
                if(_size.y == 0) {
                    _size.y = _texture->height();
                }
                
                kk::Float top = - _size.y * _anchor.y;
                kk::Float bottom = _size.y * (1.0 - _anchor.y);
                kk::Float left = - _size.x * _anchor.x;
                kk::Float right = _size.x * (1.0 - _anchor.x);
                
                ctx->drawTexture(_texture, vec4(left,top,left +right,top + bottom), vec4(0,0,_texture->width(),_texture->height()));
            }
            
        }
        
        kk::StringProperty GLImageElement::Property_name(&kk::named::name,(kk::StringProperty::Getter)&GLImageElement::name,(kk::StringProperty::Setter)&GLImageElement::setName);
        Vec2Property GLImageElement::Property_size(&kk::named::size,(Vec2Property::Getter)&GLImageElement::size,(Vec2Property::Setter)&GLImageElement::setSize);
        Vec2Property GLImageElement::Property_anchor(&kk::named::anchor,(Vec2Property::Getter)&GLImageElement::anchor,(Vec2Property::Setter)&GLImageElement::setAnchor);
        kk::Property * GLImageElement::Propertys[] = {
            &GLImageElement::Property_name,
            &GLImageElement::Property_size,
            &GLImageElement::Property_anchor,
            NULL
        };
        
        IMP_CLASS(GLImageElement, kk::gl::GLElement, GLImageElement::Propertys, NULL)
        
        void GLTextElement::init() {
            GLElement::init();
            _size = vec2(0);
            _anchor = vec2(0.5,0.5);
            _maxWidth = FLOAT_MAX;
            _fontSize = 14;
            _color = vec4(0,0,0,1);
            _texture = NULL;
        }
        
        GLTextElement::~GLTextElement() {
            if(_texture) {
                delete _texture;
            }
        }
        
        CString GLTextElement::text() {
            return _text.c_str();
        }
        
        void GLTextElement::setText(CString v) {
            _text = v;
            if(_texture) {
                delete _texture;
                _texture = NULL;
            }
        }
        
        kk::Float GLTextElement::maxWidth() {
            return _maxWidth;
        }
        
        void GLTextElement::setMaxWidth(kk::Float size) {
            _maxWidth = size;
        }
        
        vec2& GLTextElement::size() {
            return _size;
        }
        
        kk::CString GLTextElement::fontFamily() {
            return _fontFamily.c_str();
        }
        
        void GLTextElement::setFontFamily(kk::CString v) {
            _fontFamily = v;
        }
        
        kk::Float GLTextElement::fontSize() {
            return _fontSize;
        }
        
        void GLTextElement::setFontSize(kk::Float v) {
            _fontSize = v;
        }
        
        vec4& GLTextElement::color() {
            return _color;
        }
        
        void GLTextElement::setColor(vec4& v) {
            _color = v;
        }
        
        vec2& GLTextElement::anchor() {
            return _anchor;
        }
        
        void GLTextElement::setAnchor(vec2& anchor) {
            _anchor = anchor;
        }
        
        void GLTextElement::onDraw(GLContext * ctx) {
            
            if(_texture == NULL){
                _texture = GLCreateStringTexture(_text.c_str(), _fontFamily.c_str(), _fontSize * ctx->scale(), _color, _maxWidth);
                if(_texture) {
                    _size.x = _texture->width();
                    _size.y = _texture->height();
                }
            }
            
            if(_texture) {
                
                kk::Float top = - _size.y * _anchor.y;
                kk::Float bottom = _size.y * (1.0 - _anchor.y);
                kk::Float left = - _size.x * _anchor.x;
                kk::Float right = _size.x * (1.0 - _anchor.x);
                
                ctx->drawTexture(_texture, vec4(left,top,left +right,top + bottom), vec4(0,0,_texture->width(),_texture->height()));
            }
            
        }
        
        kk::StringProperty GLTextElement::Property_text(&kk::named::text,(kk::StringProperty::Getter)&GLTextElement::text,(kk::StringProperty::Setter)&GLTextElement::setText);
        kk::FloatProperty GLTextElement::Property_maxWidth(&kk::named::maxWidth,(kk::FloatProperty::Getter)&GLTextElement::maxWidth,(kk::FloatProperty::Setter)&GLTextElement::setMaxWidth);
        Vec2Property GLTextElement::Property_size(&kk::named::size,(Vec2Property::Getter)&GLTextElement::size,NULL);
        Vec2Property GLTextElement::Property_anchor(&kk::named::anchor,(Vec2Property::Getter)&GLTextElement::anchor,(Vec2Property::Setter)&GLTextElement::setAnchor);
        kk::StringProperty GLTextElement::Property_fontFamily(&kk::named::fontFamily,(kk::StringProperty::Getter)&GLTextElement::fontFamily,(kk::StringProperty::Setter)&GLTextElement::setFontFamily);
        kk::FloatProperty GLTextElement::Property_fontSize(&kk::named::fontSize,(kk::FloatProperty::Getter)&GLTextElement::fontSize,(kk::FloatProperty::Setter)&GLTextElement::setFontSize);
        Vec4Property GLTextElement::Property_color(&kk::named::color,(Vec4Property::Getter)&GLTextElement::color,(Vec4Property::Setter)&GLTextElement::setColor);
        kk::Property * GLTextElement::Propertys[] = {
            &GLTextElement::Property_text,
            &GLTextElement::Property_maxWidth,
            &GLTextElement::Property_size,
            &GLTextElement::Property_anchor,
            &GLTextElement::Property_fontFamily,
            &GLTextElement::Property_fontSize,
            &GLTextElement::Property_color,
            NULL
        };
        
        IMP_CLASS(GLTextElement, kk::gl::GLElement, GLTextElement::Propertys, NULL);
        
        GLProgram::GLProgram(kk::CString vshCode,kk::CString fshCode) {
            
            _value = 0;
    
            GLint status = GL_TRUE;
            GLuint vshShader = 0,fshShader = 0;
            GLchar log[2048];
            GLint logLen = 0;
            
            vshShader = glCreateShader(GL_VERTEX_SHADER);
            
            glShaderSource(vshShader, 1, &vshCode, NULL);
            
            glCompileShader(vshShader);
            
            glGetShaderInfoLog(vshShader, sizeof(log), &logLen, log);
            
            if(logLen >0){
                kk::Log("Shader compile log: %s", log);
            }
            
            glGetShaderiv(vshShader, GL_COMPILE_STATUS, &status);
            
            if (status != GL_TRUE) {
                
                glDeleteShader(vshShader);
                
                kk::Log("Failed to vsh compile shader\n");
                
                return;
            }
            
            fshShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fshShader, 1, &fshCode, NULL);
            glCompileShader(fshShader);
            
            glGetShaderInfoLog(fshShader, sizeof(log), &logLen, log);
            
            if(logLen >0){
                kk::Log("Shader compile log: %s", log);
            }
            
            glGetShaderiv(fshShader, GL_COMPILE_STATUS, &status);
            
            if (status != GL_TRUE) {
                
                glDeleteShader(vshShader);
                glDeleteShader(fshShader);
                
                kk::Log("Failed to fsh compile shader");
                
                return;
            }
            
            _value = glCreateProgram();
            
            glAttachShader(_value, vshShader);
            glAttachShader(_value, fshShader);
            
            glLinkProgram(_value);
            
            if (vshShader){
                glDeleteShader(vshShader);
            }
            
            if (fshShader){
                glDeleteShader(fshShader);
            }
            
            glGetProgramInfoLog(_value, sizeof(log), &logLen, log);
            
            if(logLen >0){
                kk::Log("Program link log: %s", log);
            }
            
            status = GL_TRUE;
            
            glGetProgramiv(_value, GL_LINK_STATUS, &status);
            
            if (status != GL_TRUE ){
                
                kk::Log("Program link error");
                glDeleteProgram(_value);
                _value = 0;
            }
            
        }
        
        GLProgram::~GLProgram() {
            
            if(_value) {
                glDeleteProgram(_value);
            }
            
        }
        
        void GLProgram::use() {
            if(_value) {
                glUseProgram(_value);
            }
        }
        
        kk::Int GLProgram::uniform(kk::CString name) {
            if(_value) {
                return glGetUniformLocation(_value, name);
            }
            return -1;
        }
        
        kk::Int GLProgram::attrib(kk::CString name) {
            if(_value) {
                return glGetAttribLocation(_value, name);
            }
            return -1;
        }
        
        void GLProgram::setUniform(kk::Int loc,kk::Float value) {
            if(_value) {
                glUniform1f(loc,value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,kk::Float * value, kk::Int count) {
            if(_value) {
                glUniform1fv(loc,count,value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,vec2 value) {
            if(_value) {
                glUniform2f(loc,value.x,value.y);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,vec2 * value, kk::Int count) {
            if(_value) {
                glUniform2fv(loc,count,(kk::Float *) value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,vec3 value) {
            if(_value) {
                glUniform3f(loc,value.x,value.y,value.z);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,vec3 * value, kk::Int count) {
            if(_value) {
                glUniform3fv(loc,count,(kk::Float *) value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,vec4 value) {
            if(_value) {
                glUniform4f(loc,value.x,value.y,value.z,value.w);
            }
        }
        void GLProgram::setUniform(kk::Int loc,vec4 * value, kk::Int count) {
            if(_value) {
                glUniform4fv(loc,count,(kk::Float *) value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,kk::Int value) {
            if(_value) {
                glUniform1i(loc,value);
            }
        }
        void GLProgram::setUniform(kk::Int loc,kk::Int * value, kk::Int count) {
            if(_value) {
                glUniform1iv(loc,count,value);
            }
        }
        void GLProgram::setUniform(kk::Int loc,mat3 value) {
            if(_value) {
                glUniformMatrix3fv(loc,1,GL_FALSE, (kk::Float *) &value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,mat3 * value, kk::Int count) {
            if(_value) {
                glUniformMatrix3fv(loc,count,GL_FALSE, (kk::Float *) value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,mat4 value) {
            if(_value) {
                glUniformMatrix4fv(loc,1,GL_FALSE, (kk::Float *) &value);
            }
        }
        
        void GLProgram::setUniform(kk::Int loc,mat4 * value, kk::Int count) {
            if(_value) {
                glUniformMatrix4fv(loc,count,GL_FALSE, (kk::Float *) value);
            }
        }
        
        void GLProgram::setAttrib(kk::Int loc,kk::Uint size,void * data,kk::Int stride) {
            glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, stride, data);
            glEnableVertexAttribArray(loc);
        }
        
        
        #define PVR_TEXTURE_FLAG_TYPE_MASK    0xff
        
        static char GLPVRTextureIdentifier[5] = "PVR!";
        
        enum
        {
            GLPVRTextureFlagTypePVRTC_2 = 24,
            GLPVRTextureFlagTypePVRTC_4
        };
        
        struct GLPVRTextureHeader {
            uint32_t headerLength;
            uint32_t height;
            uint32_t width;
            uint32_t numMipmaps;
            uint32_t flags;
            uint32_t dataLength;
            uint32_t bpp;
            uint32_t bitmaskRed;
            uint32_t bitmaskGreen;
            uint32_t bitmaskBlue;
            uint32_t bitmaskAlpha;
            uint32_t pvrTag;
            uint32_t numSurfs;
        };
        
        
        GLTexture::GLTexture(void * data, kk::Uint size, kk::Int width,kk::Int height, GLTextureType type)
        :_id(0),_width(width),_height(height) {
            
            if(type == GLTextureTypeRGBA || type == GLTextureTypeBGRA) {
                
                glGenTextures(1, &_id);
                glBindTexture(GL_TEXTURE_2D, _id);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type == GLTextureTypeRGBA ? GL_RGBA : GL_BGRA, GL_UNSIGNED_BYTE, data);
                
                return;
            }
            
            {
                GLPVRTextureHeader *header = NULL;
                uint32_t flags, pvrTag;
                uint32_t dataLength = 0, dataOffset = 0, dataSize = 0;
                uint32_t blockSize = 0, widthBlocks = 0, heightBlocks = 0;
                uint32_t width = 0, height = 0, bpp = 4;
                uint8_t *bytes = NULL;
                uint32_t formatFlags;
                GLenum err;
                
                header = (GLPVRTextureHeader *)data;
                
                pvrTag = ntohl(header->pvrTag);
                
                if (GLPVRTextureIdentifier[0] != ((pvrTag >>  0) & 0xff) ||
                    GLPVRTextureIdentifier[1] != ((pvrTag >>  8) & 0xff) ||
                    GLPVRTextureIdentifier[2] != ((pvrTag >> 16) & 0xff) ||
                    GLPVRTextureIdentifier[3] != ((pvrTag >> 24) & 0xff))
                {
                    return;
                }
                
                flags = ntohl(header->flags);
                formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;
                
                if (formatFlags == GLPVRTextureFlagTypePVRTC_4 || formatFlags == GLPVRTextureFlagTypePVRTC_2)
                {
                    GLenum fmt = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
                    
                    if (formatFlags == GLPVRTextureFlagTypePVRTC_4)
                        fmt = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
                    else if (formatFlags == GLPVRTextureFlagTypePVRTC_2)
                        fmt = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
                    
                    _width = width = ntohl(header->width);
                    _height = height = ntohl(header->height);
                    
                    bool alpha = false;
                    
                    if (ntohl(header->bitmaskAlpha))
                        alpha = true;
                    
                    bytes = ((uint8_t *) data) + sizeof(GLPVRTextureHeader);
                    
                    glGenTextures(1, &_id);
                    glBindTexture(GL_TEXTURE_2D, _id);
                    
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    
                    int i=0;
                    
                    // Calculate the data size for each texture level and respect the minimum number of blocks
                    while (dataOffset < dataLength)
                    {
                        if (formatFlags == GLPVRTextureFlagTypePVRTC_4)
                        {
                            blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
                            widthBlocks = width / 4;
                            heightBlocks = height / 4;
                            bpp = 4;
                        }
                        else
                        {
                            blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
                            widthBlocks = width / 8;
                            heightBlocks = height / 4;
                            bpp = 2;
                        }
                        
                        // Clamp to minimum number of blocks
                        if (widthBlocks < 2)
                            widthBlocks = 2;
                        if (heightBlocks < 2)
                            heightBlocks = 2;
                        
                        dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
                        
                        glCompressedTexImage2D(GL_TEXTURE_2D, i, fmt, width, height, 0, dataSize, bytes + dataOffset);
                        
                        err = glGetError();
                        
                        if (err != GL_NO_ERROR){
                            kk::Log("Error uploading compressed texture level: %d. glError: 0x%04X", i, err);
                            glDeleteTextures(1,&_id);
                            _id = 0;
                            return;
                        }
                        
                        dataOffset += dataSize;
                        
                        width = MAX(width >> 1, 1);
                        height = MAX(height >> 1, 1);
                        i ++;
                    }
                
                }
            }
        }
        
        GLTexture::~GLTexture() {
            if(_id) {
                glDeleteTextures(1, &_id);
            }
        }
        
        kk::Int GLTexture::width() {
            return _width;
        }
        
        kk::Int GLTexture::height() {
            return _height;
        }
        
        void GLTexture::active(kk::Uint textureId) {
            if(_id) {
                glActiveTexture(_id);
                glBindTexture(GL_TEXTURE_2D, _id);
            }
        }
        
    }
    
}
