#include "Gizmo.h"

#include "renderer/Node.h"
#include "renderer/Model.h"

#include "maths/Vector3.h"
#include "maths/Vector4.h"

#include "renderer/IViewer.h"

#include "Selection.h"

void Gizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer) {
  bool hasSelection = selection.hasSelection();
  if (hasSelection) {
    Node* selectedNode = selection.selection();

    Vector3 viewTranslation = selectedNode->localToWorld().translation().vec3();
    view_->setTranslation(viewTranslation);
    
    Vector3 viewerToGizmo = viewer->position() - view_->localToWorld().translation().vec3();
    float distanceToViewer = viewerToGizmo.length();
    
    Matrix4x4 viewScale = Matrix4x4::scale(distanceToViewer) * Matrix4x4::scale(0.1f);
    view_->setScale(viewScale);
  }
}
