#ifndef BOUNDS_H
#define BOUNDS_H

#include "IEditorOverlay.h"
#include "renderer/IGraphicsInterface.h"

class World;
class IViewer;
class IEffect;

class Bounds : public IEditorOverlay {

public:

	void init();

	void render(IViewer* viewer, const World& world) const;

private:

	IEffect* effect_;
	VertexBuffer cube_;

};

#endif
