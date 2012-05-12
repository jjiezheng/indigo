#ifndef MouseLayer_H_
#define MouseLayer_H_

#include "renderer/Layer2d.h"

class MouseLayer : public Layer2d {
  
public:
  
  static 
  MouseLayer* mouse();
  
private:
  
  void init();
  
  void update(float dt);
  
private:
  
  MouseLayer() { };
  
};

#endif
