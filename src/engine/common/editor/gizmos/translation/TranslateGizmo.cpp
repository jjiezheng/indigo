#include "TranslateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "renderer/Transforms.h"

void TranslateGizmo::init() {
  view_.init();
}

void TranslateGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

void TranslateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* const viewer) {
  view_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }

  Matrix4x4 selectedLocalToWorld = selection.selection()->localToWorld();
  Vector4 selectedTranslation = selectedLocalToWorld.translation();
  Vector4 selectedMidPoint = selection.selection()->boundingBox().mid();
  Matrix4x4 viewTranslation = Matrix4x4::translation(selectedTranslation) * Matrix4x4::translation(selectedMidPoint);

  Vector3 viewerToGizmo = viewer->position() - view_.localToWorld().translation().vec3();
  float distanceToViewer = viewerToGizmo.length();
  Matrix4x4 viewScale = Matrix4x4::scale(distanceToViewer);

  Matrix4x4 viewLocalToWorld = viewTranslation * viewScale * Matrix4x4::scale(0.1f);
  view_.setLocalToWorld(viewLocalToWorld);

  Vector4 selectedWorldPosition = selection.selection()->localToWorld().translation();
  Point selectedScreenSpace = Transforms::worldSpaceToScreenSpace(viewer->viewProjection(), selectedWorldPosition);

  Point mouseOffset = mousePosition - startPosition_;
  Point selectedOffsetScreenSpace = selectedScreenSpace + mouseOffset;

  Vector4 selectedOffsetWorldSpace = Transforms::screenSpaceToWorldSpace(viewer->viewProjection().inverse(), selectedOffsetScreenSpace, selectedScreenSpace.z);
  Matrix4x4 selectedOffsetLocalToWorldSpace = Matrix4x4::translation(selectedOffsetWorldSpace);

  switch(translateMode_) {
    case TRANSLATE_GIZMO_MODE_X:
      selectedOffsetLocalToWorldSpace.m24 = 0;
      selectedOffsetLocalToWorldSpace.m34 = 0;
      selection.selection()->setLocalToWorld(selectedOffsetLocalToWorldSpace);
      break;

    case TRANSLATE_GIZMO_MODE_Y:
      selectedOffsetLocalToWorldSpace.m14 = 0;
      selectedOffsetLocalToWorldSpace.m34 = 0;
      selection.selection()->setLocalToWorld(selectedOffsetLocalToWorldSpace);
      break;

    case TRANSLATE_GIZMO_MODE_Z:
      selectedOffsetLocalToWorldSpace.m14 = 0;
      selectedOffsetLocalToWorldSpace.m24 = 0;
      selection.selection()->setLocalToWorld(selectedOffsetLocalToWorldSpace);
      break;
  }

  startPosition_ = mousePosition;
}

bool TranslateGizmo::mouseDown(const Point& mousePosition, const Ray& mouseRay) {
  startPosition_ = mousePosition;
  TranslateGizmoSelectionResult result = view_.selectFromRay(mouseRay);
  translateMode_ = result.mode;
  return result.selected;
}

void TranslateGizmo::mouseUp() {
  translateMode_ = TRANSLATE_GIZMO_MODE_UNKNOWN;
}
