#include "IGraphicsInterface.h"

#include "platform/PlatformDefs.h"

#include "Direct3D11GraphicsInterface.h"

IGraphicsInterface* IGraphicsInterface::createInterface() {
#ifdef PLATFORM_WINDOWS
  return new Direct3D11GraphicsInterface();
#endif
}
