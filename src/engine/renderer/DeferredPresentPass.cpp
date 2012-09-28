#include "DeferredPresentPass.h"

#include "IEffect.h"
#include "Geometry.h"

#include "GraphicsInterface.h"

#include "SceneContext.h"

void DeferredPresentPass::init() {
  effect_ = IEffect::effectFromFile(IEffect::SHADER_FULLSCREEN_TEXTURE);
  quadVbo_ = Geometry::screenPlane();
}

void DeferredPresentPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::beginPerformanceEvent("Present", Color4::GREEN);

  GraphicsInterface::resetRenderTarget();
  GraphicsInterface::clearBuffer(sceneContext.backgroundColor());
  effect_->beginDraw();
  effect_->setTexture(fullScreenTexture_, "Texture");
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);

  GraphicsInterface::endPerformanceEvent();
}