#include "DeferredShadowPass.h"

#include <vector>

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SpotLight.h"
#include "SceneContext.h"
#include "Geometry.h"

void DeferredShadowPass::init() {
  effect_ = IEffect::effectFromFile("cgfx/deferred_shadow_map.cgfx");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredShadowPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
   GraphicsInterface::setRenderTarget(shadowRenderTarget_, false);

  std::vector<SpotLight*> spotLights = sceneContext.spotLights();

  for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {    
    effect_->beginDraw();
    GraphicsInterface::setPass(effect_->pass()); 
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, 6);
    effect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}