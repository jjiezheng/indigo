#ifndef GAME_H
#define GAME_H

#include "core/Clock.h"

#include "renderer/World.h"
#include "renderer/SceneContext.h"
#include "renderer/Renderer3dDeferred.h"
#include "renderer/Camera.h"
#include "renderer/UI.h"

#include "input/IKeyboardListener.h"

class ScopeStack;

class Game : public IKeyboardListener {
  
public:
  
  Game(ScopeStack* systemStack)
    : systemStack_(systemStack)
    , renderer_(systemStack) { }
  
public:
  
  void init(const char* sceneFile);
  
  void mainLoop();

  void destroy();

public:

  void keyUp(int keyCode);
  
private:
  
  ScopeStack* systemStack_;
  UI ui_;
  Camera camera_;
  Renderer3dDeferred renderer_;
  Clock clock_;
  World world_;  
  SceneContext sceneContext_;

};

#endif
