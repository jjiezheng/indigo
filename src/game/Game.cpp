#include "Game.h" 

#include "renderer/GraphicsInterface.h"
#include "maths/Angles.h"

#include "renderer/WorldLoader.h"

//#include "platform/WindowsUtils.h"

void Game::init(const char* sceneFile) {
  renderer_.init(GraphicsInterface::screenSize());

  clock_.init();
  
  camera_.translateZ(1.5f);
  
  camera_.setPerspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 1000.0f);

  if (sceneFile) {
    WorldLoader loader; 
    loader.loadFromSceneFile(sceneFile, world_, sceneContext_);
  }

  //WindowsUtils::setKeyboardListener(this);
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  
  renderer_.render(&camera_, world_, sceneContext_);
}

void Game::keyUp(int keyCode) {
  if (keyCode > 48 && keyCode < 58) {
	  int renderTargetgId = keyCode - 49;
	  renderer_.presentRenderTarget(renderTargetgId);
  }
}
