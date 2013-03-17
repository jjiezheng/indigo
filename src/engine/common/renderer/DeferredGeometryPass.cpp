#include "DeferredGeometryPass.h"

#include "GraphicsInterface.h"

#include "Mesh.h"
#include "World.h"
#include "EffectCache.h"
#include "maths/Matrix3x3.h"

#include "IEffect.h" 
#include "IViewer.h"

#include "Color4.h"
#include "SceneContext.h"
#include "EffectMeshList.h"

void DeferredGeometryPass::init() {
	const int kRenderTargetCount = 4;
	RenderTarget renderTargets[kRenderTargetCount] = {colorRenderTarget_, normalRenderTarget_, depthRenderTarget_, normalViewSpaceRenderTarget_};
	gBufferFrameBuffer_ = GraphicsInterface::createFrameBuffer(renderTargets, kRenderTargetCount, true);
}

void DeferredGeometryPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
	GraphicsInterface::beginPerformanceEvent("G-Buffer");
  
	GraphicsInterface::resetRenderTarget(true);
	GraphicsInterface::setFrameBuffer(gBufferFrameBuffer_);
	
	GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
  GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

	GraphicsInterface::clearActiveColorBuffers(Color4::NOTHING);
	GraphicsInterface::clearActiveDepthBuffer();

	GraphicsInterface::enableSmoothing();
	GraphicsInterface::setRenderState(CULL_MODE_BACK);

  EffectMeshList meshList;
  world.collectMeshes(&meshList);

	for (hash_map<IEffect*, std::vector<const Mesh*> >::const_iterator i = meshList.begin(); i != meshList.end(); ++i) {
		IEffect* effect = (*i).first;
		GraphicsInterface::enableSmoothing();

		std::vector<const Mesh*> effectMeshes = (*i).second;
		for (std::vector<const Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
			Matrix4x4 projection = viewer->projection();
			Matrix4x4 viewTransform = viewer->viewTransform();
			Matrix4x4 localToWorld = (*meshIt)->parent()->localToWorld();
			Material material = (*meshIt)->material();
			effect->beginDraw();
			effect->setUniform(viewer->nearDistance(), "Near");
			effect->setUniform(viewer->farDistance(), "Far");
			effect->setSamplerState(0, UV_ADDRESS_WRAP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
			material.bind(projection, viewTransform, localToWorld, effect);
			effect->commitBuffers();
			(*meshIt)->render();
			effect->endDraw();
		}

		GraphicsInterface::disableSmoothing();
	}

	GraphicsInterface::disableSmoothing();

	GraphicsInterface::endPerformanceEvent();
}