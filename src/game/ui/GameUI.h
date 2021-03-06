#ifndef GAMEUI_H
#define GAMEUI_H

#include "ui/UI.h"

class IRenderChannelInfoService;

class GameUI {

public:

  void init(IRenderChannelInfoService* renderChannelInfoService);

	void destroy();
  
public:
  
  void keyUp(int keyCode);

public:

  void render();

  void update(float dt);

public:

	void showMouse(bool isShowing);

private:

  UI ui_;

};

#endif