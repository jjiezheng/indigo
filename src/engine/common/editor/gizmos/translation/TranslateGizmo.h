#ifndef TRANSLATE_GIZMO_H
#define TRANSLATE_GIZMO_H

#include "../../IEditorTool.h"

#include "TranslateGizmoView.h"

class IViewer;
class Model;
class Ray;

class TranslateGizmo : public IEditorTool {

public:

  TranslateGizmo()
    : selected_(0) { }

public:

  void init();

  void render(IViewer* viewer) const;

  void update(float dt, const Selection& selection);

public:

  void setSelected(Model* model);

  bool mousePick(const Ray& ray);

  bool selectFromRay(const Ray& ray);

private:

  Model* selected_;
  TranslateGizmoView view_;

};

inline void TranslateGizmo::setSelected(Model* selected) {
  selected_ = selected;
}

#endif