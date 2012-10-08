#include "DeferredFXAAPass.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"
#include "Geometry.h"
#include "EffectCache.h"
#include "IEffect.h"

#include "maths/Vector2.h"

#include "IDeferredRenderTargetContainer.h"

#include "memory/Allocation.h"


void DeferredFXAAPass::init(const CSize& screenSize) {
  colorLumaTexture_ = GraphicsInterface::createTexture(screenSize);
  colorLumaTarget_ = GraphicsInterface::createRenderTarget(colorLumaTexture_);

  fxaaRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  fxaaRenderTarget_ = GraphicsInterface::createRenderTarget(fxaaRenderTexture_);

  fxaaEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/fxaa_main.shader");
  colorLumaEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/fxaa_color_luma.shader");

  quadVbo_ = Geometry::screenPlane();
}

unsigned int DeferredFXAAPass::render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("FXAA");

  {
    GraphicsInterface::beginPerformanceEvent("Color Luma");

    GraphicsInterface::setRenderTarget(colorLumaTarget_, false);

    colorLumaEffect_->setTexture(inputMap, "InputMap");

    colorLumaEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);

    GraphicsInterface::endPerformanceEvent();
  }

  {
    GraphicsInterface::beginPerformanceEvent("FXAA");

    GraphicsInterface::setRenderTarget(fxaaRenderTarget_, false);

    fxaaEffect_->setTexture(colorLumaTexture_, "FinalMap");

    CSize screenSize = GraphicsInterface::backBufferSize();
    Vector2 screenSizeInv;
    screenSizeInv.x = 1.0f / screenSize.width;
    screenSizeInv.y = 1.0f / screenSize.height;
    fxaaEffect_->setUniform(screenSizeInv, "ScreenSizeInv");

    fxaaEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();

  return fxaaRenderTexture_;
}

void DeferredFXAAPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("FXAA", fxaaRenderTexture_);
}
