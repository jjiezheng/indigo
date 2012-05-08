#ifndef GAME_H
#define GAME_H

#include "Clock.h"
#include "World.h"
#include "SceneContext.h"
#include "Properties.h"

#include "Renderer3d.h"
#include "RendererShadow.h"

class Camera;
class Mesh;

class Game {
  
public:
  
  void init();
  
  void mainLoop();
  
  void keyUp(char character);
  
private:
  
  Camera* camera_;
  RendererShadow shadowRenderer_;
  Renderer3d renderer_;
  World world_;  
  Clock clock_;
  SceneContext sceneContext_;
  Properties properties_;
  
};

#endif
