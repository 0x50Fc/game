//
//  kk-game.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/7.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_game_h
#define kk_game_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-element.h>
#include <KKGame/kk-gl.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#endif

#include <map>
#include <string>

namespace kk {
    
    namespace game {
        
        
        typedef kk::Int64 GMTimeInterval; /** 毫秒 **/
        
        GMTimeInterval getSystemCurrentTimeInterval();
        
        class GMContext : public kk::Object {
        DEF_CLASS(GMContext)
        public:
            virtual GMTimeInterval current();
            virtual GMTimeInterval speed();
            virtual void setSpeed(GMTimeInterval v);
            virtual kk::Int64 count();
            virtual void tick();
            
            static kk::Int64Property Property_current;
            static kk::Int64Property Property_speed;
            static kk::Int64Property Property_count;
            static kk::Property *Propertys[];
            
        protected:
            GMTimeInterval _current;
            GMTimeInterval _speed;
            GMTimeInterval _count;
        };
        
        class GMElement: public kk::Element {
        DEF_CLASS(GMElement)
        public:
            virtual void tick(GMContext * ctx);
            virtual kk::Boolean isPaused();
            virtual void pause();
            virtual void resume();
            virtual GMTimeInterval current();
            
            static kk::BooleanProperty Property_paused;
            static kk::Int64Property Property_current;
            static kk::Property * Propertys[];
            
        protected:
            virtual void onTick(GMContext * ctx);
            kk::Boolean _paused;
            GMTimeInterval _current;
        };
        
        class GMSceneElement: public kk::gl::GLDrawable, public kk::gl::GLTextureProvider, public GMElement {
        DEF_CLASS(GMSceneElement)
        public:
            virtual void draw(kk::gl::GLContext * ctx);
            virtual void emit(CString name,Event * event);
            virtual kk::gl::GLTexture * getTexture(kk::CString name);
            virtual ~GMSceneElement();
        protected:
            std::map<std::string,kk::gl::GLTexture*> _textures;
        };
        
        class GMTextureElement : public kk::Element {
        DEF_CLASS(GMTextureElement)
        public:
            virtual kk::CString path();
            virtual kk::CString name();
            virtual void setPath(kk::CString path);
            virtual void setName(kk::CString name);
            
            static kk::StringProperty Property_path;
            static kk::StringProperty Property_name;
            static kk::Property * Propertys[];
            
        protected:
            kk::String _path;
            kk::String _name;
        };
        
    }
    
}

#endif /* kk_game_h */
