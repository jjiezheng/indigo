#include "Game.h" 

#include "renderer/Camera.h"
#include "renderer/WorldLoader.h"

#include "renderer/GraphicsInterface.h"
#include "maths/Angles.h"

#include "platform/WindowsUtils.h"

void Game::init(const char* sceneFile) {
  clock_.init();
  properties_.init();
  
  camera_.translateY(4.0f);
  camera_.rotateX(toRadians(-90));
  camera_.setPerspective(toRadians(45.0f), GraphicsInterface::aspectRatio(), 0.5f, 1000.0f);
  
  renderer_.init(GraphicsInterface::screenSize());

  WindowsUtils::setKeyboardListener(this);

  WorldLoader loader; 
  loader.loadFromSceneFile(sceneFile, world_, sceneContext_);
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  
  renderer_.render(&camera_, world_, sceneContext_);
}

void Game::keyUp(int keyCode) {
  LOG(LOG_CHANNEL_TEMP, "%d%", keyCode);
}
