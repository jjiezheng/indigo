#ifndef TRANSLATE_GIZMO_H
#define TRANSLATE_GIZMO_H

#include "../../IEditorTool.h"

#include "TranslateGizmoView.h"

class IViewer;
class Model;
class Ray;

class TranslateGizmo : public IEditorTool {

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection, const Ray& mouseRay, const IViewer* viewer);

public:

  bool mouseDown(const Ray& ray, const Selection& selection);

  void mouseUp();

private:

  TranslateGizmoView view_;

};

#endif