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
        public:
            DEF_CLASS(GMContext)
            virtual GMTimeInterval current();
            virtual GMTimeInterval speed();
            virtual void setSpeed(GMTimeInterval v);
            virtual void tick();
            virtual kk::Int64 count();
        protected:
            GMContext(ScriptContext context,ScriptPtr ptr);
            kk::Int64Property _current;
            kk::Int64Property _speed;
            kk::Int64Property _count;
        };
        
        class GMElement: public kk::Element {
        public:
            DEF_CLASS(GMElement)
            virtual void tick(GMContext * ctx);
            virtual kk::Boolean isPaused();
            virtual void pause();
            virtual void resume();
            virtual GMTimeInterval current();
        protected:
            GMElement(ScriptContext context,ScriptPtr ptr);
            virtual void onTick(GMContext * ctx);
            kk::BooleanProperty _paused;
            kk::Int64Property _current;
        };
        
        class SceneElement: public kk::gl::GLDrawable, public GMElement {
        public:
            DEF_CLASS(SceneElement)
            virtual void draw(kk::gl::GLContext * ctx);
            virtual void emit(CString name,Event * event);
            virtual ~SceneElement();
        protected:
            SceneElement(ScriptContext context,ScriptPtr ptr);
            std::map<std::string,kk::gl::GLTexture*> _textures;
        };
        
        class TextureElement : public kk::Element {
        public:
            DEF_CLASS(TextureElement)
            virtual kk::CString path();
            virtual kk::CString name();
            virtual void setPath(kk::CString path);
            virtual void setName(kk::CString name);
        protected:
            TextureElement(ScriptContext context,ScriptPtr ptr);
            kk::StringProperty _path;
            kk::StringProperty _name;
        };
        
        void openlibs(ScriptContext context);
        
    }
    
}

#endif /* kk_game_h */
