#include "EditorLayer.h"

#include "core/HashMap.h"

#include "GraphicsInterface.h"

#include "Mesh.h"
#include "World.h"
#include "EffectCache.h"
#include "maths/Matrix3x3.h"

#include "IEffect.h" 
#include "IViewer.h"

#include "Color4.h"
#include "SceneContext.h"

void EditorLayer::init() {
	selectionEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/color.shader");
}

void EditorLayer::update(float dt) {

}

void EditorLayer::render(IViewer* viewer, World& world) {

	{
		GraphicsInterface::beginPerformanceEvent("Editor");

		GraphicsInterface::resetRenderTarget(false);

		GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
		GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

		GraphicsInterface::setRenderState(true, true);

		hash_map<IEffect*, std::vector<Mesh*> > effects;

		std::vector<Model*>::iterator it = world.begin();
		for (; it != world.end(); ++it) {
			(*it)->visit(effects);
		}

		hash_map<IEffect*, std::vector<Mesh*> >::iterator i = effects.begin();
		for (; i != effects.end(); ++i) {

			std::vector<Mesh*> effectMeshes = (*i).second;
			for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {				
				selectionEffect_->beginDraw();

				Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * (*meshIt)->localToWorld() * Matrix4x4::scale(1.0001f);
				selectionEffect_->setUniform(modelViewProjection, "ModelViewProj");
				selectionEffect_->setUniform(Color3::ORANGE, "Color");

				selectionEffect_->commitBuffers();
				(*meshIt)->render();
				selectionEffect_->endDraw();
			}
		}

		GraphicsInterface::endPerformanceEvent();
	}
}