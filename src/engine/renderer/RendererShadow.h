#ifndef RENDERER_SHADOW_H
#define RENDERER_SHADOW_H

class CSize;
class World;
class SceneContext;
class IViewer;
class IEffect;

class RendererShadow {
  
public:
  
  void init(const CSize& screenSize);
  
  void renderToShadowMap(IViewer* viewer, World& world, SceneContext& sceneContext);
  
private:

  IEffect* depthShader;
  unsigned int shadowTexture_;
  unsigned int shadowTexture2_;
  unsigned int renderTarget_;

};

#endif
