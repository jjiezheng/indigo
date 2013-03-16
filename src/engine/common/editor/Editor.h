#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "input/MouseState.h"
#include "renderer/Camera.h"
#include "renderer/World.h"

#include "gizmos/translation/TranslateGizmo.h"

#include "Bounds.h"
#include "Selection.h"

class IViewer;
class World;
class IEffect;

class Editor {

public:

	Editor()
		: isVisible_(false) { }

public:

	void init();

	void update(float dt);

	void render(IViewer* viewer, World& world);

  void setCamera(Camera* camera);

public:

	void toggleVisible();

public:

	void mouseUp(MouseButton mouseButton, const World& world);

  void pickModel(const World& world);

private:

  Camera* camera_;
  World* world_;

  Selection selection_;
	Bounds bounds_;
  TranslateGizmo translate_;
	bool isVisible_;

};

inline void Editor::setCamera(Camera* camera) {
  camera_ = camera;
}

inline void Editor::toggleVisible() {
	isVisible_ = !isVisible_;
}

#endif