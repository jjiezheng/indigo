#ifndef RENDERER3D_DEFERRED_H
#define RENDERER3D_DEFERRED_H

#include "maths/Vector2.h"

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

  void clearBuffers();
  void renderGeometry(IViewer* viewer, World& world, const SceneContext& sceneContext);
  void renderDirectionalLights(IViewer* viewer, World& world, const SceneContext& sceneContext);
  void renderPointLights(IViewer* viewer, World& world, const SceneContext& sceneContext);
  void renderFinal(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  Vector2 halfPixel_;

private:

  unsigned int colorMapTexture_;
  unsigned int colorRenderTarget_;

  unsigned int normalMapTexture_;
  unsigned int normalRenderTarget_;

  unsigned int depthMapTexture_;
  unsigned int depthRenderTarget_;

  unsigned int lightMapTexture_;
  unsigned int lightMapRenderTarget_;

  IEffect* directionalLightEffect_;

  IEffect* pointLightEffect_;
  Model* pointLightModel_;

  IEffect* finalEffect_;
  unsigned int finalQuadVBOId_;
};

#endif
