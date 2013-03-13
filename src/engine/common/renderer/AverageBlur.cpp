#include "AverageBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"
#include "EffectCache.h"
#include "core/String.h"

void AverageBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;

  blurMapTexture_ = GraphicsInterface::createTexture(bufferSize, IGraphicsInterface::R32G32B32A32);
  blurRenderTarget_ = GraphicsInterface::createRenderTarget(blurMapTexture_);
  blurFrameBuffer_ = GraphicsInterface::createFrameBuffer(blurRenderTarget_, false);
  
  quadVbo_ = Geometry::screenPlane();
  
  verticalEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/average_blur_vertical.shader");
}

void AverageBlur::render(FrameBuffer destFrameBuffer, TextureId destTexture, TextureId srcTexture, unsigned int iterations) {
  GraphicsInterface::setRenderState(true);

  FrameBuffer frameBufferA = blurFrameBuffer_;
  FrameBuffer frameBufferB = destFrameBuffer;

  TextureId textureA = srcTexture;
  TextureId textureB = blurMapTexture_;
  
	for (unsigned int i = 0; i < iterations; i++) {
    blur(frameBufferA, textureA);

    if (textureA == srcTexture) {
      textureA = destTexture;
    }

    {
      TextureId temp = textureA;
      textureA = textureB;
      textureB = temp;
    }

    {
      FrameBuffer temp = frameBufferA;
      frameBufferA = frameBufferB;
      frameBufferB = temp;
    }
  }
}

void AverageBlur::blur(FrameBuffer destFrameBuffer, TextureId srcTexture) {
  GraphicsInterface::beginPerformanceEvent("Pass");

  GraphicsInterface::setFrameBuffer(destFrameBuffer);
  GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
  GraphicsInterface::clearActiveDepthBuffer();
  GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

  verticalEffect_->beginDraw();
  verticalEffect_->setTexture(srcTexture, "SourceMap");
  verticalEffect_->setUniform(1.0f / (float)bufferSize_.height, "TexelSize");

  verticalEffect_->commitBuffers();
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  verticalEffect_->endDraw();

  GraphicsInterface::endPerformanceEvent();
}
