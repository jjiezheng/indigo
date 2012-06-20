#include "DeferredFinalPass.h"

#include "IEffect.h"

#include "VertexDefinition.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"

#include "Geometry.h"

void DeferredFinalPass::init() {
  finalEffect_ = IEffect::effectFromFile("cgfx/deferred_final_composition.cgfx");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredFinalPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(finalRenderTarget_, false);
  GraphicsInterface::clearRenderTarget(finalRenderTarget_, sceneContext.backgroundColor());
  finalEffect_->beginDraw();
  finalEffect_->setTexture(colorMapTexture_, "ColorMap");
  finalEffect_->setTexture(lightMapTexture_, "LightMap");
  finalEffect_->setUniform(halfPixel_, "HalfPixel");
  GraphicsInterface::setPass(finalEffect_->pass()); 
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
  finalEffect_->resetStates();
  GraphicsInterface::resetRenderTarget();
}
