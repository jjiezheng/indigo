#include "TranslateGizmoArrow.h"

#include "renderer/EffectCache.h"
#include "renderer/IViewer.h"
#include "renderer/IEffect.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/Model.h"
#include "renderer/Geometry.h"
#include "renderer/FlatMeshList.h"

#include "maths/Angles.h"

#include "maths/Matrix4x4.h"

#include "renderer/Node.h"


void TranslateGizmoArrow::init() {
  effect_ = EffectCache::instance()->loadEffect("shaders/compiled/color.shader");

  Mesh coneMesh;
  coneMesh.createBuffers(Geometry::CONE_VERTEX_DATA, Geometry::CONE_VERTEX_COUNT, Geometry::CONE_VERTEX_FORMAT);

  Matrix4x4 translationAlongLine = Matrix4x4::translation(Vector4(0, 0, 1, 0));
  Matrix4x4 coneLocalToWorld = translationAlongLine * Matrix4x4::scale(0.1f) * Matrix4x4::scale(Vector4(0.5f, 0.5f, 2.0f, 1.0f));

  coneModel_.addMesh(coneMesh);
  coneModel_.setLocalToWorld(coneLocalToWorld);

  Mesh lineMesh;
  lineMesh.createBuffers(Geometry::LINE_VERTEX_DATA, Geometry::LINE_VERTEX_COUNT, Geometry::LINE_VERTEX_FORMAT);
  lineModel_.addMesh(lineMesh);

  addChild(&coneModel_);
  addChild(&lineModel_);
}

void TranslateGizmoArrow::render(IViewer* viewer) const {
  GraphicsInterface::beginPerformanceEvent("Arrow");

  GraphicsInterface::resetRenderTarget(false);
  GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
  GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);
  GraphicsInterface::setRenderState(CULL_MODE_NONE, true);

  if (drawBounds_)
  {
    effect_->beginDraw();

    BoundingBox bounds = boundingBox();

    Vector4 scale(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y, bounds.max.z - bounds.min.z, 2.0f);
    scale /= 2.0f;

    Vector4 translation(bounds.max.x + bounds.min.x, bounds.max.y + bounds.min.y, bounds.max.z + bounds.min.z, 2.0f);
    translation /= 2.0f;

    Matrix4x4 model = localToWorld() * Matrix4x4::translation(translation) * Matrix4x4::scale(scale);
    Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * Matrix4x4::scale(1.0001f);

    effect_->setUniform(modelViewProjection, "ModelViewProj");
    effect_->setUniform(arrowColor_, "Color");

    effect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(Geometry::UNIT_CUBE_VERTEX_BUFFER, Geometry::UNIT_CUBE_VERTEX_COUNT, Geometry::UNIT_CUBE_VERTEX_FORMAT);
    effect_->endDraw();
  }

  // children
  { 
    FlatMeshList meshList;
    collectMeshes(&meshList);

    for (std::vector<const Mesh*>::const_iterator i = meshList.begin(); i != meshList.end(); ++i) {
      effect_->beginDraw();

      Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * (*i)->parent()->localToWorld();
      effect_->setUniform(modelViewProjection, "ModelViewProj");

      Color3 color = arrowColor_;

      if (isHighlighted_) {
        color = Color3::YELLOW;
      }

      effect_->setUniform(color, "Color");

      GraphicsInterface::setRenderState(CULL_MODE_NONE, false);

      effect_->commitBuffers();
      (*i)->render();
      effect_->endDraw();
    }
  }

  GraphicsInterface::endPerformanceEvent();
}
