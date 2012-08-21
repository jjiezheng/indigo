#include "Renderer3dDeferred.h"

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"

#include "GraphicsInterface.h"

#include "DeferredRenderTarget.h"

void Renderer3dDeferred::init(const CSize& screenSize) {
  initStage_.init(screenSize);
  initStage_.collectRenderTargets(this);

  lightingStage_.init(screenSize);
  //lightingStage_.collectRenderTargets(this);
  
  postProcessingStage_.init(screenSize);
  //postProcessingStage_.collectRenderTargets(this);

  presentStage_.init(screenSize);
  //presentStage_.collectRenderTargets(this);

  setActiveRenderTargetIndex(renderTargets_.size() - 1);
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  initStage_.render(viewer, world, sceneContext);
  lightingStage_.render(viewer, world, sceneContext, initStage_);
  postProcessingStage_.render(viewer, lightingStage_.lightMap(), initStage_);

  DeferredRenderTarget renderTargetToPresent = renderTargets_[activeRenderTargetIndex_];
  presentStage_.render(lightingStage_.lightMap());
}

void Renderer3dDeferred::addRenderTarget(const std::string& renderTargetName, unsigned int renderTargetId) {
  DeferredRenderTarget renderTarget(renderTargetName, renderTargetId);
  renderTargets_.push_back(renderTarget);
}

void Renderer3dDeferred::setActiveRenderTargetIndex(unsigned int renderTargetIndex) {
  if (renderTargetIndex < renderTargets_.size()) {
    activeRenderTargetIndex_ = renderTargetIndex;
  } else {
    activeRenderTargetIndex_ = renderTargets_.size() - 1;
  }
}