#ifndef OPENGL_H
#define OPENGL_H

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
#include "gl/glew.h"

#pragma comment(lib,"opengl32.lib")
#include <GL/glfw.h>

#endif

#ifdef PLATFORM_MAC
//#include <OpenGL/gl3.h>
//#include <OpenGL/gl3ext.h>
//#include <OpenGL/gltypes.h>
//#include <OpenGL/gl.h>
//typedef int64_t GLint64EXT;
//typedef uint64_t GLuint64EXT;

//#include <GL/glew.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GL/glfw.h>

#define glBindVertexArray glBindVertexArrayAPPLE
#define glGenVertexArrays glGenVertexArraysAPPLE

#endif

#endif