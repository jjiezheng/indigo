#ifndef Layer2d_H_
#define Layer2d_H_

#include "SceneNode.h"

class Layer2d : public SceneNode {
  
public:
  
  void render(Camera *camera, Shader *shader, const Matrix4x4& transform) const;
  
protected:
  
  virtual 
  void init();
  
private:
  
  Shader* shader_;
      
};

#endif
