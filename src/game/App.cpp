#include "App.h"

#include "platform/PlatformDefs.h"
#include "renderer/GraphicsInterface.h"
#include "maths/Random.h"

int App::run(const char* sceneFile) {
  Random::seed();

#ifdef PLATFORM_WINDOWS
  GraphicsInterface::init(GRAPHICSAPI_D3D11);
#endif

#ifdef PLATFORM_PS3
  GraphicsInterface::init(GRAPHICSAPI_PS3GCM);
#endif

  GraphicsInterface::openWindow(1024, 768, 1);

  game_.init(sceneFile);

  bool quit = false;  
  while (!quit) {
    game_.mainLoop();
    GraphicsInterface::swapBuffers();
    quit = GraphicsInterface::windowClosed();
  }

  return GraphicsInterface::closeWindow();
}