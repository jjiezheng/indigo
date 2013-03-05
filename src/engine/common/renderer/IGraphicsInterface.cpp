#include "IGraphicsInterface.h"

#include "platform/PlatformDefs.h"

#ifdef RENDERER_D3D
  #include "Direct3D11GraphicsInterface.h"
#endif

#if defined(RENDERER_OPENGL) || defined(RENDERER_OPENGL)
  #include "OpenGL32GraphicsInterface.h"
#endif

#ifdef RENDERER_GCM
  #include "PS3GCMGraphicsInterface.h"
#endif

#ifdef RENDERER_GNM
#include "GNMGraphicsInterface.h"
#endif

IGraphicsInterface* IGraphicsInterface::createInterface() {
#ifdef RENDERER_D3D
    return new Direct3D11GraphicsInterface();
#endif

#if defined(RENDERER_OPENGL) || defined(RENDERER_OPENGL)
  return new OpenGL32GraphicsInterface();
#endif

#ifdef RENDERER_GCM
  return new PS3GCMGraphicsInterface();
#endif

#ifdef RENDERER_GNM
  return new GNMGraphicsInterface();
#endif
}
