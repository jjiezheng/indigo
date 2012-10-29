#ifndef GAME_H
#define GAME_H

#include "memory/ScopeStack.h"
#include "core/Clock.h"

#include "renderer/World.h"
#include "renderer/SceneContext.h"
#include "renderer/Renderer3dDeferred.h"
#include "renderer/Camera.h"
#include "renderer/UI.h"

#include "input/IKeyboardListener.h"

class Game : public IKeyboardListener {
    
public:
  
  void init(ScopeStack* systemStack, const char* sceneFile);
  
  void mainLoop();

  void destroy();

public:

  void keyUp(int keyCode);
  
private:
  
  UI ui_;
  Camera camera_;
  Renderer3dDeferred renderer_;
  Clock clock_;
  World world_;  
  SceneContext sceneContext_;

};

#endif
