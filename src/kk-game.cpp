//
//  kk-game.cpp
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "kk-game.h"


namespace kk {
    
    namespace game {
        
        GMTimeInterval getSystemCurrentTimeInterval() {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }
        
        GMTimeInterval GMContext::current() {
            return _current.get();
        }
        
        GMTimeInterval GMContext::speed() {
            return _speed.get();
        }
        
        void GMContext::setSpeed(GMTimeInterval v) {
            _speed.set(v);
        }
        
        void GMContext::tick() {
            _current.set(_current.get() + _speed.get());
            _count.set(_count.get() + 1);
        }
        
        kk::Int64 GMContext::count() {
            return _count.get();
        }
        
        GMContext::GMContext(ScriptContext context,ScriptPtr ptr)
            :kk::Object(context,ptr)
                ,_current(this,&kk::P::current)
                ,_speed(this,&kk::P::speed)
                ,_count(this,&kk::P::count)
        {
            _speed.set(1000 / 60);
        }
        
        void GMElement::onTick(GMContext * ctx) {
            
        }
        
        void GMElement::tick(GMContext * ctx) {
            
            if(! _paused.get()) {
                _current.set(_current.get() + ctx->speed());
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
        
        GMElement::GMElement(ScriptContext context,ScriptPtr ptr)
            :kk::Element(context,ptr)
                ,_current(this,&kk::P::current)
                ,_paused(this,&kk::P::paused)
        {
            
        }
        
        kk::Boolean GMElement::isPaused() {
            return _paused.get();
        }
        
        void GMElement::pause() {
            _paused.set(true);
        }
        
        void GMElement::resume() {
            _paused.set(false);
            _current.set((kk::Int64) 0);
        }
        
        GMTimeInterval GMElement::current() {
            return _current.get();
        }
        
        SceneElement::SceneElement(ScriptContext context,ScriptPtr ptr):GMElement(context,ptr) {
            
        }
        
        SceneElement::~SceneElement() {
            
            {
                std::map<std::string,kk::gl::GLTexture*>::iterator i = _textures.begin();
                while(i != _textures.end()) {
                    delete i->second;
                    i ++;
                }
            }
            
        }
        
        void SceneElement::draw(kk::gl::GLContext * ctx) {
            
            Element * p = firstChild();
            
            while(p) {
                
                GLDrawable * v = dynamic_cast<GLDrawable *>(p);
                
                if(v) {
                    v->draw(ctx);
                }
                
                p  = p->nextSibling();
            }
            
        }
        
        void SceneElement::emit(CString name,Event * event) {
            GMElement::emit(name, event);
            
            ElementActionEvent * e = dynamic_cast<ElementActionEvent *>(event);
            
            if(e != NULL
               && (e->actionType.get() == ElementActionTypeAdd && e->element.get() == this)) {
                
                {
                    TextureElement * v = dynamic_cast<TextureElement *>(e->asElement.get());
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
        
        kk::CString TextureElement::path() {
            return _path.get().c_str();
        }
        
        kk::CString TextureElement::name() {
            return _name.get().c_str();
        }
        
        void TextureElement::setPath(kk::CString path) {
            _path.set(path);
        }
        
        void TextureElement::setName(kk::CString name) {
            _name.set(name);
        }
        
        TextureElement::TextureElement(ScriptContext context,ScriptPtr ptr)
        :kk::Element(context,ptr)
        , _path(this,&kk::P::path)
        , _name(this,&kk::P::name){
            
        }
        
        void openlibs(ScriptContext context) {
            
            ScriptOpenClass(context, "Document", Document::Class);
            ScriptOpenClass(context, "Element", Element::Class);
            ScriptOpenClass(context, "ElementEvent", ElementEvent::Class);
            ScriptOpenClass(context, "ElementActionEvent", ElementActionEvent::Class);
            
            ScriptOpenClass(context, "GLElement", kk::gl::GLElement::Class);
            
        }
        
    }
    
}

