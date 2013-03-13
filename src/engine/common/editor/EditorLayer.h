#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

class IViewer;
class World;
class IEffect;

class EditorLayer {

public:

	void init();

	void update(float dt);

	void render(IViewer* viewer, World& world);

private:

	IEffect* selectionEffect_;

};

#endif