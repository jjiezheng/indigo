#ifndef Scene_H_
#define Scene_H_

#include "SceneNode.h"
#include <vector>

class Light;
class Camera;
class Shader;

class Scene : public SceneNode {

public:
  
  void init();
  
  virtual
  void render();
  
  void addLight(Light* light);
  
  void addCamera(Camera* camera);
  
private:
  
  std::vector<Light*> lights_;
  std::vector<Camera*> cameras_;
  
};

#endif
