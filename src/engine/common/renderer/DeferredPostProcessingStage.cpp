#include "DeferredPostProcessingStage.h"

#include "GraphicsInterface.h"

#include "Color4.h"

#include "DeferredSSAOPass.h"
#include "DeferredGodRaysPass.h"
#include "DeferredFXAAPass.h"
#include "IDeferredRenderTargetContainer.h"

#include "memory/Allocation.h"

void DeferredPostProcessingStage::init(const CSize& screenSize) { 
  //IDeferredPostProcessingPass* ssaoPass = new DeferredSSAOPass();
  //passes_.push_back(ssaoPass);

//   IDeferredPostProcessingPass* godRaysPass = new DeferredGodRaysPass();
//   passes_.push_back(godRaysPass);
 
  IDeferredPostProcessingPass* fxaaPass = new DeferredFXAAPass();
  passes_.push_back(fxaaPass);

  for (std::vector<IDeferredPostProcessingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->init(screenSize);
  }
}

void DeferredPostProcessingStage::render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Post Processing");

  finalComposition_ = inputMap;

  for (std::vector<IDeferredPostProcessingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    finalComposition_ = (*i)->render(viewer, finalComposition_, sceneContext, initStage);
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredPostProcessingStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  for (std::vector<IDeferredPostProcessingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->collectRenderTargets(renderTargetContainer);
  }
}