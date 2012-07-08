#ifndef DEFERRED_DIRECTIONAL_LIGHTS_PASS_H
#define DEFERRED_DIRECTIONAL_LIGHTS_PASS_H

#include "IDeferredPass.h"

class IEffect;

class DeferredDirectionalLightsPass : public IDeferredPass {

public:

  DeferredDirectionalLightsPass(unsigned int lightMapRenderTarget, unsigned int normalMapTexture)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , normalMapTexture_(normalMapTexture) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int lightMapRenderTarget_;
  
  unsigned int normalMapTexture_;

  unsigned int quadVbo_;

  IEffect* directionalLightEffect_;

};

#endif
