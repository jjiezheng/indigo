#ifndef SPINNING_CUBE_H
#define SPINNING_CUBE_H


#include "entity/IActor.h"

class Model;
class Material;
class IEffect;

class SpinningCube : public IActor {
  
public:
  
  SpinningCube(Model* model)
    : model_(model)
    , time_(0) { }
  
public:
  
	void init() { };
  
	void update(float dt);
  
	void debugRender() { };
  
private:
  
  Model* model_;
  float time_;
  
};

#endif
