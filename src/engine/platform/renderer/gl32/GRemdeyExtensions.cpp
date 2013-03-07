#include "GRemdeyExtensions.h"

//#include <GL/glx.h>

#include "platform/PlatformDefs.h"

PFNGLSTRINGMARKERGREMEDYPROC glStringMarkerGREMEDY = NULL;

#ifdef __APPLE__

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

void initGremedyExtension(void) {
#ifdef PLATFORM_APPLE
  glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)NSGLGetProcAddress("glStringMarkerGREMEDY");
#endif

#ifdef PLATFORM_LINUX
  glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)glXGetProcAddress((const GLubyte*)"glStringMarkerGREMEDY");
#endif
}
