#include "DeferredFXAAPass.h"

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"
#include "Geometry.h"

void DeferredFXAAPass::init() {
  finalEffect_ = IEffect::effectFromFile("cgfx/deferred_fxaa.cgfx");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredFXAAPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(sceneContext.backgroundColor());
  finalEffect_->beginDraw();

  finalEffect_->setTexture(finalRenderTexture_, "FinalMap");
  finalEffect_->setUniform(halfPixel_, "HalfPixel");

  CSize screenSize = GraphicsInterface::screenSize();
  Vector2 screenSizeInv;
  screenSizeInv.x = 1.0f / screenSize.width;
  screenSizeInv.y = 1.0f / screenSize.height;
  finalEffect_->setUniform(screenSizeInv, "ScreenSizeInv");

  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, 6);
  finalEffect_->resetStates();
}
