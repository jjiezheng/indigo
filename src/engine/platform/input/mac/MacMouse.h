#ifndef MAC_MOUSE_H
#define MAC_MOUSE_H

#include "IMouse.h"

class MacMouse : public IMouse {

public:
  
  void setup();
  
  Point position();
  
  void setPosition(const Point& position);
  
  bool isLeftButtonDown();
  
  bool isButtonDown(MouseButton button);
  
  void hideOSMouse(bool isHidden);
  
  void setMouseListener(IMouseListener* mouseListener);
  
private:
  
  void onMouseUp(int mouseButton);
  
  void onMouseDown(int mouseButton);
  
  void onMouseScroll(int position);
  
private:
  
  static void glfw_mouse_callback(int mouseButton, int action);
  
  static void glfw_scroll_callback(int position);
  
private:
  
  IMouseListener* mouseListener_;
  static MacMouse* instance_;

};

inline void MacMouse::setMouseListener(IMouseListener* mouseListener) {
  mouseListener_ = mouseListener;
}

#endif
