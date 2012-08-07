#ifndef DEFERRED_SPOT_LIGHTS_PASS_H
#define DEFERRED_SPOT_LIGHTS_PASS_H

#include "IDeferredPass.h"

#include "GaussianBlur.h"

class IEffect;
class Model;

class DeferredSpotLightsPass : public IDeferredPass {

public:

  DeferredSpotLightsPass(unsigned int lightMapRenderTarget, unsigned int colorMapTexture, unsigned int normalMapTexture, unsigned int depthMapTexture)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , normalMapTexture_(normalMapTexture)
    , depthMapTexture_(depthMapTexture) 
    , spotLightRenderTarget_(0)
    , spotLightRenderTexture_(0)
    , quadVbo_(0)
    , spotLightModel_(0)
    , lightEffect_(0)
    , shadowMapEffect_(0)
    , accumulationEffect_(0) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int lightMapRenderTarget_;

  unsigned int colorMapTexture_;
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;

  unsigned int spotLightRenderTarget_;
  unsigned int spotLightRenderTexture_;

  unsigned int quadVbo_;

  GaussianBlur gaussianBlur_;

  Model* spotLightModel_;

  IEffect* lightEffect_;
  IEffect* shadowMapEffect_;
  IEffect* accumulationEffect_;

};

#endif
