#ifndef DEFERRED_SPOT_LIGHTS_PASS_H
#define DEFERRED_SPOT_LIGHTS_PASS_H

#include "maths/Vector2.h"

#include "IDeferredPass.h"

class IEffect;

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

  IEffect* effect_;

  unsigned int lightMapRenderTarget_;
  
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;

  Vector2 halfPixel_;

  unsigned int quadVbo_;

};

#endif
