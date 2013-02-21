#include "Line.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"

#include "IEffect.h"
#include "EffectCache.h"
#include "Geometry.h"

#include "GraphicsInterface.h"

Line* Line::line() {
	Line* line = new Line();
	line->init();
	return line;
}

void Line::render(const Matrix4x4& projection) {
	GraphicsInterface::beginPerformanceEvent("Line");

	Matrix4x4 translate = Matrix4x4::translation(Vector4(100, 0, 0, 1));
	Matrix4x4 scale = Matrix4x4::scale(Vector4(1, 20, 1, 1));

	Matrix4x4 model = translate * scale;

	

	effect_->beginDraw();

	Matrix4x4 modelProjection = projection * model;
	effect_->setUniform(modelProjection, "ModelViewProjection");

	GraphicsInterface::resetRenderTarget(false);
	GraphicsInterface::setRenderState(true);
	GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

	effect_->commitBuffers();
	GraphicsInterface::drawVertexBuffer(vertexBuffer_, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
	effect_->endDraw();

	GraphicsInterface::endPerformanceEvent();
}

void Line::init() {
	vertexBuffer_ = Geometry::line();
	effect_ = EffectCache::instance()->loadEffect("shaders/compiled/line.shader");
}
