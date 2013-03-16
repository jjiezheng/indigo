#ifndef TRANSLATE_GIZMO_H
#define TRANSLATE_GIZMO_H

#include "TranslateGizmoView.h"

class IViewer;
class Model;
class Ray;

class TranslateGizmo {

public:

  TranslateGizmo()
    : selected_(0) { }

public:

  void init();

  void render(IViewer* viewer);

public:

  void setSelected(Model* model);

  bool selectFromRay(const Ray& ray);

private:

  Model* selected_;
  TranslateGizmoView view_;

};

inline void TranslateGizmo::setSelected(Model* selected) {
  selected_ = selected;
}

#endif