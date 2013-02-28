#include "Sprite.h"

#include "renderer/GraphicsInterface.h"
#include "renderer/IEffect.h"
#include "renderer/EffectCache.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"

#include "renderer/Geometry.h"

Sprite* Sprite::fromFile(const std::string& spriteFilePath) {
  Sprite* sprite = new Sprite();
  sprite->init(spriteFilePath);
  return sprite;
}

void Sprite::init(const std::string& spriteFilePath) {
  textureId_ = GraphicsInterface::loadTexture(spriteFilePath.c_str());
	TextureInfo textureInfo = GraphicsInterface::textureInfo(textureId_);
	
	size_.width = textureInfo.width;
	size_.height = textureInfo.height;

  vertexBuffer_ = Geometry::screenPlane();
	effect_ = EffectCache::instance()->loadEffect("shaders/compiled/sprite.shader");
  effect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
}

void Sprite::render(const Matrix4x4& projection, const Matrix4x4& model) {
  GraphicsInterface::beginPerformanceEvent("Sprite");

	effect_->beginDraw();
  Matrix4x4 modelProjection = projection * model;
  effect_->setUniform(modelProjection, "ModelProjection");
  effect_->setTexture(textureId_, "ColorMap");

  GraphicsInterface::resetRenderTarget(false);
  GraphicsInterface::setBlendState(IGraphicsInterface::ALPHA);

  effect_->commitBuffers();
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, Geometry::FONT_PLANE_VERTEX_COUNT, Geometry::FONT_PLANE_VERTEX_FORMAT);
  effect_->endDraw();

  GraphicsInterface::endPerformanceEvent();
}
