#include "Label.h"

#include "EffectCache.h"

#include "io/FntFileParser.h"

#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"
#include "maths/Vector2.h"

#include "IEffect.h"
#include "Geometry.h"

#include "GraphicsInterface.h"

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
	characters_.clear();
	for (unsigned int i = 0; i < text.size(); i++) {
		FontCharacter character = font_.getCharacter(text[i]);
		characters_.push_back(character);
	}
} 

void Label::render(const Matrix4x4& projection) const {
	GraphicsInterface::beginPerformanceEvent("Label");

	unsigned int nextCharacterOffset = 0;
	for (std::vector<FontCharacter>::const_iterator i = characters_.begin(); i != characters_.end(); ++i) {

		int x = nextCharacterOffset + (*i).xoffset +  x_;
		int y = font_.lineHeight() - (*i).height - (*i).yoffset + y_;
		Matrix4x4 model = Matrix4x4::translation(Vector4((float)x, (float)y, 0.0f, 1.0f));

		Matrix4x4 modelProjection = projection * model;

		labelEffect_->setUniform(modelProjection, "ModelProjection");
		labelEffect_->setTexture(font_.texture(), "ColorMap");

		GraphicsInterface::resetRenderTarget(false);
		GraphicsInterface::setBlendState(IGraphicsInterface::ALPHA);

		labelEffect_->beginDraw();
		GraphicsInterface::drawVertexBuffer((*i).vertexBuffer, Geometry::FONT_PLANE_VERTEX_COUNT, Geometry::FONT_PLANE_VERTEX_FORMAT);
		labelEffect_->endDraw();

		nextCharacterOffset += (*i).xadvance;
	}

	GraphicsInterface::endPerformanceEvent();
}

void Label::init() {
//	labelEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/label.shader");
//	labelEffect_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_LINEAR, COMPARISON_NONE);
}