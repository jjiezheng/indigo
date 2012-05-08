#include "Game.h"

#include "Standard.h"

#include "Scheduler.h"
#include "Scene.h"
#include "Renderer.h"

#include "MacPlatform.h"
#include "ResourceCache.h"

#include "GameScene.h"

#include "Camera.h"
#include "FogTypes.h"

#include "WorldLoader.h"
#include "Box.h"

void Game::init() {  
  properties_.init();
  
  renderer_.setBackgroundColor(Color3(0, 1, 0));

  camera_ = Camera::camera();
  camera_->translateZ(10);
  camera_->translateY(1.8);
//  camera_->translateY(15);
//  camera_->rotateX(-60);
  
  Vector2 screenSize = MacPlatform::instance()->screen_size();
  float aspectRatio = screenSize.aspectRatio();
  
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
  camera_->setProjection(projection);

  WorldLoader loader;
  loader.loadFromSceneFile("amyrose.scene", world_, sceneContext_);
  
  sceneContext_.setFog(FOG_EXP, 0.66f, -10, -100, Color4(0.6f, 0.6f, 0.6f));
  
  shadowRenderer_.init(screenSize);
  renderer_.setBackgroundColor(Color3(0.4f, 0.6f, 0.93f));
}

void Game::mainLoop() {  
  float dt = clock_.delta_time();
  Scheduler::instance()->update(dt);   
  
  camera_->update(dt);
  
  shadowRenderer_.render(world_, sceneContext_);
  renderer_.render(camera_, world_, sceneContext_);

  if (properties_.getProperty(PROPERTY_RENDER_SHADOWMAP)) {
    shadowRenderer_.renderDebug(sceneContext_);
  }
}

void Game::keyUp(char character) {
  properties_.keyUp(character);
}
