#ifndef WINDOWSINTERNALMOUSE_H
#define WINDOWSINTERNALMOUSE_H

#include "IMouse.h"

class WindowsInternalMouse : public IMouse {

public:

	void setup() { };

  Point position();

  void setPosition(const Point& position);

  bool isLeftButtonDown();

  bool isButtonDown(MouseButton button);

  void hideOSMouse(bool isHidden);

	void setMouseListener(IMouseListener* mouseListener);

};

#endif
