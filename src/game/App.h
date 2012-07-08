#ifndef APP_H
#define APP_H

#include "Game.h"

class App {
  
public:
  
  int run(const char* sceneFile);
  
private:
  
  Game game_;
  
};

#endif
