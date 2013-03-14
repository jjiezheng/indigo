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
	editor_.init();

	//camera_.translateY(0.8f);
	camera_.translateZ(4.0f);
	camera_.setIsPlayerControlled(true);
	camera_.setProjection(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 100.0f);

  editor_.setCamera(&camera_);

	if (sceneFile) {
		WorldLoader loader; 
		loader.loadFromSceneFile(sceneFile, world_, sceneContext_, actorFactory_);
	}

	Keyboard::setKeydownListener(this);
	Mouse::setMouseListener(this);
}

void Game::mainLoop() {
  Pad::update();
  Keyboard::update();

	float dt = clock_.delta_time();
	camera_.update(dt);
	ui_.update(dt);
	world_.update(dt);
	editor_.update(dt);

	renderer_.render(&camera_, world_, sceneContext_);
	editor_.render(&camera_, world_);
	ui_.render();
}

void Game::mouseUp(MouseButton mouseButton) {
	editor_.mouseUp(mouseButton, world_);
}

void Game::keyUp(KeyCode keyCode) {
  ui_.keyUp(keyCode);
  LOG(LOG_CHANNEL_INPUT, "Key: %d", keyCode);

	if (KEY_BACKTICK == keyCode) {
		editor_.toggleVisible();
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

void Game::mouseScroll(int delta) {
  camera_.moveForward(0.01f * delta);
}
