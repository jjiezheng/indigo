#ifndef RENDERER3D_H
#define RENDERER3D_H

class Camera;
class World;
class SceneContext;

class Renderer3d {
  
public:
  
  void render(const Camera& camera, const World& world, const SceneContext& sceneContext);
    
};

#endif
