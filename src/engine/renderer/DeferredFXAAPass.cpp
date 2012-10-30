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
  colorLumaTexture_ = GraphicsInterface::createTexture(GraphicsInterface::screenSize());
  colorLumaTarget_ = GraphicsInterface::createRenderTarget(colorLumaTexture_);
  colorLumaEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/fxaa_color_luma.shader");
	colorLumaEffect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);

  fxaaRenderTexture_ = GraphicsInterface::createTexture(GraphicsInterface::screenSize());
  fxaaRenderTarget_ = GraphicsInterface::createRenderTarget(fxaaRenderTexture_);
  fxaaEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/fxaa_main.shader");
  fxaaEffect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);

  quadVbo_ = Geometry::screenPlane();
}

unsigned int DeferredFXAAPass::render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("FXAA");

  GraphicsInterface::setViewport(GraphicsInterface::screenSize());

  {
    GraphicsInterface::beginPerformanceEvent("Color Luma");

    GraphicsInterface::setRenderTarget(colorLumaTarget_, false, GraphicsInterface::screenSize());
    GraphicsInterface::clearActiveColorBuffers(Color4::TRANSPAREN);

		colorLumaEffect_->setUniform(GraphicsInterface::halfPixel(), "HalfPixel");
    colorLumaEffect_->setTexture(inputMap, "InputMap");

    GraphicsInterface::setRenderState(true);

    colorLumaEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    colorLumaEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }

  {
    GraphicsInterface::beginPerformanceEvent("FXAA");

    GraphicsInterface::setRenderTarget(fxaaRenderTarget_, false, GraphicsInterface::screenSize());
    GraphicsInterface::clearActiveColorBuffers(Color4::TRANSPAREN);

    fxaaEffect_->setTexture(colorLumaTexture_, "FinalMap");

    CSize screenSize = GraphicsInterface::screenSize();
    Vector2 screenSizeInv;
    screenSizeInv.x = 1.0f / screenSize.width;
    screenSizeInv.y = 1.0f / screenSize.height;
    fxaaEffect_->setUniform(screenSizeInv, "ScreenSizeInv");

		fxaaEffect_->setUniform(Vector2((float)screenSize.width, (float)screenSize.height), "ScreenSize");

		fxaaEffect_->setUniform(GraphicsInterface::halfPixel(), "HalfPixel");

    GraphicsInterface::setRenderState(true);

    fxaaEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    fxaaEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();

  return fxaaRenderTexture_;
}

void DeferredFXAAPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("FXAA Luma", colorLumaTexture_);
  renderTargetContainer->addRenderTarget("FXAA Final", fxaaRenderTexture_);
}
