#ifndef DEFERRED_SPOT_LIGHTS_PASS_H
#define DEFERRED_SPOT_LIGHTS_PASS_H

#include "maths/Vector2.h"

#include "IDeferredPass.h"

class IEffect;
class Model;

class DeferredSpotLightsPass : public IDeferredPass {

public:

  DeferredSpotLightsPass(unsigned int lightMapRenderTarget, unsigned int normalMapTexture, unsigned int depthMapTexture, const Vector2& halfPixel)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , normalMapTexture_(normalMapTexture)
    , depthMapTexture_(depthMapTexture)
    , halfPixel_(halfPixel) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  IEffect* lightEffect_;
  IEffect* shadowMapEffect_;

  unsigned int lightMapRenderTarget_;
  
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;

  unsigned int shadowMapRenderTarget_;
  unsigned int shadowMapTexture_;

  Vector2 halfPixel_;

  Model* spotLightModel_;

};

#endif
