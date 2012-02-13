#ifndef Layer3d_H_
#define Layer3d_H_

#include "SceneNode.h"

class Light;
class Camera;

class Layer3d : public SceneNode {
  
protected:
  
  virtual void init();
  
public:
  
  void addLight(Light* light);
  
  void addCamera(Camera* camera);
  
  void render(Camera *camera, Shader *shader, const glm::mat4 &transform) const;
  
private:
  
  std::vector<Light*> lights_;
  std::vector<Camera*> cameras_;
  
};

#endif
