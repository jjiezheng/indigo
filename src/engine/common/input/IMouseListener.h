#ifndef IMOUSE_LISTENER_H
#define IMOUSE_LISTENER_H

#include "MouseState.h"

class IMouseListener {

public:

	virtual void mouseUp(MouseButton mouseCode) = 0;

};

#endif
