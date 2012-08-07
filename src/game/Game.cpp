#include "Game.h" 

#include "renderer/Camera.h"
#include "renderer/WorldLoader.h"

#include "renderer/GraphicsInterface.h"

void Game::init(const char* sceneFile) {
  clock_.init();
  properties_.init();
  
  camera_.translateZ(2.0f);
  camera_.setPerspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
  
  renderer_.init(GraphicsInterface::screenSize());

  WorldLoader loader; 
  loader.loadFromSceneFile(sceneFile, world_, sceneContext_);
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  
  renderer_.render(&camera_, world_, sceneContext_);
}