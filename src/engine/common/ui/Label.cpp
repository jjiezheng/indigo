#include "Label.h"

#include "renderer/EffectCache.h"

#include "io/FntFileParser.h"
#include "memory/Allocation.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"
#include "maths/Vector2.h"

#include "renderer/IEffect.h"
#include "renderer/Geometry.h"
#include "renderer/Color4.h"

#include "renderer/GraphicsInterface.h"

Label* Label::labelWithFont(const std::string& fontFilePath) {
	Label* label = new Label();
	label->loadFont(fontFilePath);
	label->init();
	return label;
}

void Label::loadFont(const std::string& fontFilePath) {
	font_ = FntFileParser::parseFile(fontFilePath);
}

void Label::setText(const std::string& text) {
  if (text.compare(text_) != 0) {

	  characters_.clear();
    
    int textureWidth = 0;

    int lastTextureWidth = 0;
	  for (unsigned int i = 0; i < text.size(); i++) {
		  FontCharacter character = font_.getCharacter(text[i]);
      textureWidth += character.width;
      lastTextureWidth = character.width;
		  characters_.push_back(character);
	  }

    textureWidth += lastTextureWidth;
    
    if (textureWidth > textureSize_.width) {
      // Need to delete the previous resources
      textureSize_ = CSize(textureWidth, font_.lineHeight());
      labelTexture_ = GraphicsInterface::createTexture(textureSize_);
      labelRenderTarget_ = GraphicsInterface::createRenderTarget(labelTexture_);
      labelFrameBuffer_ = GraphicsInterface::createFrameBuffer(labelRenderTarget_, false);
    }

    isDirty_ = true;
    text_ = text;
  }
}

void Label::render(const Matrix4x4& projection) {
	GraphicsInterface::beginPerformanceEvent("Label");

  if (isDirty_) {
    GraphicsInterface::setFrameBuffer(labelFrameBuffer_);
    GraphicsInterface::clearActiveColorBuffers(Color4::TRANSPAREN);

    GraphicsInterface::setViewport(textureSize_);
    Matrix4x4 proj = Matrix4x4::orthographic_screen(0.0f, (float)textureSize_.width, 0.0f, (float)textureSize_.height, -1.0f, 1.0f);


    unsigned int nextCharacterOffset = 0;
    for (std::vector<FontCharacter>::const_iterator i = characters_.begin(); i != characters_.end(); ++i) {
      
      int x = nextCharacterOffset + (*i).xoffset;
      int y = font_.lineHeight() - (*i).height - (*i).yoffset;
      Matrix4x4 model = Matrix4x4::translation(Vector4((float)x, (float)y, 0.0f, 1.0f));

      Matrix4x4 modelProjection = proj * model;

      labelEffect_->beginDraw();
      labelEffect_->setTexture(font_.texture(), "ColorMap");

      labelEffect_->setUniform(modelProjection, "ModelProjection");
      
      labelEffect_->commitBuffers();
      GraphicsInterface::drawVertexBuffer((*i).vertexBuffer, Geometry::FONT_PLANE_VERTEX_COUNT, Geometry::FONT_PLANE_VERTEX_FORMAT);
      labelEffect_->endDraw();

      nextCharacterOffset += (*i).xadvance;
    }
    
    isDirty_ = false;
  }

  GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());

  GraphicsInterface::resetRenderTarget(false);

  {
    labelEffect_->beginDraw();
    labelEffect_->setTexture(labelTexture_, "ColorMap");

    Matrix4x4 preScale = Matrix4x4::scale(Vector4(0.5f, 0.5f, 1.0f, 1.0f));
    Matrix4x4 scale = Matrix4x4::scale(Vector4((float)textureSize_.width, (float)textureSize_.height, 1, 1));
    Matrix4x4 model = Matrix4x4::translation(Vector4((float)x_ + textureSize_.width / 2.0f, (float)y_ + textureSize_.height / 2.0f, 0.0f, 1.0f));

    Matrix4x4 modelProjection = projection * model * scale * preScale;

    labelEffect_->setUniform(modelProjection, "ModelProjection");

    labelEffect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(labelVertexBuffer_, Geometry::FONT_PLANE_VERTEX_COUNT, Geometry::FONT_PLANE_VERTEX_FORMAT);
    labelEffect_->endDraw();
  }

  
	GraphicsInterface::endPerformanceEvent();
}

void Label::init() {
	labelEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/label.shader");
	labelEffect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);

  labelVertexBuffer_ = Geometry::screenPlane();
}
