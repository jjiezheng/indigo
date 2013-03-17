#include "Bounds.h"

#include "renderer/EffectCache.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/Color4.h"
#include "renderer/Mesh.h"
#include "renderer/World.h"
#include "renderer/IEffect.h"
#include "renderer/Geometry.h"

#include "renderer/IViewer.h"

#include "core/HashMap.h"

void Bounds::init() {
	effect_ = EffectCache::instance()->loadEffect("shaders/compiled/color.shader");
	cube_ = Geometry::unitCube();
}

void Bounds::render(IViewer* viewer, const World& world) const {
	GraphicsInterface::beginPerformanceEvent("Bounds");

	GraphicsInterface::resetRenderTarget(true);

	GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
	GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);
	GraphicsInterface::setRenderState(CULL_MODE_NONE, true);

	for (std::vector<Model*>::const_iterator it = world.begin(); it != world.end(); ++it) {
		effect_->beginDraw();

		BoundingBox bounds = (*it)->boundingBox();

		Vector4 scale(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y, bounds.max.z - bounds.min.z, 2.0f);
		scale /= 2.0f;

		Vector4 translation(bounds.max.x + bounds.min.x, bounds.max.y + bounds.min.y, bounds.max.z + bounds.min.z, 2.0f);
		translation /= 2.0f;

		Matrix4x4 model = (*it)->localToWorld() * Matrix4x4::translation(translation) * Matrix4x4::scale(scale);

		Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * Matrix4x4::scale(1.0001f);
		effect_->setUniform(modelViewProjection, "ModelViewProj");
		effect_->setUniform(Color3::CORNFLOWERBLUE, "Color");

		effect_->commitBuffers();
		GraphicsInterface::drawVertexBuffer(cube_, Geometry::UNIT_CUBE_VERTEX_COUNT, Geometry::UNIT_CUBE_VERTEX_FORMAT);
		effect_->endDraw();
	}
	
	GraphicsInterface::endPerformanceEvent();
}