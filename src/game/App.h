#ifndef APP_H
#define APP_H

#include "Game.h"

class App {
  
public:
  
  int run();
  
private:
  
  static void keyFunction(int character, int down);
  
private:
  
  void keyUp(char character);
  
private:
  
  static App* app_;
  Game game_;
  
};

#endif
