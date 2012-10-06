#include "DeferredGeometryPass.h"

#include "core/HashMap.h"

#include "GraphicsInterface.h"

#include "Mesh.h"
#include "World.h"
#include "EffectCache.h"
#include "maths/Matrix3x3.h"

#include "IEffect.h" 
#include "IViewer.h"

#include "Color4.h"

void DeferredGeometryPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::beginPerformanceEvent("G-Buffer", Color4::GREEN);

  GraphicsInterface::resetRenderTarget(true);

  unsigned int renderTargets[] = {colorRenderTarget_, normalRenderTarget_, depthRenderTarget_};
  GraphicsInterface::setRenderTarget(renderTargets, 3, true);

  GraphicsInterface::setViewport(GraphicsInterface::screenSize());
  GraphicsInterface::clearBuffer(Color4::CORNFLOWERBLUE);
  GraphicsInterface::clearDepthTarget(GraphicsInterface::depthBufferTexture());

  GraphicsInterface::setRenderState(true);

  hash_map<int, std::vector<Mesh*> > effects;

  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(effects);
  }

  hash_map<int, std::vector<Mesh*> >::iterator i = effects.begin();
  for (; i != effects.end(); ++i) {

    unsigned int effectId = (*i).first;
    IEffect* effect = EffectCache::instance()->getEffect(effectId);

    effect->setUniform(viewer->nearDistance(), "Near");
    effect->setUniform(viewer->farDistance(), "Far");

    std::vector<Mesh*> effectMeshes = (*i).second;
    for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
      Matrix4x4 projection = viewer->projection();
      Matrix4x4 viewTransform = viewer->viewTransform();
      Matrix4x4 localToWorld = (*meshIt)->localToWorld();
      Material material = (*meshIt)->material();
      material.bind(projection, viewTransform, localToWorld, effect);
      effect->beginDraw();
      (*meshIt)->render();
    }

    effect->endDraw();
  }

   GraphicsInterface::endPerformanceEvent();
}