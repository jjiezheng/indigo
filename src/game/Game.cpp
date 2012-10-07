#include "Game.h" 

#include "renderer/GraphicsInterface.h"
#include "maths/Angles.h"

#include "renderer/WorldLoader.h"

#include "input/Pad.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"

void Game::init(const char* sceneFile) {
  Pad::init();
  Mouse::init();
  Keyboard::init();

  renderer_.init(GraphicsInterface::backBufferSize());

  clock_.init();
  
  camera_.translateZ(5.5f);
  camera_.translateY(0.0f);
  //camera_.rotateX(toRadians(-90));
  
  camera_.setPerspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 1000.0f);

  if (sceneFile) {
    WorldLoader loader; 
    loader.loadFromSceneFile(sceneFile, world_, sceneContext_);
  }
  
  Keyboard::setKeydownListener(this);
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  Pad::update();
  Keyboard::update();
  renderer_.render(&camera_, world_, sceneContext_);
}

void Game::keyUp(int keyCode) {
  if (keyCode > 47 && keyCode < 59) {
	  int renderTargetgId = keyCode - 49 + 5;
	  renderer_.presentRenderTarget(renderTargetgId);
  }
}

void Game::destroy() {
  renderer_.destroy();
  world_.destroy();
}
