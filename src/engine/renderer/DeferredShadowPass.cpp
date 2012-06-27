#include "DeferredShadowPass.h"

#include <vector>

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SpotLight.h"
#include "SceneContext.h"
#include "Geometry.h"

#include <vector>
#include "Mesh.h"
#include "World.h"

#include "maths/Matrix3x3.h"

#include "IViewer.h"

void DeferredShadowPass::init() {
  effect_ = IEffect::effectFromFile("cgfx/deferred_shadow_map.cgfx");
  shadowMapEffect_ = IEffect::effectFromFile("cgfx/deferred_depth.cgfx");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredShadowPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(shadowRenderTarget_, true);
  GraphicsInterface::resetRenderTarget();
  GraphicsInterface::clearBuffer(Color4::WHITE);

  stdext::hash_map<int, std::vector<Mesh*>> meshes;
 
  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(meshes);
  }

  std::vector<SpotLight*> spotLights = sceneContext.spotLights();
  for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {   
    stdext::hash_map<int, std::vector<Mesh*>>::iterator i = meshes.begin();
    for (; i != meshes.end(); ++i) {
      std::vector<Mesh*> effectMeshes = (*i).second;
      for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
        (*meshIt)->material().bind((*light)->projection(), (*light)->viewTransform(), (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, shadowMapEffect_);

        shadowMapEffect_->beginDraw();
        GraphicsInterface::setPass(shadowMapEffect_->pass()); 
        GraphicsInterface::setRenderState(true);
        (*meshIt)->render();

        shadowMapEffect_->resetStates();
      }
    }

    GraphicsInterface::resetRenderTarget();
  }
}