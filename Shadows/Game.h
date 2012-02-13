#ifndef CubeFX_Game_h
#define CubeFX_Game_h

#include "Scene.h"
#include "Clock.h"

class Game {
  
public:
  
  static Game* instance();
  
public:
  
  void init_with_scene(Scene* scene);
  
  void changeScene(Scene* scene);
  
  void main_loop();
  
private:
  
  Game();
  
private:
  
  Scene* runningScene_;
  Scene* nextScene_;
  
  Clock clock_;
  
};

#endif
