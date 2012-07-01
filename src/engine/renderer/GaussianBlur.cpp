#include "GaussianBlur.h"

#include "GraphicsInterface.h"
#include "Geometry.h"

#include "Color4.h"
#include "IEffect.h"

void GaussianBlur::init(const CSize& bufferSize) {
  bufferSize_ = bufferSize;

  gaussianVerticalMapTexture_ = GraphicsInterface::createTexture(bufferSize);
  gaussianVerticalRenderTarget_ = GraphicsInterface::createRenderTarget(gaussianVerticalMapTexture_);

  gaussianHorizontalMapTexture_ = GraphicsInterface::createTexture(bufferSize);
  gaussianHorizontalRenderTarget_ = GraphicsInterface::createRenderTarget(gaussianHorizontalMapTexture_);

  quadVbo_ = Geometry::screenPlane();

  gaussianBlurEffect_ = IEffect::effectFromFile("cgfx/gaussian_blur.cgfx");
}

void GaussianBlur::render(unsigned int sourceTexture) {
  {
    GraphicsInterface::setRenderTarget(gaussianVerticalRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(gaussianVerticalRenderTarget_, Color4::WHITE);

    gaussianBlurEffect_->setTexture(sourceTexture, "SourceMap");

    CSize screenSize = GraphicsInterface::screenSize(); 
    gaussianBlurEffect_->setUniform(bufferSize_.width, "SceneWith");
    gaussianBlurEffect_->setUniform(bufferSize_.height, "SceneHeight");

    gaussianBlurEffect_->activatePass(0);
    gaussianBlurEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
    gaussianBlurEffect_->resetStates(); 

    GraphicsInterface::resetRenderTarget();
  }

  {
    GraphicsInterface::setRenderTarget(gaussianHorizontalRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(gaussianHorizontalRenderTarget_, Color4::WHITE);

    gaussianBlurEffect_->setTexture(gaussianVerticalMapTexture_, "SourceMap");

    CSize screenSize = GraphicsInterface::screenSize(); 
    gaussianBlurEffect_->setUniform(bufferSize_.width, "SceneWith");
    gaussianBlurEffect_->setUniform(bufferSize_.height, "SceneHeight");

    gaussianBlurEffect_->activatePass(0);
    gaussianBlurEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);         
    gaussianBlurEffect_->resetStates(); 

    GraphicsInterface::resetRenderTarget();
  }

  GraphicsInterface::generateMipMaps(gaussianHorizontalMapTexture_);
}