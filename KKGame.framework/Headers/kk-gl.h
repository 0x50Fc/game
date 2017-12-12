//
//  kk-gl.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_gl_h
#define kk_gl_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-element.h>
#include <KKGame/kk-document.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#endif

#include <vector>

namespace kk {
    
    namespace gl {
        
        typedef glm::vec2 vec2;
        typedef glm::vec3 vec3;
        typedef glm::vec4 vec4;
        typedef glm::mat3 mat3;
        typedef glm::mat4 mat4;
        
        class Vec4Property : public kk::TProperty<vec4> {
        public:
            Vec4Property(Object * object,Property * property);
            virtual ScriptResult getScript();
            virtual ScriptResult setScript();
            virtual String toString() ;
            virtual void set(vec4 value) ;
            virtual void set(CString value) ;
        };
        
        class Mat4Property : public kk::TProperty<mat4> {
        public:
            Mat4Property(Object * object,Property * property);
            virtual ScriptResult getScript();
            virtual ScriptResult setScript();
            virtual String toString() ;
            virtual void set(mat4 value) ;
            virtual void set(CString value) ;
        };
        
        struct GLContextState {
            mat4 projection;
            mat4 view;
            kk::Float opacity;
        };
        
        class GLContext : public kk::Object {
        public:
            DEF_CLASS(GLContext)
            virtual GLContextState& state();
            virtual void store();
            virtual void restore();
        protected:
            GLContext(ScriptContext context,ScriptPtr ptr);
            std::vector<GLContextState> _states;
        };
        
        class GLDrawable {
        public:
            virtual void draw(GLContext * ctx) = 0;
        };
        
        class GLElement : public GLDrawable, public kk::Element {
        public:
            DEF_CLASS(GLElement)
            virtual vec4 position();
            virtual void setPosition(vec4 v);
            virtual mat4 transform();
            virtual void setTransform(mat4 v);
            virtual kk::Float opacity();
            virtual void setOpacity(kk::Float v);
            virtual void draw(GLContext * ctx);
        protected:
            GLElement(ScriptContext context,ScriptPtr ptr);
            Vec4Property _position;
            Mat4Property _transform;
            kk::FloatProperty _opacity;
        };
        
        enum GLTextureType {
            GLTextureTypeRGBA,GLTextureTypeBGRA,GLTextureTypePVR
        };
        
        class GLTexture {
        public:
            GLTexture(void * data, kk::Uint size, kk::Int width,kk::Int height,GLTextureType type);
            virtual ~GLTexture();
            virtual kk::Int width();
            virtual kk::Int height();
            virtual void active(kk::Uint textureId);
        protected:
            kk::Int _width;
            kk::Int _height;
            kk::Uint _id;
        };
        
        extern GLTexture * GLCreateTexture(kk::Application * app,kk::CString path);
        
        
        class GLProgram {
        public:
            GLProgram(kk::CString vshCode,kk::CString fshCode);
            virtual ~GLProgram();
            virtual void use();
            virtual kk::Int uniform(kk::CString name);
            virtual kk::Int attrib(kk::CString name);
            virtual void setUniform(kk::Int loc,kk::Float value);
            virtual void setUniform(kk::Int loc,kk::Float * value, kk::Int count);
            virtual void setUniform(kk::Int loc,vec2 value);
            virtual void setUniform(kk::Int loc,vec2 * value, kk::Int count);
            virtual void setUniform(kk::Int loc,vec3 value);
            virtual void setUniform(kk::Int loc,vec3 * value, kk::Int count);
            virtual void setUniform(kk::Int loc,vec4 value);
            virtual void setUniform(kk::Int loc,vec4 * value, kk::Int count);
            virtual void setUniform(kk::Int loc,kk::Int value);
            virtual void setUniform(kk::Int loc,kk::Int * value, kk::Int count);
            virtual void setUniform(kk::Int loc,mat3 value);
            virtual void setUniform(kk::Int loc,mat3 * value, kk::Int count);
            virtual void setUniform(kk::Int loc,mat4 value);
            virtual void setUniform(kk::Int loc,mat4 * value, kk::Int count);
            virtual void setAttrib(kk::Int loc,kk::Uint size,void * data,kk::Int stride);
            
        protected:
            kk::Uint _value;
        };
        
    }
    
}

#endif /* kk_gl_h */
