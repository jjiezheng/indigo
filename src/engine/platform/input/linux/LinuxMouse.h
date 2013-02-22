#ifndef LINUX_MOUSE_H
#define LINUX_MOUSE_H

#include "IMouse.h"

class LinuxMouse : public IMouse {

public:

  void setup();

  Point position();

  bool isLeftButtonDown();

  void hideOSMouse(bool isHidden);

};

#endif
