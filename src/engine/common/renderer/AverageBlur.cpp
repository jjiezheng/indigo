#include "AverageBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"
#include "EffectCache.h"
#include "core/String.h"

void AverageBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;
  
  horizontalMapTexture_ = GraphicsInterface::createTexture(bufferSize, IGraphicsInterface::R32G32B32A32);
  horizontalRenderTarget_ = GraphicsInterface::createRenderTarget(horizontalMapTexture_);
  horizonalFrameBuffer_ = GraphicsInterface::createFrameBuffer(horizontalRenderTarget_, false);
  
	verticalMapTexture_ = GraphicsInterface::createTexture(bufferSize, IGraphicsInterface::R32G32B32A32);
	verticalRenderTarget_ = GraphicsInterface::createRenderTarget(verticalMapTexture_);
	verticalFrameBuffer_ = GraphicsInterface::createFrameBuffer(verticalRenderTarget_, false);
  
  quadVbo_ = Geometry::screenPlane();
  
  horizontalEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/average_blur_horizontal.shader");
  verticalEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/average_blur_vertical.shader");
	outputEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_fullscreen_texture.shader");
}

void AverageBlur::render(FrameBuffer outputFrameBuffer, TextureId outputTexture, TextureId sourceTexture, unsigned int iterations) {
  GraphicsInterface::setRenderState(true);
  
	for (unsigned int i = 0; i < iterations; i++) {
    
		GraphicsInterface::beginPerformanceEvent("Pass");
    
    //		{
    //			GraphicsInterface::beginPerformanceEvent("Horizontal");
    //
    //			GraphicsInterface::setFrameBuffer(horizonalFrameBuffer_);
    //			GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
    //
    //			horizontalEffect_->beginDraw();
    //			horizontalEffect_->setTexture(sourceTexture, "SourceMap");
    //			horizontalEffect_->setUniform(1.0f/(float)bufferSize_.width, "TexelSize");
    //
    //			horizontalEffect_->commitBuffers();
    //			GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    //			horizontalEffect_->endDraw();
    //
    //			GraphicsInterface::endPerformanceEvent();
    //		}
    
    //		{
    //			GraphicsInterface::beginPerformanceEvent("Vertical");
    //
    //			GraphicsInterface::setFrameBuffer(verticalFrameBuffer_);
    //			GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
    //
    //			verticalEffect_->beginDraw();
    //			verticalEffect_->setTexture(horizontalMapTexture_, "SourceMap");
    //			verticalEffect_->setUniform(1.0f/(float)bufferSize_.height, "TexelSize");
    //
    //			verticalEffect_->commitBuffers();
    //			GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    //			verticalEffect_->endDraw();
    //
    //			GraphicsInterface::endPerformanceEvent();
    //		}
    
		sourceTexture = verticalMapTexture_;
    
		GraphicsInterface::endPerformanceEvent();
	}
  
	{
    //		GraphicsInterface::beginPerformanceEvent("Output");
    //
    //		GraphicsInterface::setFrameBuffer(outputFrameBuffer);
    //		GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
    //
    //		outputEffect_->beginDraw();
    //		outputEffect_->setTexture(verticalMapTexture_, "ColorMap");
    //
    //		outputEffect_->commitBuffers();
    //		GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    //		outputEffect_->endDraw();
    //    
    //		GraphicsInterface::endPerformanceEvent();
	}
}