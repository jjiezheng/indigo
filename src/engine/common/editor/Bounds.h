#ifndef BOUNDS_H
#define BOUNDS_H

#include "renderer/IGraphicsInterface.h"

class World;
class IViewer;
class IEffect;

class Bounds {

public:

	void init();

	void render(IViewer* viewer, World& world) const;

private:

	IEffect* effect_;
	VertexBuffer cube_;

};

#endif
