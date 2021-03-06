#include "DeferredLightingRenderStage.h"

#include "GraphicsInterface.h"
#include "Color4.h"

#include "DeferredDirectionalLightsPass.h"
#include "DeferredSpotLightsPass.h"
#include "DeferredSkyBoxPass.h"

#include "IDeferredLightingPass.h"
#include "IDeferredRenderTargetContainer.h"

void DeferredLightingRenderStage::init(const CSize& screenSize) {
    lightMapTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R32G32B32A32);
    lightRenderTarget_ = GraphicsInterface::createRenderTarget(lightMapTexture_);

    lightFrameBuffer_ = GraphicsInterface::createFrameBuffer(lightRenderTarget_, false);

    //IDeferredLightingPass* directionalLightingPass = new DeferredDirectionalLightsPass();
   // passes_.push_back(directionalLightingPass);

    IDeferredLightingPass* spotLightingPass = new DeferredSpotLightsPass();
    passes_.push_back(spotLightingPass);

    for (std::vector<IDeferredLightingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
      (*i)->init(screenSize);
    }
}

void DeferredLightingRenderStage::render(IViewer* viewer, World& world, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Lighting");

  GraphicsInterface::setFrameBuffer(lightFrameBuffer_);
  GraphicsInterface::clearActiveColorBuffers(Color4::TRANSPAREN);

  for (std::vector<IDeferredLightingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->render(viewer, world, sceneContext, lightFrameBuffer_, initStage);
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredLightingRenderStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  for (std::vector<IDeferredLightingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->collectRenderTargets(renderTargetContainer);
  }

  renderTargetContainer->addRenderTarget("Final LightMap", lightMapTexture_);
}
