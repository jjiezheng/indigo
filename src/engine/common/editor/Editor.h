#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "input/MouseState.h"
#include "renderer/Camera.h"
#include "renderer/World.h"

#include "Bounds.h"
#include "Selection.h"

#include "input/KeyboardState.h"

class IViewer;
class World;
class IEffect;
class IEditorTool;
class IEditorOverlay;

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

  void mouseDown(MouseButton mouseButton, const World& world);

	void mouseUp(MouseButton mouseButton, const World& world);

  void keyUp(KeyCode keyCode);

private:

  Camera* camera_;
  World* world_;

  std::map<KeyCode, IEditorTool*> tools_;
  std::vector<IEditorOverlay*> overlays_;

  Selection selection_;
	bool isVisible_;

};

inline void Editor::setCamera(Camera* camera) {
  camera_ = camera;
}

inline void Editor::toggleVisible() {
	isVisible_ = !isVisible_;
}

#endif