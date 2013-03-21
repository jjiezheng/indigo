#ifndef TRANSLATE_GIZMO_H
#define TRANSLATE_GIZMO_H

#include "../../Gizmo.h"

#include "TranslateGizmoView.h"

#include "maths/Point.h"

class IViewer;
class Model;
class Ray;

class TranslateGizmo : public Gizmo {

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer);

public:

  bool mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay);

  void mouseUp();

private:

  TranslateGizmoView translateView_;
  TranslateGizmoMode translateMode_;
  Point startMousePosition_;
  Vector3 startSelectionPosition_;

};

#endif