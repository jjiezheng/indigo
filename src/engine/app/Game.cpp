#include "Game.h"

#include "Standard.h"

#include "Scheduler.h"
#include "Scene.h"
#include "Renderer.h"

#include "MacPlatform.h"
#include "ResourceCache.h"

#include "GameScene.h"

static Game* instance_ = nullptr;

Game::Game() 
  : runningScene_(nullptr)
  , nextScene_(nullptr) { 
    renderer_ = Renderer::renderer();
}

Game* Game::instance() {
  if (!instance_) {
    instance_ = new Game();
    
    instance_->init_with_scene(GameScene::scene());
  }
  return instance_;
}

void Game::init_with_scene(Scene* scene) {  
  runningScene_ = scene;  
}

void Game::changeScene(Scene *scene) {
  nextScene_ = scene;
}

void Game::main_loop() {  
  if (nextScene_) {
    SAFE_DELETE(runningScene_);
    runningScene_ = nextScene_;
    nextScene_ = nullptr;
  }
  
  float dt = clock_.delta_time();
  Scheduler::instance()->update(dt);
  
  renderer_->render(runningScene_);
}
