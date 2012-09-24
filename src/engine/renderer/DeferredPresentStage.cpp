#include "DeferredPresentStage.h"

#include "IEffect.h"

#include "Geometry.h"
#include "Color4.h"

#include "GraphicsInterface.h"

void DeferredPresentStage::init(const CSize& screenSize) {
  effect_ = IEffect::effectFromFile("effects/deferred_fullscreen_texture.effect");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredPresentStage::render(unsigned int presentTextureId) {
  GraphicsInterface::beginPerformanceEvent("Present", Color4::GREEN);

  GraphicsInterface::resetRenderTarget();
  effect_->beginDraw();
  effect_->setTexture(presentTextureId, "texture");
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);

  GraphicsInterface::endPerformanceEvent();
}