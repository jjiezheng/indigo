#include "Game.h" 

#include "renderer/GraphicsInterface.h"
#include "maths/Angles.h"

#include "renderer/WorldLoader.h"

#include "input/Pad.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"

#include "maths/Plane.h"

#include "ui/FPSStats.h"
#include "ui/RenderChannelInfo.h"

#include "memory/Pools.h"

void Game::init(const char* sceneFile) {
  Pad::init();
  Mouse::init();
  Keyboard::init();

  renderer_.init(GraphicsInterface::backBufferSize());
//  ui_.init(GraphicsInterface::backBufferSize());
//
  clock_.init();

  camera_.translateZ(5.5f);
  camera_.translateY(0.0f);
  //camera_.rotateX(toRadians(-90));
  
  camera_.setProjection(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 1000.0f);

//
//	FPSStats* fpsStats = FPSStats::stats();
//	ui_.addControl(fpsStats);
//
//	RenderChannelInfo* renderChannelInfo = RenderChannelInfo::info(&renderer_);
//	ui_.addControl(renderChannelInfo);
//
  Keyboard::setKeydownListener(this);

  if (sceneFile) {
    ScopeStack* worldStack = syspool::stack->childStack();
    levelpool::setStack(worldStack);
    
    WorldLoader loader;
    loader.loadFromSceneFile(sceneFile, world_, sceneContext_);
  }
}
 
void Game::mainLoop() {
//  float dt = clock_.delta_time();
//  camera_.update(dt);
//  Pad::update();
//  Keyboard::update();
//  ui_.update(dt);
//
//  renderer_.render(&camera_, world_, sceneContext_);
//  ui_.render();
}

void Game::keyUp(int keyCode) {
//  if (keyCode > 47 && keyCode < 59) {
//	  int renderTargetgId = keyCode - 49;// + 5;
//	  renderer_.presentRenderTarget(renderTargetgId);
//  }
}

void Game::destroy() {
//  renderer_.destroy();
//  world_.destroy();
}
