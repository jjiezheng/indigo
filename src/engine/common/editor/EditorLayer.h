#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "input/MouseState.h"

class IViewer;
class World;
class IEffect;

class EditorLayer {

public:

	void init();

	void update(float dt);

	void render(IViewer* viewer, World& world);

public:

	void mouseUp(MouseButton mouseButton);

private:

	IEffect* selectionEffect_;

};

#endif