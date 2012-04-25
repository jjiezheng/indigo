#include "MouseClickDispatcher.h"

#include "IMouseClickListener.h"
#include "Standard.h"

static MouseClickDispatcher* instance_ = 0;

MouseClickDispatcher* MouseClickDispatcher::instance() {
  if (!instance_) {
    instance_ = new MouseClickDispatcher();
  }
  return instance_;
}

void MouseClickDispatcher::mouseDown(int buttonId, const Vector2& location) {
  for (IMouseClickListener* listener : listeners_) {
    listener->onMouseDown(buttonId, location);
  }  
}

void MouseClickDispatcher::mouseUp(int buttonId, const Vector2& location) {
  for (IMouseClickListener* listener : listeners_) {
    listener->onMouseUp(buttonId, location);
  }
}

void MouseClickDispatcher::addListener(IMouseClickListener* listener) {
  listeners_.push_back(listener);
}
