#ifndef CubeFX_Game_h
#define CubeFX_Game_h

#include "Clock.h"

class Renderer;
class Scene;

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
  
  Renderer* renderer_;
  
  Clock clock_;
  
};

#endif
