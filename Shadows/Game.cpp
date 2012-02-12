#include "Game.h"

#include "Standard.h"

#include "Scheduler.h"

Game* Game::game() {
  Game* game = new Game();
  return game;
}

void Game::init_with_scene(Scene* scene) {  
  runningScene_ = scene;  
}

void Game::main_loop() {
  float dt = clock_.delta_time();
  Scheduler::instance()->update(dt);
  runningScene_->render();
}