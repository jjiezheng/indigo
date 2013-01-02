#include "Sprite.h"

#include "renderer/GraphicsInterface.h"
#include "renderer/IEffect.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"

#include "Geometry.h"

#include "input/Mouse.h"

Sprite* Sprite::fromFile(const std::string& spriteFilePath) {
  Sprite* sprite = new Sprite();
  sprite->init(spriteFilePath);
  return sprite;
}

void Sprite::init(const std::string& spriteFilePath) {
  textureId_ = GraphicsInterface::loadTexture(spriteFilePath.c_str());
  vertexBuffer_ = Geometry::screenPlane();
  effect_ = IEffect::effectFromFile("shaders/compiled/sprite.shader");
  effect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
}

void Sprite::render(const Matrix4x4& projection) {
  GraphicsInterface::beginPerformanceEvent("Sprite");

  Point mousePosition = Mouse::position();
  Matrix4x4 model = Matrix4x4::translation(Vector4((float)mousePosition.x, (float)-mousePosition.y, 0.0f, 1.0f));

  TextureInfo cursorInfo = GraphicsInterface::textureInfo(textureId_);

  Matrix4x4 scale = Matrix4x4::scale(Vector4((float)cursorInfo.width / 2.0f, (float)cursorInfo.height / 2.0f, 1, 1));

  Matrix4x4 modelProjection = projection * model * scale;

  effect_->setUniform(modelProjection, "ModelProjection");
  effect_->setTexture(textureId_, "ColorMap");

  GraphicsInterface::resetRenderTarget(true);
  GraphicsInterface::setBlendState(IGraphicsInterface::ALPHA);

  effect_->beginDraw();
  GraphicsInterface::drawVertexBuffer(vertexBuffer_, Geometry::FONT_PLANE_VERTEX_COUNT, Geometry::FONT_PLANE_VERTEX_FORMAT);
  effect_->endDraw();

  GraphicsInterface::endPerformanceEvent();
}
