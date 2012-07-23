#include "AverageBlur.h"

#include "maths/Vector2.h"

#include "GraphicsInterface.h"
#include "Geometry.h"
#include "Color4.h"
#include "IEffect.h"

void AverageBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;

  if (!outputRenderTarget_) {
    outputRenderTexture_ = GraphicsInterface::createTexture(bufferSize);
    outputRenderTarget_ = GraphicsInterface::createRenderTarget(outputRenderTexture_);
  }

  quadVbo_ = Geometry::screenPlane();
  effect_ = IEffect::effectFromFile("cgfx/average_blur.hlsl");
}

void AverageBlur::render(unsigned int sourceTexture) {
  GraphicsInterface::setRenderState(true);

  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(outputRenderTarget_, Color4::WHITE);

    Vector2 texelSize(1.0f / GraphicsInterface::screenWidth(), 1.0f / GraphicsInterface::screenHeight());
    effect_->setUniform(texelSize, "TexelSize");
    effect_->setTexture(sourceTexture, "SourceMap");

    effect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
  }

  GraphicsInterface::generateMipMaps(outputRenderTarget_);
}