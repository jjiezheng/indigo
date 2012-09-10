#include "Renderer3dDeferred.h"

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"

#include "GraphicsInterface.h"

#include "DeferredRenderTarget.h"

#include "io/Log.h"

void Renderer3dDeferred::init(const CSize& screenSize) {
  initStage_.init(screenSize);
  initStage_.collectRenderTargets(this);

  lightingStage_.init(screenSize);
  //lightingStage_.collectRenderTargets(this);

  skyStage_.init(screenSize);
  //skyStage_.collectRenderTargets(this);
  
  postProcessingStage_.init(screenSize);
  //postProcessingStage_.collectRenderTargets(this);

  presentStage_.init(screenSize);
  
  presentRenderTarget(renderTargets_.size() - 1);
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  initStage_.render(viewer, world, sceneContext);
  //lightingStage_.render(viewer, world, sceneContext, initStage_);
  //skyStage_.render(viewer, world, lightingStage_);
  //postProcessingStage_.render(viewer, lightingStage_.lightMap(), initStage_);

  DeferredRenderTarget renderTargetToPresent = renderTargets_[activeRenderTargetIndex_];
  presentStage_.render(renderTargetToPresent.renderTargetId);
}

void Renderer3dDeferred::addRenderTarget(const std::string& renderTargetName, unsigned int renderTargetId) {
  DeferredRenderTarget renderTarget(renderTargetName, renderTargetId);
  renderTargets_.push_back(renderTarget);
}

void Renderer3dDeferred::presentRenderTarget(unsigned int renderTargetIndex) {
  if (renderTargetIndex < renderTargets_.size()) {
    activeRenderTargetIndex_ = renderTargetIndex;

    DeferredRenderTarget renderTargetToPresent = renderTargets_[activeRenderTargetIndex_];
    LOG(LOG_CHANNEL_RENDERER, "Presenting %s", renderTargetToPresent.name.c_str());
  
  } else {
    activeRenderTargetIndex_ = renderTargets_.size() - 1;
  }
}