#ifndef MAC_MOUSE_H
#define MAC_MOUSE_H

#include "IMouse.h"

class MacMouse : public IMouse {

public:

  void setup();

  Point position();

	bool isLeftButtonDown();

};

#endif
