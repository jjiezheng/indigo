#include "DeferredGeometryPass.h"

#include <hash_map>

#include "GraphicsInterface.h"

#include "Mesh.h"
#include "World.h"
#include "EffectCache.h"
#include "maths/Matrix3x3.h"

#include "IEffect.h" 
#include "IViewer.h"

void DeferredGeometryPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderState(true);

  unsigned int renderTargets[] = {colorRenderTarget_, normalRenderTarget_, depthRenderTarget_};
  GraphicsInterface::setRenderTarget(renderTargets, 3, true);

  stdext::hash_map<int, std::vector<Mesh*>> effects;

  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(effects);
  }

  stdext::hash_map<int, std::vector<Mesh*>>::iterator i = effects.begin();
  for (; i != effects.end(); ++i) {

    unsigned int effectId = (*i).first;
    IEffect* effect = EffectCache::instance()->getEffect(effectId);

    std::vector<Mesh*> effectMeshes = (*i).second;
    for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
      Matrix4x4 projection = viewer->projection();
      Matrix4x4 viewTransform = viewer->viewTransform();
      Matrix4x4 localToWorld = (*meshIt)->localToWorld();
      Material material = (*meshIt)->material();
      material.bind(projection, viewTransform, localToWorld, sceneContext, effect);
      effect->beginDraw();
      (*meshIt)->render();
    }
  }
}