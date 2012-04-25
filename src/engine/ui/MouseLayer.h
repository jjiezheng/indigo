#ifndef MouseLayer_H_
#define MouseLayer_H_

#include "Layer2d.h"

class MouseLayer : public Layer2d {
  
public:
  
  static 
  MouseLayer* mouse();
  
private:
  
  void init();
  
  void update(float dt);
  
private:
  
  MouseLayer() = default;
  
};

#endif
