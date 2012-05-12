#ifndef OPENGL_H
#define OPENGL_H

#include "platform/PlatformDefs.h"

#if PLATFORM == PLATFORM_WINDOWS
#include "gl/glew.h"
#pragma comment(lib,"opengl32.lib")
#endif

#if PLATFORM == PLATFORM_MAC
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#endif