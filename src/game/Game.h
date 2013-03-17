#ifndef GAME_H
#define GAME_H

#include "app/IGame.h"

#include "core/Clock.h"

#include "renderer/World.h"
#include "renderer/SceneContext.h"
#include "renderer/Renderer3dDeferred.h"
#include "renderer/Camera.h"
#include "ui/GameUI.h"
#include "editor/Editor.h"

#include "input/IKeyboardListener.h"
#include "input/IMouseListener.h"

#include "entity/ActorFactory.h"

class Game : public IGame, public IKeyboardListener, public IMouseListener {
  
public:
  
  void init(const char* sceneFile);
  
  void mainLoop();

  void destroy();

public:

  void keyUp(KeyCode keyCode);

  void keyDown(KeyCode keyCode) { };

public:

	void mouseUp(MouseButton mouseButton);

  void mouseDown(MouseButton mouseButton);

  void mouseScroll(int delta);
 
private:
  
  GameUI ui_;
  Camera camera_;
  Renderer3dDeferred renderer_;
  Clock clock_;
  World world_;
  SceneContext sceneContext_;
	Editor editor_;
	ActorFactory actorFactory_;

};

#endif
