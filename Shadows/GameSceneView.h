#ifndef GameSceneView_H_
#define GameSceneView_H_

#include "SceneNode.h"

class GameSceneView : public SceneNode {
  
public:
  
  static GameSceneView* view();
  
public:
  
  void init();
  
};

#endif
