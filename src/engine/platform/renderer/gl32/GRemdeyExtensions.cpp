#include "GRemdeyExtensions.h"

PFNGLSTRINGMARKERGREMEDYPROC glStringMarkerGREMEDY = NULL;

void initGremedyExtension(void) {
  glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)NSGLGetProcAddress("glStringMarkerGREMEDY");
}

#include <stdlib.h>
#include <string.h>
#include <AvailabilityMacros.h>

#include <dlfcn.h>

void* NSGLGetProcAddress (const char *name)
{
  static void* image = NULL;
  
  if (NULL == image) {
    image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);
  }
  
  if(!image) {
    return NULL;
  }
  
  void* addr = dlsym(image, (const char*)name);
  return addr;
}
