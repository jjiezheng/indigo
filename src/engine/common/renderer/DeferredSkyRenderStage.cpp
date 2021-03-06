#include "DeferredSkyRenderStage.h"

#include "IDeferredRenderTargetContainer.h"
#include "IEffect.h"
#include "EffectCache.h"
#include "IViewer.h"
#include "Geometry.h"
#include "Color4.h"
#include "World.h"

#include "DeferredLightingRenderStage.h"

void DeferredSkyRenderStage::init(const CSize &screenSize) {
  skyRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  skyRenderTarget_ = GraphicsInterface::createRenderTarget(skyRenderTexture_);

  compositeEffect_ = EffectCache::instance()->loadEffect("cgfx/composite.hlsl");

  quadVBO_ = Geometry::screenPlane();
}

void DeferredSkyRenderStage::render(IViewer* viewer, World& world, DeferredLightingRenderStage& lightingStage) {
  GraphicsInterface::beginPerformanceEvent("Sky");

  {
    GraphicsInterface::beginPerformanceEvent("SkyDome");

    GraphicsInterface::clearRenderTarget(skyRenderTarget_, Color4::TRANSPAREN);

    GraphicsInterface::setRenderTarget(skyRenderTarget_, false);

    if (world.hasSkyDome()) {
      world.skyDome().render(viewer->projection(), viewer->viewTransform(), viewer->translation());
    }

    GraphicsInterface::endPerformanceEvent();
  }

  {
    GraphicsInterface::beginPerformanceEvent("Composite");

    GraphicsInterface::setRenderTarget(skyRenderTarget_, false);

		compositeEffect_->beginDraw();
    compositeEffect_->setTexture(lightingStage.lightMap(), "ColorMap");

		compositeEffect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(quadVBO_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredSkyRenderStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Sky", skyRenderTexture_);
}