#include "DeferredClearBuffersPass.h"

#include "GraphicsInterface.h"
#include "Color4.h"
#include "SceneContext.h"

void DeferredClearBuffersPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(Color4::CORNFLOWERBLUE);
  GraphicsInterface::clearRenderTarget(lightRenderTarget_, Color4::BLACK);
  GraphicsInterface::clearRenderTarget(colorRenderTarget_, sceneContext.backgroundColor());
  GraphicsInterface::clearRenderTarget(normalRenderTarget_, Color4::WHITE);
  GraphicsInterface::clearRenderTarget(depthRenderTarget_, Color4::WHITE);
  GraphicsInterface::clearRenderTarget(compositionRenderTarget_, Color4::TRANSPAREN);
}
