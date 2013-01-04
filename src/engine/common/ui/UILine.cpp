#include "UILine.h"

#include "renderer/Line.h"

UILine* UILine::line() {
	UILine* line = new UILine();
	line->init();
	return line;
}

void UILine::render(const Matrix4x4& projection) {
	line_->render(projection);
}

void UILine::update(float dt) {

}

void UILine::init() {
	line_ = Line::line();
}
