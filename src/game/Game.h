#ifndef GAME_H
#define GAME_H

#include "app/IGame.h"

#include "core/Clock.h"

#include "renderer/World.h"
#include "renderer/SceneContext.h"
#include "renderer/Renderer3dDeferred.h"
#include "renderer/Camera.h"
#include "ui/GameUI.h"
#include "editor/EditorLayer.h"

#include "input/IKeyboardListener.h"
#include "entity/ActorFactory.h"

class Game : public IGame, public IKeyboardListener {
  
public:
  
  void init(const char* sceneFile);
  
  void mainLoop();

  void destroy();

public:

  void keyUp(int keyCode);
  
private:
  
  GameUI ui_;
  Camera camera_;
  Renderer3dDeferred renderer_;
  Clock clock_;
  World world_;
  SceneContext sceneContext_;
	EditorLayer editor_;
	ActorFactory actorFactory_;

};

#endif
