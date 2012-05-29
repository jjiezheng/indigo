#ifndef RENDERER_SHADOW_H
#define RENDERER_SHADOW_H

class CSize;
class World;
class SceneContext;
class IViewer;

class RendererShadow {
  
public:
  
  void init(const CSize& screenSize);
  
  void renderToShadowMap(IViewer* viewer, const World& world, SceneContext& sceneContext);
  
private:

  unsigned int shadowMap_;

};

#endif
