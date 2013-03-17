#ifndef TRANSLATE_GIZMO_VIEW_H
#define TRANSLATE_GIZMO_VIEW_H

#include "renderer/Color3.h"

#include "TranslateGizmoArrow.h"

class IViewer;
class Ray;

class TranslateGizmoView : public Node {

public:

  TranslateGizmoView()
    : xArrow_(Color3::BLUE)
    , yArrow_(Color3::GREEN)
    , zArrow_(Color3::RED)
  { }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  bool selectFromRay(const Ray& ray);

private:

  TranslateGizmoArrow xArrow_;
  TranslateGizmoArrow yArrow_;
  TranslateGizmoArrow zArrow_;

};

#endif