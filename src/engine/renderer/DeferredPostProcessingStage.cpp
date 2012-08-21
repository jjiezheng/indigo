#include "DeferredPostProcessingStage.h"

#include "GraphicsInterface.h"

#include "Color4.h"

#include "DeferredSSAOPass.h"
#include "DeferredFXAAPass.h"
#include "IDeferredRenderTargetContainer.h"

void DeferredPostProcessingStage::init(const CSize& screenSize) {    
  IDeferredPostProcessingPass* ssaoPass = new DeferredSSAOPass();
  passes_.push_back(ssaoPass);

  IDeferredPostProcessingPass* fxaaPass = new DeferredFXAAPass();
  passes_.push_back(fxaaPass);

  for (std::vector<IDeferredPostProcessingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->init(screenSize);
  }
}

void DeferredPostProcessingStage::render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Post Processing", Color4::GREEN);

  finalComposition_ = inputMap;

  for (std::vector<IDeferredPostProcessingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    finalComposition_ = (*i)->render(viewer, finalComposition_, initStage);
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredPostProcessingStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  for (std::vector<IDeferredPostProcessingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    renderTargetContainer->addRenderTarget((*i)->passName(), (*i)->passMap());
  }
}
