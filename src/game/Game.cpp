#include "Game.h" 

#include "renderer/GraphicsInterface.h"
#include "maths/Angles.h"

#include "renderer/WorldLoader.h"

#include "input/Pad.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"

#include "maths/Plane.h"

#include "entity/ActorRegistry.h"

void Game::init(const char* sceneFile) {
  Pad::init();
  Mouse::init();
  Keyboard::init();

	ActorRegistry::registerActors(actorFactory_);

  renderer_.init(GraphicsInterface::backBufferSize());
//  ui_.init(&renderer_);

  clock_.init();
  
// 	camera_.translateZ(2.0f);
// 	camera_.translateY(5.3f);
// 	camera_.rotateX(-1.0f);
	camera_.translateZ(4.0f);
	//camera_.rotateX(toRadians(-90));
  camera_.setIsPlayerControlled(true);
  
  camera_.setProjection(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 30.0f);

  if (sceneFile) {
		WorldLoader loader; 
		loader.loadFromSceneFile(sceneFile, world_, sceneContext_, actorFactory_);
  }

  
  Keyboard::setKeydownListener(this);
  //Mouse::hideOSMouse(true);
  
  renderer_.presentRenderTarget(6);
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  Pad::update();
  Keyboard::update();
//  ui_.update(dt);

	world_.update(dt);
  
	renderer_.render(&camera_, world_, sceneContext_);
	
//	world_.debugRender();

//  ui_.render();  
}

void Game::keyUp(int keyCode) {
	if (keyCode > 47 && keyCode < 59) {
	  int renderTargetgId = keyCode - 49;// + 5;
	  renderer_.presentRenderTarget(renderTargetgId);
  }
}

void Game::destroy() {
	ui_.destroy();
  renderer_.destroy();
  world_.destroy();
}
