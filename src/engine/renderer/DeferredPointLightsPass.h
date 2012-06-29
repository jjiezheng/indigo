#ifndef DEFERRED_POINT_LIGHTS_PASS_H
#define DEFERRED_POINT_LIGHTS_PASS_H

#include "maths/Vector2.h"

#include "IDeferredPass.h"

class IEffect;
class Model;

class DeferredPointLightsPass : public IDeferredPass {

public:

  DeferredPointLightsPass(unsigned int lightMapRenderTarget, unsigned int normalMapTexture, unsigned int depthMapTexture, unsigned int shadowMapTexture, const Vector2& halfPixel)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , normalMapTexture_(normalMapTexture)
    , depthMapTexture_(depthMapTexture)
    , shadowMapTexture_(shadowMapTexture_)
    , halfPixel_(halfPixel) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int lightMapRenderTarget_;
  
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;
  unsigned int shadowMapTexture_;

  unsigned int quadVbo_;

  IEffect* pointLightEffect_;
  Model* pointLightModel_;

  Vector2 halfPixel_;

};

#endif
