#include "GaussianBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"
#include "core/String.h"

static int kMipLevels = 1;

void GaussianBlur::init(const CSize& bufferSize, int tapSize) {
  bufferSize_ = bufferSize;

  if (!outputRenderTarget_) {
    outputRenderTexture_ = GraphicsInterface::createTexture(bufferSize);
    outputRenderTarget_ = GraphicsInterface::createRenderTarget(outputRenderTexture_);
  }

  gaussianHorizontalMapTexture_ = GraphicsInterface::createTexture(bufferSize);
  gaussianHorizontalRenderTarget_ = GraphicsInterface::createRenderTarget(gaussianHorizontalMapTexture_);

  quadVbo_ = Geometry::screenPlane();

  String horizontalFilename = String::withFormat("cgfx/gaussian_blur_horizontal_%d_tap.hlsl", tapSize);
  gaussianBlurHorizontalEffect_ = IEffect::effectFromFile(horizontalFilename.c_str());

  String verticalFilename = String::withFormat("cgfx/gaussian_blur_vertical_%d_tap.hlsl", tapSize);
  gaussianBluVerticalEffect_ = IEffect::effectFromFile(verticalFilename.c_str());
}

void GaussianBlur::render(unsigned int sourceTexture) {
  GraphicsInterface::setRenderState(true);

  {
    GraphicsInterface::setRenderTarget(gaussianHorizontalRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(gaussianHorizontalRenderTarget_, Color4::WHITE);
    
    gaussianBlurHorizontalEffect_->setTexture(sourceTexture, "SourceMap");

    CSize screenSize = GraphicsInterface::screenSize(); 
    gaussianBlurHorizontalEffect_->setUniform(bufferSize_.width, "SceneWidth");

    gaussianBlurHorizontalEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
  }

  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(outputRenderTarget_, Color4::WHITE);

    gaussianBluVerticalEffect_->setTexture(gaussianHorizontalMapTexture_, "SourceMap");

    CSize screenSize = GraphicsInterface::screenSize(); 
    gaussianBluVerticalEffect_->setUniform(bufferSize_.height, "SceneHeight");

    gaussianBluVerticalEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
  }

  GraphicsInterface::generateMipMaps(outputRenderTarget_);
}