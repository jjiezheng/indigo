#ifndef OPENGL_H
#define OPENGL_H

#ifdef _WIN32

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment(lib,"opengl32.lib")

#endif


#ifdef APPLE

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#endif

#endif