#include "IGraphicsInterface.h"

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
  #include "Direct3D11GraphicsInterface.h"
#endif

#if defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
  #include "OpenGL32GraphicsInterface.h"
#endif

#ifdef PLATFORM_PS3
  #include "PS3GCMGraphicsInterface.h"
#endif

IGraphicsInterface* IGraphicsInterface::createInterface() {
#ifdef PLATFORM_WINDOWS
    return new Direct3D11GraphicsInterface();
#endif

#if defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
  return new OpenGL32GraphicsInterface();
#endif

#ifdef PLATFORM_PS3
  return new PS3GCMGraphicsInterface();
#endif
}
