#ifndef TitleScene_H_
#define TitleScene_H_

#include "Scene.h"

class TitleScene : public Scene {
  
public:
  
  static TitleScene* scene();
  
private:
  
  void init();
  
private:
  
  TitleScene() = default;
  
};

#endif
