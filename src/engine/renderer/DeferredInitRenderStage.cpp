#include "DeferredInitRenderStage.h"

#include "IDeferredRenderTargetContainer.h"
#include "DeferredClearBuffersPass.h"
#include "DeferredGeometryPass.h"

#include "GraphicsInterface.h"

#include "Color4.h"

#include <stdio.h>

void DeferredInitRenderStage::init(const CSize& screenSize) {
  colorMapTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R8G8B8A8, 1, 1);
  colorRenderTarget_ = GraphicsInterface::createRenderTarget(colorMapTexture_);

  normalMapTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R8G8B8A8);
  normalRenderTarget_ = GraphicsInterface::createRenderTarget(normalMapTexture_);

  depthMapTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R32G32B32A32);
  depthRenderTarget_ = GraphicsInterface::createRenderTarget(depthMapTexture_);

  IDeferredPass* clearBuffersPass = new DeferredClearBuffersPass(colorRenderTarget_, normalRenderTarget_);
  passes_.push_back(clearBuffersPass);

  IDeferredPass* geometryPass = new DeferredGeometryPass(colorRenderTarget_, normalRenderTarget_, depthRenderTarget_);
  passes_.push_back(geometryPass);
}

void DeferredInitRenderStage::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::beginPerformanceEvent("Init", Color4::GREEN);

  for (std::vector<IDeferredPass*>::iterator i = passes_.begin(); i != passes_.end(); ++i) {
    (*i)->render(viewer, world, sceneContext);
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredInitRenderStage::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Color", colorMapTexture_);
  renderTargetContainer->addRenderTarget("Normal", normalMapTexture_);
  renderTargetContainer->addRenderTarget("Normal", depthMapTexture_);
  renderTargetContainer->addRenderTarget("Depth", GraphicsInterface::depthBufferTexture());
}
