#include "GaussianBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"
#include "EffectCache.h"
#include "core/String.h"

void GaussianBlur::init(const CSize& bufferSize, int tapSize) {
  bufferSize_ = bufferSize;

  if (!outputRenderTarget_) {
    outputRenderTexture_ = GraphicsInterface::createTexture(bufferSize);
    outputRenderTarget_ = GraphicsInterface::createRenderTarget(outputRenderTexture_);
  }

  gaussianHorizontalMapTexture_ = GraphicsInterface::createTexture(bufferSize);
  gaussianHorizontalRenderTarget_ = GraphicsInterface::createRenderTarget(gaussianHorizontalMapTexture_);

  quadVbo_ = Geometry::screenPlane();

  String horizontalFilename = String::withFormat("shaders/compiled/gaussian_blur_horizontal_%d_tap.shader", tapSize);
  gaussianBlurHorizontalEffect_ = EffectCache::instance()->loadEffect(horizontalFilename.c_str());

  String verticalFilename = String::withFormat("shaders/compiled/gaussian_blur_vertical_%d_tap.shader", tapSize);
  gaussianBluVerticalEffect_ = EffectCache::instance()->loadEffect(verticalFilename.c_str());
}

void GaussianBlur::render(unsigned int sourceTexture) {
  GraphicsInterface::setRenderState(true);

  {
    GraphicsInterface::setRenderTarget(gaussianHorizontalRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(gaussianHorizontalRenderTarget_, Color4::WHITE);
    
    gaussianBlurHorizontalEffect_->setTexture(sourceTexture, "SourceMap");

    gaussianBlurHorizontalEffect_->setUniform(bufferSize_.width, "SceneWidth");

    gaussianBlurHorizontalEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);         
  }

  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(outputRenderTarget_, Color4::WHITE);

    gaussianBluVerticalEffect_->setTexture(gaussianHorizontalMapTexture_, "SourceMap");

    gaussianBluVerticalEffect_->setUniform(bufferSize_.height, "SceneHeight");

    gaussianBluVerticalEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);         
  }

  GraphicsInterface::generateMipMaps(outputRenderTarget_);
}