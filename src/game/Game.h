#ifndef GAME_H
#define GAME_H

#include "core/Clock.h"
#include "config/Properties.h"

#include "renderer/World.h"
#include "renderer/SceneContext.h"
#include "renderer/Renderer3d.h"
#include "renderer/RendererShadow.h"
#include "renderer/Camera.h"

class Game {
  
public:
  
  void init();
  
  void mainLoop();
  
private:
  
  Camera camera_;
  RendererShadow shadowRenderer_;
  Renderer3d renderer_;
  World world_;  
  Clock clock_;
  SceneContext sceneContext_;
  Properties properties_;
};

#endif
