#include "RotateGizmoView.h"

#include "maths/Angles.h"

#include <algorithm>

void RotateGizmoView::init() {
  xRing_.init();
  Matrix4x4 xRotation = Matrix4x4::rotationX(toRadians(90)) * Matrix4x4::rotationY(toRadians(90));
  xRing_.setOrientation(xRotation);
  addChild(&xRing_);

  yRing_.init();
//  Matrix4x4 yRotation = Matrix4x4::rotationX(toRadians(90));
//  xRing_.setOrientation(yRotation);

 // addChild(&yRing_);

  zRing_.init();
  Matrix4x4 zRotation = Matrix4x4::rotationX(toRadians(90)) * Matrix4x4::rotationY(toRadians(90));
  zRing_.setOrientation(zRotation);
//  addChild(&zRing_);
}

void RotateGizmoView::render(IViewer* viewer) const {
  xRing_.render(viewer);
//  yRing_.render(viewer);
//  zRing_.render(viewer);
}

bool sortHighlightResults(std::pair<RotateGizmoRing*, IntersectionResult*> a, std::pair<RotateGizmoRing*, IntersectionResult*> b) {
  return a.second->distance > b.second->distance;
}

void RotateGizmoView::highlightFromRay(const Ray& ray) {

  xRing_.setHighlight(false);
  yRing_.setHighlight(false);
  zRing_.setHighlight(false);

  std::vector<std::pair<RotateGizmoRing*, IntersectionResult*> > results;

  IntersectionResult xResult = xRing_.testIntersect(ray);
  results.push_back(std::make_pair(&xRing_, &xResult));

  IntersectionResult yResult = yRing_.testIntersect(ray);
  results.push_back(std::make_pair(&yRing_, &yResult));

  IntersectionResult zResult = zRing_.testIntersect(ray);
  results.push_back(std::make_pair(&zRing_, &zResult));

  std::sort(results.begin(), results.end(), sortHighlightResults);

  for (std::vector<std::pair<RotateGizmoRing*, IntersectionResult*> >::iterator i = results.begin(); i != results.end(); ++i) {
    if ((*i).second->intersected) {
      (*i).first->setHighlight(true);
      break;
    }
  }
}

bool sortSelectResults(std::pair<RotateGizmoMode, IntersectionResult*> a, std::pair<RotateGizmoMode, IntersectionResult*> b) {
  return a.second->distance > b.second->distance;
}

RotateGizmoSelectionResult RotateGizmoView::selectFromRay(const Ray& ray) {

  xRing_.setHighlight(false);
  yRing_.setHighlight(false);
  zRing_.setHighlight(false);

  std::vector<std::pair<RotateGizmoMode, IntersectionResult*> > results;

  IntersectionResult xResult = xRing_.testIntersect(ray);
  results.push_back(std::make_pair(ROTATE_GIZMO_MODE_X, &xResult));

  IntersectionResult yResult = yRing_.testIntersect(ray);
  results.push_back(std::make_pair(ROTATE_GIZMO_MODE_Y, &yResult));

  IntersectionResult zResult = zRing_.testIntersect(ray);
  results.push_back(std::make_pair(ROTATE_GIZMO_MODE_Z, &zResult));

  std::sort(results.begin(), results.end(), sortSelectResults);

  RotateGizmoSelectionResult result;

  for (std::vector<std::pair<RotateGizmoMode, IntersectionResult*> >::iterator i = results.begin(); i != results.end(); ++i) {
    if ((*i).second->intersected) {
      result.mode = (*i).first;
      result.selected = true;
      break;
    }
  }

  return result;
}

void RotateGizmoView::highlightX() {
  xRing_.setHighlight(true);
}

void RotateGizmoView::highlightY() {
  yRing_.setHighlight(true);
}

void RotateGizmoView::highlightZ() {
  zRing_.setHighlight(true);
}
