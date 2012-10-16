#include "AverageBlur.h"

#include "maths/Vector2.h"

#include "GraphicsInterface.h"
#include "Geometry.h"
#include "Color4.h"
#include "EffectCache.h"
#include "IEffect.h"

#include "memory/Allocation.h"

AverageBlur::~AverageBlur() {
  SAFE_DELETE(effect_);
}

void AverageBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;

  if (!outputRenderTarget_) {
    outputRenderTexture_ = GraphicsInterface::createTexture(bufferSize);
    outputRenderTarget_ = GraphicsInterface::createRenderTarget(outputRenderTexture_);
  }

  quadVbo_ = Geometry::screenPlane();
  effect_ = EffectCache::instance()->loadEffect("shaders/compiled/average_blur.shader");
}

void AverageBlur::render(unsigned int sourceTexture) {
  GraphicsInterface::beginPerformanceEvent("Average Blur");

  GraphicsInterface::setRenderState(true);

  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);

    Vector2 texelSize(1.0f / GraphicsInterface::backBufferWidth(), 1.0f / GraphicsInterface::backBufferHeight());
    effect_->setUniform(texelSize, "TexelSize");
    effect_->setTexture(sourceTexture, "SourceMap");

    effect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);         
  }

  //GraphicsInterface::generateMipMaps(outputRenderTexture_);
  GraphicsInterface::endPerformanceEvent();
}
