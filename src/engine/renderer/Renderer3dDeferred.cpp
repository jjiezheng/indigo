#include "Renderer3dDeferred.h"

#include "memory/Allocation.h"

#include "IDeferredPass.h"
#include "DeferredClearBuffersPass.h"
#include "DeferredGeometryPass.h"
#include "DeferredDirectionalLightsPass.h"
#include "DeferredPointLightsPass.h"
#include "DeferredCompositionPass.h"
#include "DeferredSpotLightsPass.h"
#include "DeferredFXAAPass.h"
#include "DeferredShadowPass.h"
#include "DeferredFullScreenBlurPass.h"
#include "DeferredPresentPass.h"

#include "GraphicsInterface.h"

Renderer3dDeferred::~Renderer3dDeferred() {
  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    SAFE_DELETE(*i);
  }
}

void Renderer3dDeferred::init(const CSize& screenSize) {
  colorMapTexture_ = GraphicsInterface::createTexture(screenSize);
  colorRenderTarget_ = GraphicsInterface::createRenderTarget(colorMapTexture_);

  normalMapTexture_ = GraphicsInterface::createTexture(screenSize);
  normalRenderTarget_ = GraphicsInterface::createRenderTarget(normalMapTexture_);

  depthMapTexture_ = GraphicsInterface::createTexture(screenSize);
  depthRenderTarget_ = GraphicsInterface::createRenderTarget(depthMapTexture_);

  lightMapTexture_ = GraphicsInterface::createTexture(screenSize);
  lightRenderTarget_ = GraphicsInterface::createRenderTarget(lightMapTexture_);

  compositionMapTexture_ = GraphicsInterface::createTexture(screenSize);
  compositionRenderTarget_ = GraphicsInterface::createRenderTarget(compositionMapTexture_);

  fxaaMapTexture_ = GraphicsInterface::createTexture(screenSize);
  fxaaRenderTarget_ = GraphicsInterface::createRenderTarget(fxaaMapTexture_);

  fullScreenBlurTexture_ = GraphicsInterface::createTexture(screenSize);
  fullScreenBlurRenderTarget_ = GraphicsInterface::createRenderTarget(fullScreenBlurTexture_);

  IDeferredPass* clearBuffersPass = new DeferredClearBuffersPass(colorRenderTarget_, depthRenderTarget_, lightRenderTarget_, normalRenderTarget_, compositionRenderTarget_);
  passes_.push_back(clearBuffersPass);

  IDeferredPass* geometryPass = new DeferredGeometryPass(colorRenderTarget_, normalRenderTarget_, depthRenderTarget_);
  passes_.push_back(geometryPass);

  /*IDeferredPass* directionalLightingPass = new DeferredDirectionalLightsPass(lightRenderTarget_, normalMapTexture_);
  passes_.push_back(directionalLightingPass);

  IDeferredPass* pointLightingPass = new DeferredPointLightsPass(lightRenderTarget_, normalMapTexture_, depthMapTexture_);
  passes_.push_back(pointLightingPass);

  IDeferredPass* spotLightingPass = new DeferredSpotLightsPass(lightRenderTarget_, normalMapTexture_, depthMapTexture_);
  passes_.push_back(spotLightingPass);

  IDeferredPass* compositionPass = new DeferredCompositionPass(compositionRenderTarget_, colorMapTexture_, lightMapTexture_);
  passes_.push_back(compositionPass);

  IDeferredPass* fxaaPass = new DeferredFXAAPass(fxaaRenderTarget_, compositionMapTexture_);
  passes_.push_back(fxaaPass);

  IDeferredPass* fullScreenBlurPass = new DeferredFullScreenBlurPass(fxaaMapTexture_, fullScreenBlurRenderTarget_);
  passes_.push_back(fullScreenBlurPass);*/

  IDeferredPass* presentPass = new DeferredPresentPass(compositionMapTexture_);
  passes_.push_back(presentPass);

  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->init();
  }
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->render(viewer, world, sceneContext);
  }
}
