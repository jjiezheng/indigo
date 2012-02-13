#ifndef GameWorldLayer_H_
#define GameWorldLayer_H_

#include "Layer3d.h"

class GameWorldLayer : public Layer3d {
  
public:
  
  static
  GameWorldLayer* layer();
  
private:
  
  void init();
  
};

#endif
