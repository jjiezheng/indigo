// ------------------------------ GRemdeyExtensions.h ------------------------------ 

// --------------------------------------------------------
// © 2004-2008 Graphic Remedy. All Rights Reserved.
// --------------------------------------------------------
#ifndef __GREMDEYEXTENSIONS
#define __GREMDEYEXTENSIONS

#include "OpenGL.h"

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GLAPI
#define GLAPI extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------- GL_GREMEDY_string_marker ----------------------- */

//#ifndef GL_GREMEDY_string_marker
//#define GL_GREMEDY_string_marker 1

typedef void (APIENTRYP PFNGLSTRINGMARKERGREMEDYPROC) (GLsizei len, const GLvoid *string);
  
extern PFNGLSTRINGMARKERGREMEDYPROC glStringMarkerGREMEDY;

//#endif /* GL_GREMEDY_string_marke#r */

/* ----------------------- GL_GREMEDY_frame_terminator ----------------------- */

#ifndef GL_GREMEDY_frame_terminator
#define GL_GREMEDY_frame_terminator 1

typedef void (APIENTRYP PFNGLFRAMETERMINATORGREMEDYPROC) (void);

#endif /* GL_GREMEDY_frame_terminator */
  
void initGremedyExtension(void);

#ifdef __cplusplus
}
#endif

#endif /* __GREMDEYEXTENSIONS */

#ifdef __APPLE__

#ifndef NS_GL_GET_PROC_ADDRESS_H
#define NS_GL_GET_PROC_ADDRESS_H

void* NSGLGetProcAddress (const char *name);

#endif

#endif
