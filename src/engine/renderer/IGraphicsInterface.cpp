#include "IGraphicsInterface.h"

#include "platform/PlatformDefs.h"

#include "Direct3D11GraphicsInterface.h"
#include "OpenGL21GraphicsInterface.h"

#include <assert.h>

IGraphicsInterface* IGraphicsInterface::createInterface(GraphicsAPIType graphicsAPIType) {
  if (graphicsAPIType == GRAPHICSAPI_D3D11) {
    return new Direct3D11GraphicsInterface();
  }

  if (graphicsAPIType == GRAPHICSAPI_OPENGL21) {
    return new OpenGL21GraphicsInterface();
  }

  assert(false);

  return 0;
}
