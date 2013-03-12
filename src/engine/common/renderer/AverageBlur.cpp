#include "AverageBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"
#include "EffectCache.h"
#include "core/String.h"

void AverageBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;
    
	verticalMapTexture_ = GraphicsInterface::createTexture(bufferSize, IGraphicsInterface::R32G32B32A32);
	verticalRenderTarget_ = GraphicsInterface::createRenderTarget(verticalMapTexture_);
	verticalFrameBuffer_ = GraphicsInterface::createFrameBuffer(verticalRenderTarget_, false);
  
  quadVbo_ = Geometry::screenPlane();
  
  verticalEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/average_blur_vertical.shader");
}

void AverageBlur::render(FrameBuffer outputFrameBuffer, TextureId outputTexture, TextureId sourceTexture, unsigned int iterations) {
  GraphicsInterface::setRenderState(true);
  
	for (unsigned int i = 0; i < iterations; i++) {
    
		GraphicsInterface::beginPerformanceEvent("Pass");
    
    GraphicsInterface::setFrameBuffer(outputFrameBuffer);
    GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);

    verticalEffect_->beginDraw();
    verticalEffect_->setTexture(outputTexture, "SourceMap");
    verticalEffect_->setUniform(1.0f / (float)bufferSize_.height, "TexelSize");

    verticalEffect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    verticalEffect_->endDraw();
    
		GraphicsInterface::endPerformanceEvent();
	}
}