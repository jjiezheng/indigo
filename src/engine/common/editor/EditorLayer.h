#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "input/MouseState.h"
#include "renderer/Camera.h"
#include "renderer/World.h"

#include "Selection.h"

class IViewer;
class World;
class IEffect;

class EditorLayer {

public:

	void init();

	void update(float dt);

	void render(IViewer* viewer, World& world);

  void setCamera(Camera* camera);

public:

	void mouseUp(MouseButton mouseButton, const World& world);

  void pickModel(const World& world);

private:

  Camera* camera_;
  World* world_;

  Selection selection_;

};

inline void EditorLayer::setCamera(Camera* camera) {
  camera_ = camera;
}

#endif