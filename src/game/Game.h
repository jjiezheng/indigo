#ifndef GAME_H
#define GAME_H

#include "core/Clock.h"
#include "config/Properties.h"

#include "renderer/World.h"
#include "renderer/SceneContext.h"
#include "renderer/Renderer3dDeferred.h"
#include "renderer/Camera.h"

#include "input/IKeyboardListener.h"

class Game : public IKeyboardListener {
  
public:
  
  void init(const char* sceneFile);
  
  void mainLoop();

public:

  void keyUp(int keyCode);
  
private:
  
  Camera camera_;
  Renderer3dDeferred renderer_;
  World world_;  
  Clock clock_;
  SceneContext sceneContext_;
  Properties properties_; 

};

#endif
