#include "DeferredInitRenderStage.h"

#include "IDeferredRenderTargetContainer.h"
#include "DeferredGeometryPass.h"

#include "GraphicsInterface.h"

#include "Color4.h"

#include <stdio.h>

void DeferredInitRenderStage::init(const CSize& screenSize) {
  colorMapTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R8G8B8A8);
  colorRenderTarget_ = GraphicsInterface::createRenderTarget(colorMapTexture_);

  normalMapTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R32G32B32A32);
  normalRenderTarget_ = GraphicsInterface::createRenderTarget(normalMapTexture_);

  normalViewSpaceMapTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R8G8B8A8);
  normalViewSpaceRenderTarget_ = GraphicsInterface::createRenderTarget(normalViewSpaceMapTexture_);

  depthMapTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R32G32B32A32);
  depthRenderTarget_ = GraphicsInterface::createRenderTarget(depthMapTexture_);

  IDeferredPass* geometryPass = new DeferredGeometryPass(colorRenderTarget_, normalRenderTarget_, normalViewSpaceRenderTarget_, depthRenderTarget_);
  geometryPass->init();

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
  renderTargetContainer->addRenderTarget("Normal View Space", normalViewSpaceMapTexture_);
  renderTargetContainer->addRenderTarget("Linear Depth", depthMapTexture_);
  renderTargetContainer->addRenderTarget("Depth Buffer", GraphicsInterface::depthBufferTexture());
}
