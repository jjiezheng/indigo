#ifndef GIZMO_H
#define GIZMO_H

#include "IEditorTool.h"

class Node;

class Gizmo : public IEditorTool {
  
public:
  
  void update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer);
  
protected:
  
  Node* view_;
  
};

#endif