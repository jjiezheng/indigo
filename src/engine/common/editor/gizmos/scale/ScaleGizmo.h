#ifndef SCALE_GIZMO_H
#define SCALE_GIZMO_H

#include "../../IEditorTool.h"
#include "maths/Point.h"

#include "ScaleGizmoView.h"

class IViewer;
class Model;
class Ray;

class ScaleGizmo : public IEditorTool {

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer);

public:

  bool mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay);

  void mouseUp();

private:


  ScaleGizmoView view_;
  ScaleGizmoMode translateMode_;
  Point startMousePosition_;
  Vector3 startSelectionPosition_;
  Vector3 lastSelectionPosition_;

};

#endif