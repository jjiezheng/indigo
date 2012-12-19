#ifndef APP_H
#define APP_H

#include "Game.h"

class App {
  
public:
  
  void init(const char* sceneFile);
  
  void mainLoop();
  
  void destroy();
    
private:
  
  Game game_;
  
};

#endif
