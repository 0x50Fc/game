//
//  kk-gl.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/8.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_gl_h
#define kk_gl_h

#ifdef TARGET_OS_IOS
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
#include <string>
#include <map>

namespace kk {
    
    namespace gl {
        
        typedef kk::Int64 GLTimeInterval; /** 毫秒 **/
        
        typedef glm::vec2 vec2;
        typedef glm::vec3 vec3;
        typedef glm::vec4 vec4;
        typedef glm::mat3 mat3;
        typedef glm::mat4 mat4;
        
        class Vec4Property : public TProperty<vec4&> {
        public:
            Vec4Property(Named * name, Getter getter, Setter setter);
            virtual void def(ScriptContext ctx);
        };
        
        class Vec3Property : public TProperty<vec3&> {
        public:
            Vec3Property(Named * name, Getter getter, Setter setter);
            virtual void def(ScriptContext ctx);
        };
        
        class Vec2Property : public TProperty<vec2&> {
        public:
            Vec2Property(Named * name, Getter getter, Setter setter);
            virtual void def(ScriptContext ctx);
        };
        
        class Mat4Property : public TProperty<mat4&> {
        public:
            Mat4Property(Named * name, Getter getter, Setter setter);
            virtual void def(ScriptContext ctx);
        };
        
        struct GLContextState {
            mat4 projection;
            mat4 view;
            kk::Float opacity;
        };
        
        class GLProgram;
        class GLTexture;
        
        class GLContext : public kk::Object {
        DEF_CLASS(GLContext)
        public:
            virtual ~GLContext();
            virtual GLContextState& state();
            virtual void store();
            virtual void restore();
            virtual void init();
            virtual void set(kk::CString name,GLProgram * program);
            virtual GLProgram * get(kk::CString name);
            virtual kk::Int width();
            virtual void setWidth(kk::Int v);
            virtual kk::Int height();
            virtual void setHeight(kk::Int v);
            virtual kk::Float scale();
            virtual void setScale(kk::Float v);
            virtual GLTimeInterval speed();
            virtual void setSpeed(GLTimeInterval v);
            
            virtual void drawTexture(GLTexture * texture,vec4 dest,vec4 src);
            
            static kk::IntProperty Property_width;
            static kk::IntProperty Property_height;
            static kk::Int64Property Property_speed;
            static kk::FloatProperty Property_scale;
            static kk::Property *Propertys[];
            
        protected:
            std::vector<GLContextState> _states;
            std::map<std::string,GLProgram *> _programs;
            kk::Int _width;
            kk::Int _height;
            kk::Float _scale;
            GLTimeInterval _speed;
        };
        
        class GLDrawable {
        public:
            virtual void draw(GLContext * ctx) = 0;
        };
        
        class GLTexture;
        
        class GLElement : public GLDrawable, public kk::Element {
        DEF_CLASS(GLElement)
        public:
            virtual vec3& position();
            virtual void setPosition(vec3& v);
            virtual mat4& transform();
            virtual void setTransform(mat4& v);
            virtual kk::Float opacity();
            virtual void setOpacity(kk::Float v);
            virtual vec3& scale();
            virtual void setScale(vec3& v);
            virtual void draw(GLContext * ctx);
            virtual void init();
            
            virtual GLTexture * getTexture(kk::CString name);
            
            static Vec3Property Property_position;
            static Vec3Property Property_scale;
            static Mat4Property Property_transform;
            static kk::FloatProperty Property_opacity;
            static kk::Property * Propertys[];
            
        protected:
            virtual void onDraw(GLContext * ctx);
            vec3 _position;
            vec3 _scale;
            mat4 _transform;
            kk::Float _opacity;
        };
        
        class GLTexture;
        
        class GLImageElement : public GLElement {
        DEF_CLASS(GLImageElement)
        public:
            virtual CString name();
            virtual void setName(CString name);
            
            virtual vec2& size();
            virtual void setSize(vec2& size);
            
            virtual vec2& anchor();
            virtual void setAnchor(vec2& anchor);
            
            virtual void init();
            
            static kk::StringProperty Property_name;
            static Vec2Property Property_size;
            static Vec2Property Property_anchor;
            static kk::Property * Propertys[];
            
        protected:
            virtual void onDraw(GLContext * ctx);
            GLTexture * _texture;
            kk::String _name;
            vec2 _size;
            vec2 _anchor;
        };
        
        class GLTextElement : public GLElement {
            DEF_CLASS(GLTextElement)
        public:
            virtual ~GLTextElement();
            virtual CString text();
            virtual void setText(CString v);
            
            virtual kk::Float maxWidth();
            virtual void setMaxWidth(kk::Float size);
            
            virtual vec2& size();
            
            virtual kk::CString fontFamily();
            virtual void setFontFamily(kk::CString v);
            
            virtual kk::Float fontSize();
            virtual void setFontSize(kk::Float v);
            
            virtual vec4& color();
            virtual void setColor(vec4& v);
            
            virtual vec2& anchor();
            virtual void setAnchor(vec2& anchor);
            
            virtual void init();
            
            static kk::StringProperty Property_text;
            static kk::FloatProperty Property_maxWidth;
            static Vec2Property Property_size;
            static Vec2Property Property_anchor;
            static kk::StringProperty Property_fontFamily;
            static kk::FloatProperty Property_fontSize;
            static Vec4Property Property_color;
            static kk::Property * Propertys[];
            
        protected:
            virtual void onDraw(GLContext * ctx);
            kk::String _text;
            kk::String _fontFamily;
            kk::Float _maxWidth;
            kk::Float _fontSize;
            vec4 _color;
            GLTexture * _texture;
            vec2 _size;
            vec2 _anchor;
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
        
        class GLTextureProvider {
        public:
            virtual GLTexture * getTexture(kk::CString name) = 0;
        };
        
        extern GLTexture * GLCreateTexture(kk::Application * app,kk::CString path);
        
        extern vec2 GLStringSize(kk::CString string,kk::CString fontFamily,kk::Float fontSize,kk::Float maxWidth);
        
        extern GLTexture * GLCreateStringTexture(kk::CString string,kk::CString fontFamily,kk::Float fontSize,vec4 textColor,kk::Float maxWidth);
        
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
