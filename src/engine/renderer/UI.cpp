#include "UI.h"

#include "Label.h"

void UI::render() const {
  for (std::vector<Label*>::const_iterator i = labels_.begin(); i != labels_.end(); ++i) {
    (*i)->render(projection_);
  }
}

void UI::init(const CSize& backBufferSize) {
  projection_ = Matrix4x4::orthographic(0.0f, (float)backBufferSize.width, 0.0f, (float)backBufferSize.height, -1.0f, 1.0f);
}

void UI::update(float dt) {
  for (std::vector<Label*>::const_iterator i = labels_.begin(); i != labels_.end(); ++i) {
    (*i)->update(dt);
  }
}
