#include "EditorLayer.h"

#include "maths/Point.h"
#include "maths/Ray.h"

#include "renderer/Transforms.h"

#include "input/Mouse.h"

void EditorLayer::init() {
	selection_.init();
	bounds_.init();
}

void EditorLayer::update(float dt) {

}

void EditorLayer::render(IViewer* viewer, World& world) {
  selection_.render(viewer);
	bounds_.render(viewer, world);
}

void EditorLayer::mouseUp(MouseButton mouseButton, const World& world) {
  if (!camera_->underPlayerControl()) {
    if (MOUSE_BUTTON_LEFT == mouseButton) {
      pickModel(world);
    }
  }
}

void EditorLayer::pickModel(const World& world) {
  Point mousePosition = Mouse::position();
  Matrix4x4 projInv = camera_->projection().inverse();

  Vector4 mouseViewSpace = Transforms::screenSpaceToViewSpace(projInv, mousePosition);
  mouseViewSpace = camera_->viewTransform().transpose() * mouseViewSpace;

  Ray mouseRay(camera_->position(), mouseViewSpace.vec3().normalize(), camera_->farDistance());
  selection_.selectFromRay(mouseRay, world);
}
 