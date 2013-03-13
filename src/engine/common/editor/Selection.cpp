#include "Selection.h"

#include "renderer/EffectCache.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/World.h"

void Selection::init() {
  selectionEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/color.shader");
}


void Selection::selectFromRay(const Ray& ray, const World& world) {
  std::vector<Model*> intersections = world.findIntersections(ray);
  LOG(LOG_CHANNEL_EDITOR, "Found %d intersections", intersections.size());
}

void Selection::render(IViewer* viewer) {
    GraphicsInterface::beginPerformanceEvent("Editor");

    GraphicsInterface::resetRenderTarget(false);

    GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
    GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

    GraphicsInterface::setRenderState(true, true);



//       std::vector<Mesh*> effectMeshes = (*i).second;
//       for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {				
//         selectionEffect_->beginDraw();
// 
//         Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * (*meshIt)->localToWorld() * Matrix4x4::scale(1.0001f);
//         selectionEffect_->setUniform(modelViewProjection, "ModelViewProj");
//         selectionEffect_->setUniform(Color3::ORANGE, "Color");
// 
//         selectionEffect_->commitBuffers();
//         (*meshIt)->render();
//         selectionEffect_->endDraw();
//       }


    GraphicsInterface::endPerformanceEvent();
}
