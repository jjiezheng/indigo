#ifndef IMOUSE_LISTENER_H
#define IMOUSE_LISTENER_H

#include "MouseState.h"

class IMouseListener {

public:

	virtual void mouseUp(MouseButton mouseCode) = 0;

  virtual void mouseDown(MouseButton mouseCode) = 0;

  virtual void mouseScroll(int delta) = 0;

};

#endif
