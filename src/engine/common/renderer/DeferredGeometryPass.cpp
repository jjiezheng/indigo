#include "DeferredGeometryPass.h"

#include "core/HashMap.h"

#include "GraphicsInterface.h"

#include "Mesh.h"
#include "World.h"
#include "EffectCache.h"
#include "maths/Matrix3x3.h"

#include "IEffect.h" 
#include "IViewer.h"

#include "Color4.h"

void DeferredGeometryPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
	GraphicsInterface::beginPerformanceEvent("G-Buffer");
  
	GraphicsInterface::resetRenderTarget(true);
  
  
//	unsigned int renderTargets[] = {colorRenderTarget_, normalRenderTarget_};
//	GraphicsInterface::setRenderTarget(renderTargets, 2, true);

	GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

	GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());

	GraphicsInterface::clearActiveColorBuffers(Color4::RED);
	GraphicsInterface::clearActiveDepthBuffer();

	GraphicsInterface::enableSmoothing();
	GraphicsInterface::setRenderState(true);

	hash_map<IEffect*, std::vector<Mesh*> > effects;

	std::vector<Model*>::iterator it = world.begin();
	for (; it != world.end(); ++it) {
		(*it)->visit(effects);
	}

	hash_map<IEffect*, std::vector<Mesh*> >::iterator i = effects.begin();
	for (; i != effects.end(); ++i) {
		IEffect* effect = (*i).first;
		effect->setUniform(viewer->nearDistance(), "Near");
		effect->setUniform(viewer->farDistance(), "Far");
		effect->setSamplerState(0, UV_ADDRESS_WRAP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);

		GraphicsInterface::enableSmoothing();

		std::vector<Mesh*> effectMeshes = (*i).second;
		for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
			Matrix4x4 projection = viewer->projection();
			Matrix4x4 viewTransform = viewer->viewTransform();
			Matrix4x4 localToWorld = (*meshIt)->localToWorld();
			Material material = (*meshIt)->material();
			material.bind(projection, viewTransform, localToWorld, effect);
			effect->beginDraw();
			(*meshIt)->render();
			effect->endDraw();
		}

		GraphicsInterface::disableSmoothing();
	}

	GraphicsInterface::disableSmoothing();

	GraphicsInterface::endPerformanceEvent();
}