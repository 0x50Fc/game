// #include "GLSLTexture.h"

#ifndef kk_glsl_GLSLTexture_h
#define kk_glsl_GLSLTexture_h

#ifdef __APPLE__
#include <KKGame/kk.h>
#include <KKGame/kk-gl.h>
#endif

namespace kk {
	namespace glsl {
		extern kk::gl::GLProgram * GLSLTextureCreate();
	}
}
#endif
