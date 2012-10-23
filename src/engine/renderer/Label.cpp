#include "Label.h"

#include "io/FntFileParser.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"
#include "maths/Vector2.h"

#include "IEffect.h"
#include "Geometry.h"


#include "GraphicsInterface.h"

Label* Label::labelWithFont(const std::string& text, const std::string& fontFilePath) {
  Label* label = new Label();
  label->loadFont(fontFilePath);
  label->init();
  label->setText(text);
  label->generateVertexBuffers();
  return label;
}

void Label::loadFont(const std::string& fontFilePath) {
  font_ = FntFileParser::parseFile(fontFilePath);
}

void Label::setText(const std::string& text) {
  characters_.clear();
  for (unsigned int i = 0; i < text.size(); i++) {
    FontCharacter character = font_.getCharacter(text[i]);
    characters_.push_back(character);
  }
}

void Label::render(const Matrix4x4& projection) const {
  unsigned int nextCharacterOffset = 0;

  for (unsigned int i = 0; i < vertexBuffers_.size(); i++) {
    unsigned int vertexBuffer = vertexBuffers_[i];
    FontCharacter character = characters_[i];

    Matrix4x4 model = Matrix4x4::translation(Vector4((float)nextCharacterOffset, 0.0f, 0.0f, 1.0f));

    Matrix4x4 modelProjection = projection * model;

    labelEffect_->setUniform(modelProjection, "ModelProjection");
    labelEffect_->setTexture(font_.texture(), "ColorMap");

    GraphicsInterface::resetRenderTarget(false);
		GraphicsInterface::setBlendState(IGraphicsInterface::ALPHA);

    labelEffect_->beginDraw();
    GraphicsInterface::drawVertexBuffer(vertexBuffer, Geometry::FONT_PLANE_VERTEX_COUNT, Geometry::FONT_PLANE_VERTEX_FORMAT);
    labelEffect_->endDraw();
    
    nextCharacterOffset += character.width;
  }
}

void Label::init() {
  labelEffect_ = IEffect::effectFromFile("shaders/compiled/label.shader");
}

void Label::generateVertexBuffers() {
  for (std::vector<FontCharacter>::iterator i = characters_.begin(); i != characters_.end(); ++i) {
    FontCharacter character = (*i);
    CSize characterSize(character.width, character.height);
		CSize characterOffset(character.x, character.y);
    unsigned int vertexBuffer = Geometry::fontCharacter(characterSize, characterOffset, font_.textureSize());
    vertexBuffers_.push_back(vertexBuffer);
  }  
}
