#include "DeferredSSAOPass.h"

#include "IEffect.h"
#include "GraphicsInterface.h"
#include "Geometry.h"

void DeferredSSAOPass::init() {
  ssaoEffect_ = IEffect::effectFromFile("cgfx/deferred_ssao.hlsl");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredSSAOPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(ssaoRenderTarget_, false);
  ssaoEffect_->beginDraw();
  //ssaoEffect_->setTexture(fullScreenTexture_, "Texture");
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
}