#include "Renderer3d.h"

#include "Model.h"
#include "World.h"
#include "Camera.h"
#include "IEffect.h"
#include "SceneContext.h"

#include "GraphicsInterface.h"
#include "EffectCache.h"

#include "maths/Matrix3x3.h"
#include <hash_map>

void Renderer3d::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(Color3::CORNFLOWERBLUE);
//  world.skyBox().render(&camera, sceneContext);
  
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
      (*meshIt)->material().bind(viewer, (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, effect);

      effect->beginDraw();
      GraphicsInterface::setPass(effect->pass()); 
      GraphicsInterface::setRenderState(true);
      (*meshIt)->render();
      effect->resetStates();
    }
  }
}