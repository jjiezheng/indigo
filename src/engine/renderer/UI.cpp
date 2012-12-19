#include "UI.h"

#include "GraphicsInterface.h"
#include "Control.h"

void UI::render() const {
	GraphicsInterface::beginPerformanceEvent("UI");
  for (std::vector<Control*>::const_iterator i = controls_.begin(); i != controls_.end(); ++i) {
    (*i)->render(projection_);
  }
	GraphicsInterface::endPerformanceEvent();
}

void UI::init(const CSize& backBufferSize) {
  projection_ = Matrix4x4::orthographic(0.0f, (float)backBufferSize.width, 0.0f, (float)backBufferSize.height, -1.0f, 1.0f);
}

void UI::update(float dt) {
  for (std::vector<Control*>::const_iterator i = controls_.begin(); i != controls_.end(); ++i) {
    (*i)->update(dt);
  }
}