#include "MouseClickDispatcher.h"

#include "core/Standard.h"

#include "IMouseClickListener.h"

static MouseClickDispatcher* instance_ = 0;

MouseClickDispatcher* MouseClickDispatcher::instance() {
  if (!instance_) {
    instance_ = new MouseClickDispatcher();
  }
  return instance_;
}


void MouseClickDispatcher::mouseDown(int buttonId, const Vector2& location) {
  std::vector<IMouseClickListener*>::iterator it = listeners_.begin();
  for (; it != listeners_.end(); ++it) {
    (*it)->onMouseDown(buttonId, location);
  }  
}

void MouseClickDispatcher::mouseUp(int buttonId, const Vector2& location) {
  std::vector<IMouseClickListener*>::iterator it = listeners_.begin();
  for (; it != listeners_.end(); ++it) {
    (*it)->onMouseUp(buttonId, location);
  }
}

void MouseClickDispatcher::addListener(IMouseClickListener* listener) {
  listeners_.push_back(listener);
}
