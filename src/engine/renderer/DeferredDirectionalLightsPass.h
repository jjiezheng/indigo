#ifndef DEFERRED_DIRECTIONAL_LIGHTS_PASS_H
#define DEFERRED_DIRECTIONAL_LIGHTS_PASS_H

#include "IDeferredLightingPass.h"

class DeferredInitRenderStage;
class IEffect;

class DeferredDirectionalLightsPass : public IDeferredLightingPass {

public:

  DeferredDirectionalLightsPass()
    : quadVbo_(0)
    , directionalLightRenderTarget_(0)
    , directionalLightRenderTexture_(0)
    , accumulationEffect_(0)
    , directionalLightEffect_(0) { }

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapTexture, const DeferredInitRenderStage& initStage);

private:

  unsigned int quadVbo_;

  unsigned int directionalLightRenderTarget_;
  unsigned int directionalLightRenderTexture_;

  IEffect* accumulationEffect_;
  IEffect* directionalLightEffect_;

};

#endif
