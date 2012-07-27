#ifndef DEFERRED_DIRECTIONAL_LIGHTS_PASS_H
#define DEFERRED_DIRECTIONAL_LIGHTS_PASS_H

#include "IDeferredPass.h"

class IEffect;

class DeferredDirectionalLightsPass : public IDeferredPass {

public:

  DeferredDirectionalLightsPass(unsigned int lightMapRenderTarget, unsigned int colorMapTexture, unsigned int normalMapTexture, unsigned int depthMapTexture)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , depthMapTexture_(depthMapTexture)
    , normalMapTexture_(normalMapTexture) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int lightMapRenderTarget_;
  
  unsigned int colorMapTexture_;
  unsigned int depthMapTexture_;
  unsigned int normalMapTexture_;

  unsigned int quadVbo_;

  unsigned int directionalLightRenderTarget_;
  unsigned int directionalLightRenderTexture_;

  IEffect* accumulationEffect_;
  IEffect* directionalLightEffect_;

};

#endif
