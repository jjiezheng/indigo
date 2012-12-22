#ifndef WINDOWSMOUSE_H
#define WINDOWSMOUSE_H

#include "IMouse.h"

class WindowsMouse : public IMouse {

public:

  void setup();

  Point position();

};

#endif
