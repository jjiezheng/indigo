#include "DeferredFXAAPass.h"

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"
#include "Geometry.h"

#include "maths/Vector2.h"

void DeferredFXAAPass::init() {
  fxaaEffect_ = IEffect::effectFromFile("cgfx/deferred_fxaa.cgfx");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredFXAAPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(fxaaRenderTarget_, false);

  fxaaEffect_->beginDraw();

  fxaaEffect_->setTexture(compositionRenderTexture_, "FinalMap");

  CSize screenSize = GraphicsInterface::screenSize();
  Vector2 screenSizeInv;
  screenSizeInv.x = 1.0f / screenSize.width;
  screenSizeInv.y = 1.0f / screenSize.height;
  fxaaEffect_->setUniform(screenSizeInv, "ScreenSizeInv");

  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
  fxaaEffect_->resetStates();

  GraphicsInterface::resetRenderTarget();
}
