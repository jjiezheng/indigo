#ifndef Scene_H_
#define Scene_H_

#include "SceneNode.h"

class Scene : public SceneNode {

public:
  
  void init();
  
  virtual
  void render();
  
  void renderDebug() const;
  
};

#endif
