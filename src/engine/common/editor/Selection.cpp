#include "Selection.h"

#include "renderer/EffectCache.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/World.h"
#include "renderer/IEffect.h"
#include "renderer/IViewer.h"

void Selection::init() {
  selectionEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/color.shader");
}

void Selection::selectFromRay(const Ray& ray, const World& world) {
  std::vector<Model*> intersections = world.findIntersections(ray);

  LOG(LOG_CHANNEL_EDITOR, "Found %d Intersections", intersections.size());

  if (intersections.size() > 0) {
    selected_ = intersections[0];
  } else {
    selected_ = NULL;
  }
}

void Selection::render(IViewer* viewer) {
  if (NULL != selected_) {
    GraphicsInterface::beginPerformanceEvent("Selection");

    GraphicsInterface::resetRenderTarget(true);

    GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
    GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);
    GraphicsInterface::setRenderState(true, true);

    selectionEffect_->beginDraw();

    Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * selected_->localToWorld() * Matrix4x4::scale(1.0001f);
    selectionEffect_->setUniform(modelViewProjection, "ModelViewProj");
    selectionEffect_->setUniform(Color3::ORANGE, "Color");

    selectionEffect_->commitBuffers();
    selected_->render();
    selectionEffect_->endDraw();

    GraphicsInterface::endPerformanceEvent();
  }
}
