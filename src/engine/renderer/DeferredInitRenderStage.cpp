#include "DeferredInitRenderStage.h"

#include "memory/Allocation.h"

#include "IDeferredRenderTargetContainer.h"
#include "DeferredGeometryPass.h"

#include "GraphicsInterface.h"

#include "Color4.h"

#include <stdio.h>

void DeferredInitRenderStage::init(const CSize& screenSize) {
  colorMapTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R8G8B8A8, 1, 1);
  colorRenderTarget_ = GraphicsInterface::createRenderTarget(colorMapTexture_);

  normalMapTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R8G8B8A8);
  normalRenderTarget_ = GraphicsInterface::createRenderTarget(normalMapTexture_);

  IDeferredPass* geometryPass = new (&Allocation::resident_allocator) DeferredGeometryPass(colorRenderTarget_, normalRenderTarget_);
  passes_.push_back(geometryPass);
}

void DeferredInitRenderStage::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::beginPerformanceEvent("Init");

  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->render(viewer, world, sceneContext);
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredInitRenderStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Color", colorMapTexture_);
  renderTargetContainer->addRenderTarget("Normal", normalMapTexture_);
  renderTargetContainer->addRenderTarget("Depth Buffer", GraphicsInterface::depthBufferTexture());
}
