#ifndef GAMEUI_H
#define GAMEUI_H

#include "ui/UI.h"

class IRenderChannelInfoService;

class GameUI {

public:

  void init(IRenderChannelInfoService* renderChannelInfoService);

public:

  void render();

  void update(float dt);

private:

  UI ui_;

};

#endif