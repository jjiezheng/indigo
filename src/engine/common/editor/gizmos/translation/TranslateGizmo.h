#ifndef TRANSLATE_GIZMO_H
#define TRANSLATE_GIZMO_H

#include "../../IEditorTool.h"

#include "TranslateGizmoView.h"

#include "maths/Point.h"

class IViewer;
class Model;
class Ray;

class TranslateGizmo : public IEditorTool {

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer);

public:

  bool mouseDown(const Point& mousePosition, const Ray& mouseRay);

  void mouseUp();

private:

  TranslateGizmoView view_;
  TranslateGizmoMode translateMode_;
  Point startPosition_;

};

#endif