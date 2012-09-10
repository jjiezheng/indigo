#include "DeferredClearBuffersPass.h"

#include "GraphicsInterface.h"
#include "Color4.h"
#include "SceneContext.h"

void DeferredClearBuffersPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::beginPerformanceEvent("Clear", Color4::GREEN);

  GraphicsInterface::clearBuffer(Color4::RED);
  GraphicsInterface::clearRenderTarget(colorRenderTarget_, Color4::TRANSPAREN);
  GraphicsInterface::clearRenderTarget(normalRenderTarget_, Color4::TRANSPAREN);
  GraphicsInterface::clearRenderTarget(depthRenderTarget_, Color4::TRANSPAREN);

  GraphicsInterface::endPerformanceEvent();
}
