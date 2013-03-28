#ifndef ROTATE_GIZMO_H
#define ROTATE_GIZMO_H

#include "../../Gizmo.h"
#include "maths/Point.h"

#include "RotateGizmoView.h"

class IViewer;
class Model;
class Ray;

class RotateGizmo : public Gizmo {
  
public:
  
  RotateGizmo()
    : lastAngle_(0.0f)
	, selected_(false) { }

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer);

public:

  bool mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay);

  void mouseUp();

private:

  RotateGizmoView rotateView_;
  RotateGizmoMode rotateMode_;

  Point startMousePosition_;
  Vector3 startSelectionPosition_;
  Vector3 lastSelectionPosition_;

  Matrix4x4 viewOrientation_;
  Matrix4x4 startSelectedOrientation_;
  
  float lastAngle_;
  
  bool selected_;

};

#endif