#ifndef WINDOWSMOUSE_H
#define WINDOWSMOUSE_H

#include "IMouse.h"

class WindowsMouse : public IMouse {

public:

  void setup();

  Point position();

  bool isLeftButtonDown();

  void hideOSMouse(bool isHidden);

};

#endif
