// ------------------------------ GRemdeyExtensions.h ------------------------------ 

// --------------------------------------------------------
// © 2004-2008 Graphic Remedy. All Rights Reserved.
// --------------------------------------------------------
#ifndef __GREMDEYEXTENSIONS
#define __GREMDEYEXTENSIONS

#include "OpenGL.h"

void initGremedyExtension(void);

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

#ifdef __cplusplus
}
#endif

#endif /* __GREMDEYEXTENSIONS */

#ifdef PLATFORM_APPLE

#ifndef NS_GL_GET_PROC_ADDRESS_H
#define NS_GL_GET_PROC_ADDRESS_H

void* NSGLGetProcAddress(const char *name, const char* libraryPath);

#endif

#endif
