#ifndef CubeFX_Game_h
#define CubeFX_Game_h

#include "Scene.h"
#include "Clock.h"

class Game {
  
public:
  
  static Game* game();
  
public:
  
  void init_with_scene(Scene* scene);
  
  void main_loop();
  
private:
  
  Scene* runningScene_;
  
  Clock clock_;
  
};

#endif
