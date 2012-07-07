#include "GaussianBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"

static int kMipLevels = 1;

void GaussianBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;

  gaussianVerticalMapTexture_ = GraphicsInterface::createTexture(bufferSize);
  gaussianVerticalRenderTarget_ = GraphicsInterface::createRenderTarget(gaussianVerticalMapTexture_);

  gaussianHorizontalMapTexture_ = GraphicsInterface::createTexture(bufferSize);
  gaussianHorizontalRenderTarget_ = GraphicsInterface::createRenderTarget(gaussianHorizontalMapTexture_);

  quadVbo_ = Geometry::screenPlane();

  gaussianBlurHorizontalEffect_ = IEffect::effectFromFile("cgfx/gaussian_blur_horizontal.cgfx");
  gaussianBluVerticalEffect_ = IEffect::effectFromFile("cgfx/gaussian_blur_vertical.cgfx");
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
    GraphicsInterface::setRenderTarget(gaussianVerticalRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(gaussianVerticalRenderTarget_, Color4::WHITE);
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

  GraphicsInterface::generateMipMaps(gaussianVerticalMapTexture_);
}