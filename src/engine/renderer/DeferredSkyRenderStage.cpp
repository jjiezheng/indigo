#include "DeferredSkyRenderStage.h"

#include "IDeferredRenderTargetContainer.h"
#include "IEffect.h"
#include "IViewer.h"
#include "Geometry.h"
#include "Color4.h"
#include "World.h"

#include "DeferredLightingRenderStage.h"

void DeferredSkyRenderStage::init(const CSize &screenSize) {
  skyRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  skyRenderTarget_ = GraphicsInterface::createRenderTarget(skyRenderTexture_);

  compositeEffect_ = IEffect::effectFromFile("cgfx/composite.hlsl");

  quadVBO_ = Geometry::screenPlane();
}

void DeferredSkyRenderStage::render(IViewer* viewer, World& world, DeferredLightingRenderStage& lightingStage) {
  GraphicsInterface::beginPerformanceEvent("Sky", Color4::GREEN);

  {
    GraphicsInterface::beginPerformanceEvent("SkyDome", Color4::MAGENTA);

    GraphicsInterface::clearRenderTarget(skyRenderTarget_, Color4::BLACK);

    GraphicsInterface::setRenderTarget(skyRenderTarget_, false);
    world.skyDome().render(viewer->projection(), viewer->viewTransform(), Matrix4x4::IDENTITY);

    GraphicsInterface::endPerformanceEvent();
  }

  {
    GraphicsInterface::beginPerformanceEvent("Composite", Color4::MAGENTA);

    GraphicsInterface::setRenderTarget(skyRenderTarget_, false);

    compositeEffect_->setTexture(lightingStage.lightMap(), "ColorMap");

    compositeEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVBO_, Geometry::SCREEN_PLANE_VERTEX_COUNT);

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredSkyRenderStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Sky", skyRenderTexture_);
}