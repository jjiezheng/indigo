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

  quadVbo_ = Geometry::screenPlane();

  String horizontalFilename = String::withFormat("shaders/compiled/gaussian_blur_horizontal_%d_tap.shader", tapSize);
  horizontalEffect_ = EffectCache::instance()->loadEffect(horizontalFilename.c_str());

  String verticalFilename = String::withFormat("shaders/compiled/gaussian_blur_vertical_%d_tap.shader", tapSize);
  verticalEffect_ = EffectCache::instance()->loadEffect(verticalFilename.c_str());
}

void GaussianBlur::render(FrameBuffer outputFrameBuffer, TextureId sourceTexture) {
  GraphicsInterface::setRenderState(true);

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

    GraphicsInterface::setFrameBuffer(outputFrameBuffer);
    //GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);

		verticalEffect_->beginDraw();
    verticalEffect_->setTexture(horizontalMapTexture_, "SourceMap");
    verticalEffect_->setUniform((float)bufferSize_.height, "SceneHeight");

		verticalEffect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT); 
		verticalEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }
}