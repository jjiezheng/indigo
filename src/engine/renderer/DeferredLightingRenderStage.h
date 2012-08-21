#ifndef DEFERRED_LIGHTING_RENDER_STAGE_H
#define DEFERRED_LIGHTING_RENDER_STAGE_H

#include "IDeferredRenderStage.h"

class IDeferredLightingPass;
class DeferredInitRenderStage;
class IDeferredRenderTargetContainer;

class DeferredLightingRenderStage : public IDeferredRenderStage {

public:

  DeferredLightingRenderStage()
    : lightMapTexture_(0)
    , lightRenderTarget_(0) { }

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

public:

  void DeferredLightingRenderStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

public:

  unsigned int lightMap() const;

private:

  unsigned int lightMapTexture_;
  unsigned int lightRenderTarget_;

  std::vector<IDeferredLightingPass*> passes_;

};

inline unsigned int DeferredLightingRenderStage::lightMap() const {
  return lightMapTexture_;
}

#endif