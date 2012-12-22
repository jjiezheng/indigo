#include "DeferredFullScreenBlurPass.h"

#include "IEffect.h"
#include "Geometry.h"

#include "GraphicsInterface.h"

#include "SceneContext.h"

#include "GaussianBlur.h"

void DeferredFullScreenBlurPass::init() {
  blur_.setRenderTarget(blurRenderTarget_);
  blur_.init(GraphicsInterface::backBufferSize(), 4);
}

void DeferredFullScreenBlurPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  blur_.render(compositionTexture_);
}