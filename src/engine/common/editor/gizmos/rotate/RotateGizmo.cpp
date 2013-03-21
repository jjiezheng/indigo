#include "RotateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "renderer/Transforms.h"

void RotateGizmo::init() {
  isActive_ = false;
  view_ = &rotateView_;
  rotateView_.init();
}

void RotateGizmo::render(IViewer* viewer) const {
  rotateView_.render(viewer);
}

void RotateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer) {
  Gizmo::update(dt, selection, mousePosition, mouseRay, viewer);
  rotateView_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }
  
  if (!selected_) {
    return;
  }
  
  Node* selectedNode = selection.selection();
  
  Vector4 mouseScreenSpace = Transforms::screenSpaceToNDCSpace(mousePosition);
  Vector4 startMouseScreenSpace = Transforms::screenSpaceToNDCSpace(startMousePosition_);
  
  Vector4 selectedWorldPosition = selectedNode->translation();
  Vector4 selectedScreenSpace = Transforms::worldSpaceToNDCSpace(viewer->viewProjection(), selectedWorldPosition);
  
  Vector4 selectedToStartMouse = startMouseScreenSpace - selectedScreenSpace;
  selectedToStartMouse.z = 0;
  selectedToStartMouse.w = 0;
  
  Vector4 selectedToMouse = mouseScreenSpace - selectedScreenSpace;
  selectedToMouse.z = 0;
  selectedToMouse.w = 0;
  
  LOG("%f %f %f %f",
      selectedScreenSpace.x, selectedScreenSpace.y, selectedScreenSpace.z, selectedScreenSpace.w);
  
  if (selectedScreenSpace.x != selectedScreenSpace.x) {
    int a = 1;
    (void)a;
  }


  selectedToMouse.normalizeIP();
  selectedToStartMouse.normalizeIP();
  
  float angle = selectedToMouse.angle(selectedToStartMouse);
  Vector4 cross = selectedToMouse.cross(selectedToStartMouse);
  
  if (cross.z > 0.0f) {
    angle = -angle;
  }
  
  float angleDelta = angle - lastAngle_;
  
  Matrix4x4 existingOrientation = selectedNode->orientation();
  Matrix4x4 orientationIncrement = Matrix4x4::IDENTITY;
  
  switch (rotateMode_) {
    case ROTATE_GIZMO_MODE_X:
      orientationIncrement = Matrix4x4::rotationX(angleDelta);
      break;
      
    case ROTATE_GIZMO_MODE_Y:
      orientationIncrement = Matrix4x4::rotationY(angleDelta);
      break;
      
    case ROTATE_GIZMO_MODE_Z:
      orientationIncrement = Matrix4x4::rotationZ(angleDelta);
      break;
      
    case ROTATE_GIZMO_MODE_UNKNOWN:
      break;
  }
  
  Matrix4x4 newOrientation = existingOrientation * orientationIncrement;
  
  selectedNode->setOrientation(newOrientation);
  rotateView_.setOrientation(newOrientation);
  
  lastAngle_ = angle;
  
  if (rotateMode_ == ROTATE_GIZMO_MODE_X) {
    rotateView_.highlightX();
  }
  
  if (rotateMode_ == ROTATE_GIZMO_MODE_Y) {
    rotateView_.highlightY();
  }
  
  if (rotateMode_ == ROTATE_GIZMO_MODE_Z) {
    rotateView_.highlightZ();
  }
}

bool RotateGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  startMousePosition_ = mousePosition;
  startSelectionPosition_ = selection.selection()->localToWorld().translation().vec3();
  lastSelectionPosition_ = startSelectionPosition_;
  lastAngle_ = 0.0f;
  
  selected_ = true;

  RotateGizmoSelectionResult result = rotateView_.selectFromRay(mouseRay);
  rotateMode_ = result.mode;
  return result.selected;
}

void RotateGizmo::mouseUp() {
  rotateMode_ = ROTATE_GIZMO_MODE_UNKNOWN;
  selected_ = false;
}
