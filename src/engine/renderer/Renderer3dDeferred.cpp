#include "Renderer3dDeferred.h"

#include "memory/Allocation.h"

#include "IDeferredPass.h"
#include "DeferredClearBuffersPass.h"
#include "DeferredGeometryPass.h"
#include "DeferredDirectionalLightsPass.h"
#include "DeferredPointLightsPass.h"
#include "DeferredFinalPass.h"
#include "DeferredSpotLightsPass.h"
#include "DeferredFXAAPass.h"
#include "DeferredShadowPass.h"

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

  shadowMapTexture_ = GraphicsInterface::createTexture(screenSize);
  shadowRenderTarget_ = GraphicsInterface::createRenderTarget(shadowMapTexture_);

  finalMapTexture_ = GraphicsInterface::createTexture(screenSize);
  finalRenderTarget_ = GraphicsInterface::createRenderTarget(finalMapTexture_);

  Vector2 halfPixel(0.5f / screenSize.width, 0.5f / screenSize.height);

  IDeferredPass* clearBuffersPass = new DeferredClearBuffersPass(colorRenderTarget_, depthRenderTarget_, lightRenderTarget_, normalRenderTarget_, shadowRenderTarget_, finalRenderTarget_);
  passes_.push_back(clearBuffersPass);

  IDeferredPass* geometryPass = new DeferredGeometryPass(colorRenderTarget_, normalRenderTarget_, depthRenderTarget_);
  passes_.push_back(geometryPass);

  IDeferredPass* directionalLightingPass = new DeferredDirectionalLightsPass(lightRenderTarget_, normalMapTexture_, halfPixel);
  passes_.push_back(directionalLightingPass);

  IDeferredPass* pointLightingPass = new DeferredPointLightsPass(lightRenderTarget_, normalMapTexture_, depthMapTexture_, halfPixel);
  passes_.push_back(pointLightingPass);

  IDeferredPass* spotLightingPass = new DeferredSpotLightsPass(lightRenderTarget_, normalMapTexture_, depthMapTexture_, halfPixel);
  passes_.push_back(spotLightingPass);

  IDeferredPass* shadowPass = new DeferredShadowPass(shadowMapTexture_, shadowRenderTarget_, lightRenderTarget_, halfPixel);
  passes_.push_back(shadowPass);

  IDeferredPass* finalPass = new DeferredFinalPass(finalRenderTarget_, colorMapTexture_, lightMapTexture_, halfPixel);
  passes_.push_back(finalPass);

  IDeferredPass* fxaaPass = new DeferredFXAAPass(finalMapTexture_, halfPixel);
  passes_.push_back(fxaaPass);

  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->init();
  }
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->render(viewer, world, sceneContext);
  }
}
