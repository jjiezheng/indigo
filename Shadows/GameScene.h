#ifndef GameScene_H_
#define GameScene_H_

#include "Scene.h"

class GameScene : public Scene {
  
public:
  
  static GameScene* scene();
  
public:
  
  void update(float dt);
    
private:
  
  void init();
  
};

#endif
