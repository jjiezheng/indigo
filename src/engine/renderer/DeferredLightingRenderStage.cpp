#include "DeferredLightingRenderStage.h"

#include "GraphicsInterface.h"
#include "Color4.h"

#include "DeferredDirectionalLightsPass.h"
#include "DeferredSpotLightsPass.h"

#include "IDeferredLightingPass.h"

void DeferredLightingRenderStage::init(const CSize& screenSize) {
    lightMapTexture_ = GraphicsInterface::createTexture(screenSize);
    lightRenderTarget_ = GraphicsInterface::createRenderTarget(lightMapTexture_);

    IDeferredLightingPass* directionalLightingPass = new DeferredDirectionalLightsPass();
    passes_.push_back(directionalLightingPass);

    /*IDeferredPass* pointLightingPass = new DeferredPointLightsPass();
    passes_.push_back(pointLightingPass);*/

    IDeferredLightingPass* spotLightingPass = new DeferredSpotLightsPass();
    passes_.push_back(spotLightingPass);

    for (std::vector<IDeferredLightingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
      (*i)->init(screenSize);
    }
}

void DeferredLightingRenderStage::render(IViewer* viewer, World& world, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Lighting", Color4::GREEN);

  GraphicsInterface::clearRenderTarget(lightRenderTarget_, Color4::BLACK);

  for (std::vector<IDeferredLightingPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->render(viewer, world, sceneContext, lightRenderTarget_, initStage);
  }

  GraphicsInterface::endPerformanceEvent();
}
