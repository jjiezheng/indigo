#include "GRemdeyExtensions.h"

#ifndef WIN32

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_LINUX
#include <GL/glx.h>
#endif

PFNGLSTRINGMARKERGREMEDYPROC glStringMarkerGREMEDY = NULL;

#ifdef PLATFORM_MAC

#include <stdlib.h>
#include <string.h>
#include <AvailabilityMacros.h>

#include <dlfcn.h>

void* NSGLGetProcAddress(const char *name, const char* libraryPath)
{
  static void* image = NULL;
  
  if (NULL == image) {
    image = dlopen(libraryPath, RTLD_LAZY);
  }
  
  if(!image) {
    return NULL;
  }
  
  void* addr = dlsym(image, (const char*)name);
  return addr;
}

#endif

#endif

void initGremedyExtension(void) {
#ifdef PLATFORM_MAC
  glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)NSGLGetProcAddress("glStringMarkerGREMEDY", "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL");
#endif

#ifdef PLATFORM_LINUX
  glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)glXGetProcAddress((const GLubyte*)"glStringMarkerGREMEDY");
#endif
}


