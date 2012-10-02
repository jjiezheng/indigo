#include "DeferredPresentStage.h"

#include "IEffect.h"

#include "Geometry.h"
#include "Color4.h"
#include "Color3.h"

#include "GraphicsInterface.h"

void DeferredPresentStage::init(const CSize& screenSize) {
  effect_ = IEffect::effectFromFile(IEffect::SHADER_FULLSCREEN_TEXTURE);
  quadVbo_ = Geometry::screenPlane();
}

void DeferredPresentStage::render(unsigned int presentTextureId, unsigned int depthTextureId) {
  GraphicsInterface::beginPerformanceEvent("Present", Color4::GREEN);

  GraphicsInterface::resetRenderTarget(false);

  effect_->setTexture(presentTextureId, "ColorMap");
  effect_->setTexture(depthTextureId, "DepthMap");
  effect_->setUniform(Color3::CORNFLOWERBLUE, "BackgroundColor");
  GraphicsInterface::setRenderState(true);

  effect_->beginDraw();
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  effect_->endDraw();

  GraphicsInterface::endPerformanceEvent();
}