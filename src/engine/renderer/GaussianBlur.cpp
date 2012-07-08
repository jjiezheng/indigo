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

  String horizontalFilename = String::withFormat("cgfx/gaussian_blur_horizontal_%d_tap.cgfx", tapSize);
  gaussianBlurHorizontalEffect_ = IEffect::effectFromFile(horizontalFilename.c_str());

  String verticalFilename = String::withFormat("cgfx/gaussian_blur_vertical_%d_tap.cgfx", tapSize);
  gaussianBluVerticalEffect_ = IEffect::effectFromFile(verticalFilename.c_str());
}

void GaussianBlur::render(unsigned int sourceTexture) {

  {
    GraphicsInterface::setRenderTarget(gaussianHorizontalRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(gaussianHorizontalRenderTarget_, Color4::WHITE);
    //GraphicsInterface::resetRenderTarget();

    gaussianBlurHorizontalEffect_->setTexture(sourceTexture, "SourceMap");

    CSize screenSize = GraphicsInterface::screenSize(); 
    gaussianBlurHorizontalEffect_->setUniform(bufferSize_.width, "SceneWidth");

    gaussianBlurHorizontalEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
    gaussianBlurHorizontalEffect_->resetStates(); 

    GraphicsInterface::resetRenderTarget();
  }

  {
    GraphicsInterface::setRenderTarget(outputRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(outputRenderTarget_, Color4::WHITE);
    //GraphicsInterface::resetRenderTarget();

    gaussianBluVerticalEffect_->setTexture(gaussianHorizontalMapTexture_, "SourceMap");

    CSize screenSize = GraphicsInterface::screenSize(); 
    gaussianBluVerticalEffect_->setUniform(bufferSize_.height, "SceneHeight");

    gaussianBluVerticalEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
    gaussianBluVerticalEffect_->resetStates(); 

    GraphicsInterface::resetRenderTarget();
  }

  GraphicsInterface::generateMipMaps(outputRenderTarget_);
}