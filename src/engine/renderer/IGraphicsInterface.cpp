#include "IGraphicsInterface.h"

#include "platform/PlatformDefs.h"
#include "memory/ScopeStack.h"

#ifdef PLATFORM_WINDOWS
  #include "Direct3D11GraphicsInterface.h"
#endif

#ifdef PLATFORM_MAC
  #include "OpenGL21GraphicsInterface.h"
#endif

#ifdef PLATFORM_PS3
  #include "PS3GCMGraphicsInterface.h"
#endif

#include "DefaultGraphicsInterface.h"

IGraphicsInterface* IGraphicsInterface::createInterface(ScopeStack* systemStack) {
#ifdef PLATFORM_WINDOWS
    return new Direct3D11GraphicsInterface();
#endif

#ifdef PLATFORM_MAC
  return systemStack->create<OpenGL21GraphicsInterface>();
#endif

#ifdef PLATFORM_PS3
  return new PS3GCMGraphicsInterface();
#endif
  
  return new DefaultGraphicsInterface();
}
