#ifndef RENDERER_SHADOW_H
#define RENDERER_SHADOW_H

class CSize;
class World;
class SceneContext;
class IViewer;
class IEffect;

class RendererShadow {
  
public:

  RendererShadow() 
    : depthShader(0)
    , shadowTexture_(0)
    , renderTarget_(0) { };

public:
  
  void init(const CSize& screenSize);
  
  void renderToShadowMap(IViewer* viewer, World& world, SceneContext& sceneContext);

  void renderDebug();
  
private:

  IEffect* depthShader;
  unsigned int shadowTexture_;
  unsigned int renderTarget_;
};

#endif
