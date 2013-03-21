#include "TranslateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "renderer/Transforms.h"

void TranslateGizmo::init() {
  view_ = &translateView_;
  translateView_.init();
}

void TranslateGizmo::render(IViewer* viewer) const {
  translateView_.render(viewer);
}

void TranslateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* const viewer) {
  Gizmo::update(dt, selection, mousePosition, mouseRay, viewer);
  
  translateView_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }

  //

  Vector3 planePosition = startSelectionPosition_;

  Point planeScreenSpace = Transforms::worldSpaceToScreenSpace(viewer->viewProjection(), planePosition);
  planeScreenSpace.x += mousePosition.x - startMousePosition_.x;
  planeScreenSpace.y += mousePosition.y - startMousePosition_.y;

  Vector4 newPlanePosition = Transforms::screenSpaceToWorldSpace(viewer->viewProjection().inverse(), planeScreenSpace, planeScreenSpace.z);
  
  Node* selectedNode = selection.selection();
  Vector3 selectionTranslation = selectedNode->translation();

  if (translateMode_ == TRANSLATE_GIZMO_MODE_X) {
    selectionTranslation.x = newPlanePosition.x;
    translateView_.highlightX();
  }

  if (translateMode_ == TRANSLATE_GIZMO_MODE_Y) {
    selectionTranslation.y = newPlanePosition.y;
    translateView_.highlightY();
  }

  if (translateMode_ == TRANSLATE_GIZMO_MODE_Z) {
    selectionTranslation.z = newPlanePosition.z;
    translateView_.highlightZ();
  }
  
  selectedNode->setTranslation(selectionTranslation);
}

bool TranslateGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  startMousePosition_ = mousePosition;
  startSelectionPosition_ = selection.selection()->localToWorld().translation().vec3();
  TranslateGizmoSelectionResult result = translateView_.selectFromRay(mouseRay);
  translateMode_ = result.mode;
  return result.selected;
}

void TranslateGizmo::mouseUp() {
  translateMode_ = TRANSLATE_GIZMO_MODE_UNKNOWN;
}
