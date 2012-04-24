#ifndef MODEL_H
#define MODEL_H

#include "SceneNode.h"

class Model : public SceneNode {
  
public:
  
  static Model* model(const char* filepath);
  
protected:
  
  Model() = default;
    
};

#endif
