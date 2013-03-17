#include "Editor.h"

#include "maths/Point.h"
#include "maths/Ray.h"

#include "renderer/Transforms.h"

#include "input/Mouse.h"

#include "IEditorOverlay.h"
#include "IEditorTool.h"

#include "CancelTool.h"
#include "gizmos/translation/TranslateGizmo.h"


void Editor::init() {
  tools_[KEY_ESCAPE] = new CancelTool();
  tools_[KEY_W] = new TranslateGizmo();
  overlays_.push_back(new Bounds());

  for (std::map<KeyCode, IEditorTool*>::iterator i = tools_.begin(); i != tools_.end(); ++i) {
    (*i).second->init();
  }

  for (std::vector<IEditorOverlay*>::iterator i = overlays_.begin(); i != overlays_.end(); ++i) {
    (*i)->init();
  }

	selection_.init();
  isVisible_ = true;
}

void Editor::update(float dt) {
	if (isVisible_) {
    Point mousePosition = Mouse::position();
    Matrix4x4 projInv = camera_->projection().inverse();
    Vector4 mouseViewSpace = Transforms::screenSpaceToViewSpace(projInv, mousePosition);
    mouseViewSpace = camera_->transform().inverse().transpose() * mouseViewSpace;
    Ray mouseRay(camera_->position(), mouseViewSpace.vec3().normalize(), camera_->farDistance());

    for (std::map<KeyCode, IEditorTool*>::iterator i = tools_.begin(); i != tools_.end(); ++i) {
      bool isActive = (*i).second->isActive();
      if (isActive) {
        (*i).second->update(dt, selection_, mouseRay, camera_);
      }
    }
  }
}

void Editor::render(IViewer* viewer, World& world) {
	if (isVisible_) {
    GraphicsInterface::beginPerformanceEvent("Editor");

    for (std::map<KeyCode, IEditorTool*>::iterator i = tools_.begin(); i != tools_.end(); ++i) {
      bool isActive = (*i).second->isActive();
      if (isActive) {
        (*i).second->render(viewer);
      }
    }

    for (std::vector<IEditorOverlay*>::iterator i = overlays_.begin(); i != overlays_.end(); ++i) {
      (*i)->render(viewer, world);
    }

		selection_.render(viewer);
    
    GraphicsInterface::endPerformanceEvent();
	}
}

void Editor::mouseDown(MouseButton mouseButton, const World& world) {
  if (isVisible_) {
    if (!camera_->underPlayerControl()) {
      if (MOUSE_BUTTON_LEFT == mouseButton) {

        Point mousePosition = Mouse::position();
        Matrix4x4 projInv = camera_->projection().inverse();

        Vector4 mouseViewSpace = Transforms::screenSpaceToViewSpace(projInv, mousePosition);
        mouseViewSpace = camera_->transform().inverse().transpose() * mouseViewSpace;

        Ray mouseRay(camera_->position(), mouseViewSpace.vec3().normalize(), camera_->farDistance());

        bool toolPicked = false;
        for (std::map<KeyCode, IEditorTool*>::iterator i = tools_.begin(); i != tools_.end(); ++i) {
          bool isActive = (*i).second->isActive();
          if (isActive) {
            toolPicked = (*i).second->mouseDown(mouseRay, selection_);
          }
        }

        if (!toolPicked) {
          selection_.select(mouseRay, world);
        }
      }
    }
  }
}

void Editor::mouseUp(MouseButton mouseButton, const World& world) {
	if (isVisible_) {
		if (!camera_->underPlayerControl()) {
			if (MOUSE_BUTTON_LEFT == mouseButton) {
        for (std::map<KeyCode, IEditorTool*>::iterator i = tools_.begin(); i != tools_.end(); ++i) {
          bool isActive = (*i).second->isActive();
          if (isActive) {
            (*i).second->mouseUp();
          }
        }
			}
		}
	}
}

void Editor::keyUp(KeyCode keyCode) {
  if (tools_.find(keyCode) == tools_.end()) {
    return;
  }

  for (std::map<KeyCode, IEditorTool*>::iterator i = tools_.begin(); i != tools_.end(); ++i) {
    (*i).second->setActive(false);
  }

  std::map<KeyCode, IEditorTool*>::iterator tool = tools_.find(keyCode);
  if (tool != tools_.end()) {
    (*tool).second->setActive(true);
  }
}