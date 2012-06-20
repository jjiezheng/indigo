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
      (*meshIt)->material().bind(viewer->projection(), viewer->viewTransform(), (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, effect);

      effect->beginDraw();
      GraphicsInterface::setPass(effect->pass()); 
      GraphicsInterface::setRenderState(true);
      (*meshIt)->render();
      effect->resetStates();
    }
  }

  GraphicsInterface::resetRenderTarget();
}