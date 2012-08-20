#include "DeferredClearBuffersPass.h"

#include "GraphicsInterface.h"
#include "Color4.h"
#include "SceneContext.h"

void DeferredClearBuffersPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::beginPerformanceEvent("Clear", Color4::GREEN);

  GraphicsInterface::clearBuffer(Color4::BLACK);
  GraphicsInterface::clearRenderTarget(colorRenderTarget_, Color4::BLACK);
  GraphicsInterface::clearRenderTarget(normalRenderTarget_, Color4::WHITE);
  GraphicsInterface::clearRenderTarget(depthRenderTarget_, Color4::WHITE);

  GraphicsInterface::endPerformanceEvent();
}
