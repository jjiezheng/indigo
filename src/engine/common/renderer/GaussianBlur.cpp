#include "GaussianBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"
#include "EffectCache.h"
#include "core/String.h"

void GaussianBlur::init(const CSize& bufferSize, int tapSize) {
  bufferSize_ = bufferSize;

  horizontalMapTexture_ = GraphicsInterface::createTexture(bufferSize, IGraphicsInterface::R32G32B32A32);
  horizontalRenderTarget_ = GraphicsInterface::createRenderTarget(horizontalMapTexture_);
  horizonalFrameBuffer_ = GraphicsInterface::createFrameBuffer(horizontalRenderTarget_, false);

	verticalMapTexture_ = GraphicsInterface::createTexture(bufferSize, IGraphicsInterface::R32G32B32A32);
	verticalRenderTarget_ = GraphicsInterface::createRenderTarget(verticalMapTexture_);
	verticalFrameBuffer_ = GraphicsInterface::createFrameBuffer(verticalRenderTarget_, false);

  quadVbo_ = Geometry::screenPlane();

  String horizontalFilename = String::withFormat("shaders/compiled/gaussian_blur_horizontal_%d_tap.shader", tapSize);
  horizontalEffect_ = EffectCache::instance()->loadEffect(horizontalFilename.c_str());

  String verticalFilename = String::withFormat("shaders/compiled/gaussian_blur_vertical_%d_tap.shader", tapSize);
  verticalEffect_ = EffectCache::instance()->loadEffect(verticalFilename.c_str());

	outputEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_fullscreen_texture.shader");
}

void GaussianBlur::render(FrameBuffer outputFrameBuffer, TextureId outputTexture, TextureId sourceTexture, unsigned int iterations) {
  GraphicsInterface::setRenderState(CULL_MODE_BACK);

	for (unsigned int i = 0; i < iterations; i++) {

		GraphicsInterface::beginPerformanceEvent("Pass");

		{
			GraphicsInterface::beginPerformanceEvent("Horizontal");

			GraphicsInterface::setFrameBuffer(horizonalFrameBuffer_);
			GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
	    
			horizontalEffect_->beginDraw();
			horizontalEffect_->setTexture(sourceTexture, "SourceMap");
			horizontalEffect_->setUniform((float)bufferSize_.width, "SceneWidth");

			horizontalEffect_->commitBuffers();
			GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);  
			horizontalEffect_->endDraw();
	    
			GraphicsInterface::endPerformanceEvent();

		}

		{
			GraphicsInterface::beginPerformanceEvent("Vertical");

			GraphicsInterface::setFrameBuffer(verticalFrameBuffer_);
			GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);

			verticalEffect_->beginDraw();
			verticalEffect_->setTexture(horizontalMapTexture_, "SourceMap");
			verticalEffect_->setUniform((float)bufferSize_.height, "SceneHeight");

			verticalEffect_->commitBuffers();
			GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT); 
			verticalEffect_->endDraw();

			GraphicsInterface::endPerformanceEvent();
		}

		sourceTexture = verticalMapTexture_;

		GraphicsInterface::endPerformanceEvent();
	}

	{
		GraphicsInterface::beginPerformanceEvent("Output");

		GraphicsInterface::setFrameBuffer(outputFrameBuffer);
		GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);

		outputEffect_->beginDraw();
		outputEffect_->setTexture(verticalMapTexture_, "ColorMap");

		outputEffect_->commitBuffers();
		GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT); 
		outputEffect_->endDraw();

		GraphicsInterface::endPerformanceEvent();
	}
}