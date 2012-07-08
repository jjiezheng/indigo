#ifndef DEFERRED_SPOT_LIGHTS_PASS_H
#define DEFERRED_SPOT_LIGHTS_PASS_H

#include "IDeferredPass.h"

#include "GaussianBlur.h"

class IEffect;
class Model;

class DeferredSpotLightsPass : public IDeferredPass {

public:

  DeferredSpotLightsPass(unsigned int lightMapRenderTarget, unsigned int normalMapTexture, unsigned int depthMapTexture)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , normalMapTexture_(normalMapTexture)
    , depthMapTexture_(depthMapTexture) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  IEffect* lightEffect_;
  IEffect* shadowMapEffect_;

  unsigned int lightMapRenderTarget_;
  
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;

  GaussianBlur gaussianBlur_;

  Model* spotLightModel_;

};

#endif
