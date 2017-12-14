#include "kk-config.h"
#include "GLSLTexture.h"

namespace kk {
	namespace glsl {
		kk::gl::GLProgram * GLSLTextureCreate(){ 
			return new kk::gl::GLProgram("\nattribute vec4 position;\nattribute vec2 texCoord;\n\nuniform\tmat4 transfrom;\n\n#ifdef GL_ES\nvarying mediump vec2 vTexCoord;\n#else\nvarying vec2 vTexCoord;\n#endif\n\nvoid main()\n{\n    gl_Position = transfrom * position;\n\tvTexCoord = texCoord;\n}\n","\n#ifdef GL_ES\nprecision lowp float;\n#endif\n\nvarying vec2 vTexCoord;\nuniform sampler2D texture;\n\nvoid main()\n{\n\tgl_FragColor =  texture2D(texture, vTexCoord);\n}\n");
		}
	}
}
