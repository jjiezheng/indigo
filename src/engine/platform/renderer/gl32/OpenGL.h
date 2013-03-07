#ifndef OPENGL_H
#define OPENGL_H

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS

#pragma comment(lib, "glew32s.lib")

#include "gl/glew.h"
//#include "gl/wglew.h"

#pragma comment(lib,"opengl32.lib")
#include "core/StdInt.h"

#define WIN32_LEAN_AND_MEAN 
//#include <windows.h>

//#define GLCOREARB_PROTOTYPES 1
//#define GLFW_INCLUDE_CORE_ARB 1
//#define GLFW_NO_GLU 1
#include <GL/glfw.h>

#endif

#ifdef PLATFORM_LINUX	
	#define GLCOREARB_PROTOTYPES 1
	#include <GL/glcorearb.h>
	#include <GL/glfw.h>
#endif

#ifdef PLATFORM_MAC

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED 1
#define CGGL_NO_OPENGL 1
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/gltypes.h>
#include <OpenGL/glu.h>

#endif

#endif