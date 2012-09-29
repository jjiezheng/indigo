#include "DeferredPresentStage.h"

#include "IEffect.h"

#include "Geometry.h"
#include "Color4.h"

#include "GraphicsInterface.h"

void DeferredPresentStage::init(const CSize& screenSize) {
  effect_ = IEffect::effectFromFile(IEffect::SHADER_FULLSCREEN_TEXTURE);
  quadVbo_ = Geometry::screenPlane();
}

void DeferredPresentStage::render(unsigned int presentTextureId) {
  GraphicsInterface::beginPerformanceEvent("Present", Color4::GREEN);

  GraphicsInterface::resetRenderTarget();
  GraphicsInterface::clearBuffer(Color4::CORNFLOWERBLUE);

  effect_->beginDraw();
  effect_->setTexture(presentTextureId, "texture");
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  effect_->endDraw();

  GraphicsInterface::endPerformanceEvent();
}