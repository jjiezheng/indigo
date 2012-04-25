#ifndef FPSLabel_H_
#define FPSLabel_H_

#include "SceneNode.h"

#include <deque>

class FPSLabel : public SceneNode {
  
public:
  
  static 
  FPSLabel* label();
  
private:
  
  void init();
  
  void update(float dt);
  
private:
  
  FPSLabel();
  
private:

  std::deque<float> fpss_;
  float timeSkipAccum_;
  
};

#endif
