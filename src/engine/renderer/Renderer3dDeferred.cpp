#include "Renderer3dDeferred.h"

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"

#include "GraphicsInterface.h"

void Renderer3dDeferred::init(const CSize& screenSize) {
  initStage_.init(screenSize);
  lightingStage_.init(screenSize);
  postProcessingStage_.init(screenSize);
  presentStage_.init(screenSize);
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  initStage_.render(viewer, world, sceneContext);
  lightingStage_.render(viewer, world, sceneContext, initStage_);
  postProcessingStage_.render(viewer, lightingStage_.lightMap(), initStage_);
  presentStage_.render(postProcessingStage_.finalComposition());
}
