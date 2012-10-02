#ifndef DEFERRED_SPOT_LIGHTS_PASS_H
#define DEFERRED_SPOT_LIGHTS_PASS_H

#include "IDeferredLightingPass.h"

#include "GaussianBlur.h"

class IEffect;
class Model;

class DeferredSpotLightsPass : public IDeferredLightingPass {

public:

  DeferredSpotLightsPass()
    : spotLightRenderTarget_(0)
    , spotLightRenderTexture_(0)
    , quadVbo_(0)
    , spotLightModel_(0)
    , lightEffect_(0)
    , shadowMapEffect_(0)
    , accumulationEffect_(0) { }

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapRenderTarget, const DeferredInitRenderStage& initStage);

private:

  unsigned int spotLightRenderTarget_;
  unsigned int spotLightRenderTexture_;

  unsigned int shadowMapDepthTexture_;

  unsigned int quadVbo_;

  GaussianBlur gaussianBlur_;

  Model* spotLightModel_;

  IEffect* lightEffect_;
  IEffect* shadowMapEffect_;
  IEffect* accumulationEffect_;

};

#endif
