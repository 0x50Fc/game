//
//  kk-game.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-game.h"

#ifdef __APPLE__

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#endif

namespace kk {
    
    namespace game {
        
        GMTimeInterval getSystemCurrentTimeInterval() {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }
        
        GMTimeInterval GMContext::current() {
            return _current;
        }
        
        GMTimeInterval GMContext::speed() {
            return _speed;
        }
        
        void GMContext::setSpeed(GMTimeInterval v) {
            _speed = v;
        }
        
        void GMContext::tick() {
            _current = _current + _speed;
            _count = _count + 1;
        }
        
        kk::Int64 GMContext::count() {
            return _count;
        }
        
        kk::Int64Property GMContext::Property_current(&kk::named::current,(kk::Int64Property::Getter) &GMContext::current,NULL);
        kk::Int64Property GMContext::Property_speed(&kk::named::speed,(kk::Int64Property::Getter) &GMContext::speed,(kk::Int64Property::Setter) &GMContext::setSpeed);
        kk::Int64Property GMContext::Property_count(&kk::named::count,(kk::Int64Property::Getter) &GMContext::count,NULL);
        kk::Property *GMContext::Propertys[] = {
            &GMContext::Property_current,
            &GMContext::Property_speed,
            &GMContext::Property_count,
            NULL
        };
        
        IMP_CLASS(GMContext, kk::Object, GMContext::Propertys, NULL)
        
        void GMElement::onTick(GMContext * ctx) {
            
        }
        
        void GMElement::tick(GMContext * ctx) {
            
            if(! _paused) {
                _current = _current + ctx->speed();
            }
            
            onTick(ctx);
            
            kk::Element * p = firstChild();
            
            while(p) {
                
                GMElement * e = dynamic_cast<GMElement *>(p);
                
                if(e) {
                    e->tick(ctx);
                }
                
                p = p->nextSibling();
            }
        }
        
        
        kk::Boolean GMElement::isPaused() {
            return _paused;
        }
        
        void GMElement::pause() {
            _paused = true;
        }
        
        void GMElement::resume() {
            _paused = false;
        }
        
        GMTimeInterval GMElement::current() {
            return _current;
        }
        
        kk::BooleanProperty GMElement::Property_paused(&kk::named::paused,(kk::BooleanProperty::Getter) &GMElement::isPaused,NULL);
        kk::Int64Property GMElement::Property_current(&kk::named::current,(kk::Int64Property::Getter) &GMElement::current,NULL);
        
        kk::Property * GMElement::Propertys[] = {
            &GMElement::Property_paused,
            &GMElement::Property_current,
            NULL
        };
        
        static ScriptResult GMElementPauseFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            GMElement * v = dynamic_cast<GMElement *>(ScriptGetObject(ctx, -1));
            
            duk_pop(ctx);
            
            if(v) {
                v->pause();
            }
            
            return 0;
        }
        
        static ScriptResult GMElementResumeFunc(ScriptContext ctx) {
            
            duk_push_this(ctx);
            
            GMElement * v = dynamic_cast<GMElement *>(ScriptGetObject(ctx, -1));
            
            duk_pop(ctx);
            
            if(v) {
                v->resume();
            }
            
            return 0;
        }
        
        static ScriptResult GMElementPrototypeFunc(ScriptContext ctx) {
            
            duk_push_string(ctx, "pause");
            duk_push_c_function(ctx, GMElementPauseFunc, 0);
            duk_put_prop(ctx, -3);
            
            duk_push_string(ctx, "resume");
            duk_push_c_function(ctx, GMElementResumeFunc, 0);
            duk_put_prop(ctx, -3);
            
            return 0;
        }
        
        IMP_CLASS(GMElement, kk::Element, GMElement::Propertys, GMElementPrototypeFunc)
        
        GMSceneElement::~GMSceneElement() {
            
            {
                std::map<std::string,kk::gl::GLTexture*>::iterator i = _textures.begin();
                while(i != _textures.end()) {
                    delete i->second;
                    i ++;
                }
            }
            
        }
        
        void GMSceneElement::draw(kk::gl::GLContext * ctx) {
            
            ctx->store();
            
            kk::gl::GLContextState& state =  ctx->state();
        
            kk::gl::vec3 v(0);
            
            v.x = 1.0f / ctx->width();
            v.y = - 1.0f / ctx->height();
            v.z = - 0.000001;
            
            state.projection = glm::scale(glm::translate(kk::gl::mat4(1), kk::gl::vec3(-1,1,0)), v);
            
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
        
        void GMSceneElement::emit(CString name,Event * event) {
            GMElement::emit(name, event);
            
            ElementActionEvent * e = dynamic_cast<ElementActionEvent *>(event);
            
            if(e != NULL
               && (e->actionType() == ElementActionTypeAdd && e->element() == this)) {
                
                {
                    GMTextureElement * v = dynamic_cast<GMTextureElement *>(e->asElement());
                    if(v){
                        kk::Document* doc = document();
                        if(doc) {
                            kk::Application * app = doc->app();
                            
                            if(app) {
                                
                                if(_textures.find(v->name()) == _textures.end()) {
                                    
                                    kk::gl::GLTexture * texture = kk::gl::GLCreateTexture(app, v->path());
                                    
                                    if(texture) {
                                        
                                        _textures[v->name()] = texture;
                                        
                                    } else {
                                        kk::Log("Not Found Texture %s : %s",v->name(), v->path());
                                    }
                                    
                                } else {
                                    kk::Log("Texture %s : %s already exists",v->name(), v->path());
                                }
                                
                            }
                        }
                        
                    }
                }
            }
        }
        
        kk::gl::GLTexture * GMSceneElement::getTexture(kk::CString name) {
            std::map<std::string,kk::gl::GLTexture*>::iterator i = _textures.find(name);
            if(i != _textures.end()) {
                return i->second;
            }
            return NULL;
        }
        
        IMP_CLASS(GMSceneElement, GMElement, NULL, NULL)
        
        kk::CString GMTextureElement::path() {
            return _path.c_str();
        }
        
        kk::CString GMTextureElement::name() {
            return _name.c_str();
        }
        
        void GMTextureElement::setPath(kk::CString path) {
            _path = path;
        }
        
        void GMTextureElement::setName(kk::CString name) {
            _name = name;
        }
        
        kk::StringProperty GMTextureElement::Property_path(&kk::named::path,(kk::StringProperty::Getter) &GMTextureElement::path,(kk::StringProperty::Setter) &GMTextureElement::setPath);
        kk::StringProperty GMTextureElement::Property_name(&kk::named::name,(kk::StringProperty::Getter) &GMTextureElement::name,(kk::StringProperty::Setter) &GMTextureElement::setName);
        kk::Property * GMTextureElement::Propertys[] = {
            &GMTextureElement::Property_path,
            &GMTextureElement::Property_name,
            NULL
        };
        
        IMP_CLASS(GMTextureElement, kk::Element, GMTextureElement::Propertys, NULL)
        
        
    }
    
}

