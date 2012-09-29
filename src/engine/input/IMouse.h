#ifndef IMOUSE_H
#define IMOUSE_H

#include "maths/Point.h"

class IMouse {

public:

  virtual void setup() = 0;

  virtual Point position() = 0;

};

#endif
