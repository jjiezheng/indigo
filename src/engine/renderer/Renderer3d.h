#ifndef RENDERER3D_H
#define RENDERER3D_H

class World;
class SceneContext;
class IViewer;

class Renderer3d {
  
public:
  
  void render(IViewer* viewer, const World& world, const SceneContext& sceneContext);
    
};

#endif
