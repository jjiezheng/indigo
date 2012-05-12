#ifndef GameScene_H_
#define GameScene_H_

#include "renderer/Scene.h"

class GameScene : public Scene {
  
public:
  
  static GameScene* scene();
  
private:
  
  void init();
  
};

#endif
