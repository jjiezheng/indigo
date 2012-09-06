#include "IGraphicsInterface.h"

#include "platform/PlatformDefs.h"

#ifdef PLATFORM_WINDOWS
  #include "Direct3D11GraphicsInterface.h"
  #include "OpenGL21GraphicsInterface.h"
#endif

#ifdef PLATFORM_MAC
  #include "Direct3D11GraphicsInterface.h"
  #include "OpenGL21GraphicsInterface.h"
#endif

#ifdef PLATFORM_PS3
#include "PS3GCMGraphicsInterface.h"
#endif

#include <assert.h>

IGraphicsInterface* IGraphicsInterface::createInterface(GraphicsAPIType graphicsAPIType) {
#ifdef PLATFORM_WINDOWS
  if (graphicsAPIType == GRAPHICSAPI_D3D11) {
    return new Direct3D11GraphicsInterface();
  }
#endif

#ifdef PLATFORM_WINDOWS
  if (graphicsAPIType == GRAPHICSAPI_OPENGL21) {
    return new OpenGL21GraphicsInterface();
  }
#endif

#ifdef PLATFORM_MAC
  if (graphicsAPIType == GRAPHICSAPI_OPENGL21) {
    return new OpenGL21GraphicsInterface();
  }
#endif

#ifdef PLATFORM_PS3
  return new PS3GCMGraphicsInterface();
#endif

  assert(false);

  return 0;
}