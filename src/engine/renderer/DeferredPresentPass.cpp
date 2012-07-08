#include "DeferredPresentPass.h"

#include "IEffect.h"
#include "Geometry.h"

#include "GraphicsInterface.h"

#include "SceneContext.h"

void DeferredPresentPass::init() {
  effect_ = IEffect::effectFromFile("cgfx/deferred_fullscreen_texture.cgfx");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredPresentPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(sceneContext.backgroundColor());
  effect_->beginDraw();
  effect_->setTexture(fullScreenTexture_, "TextureMap");
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
  effect_->resetStates();
}