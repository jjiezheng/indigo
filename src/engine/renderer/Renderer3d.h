#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <vector>

#include "Color3.h"

class Camera;
class Model;
class World;
class SceneContext;

class Renderer3d {
  
public:
  
  void render(const Camera* camera, const World& world, const SceneContext& sceneContext);
  
  void setBackgroundColor(const Color3& color);
  
    
private:
  
  Color3 backgroundColor_;
  
};

inline void Renderer3d::setBackgroundColor(const Color3 &backgroundColor) {
  backgroundColor_ = backgroundColor;
}

#endif
