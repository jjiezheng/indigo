#include "DeferredClearBuffersPass.h"

#include "GraphicsInterface.h"
#include "Color3.h"

void DeferredClearBuffersPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(Color3::CORNFLOWERBLUE);
  GraphicsInterface::clearRenderTarget(lightRenderTarget_, Color3::BLACK);
  GraphicsInterface::clearRenderTarget(colorRenderTarget_, Color3::BLACK);
  GraphicsInterface::clearRenderTarget(normalRenderTarget_, Color3::BLACK);
  GraphicsInterface::clearRenderTarget(depthRenderTarget_, Color3::WHITE);
}
