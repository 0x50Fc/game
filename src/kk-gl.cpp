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
        
        Vec4Property::Vec4Property(Object * object,Property * property):kk::TProperty<vec4>(object,property) {
            
        }
        
        ScriptResult Vec4Property::getScript() {
            return 0;
        }
        
        ScriptResult Vec4Property::setScript() {
            return 0;
        }
        
        String Vec4Property::toString() {
            char v[255];
            snprintf(v, sizeof(v), "%g %g %g %g",_value.x,_value.y,_value.z,_value.w);
            return v;
        }
        
        void Vec4Property::set(CString value) {
            
        }
        
        void Vec4Property::set(vec4 value) {
            _value = value;
            change();
        }
        
        Vec3Property::Vec3Property(Object * object,Property * property):kk::TProperty<vec3>(object,property) {
            
        }
        
        ScriptResult Vec3Property::getScript() {
            return 0;
        }
        
        ScriptResult Vec3Property::setScript() {
            return 0;
        }
        
        String Vec3Property::toString() {
            char v[255];
            snprintf(v, sizeof(v), "%g %g %g",_value.x,_value.y,_value.z);
            return v;
        }
        
        void Vec3Property::set(CString value) {
            
        }
        
        void Vec3Property::set(vec3 value) {
            _value = value;
            change();
        }
        
        Mat4Property::Mat4Property(Object * object,Property * property):kk::TProperty<mat4>(object,property) {
            
        }
        
        ScriptResult Mat4Property::getScript() {
            return 0;
        }
        
        ScriptResult Mat4Property::setScript() {
            return 0;
        }
        
        String Mat4Property::toString() {
            return "";
        }
        
        void Mat4Property::set(CString value) {
            
        }
        
        void Mat4Property::set(mat4 value) {
            _value = value;
            change();
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
        
        GLContext::GLContext(ScriptContext context,ScriptPtr ptr):kk::Object(context,ptr) {
            
            GLContextState state;
            state.projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
            state.view = glm::mat4(1.0f);
            state.opacity = 1.0;
            
            _states.push_back(state);
            
        }
        
        vec3 GLElement::position(){
            return _position.get();
        }
        
        void GLElement::setPosition(vec3 v) {
            _position.set(v);
        }
        
        mat4 GLElement::transform() {
            return _transform.get();
        }
        
        void GLElement::setTransform(mat4 v) {
            _transform.set(v);
        }
        
        kk::Float GLElement::opacity() {
            return _opacity.get();
        }
        
        void GLElement::setOpacity(kk::Float v) {
            _opacity.set(v);
        }
        
        GLElement::GLElement(ScriptContext context,ScriptPtr ptr)
            :kk::Element(context,ptr),
            _position(this,&P::position),
            _transform(this,&P::transform),
            _opacity(this,&P::opacity)
        {
            _opacity.set(1);
        }
        
        void GLElement::onDraw(GLContext * ctx) {
        
        }
        
        void GLElement::draw(GLContext * ctx) {

            ctx->store();
            
            GLContextState & s = ctx->state() ;
            
            s.opacity = s.opacity * _opacity.get();
            s.view = glm::translate(s.view * s.view, _position.get()) ;

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
        :_id(0),_width(0),_height(0) {
            
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
