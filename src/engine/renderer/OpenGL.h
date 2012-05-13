#ifndef OPENGL_H
#define OPENGL_H

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
#include "gl/glew.h"
#pragma comment(lib,"opengl32.lib")
#include <GL/glfw.h>

#endif

#ifdef PLATFORM_MAC
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GL/glfw.h>
#endif

#endif