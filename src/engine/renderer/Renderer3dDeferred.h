#ifndef RENDERER3D_DEFERRED_H
#define RENDERER3D_DEFERRED_H

class World;
class SceneContext;
class IViewer;
class CSize;
class IEffect;
class Model;

class Renderer3dDeferred {

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  void renderGeometry(IViewer* viewer, World& world, const SceneContext& sceneContext);
  void renderLights(IViewer* viewer, World& world, const SceneContext& sceneContext);
  void renderFinal(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorRenderTexture_;
  unsigned int colorRenderTarget_;

  unsigned int normalRenderTexture_;
  unsigned int normalRenderTarget_;

  unsigned int depthRenderTexture_;
  unsigned int depthRenderTarget_;

  unsigned int pointLightTexture_;
  unsigned int pointLightRenderTarget_;

  IEffect* pointLightEffect_;
  Model* pointLightModel_;

  IEffect* finalEffect_;
  unsigned int finalQuadVBOId_;
};

#endif
