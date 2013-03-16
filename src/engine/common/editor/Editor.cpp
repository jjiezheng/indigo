#include "Editor.h"

#include "maths/Point.h"
#include "maths/Ray.h"

#include "renderer/Transforms.h"

#include "input/Mouse.h"

void Editor::init() {
	selection_.init();
	bounds_.init();
  translate_.init();
  isVisible_ = true;
}

void Editor::update(float dt) {
	if (isVisible_) {

	}
}

void Editor::render(IViewer* viewer, World& world) {
	if (isVisible_) {
    GraphicsInterface::beginPerformanceEvent("Editor");
		selection_.render(viewer);
		bounds_.render(viewer, world);

    //if (selection_.hasSelection()) {
      //Model* selection = selection_.selection();
     // translate_.setSelected(selection);
      translate_.render(viewer);
    //}

    GraphicsInterface::endPerformanceEvent();
	}
}

void Editor::mouseUp(MouseButton mouseButton, const World& world) {
	if (isVisible_) {
		if (!camera_->underPlayerControl()) {
			if (MOUSE_BUTTON_LEFT == mouseButton) {
				pickModel(world);
			}
		}
	}
}

void Editor::pickModel(const World& world) {
  Point mousePosition = Mouse::position();
  Matrix4x4 projInv = camera_->projection().inverse();

  LOG(LOG_CHANNEL_EDITOR, "%d %d", mousePosition.x, mousePosition.y);

  Vector4 mouseViewSpace = Transforms::screenSpaceToViewSpace(projInv, mousePosition);
  mouseViewSpace = camera_->transform().inverse().transpose() * mouseViewSpace;

  Ray mouseRay(camera_->position(), mouseViewSpace.vec3().normalize(), camera_->farDistance());


  bool translationHit = translate_.selectFromRay(mouseRay);

  if (translationHit) {
    LOG(LOG_CHANNEL_EDITOR, "Translation Hit");
  }

  selection_.selectFromRay(mouseRay, world);
}
 