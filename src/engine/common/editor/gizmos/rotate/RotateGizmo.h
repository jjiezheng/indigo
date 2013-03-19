#ifndef ROTATE_GIZMO_H
#define ROTATE_GIZMO_H

#include "../../IEditorTool.h"
#include "maths/Point.h"

#include "RotateGizmoView.h"

class IViewer;
class Model;
class Ray;

class RotateGizmo : public IEditorTool {

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer);

public:

  bool mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay);

  void mouseUp();

private:

  RotateGizmoView view_;

};

#endif