#ifndef OPENGL_H
#define OPENGL_H

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS

#include "gl/glew.h"
#include "gl/wglew.h"

#pragma comment(lib,"opengl32.lib")
//#include <GL/glfw.h>

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