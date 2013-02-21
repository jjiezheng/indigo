#include "DeferredPresentStage.h"

#include "memory/Allocation.h"
#include "maths/Vector2.h"

#include "IEffect.h"

#include "Geometry.h"
#include "Color4.h"
#include "Color3.h"

#include "GraphicsInterface.h"

#include "EffectCache.h"

void DeferredPresentStage::init(const CSize& screenSize) {
  effect_ = EffectCache::instance()->loadEffect(IEffect::SHADER_FULLSCREEN_TEXTURE);
	effect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
  quadVbo_ = Geometry::screenPlane();
  
  textureId_ = GraphicsInterface::loadTexture("debug/mipmap_debug.dds");
}

void DeferredPresentStage::render(unsigned int presentTextureId, unsigned int depthTextureId) {
  GraphicsInterface::beginPerformanceEvent("Present");

  GraphicsInterface::resetRenderTarget(false);
  GraphicsInterface::setViewport(GraphicsInterface::screenSize());
  GraphicsInterface::clearActiveColorBuffers(Color4::CORNFLOWERBLUE);
  GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

  effect_->beginDraw();
	effect_->setUniform(GraphicsInterface::halfScreenPixel(), "HalfPixel");
  effect_->setTexture(presentTextureId, "ColorMap");
  
  GraphicsInterface::setRenderState(true);

	effect_->commitBuffers();
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  effect_->endDraw();

  GraphicsInterface::endPerformanceEvent();
}