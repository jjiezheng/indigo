#include "Game.h" 

#include "renderer/GraphicsInterface.h"
#include "maths/Angles.h"

#include "renderer/WorldLoader.h"

#include "input/Pad.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"

#include "maths/Plane.h"
#include "maths/Point.h"

#include "entity/ActorRegistry.h"

void Game::init(const char* sceneFile) {
  CSize backBufferSize = GraphicsInterface::backBufferSize();
	ActorRegistry::registerActors(actorFactory_);
  renderer_.init(backBufferSize);
  ui_.init(&renderer_);

  Pad::init();
  Mouse::init();
  Point mousePosition((int)(backBufferSize.width / 2.0f), (int)(backBufferSize.height / 2.0f));
  Mouse::setPosition(mousePosition);
  Keyboard::init();

  clock_.init();
  
// 	camera_.translateZ(2.0f);
 	camera_.translateY(1.8f);
// 	camera_.rotateX(-1.0f);
	camera_.translateZ(4.0f);
	//camera_.rotateX(toRadians(-90));
  camera_.setIsPlayerControlled(false);
  
  camera_.setProjection(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 100.0f);

  if (sceneFile) {
		WorldLoader loader; 
		loader.loadFromSceneFile(sceneFile, world_, sceneContext_, actorFactory_);
  }

  Keyboard::setKeydownListener(this);  
  keyUp(KEY_BACKTICK);
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  Pad::update();
  Keyboard::update();
  ui_.update(dt);

	world_.update(dt);
  
	renderer_.render(&camera_, world_, sceneContext_);
	
//	world_.debugRender();

  ui_.render();  
}

void Game::keyUp(int keyCode) {
	LOG(LOG_CHANNEL_TEMP, "Keycode: %d", keyCode);

	static int mouseMode = 0;
	if (keyCode == KEY_BACKTICK) {
    LOG(LOG_CHANNEL_TEMP, "%d", mouseMode);
    switch(mouseMode++) {
      case 0: 
        Mouse::hideOSMouse(true);
        camera_.setIsPlayerControlled(true);
        ui_.showMouse(false);
        break;
      case 1:
        Mouse::hideOSMouse(true);
        camera_.setIsPlayerControlled(false);
        ui_.showMouse(true);
        break;
      case 2:
        Mouse::hideOSMouse(false);
        camera_.setIsPlayerControlled(false);
        ui_.showMouse(false);
        break;
    }

    if (mouseMode > 2) {
      mouseMode = 0;
    }

	}

	if (keyCode > KEY_0 - 1 && keyCode < KEY_9 + 1) {
	  int renderTargetgId = keyCode - KEY_1;
	  renderer_.presentRenderTarget(renderTargetgId);
  }
}

void Game::destroy() {
	ui_.destroy();
  renderer_.destroy();
  world_.destroy();
}
