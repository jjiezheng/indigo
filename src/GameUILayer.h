#ifndef GameUILayer_H_
#define GameUILayer_H_

#include "Layer2d.h"

class GameUILayer : public Layer2d {
  
public:
  
  static 
  GameUILayer* layer();
  
private:
  
  void init();
  
private:
  
  GameUILayer() = default;
  
};

#endif
