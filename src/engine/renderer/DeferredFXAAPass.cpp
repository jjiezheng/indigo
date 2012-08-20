#include "DeferredFXAAPass.h"

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"
#include "Geometry.h"

#include "maths/Vector2.h"

void DeferredFXAAPass::init(const CSize& screenSize) {
  fxaaRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  fxaaRenderTarget_ = GraphicsInterface::createRenderTarget(fxaaRenderTexture_);

  fxaaEffect_ = IEffect::effectFromFile("cgfx/deferred_fxaa.hlsl");
  quadVbo_ = Geometry::screenPlane();
}

unsigned int DeferredFXAAPass::render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("FXAA", Color4::ORANGE);

  GraphicsInterface::setRenderTarget(fxaaRenderTarget_, false);

  fxaaEffect_->setTexture(inputMap, "FinalMap");

  CSize screenSize = GraphicsInterface::screenSize();
  Vector2 screenSizeInv;
  screenSizeInv.x = 1.0f / screenSize.width;
  screenSizeInv.y = 1.0f / screenSize.height;
  fxaaEffect_->setUniform(screenSizeInv, "ScreenSizeInv");

  fxaaEffect_->beginDraw();
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);

  GraphicsInterface::endPerformanceEvent();

  return fxaaRenderTexture_;
}
