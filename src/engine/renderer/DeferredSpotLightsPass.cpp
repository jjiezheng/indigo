#include "DeferredSpotLightsPass.h"

#include <vector>

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"

#include "SpotLight.h"

#include "IViewer.h"

#include "VertexDefinition.h"

#include "Model.h"
#include "WorldLoader.h"

void DeferredSpotLightsPass::init() {
  effect_ = IEffect::effectFromFile("cgfx/deferred_lighting_spot_light.cgfx");

  spotLightModel_ = new Model();
  WorldLoader().loadModel(spotLightModel_, "debug/cone.dae");
}

void DeferredSpotLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);
  effect_->setUniform(halfPixel_, "HalfPixel");

  effect_->setTexture(normalMapTexture_, "NormalMap");
  effect_->setTexture(depthMapTexture_, "DepthMap");

  std::vector<SpotLight> spotLights = sceneContext.spotLights();

  for (std::vector<SpotLight>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {    
    Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
    effect_->setUniform(viewProjection, "ViewProj");
    effect_->setUniform(viewProjection.inverse(), "ViewProjInv");

    effect_->setUniform(halfPixel_, "HalfPixel");
    effect_->setUniform((*light).position(), "LightPosition");
    effect_->setUniform((*light).direction(), "LightDirection");
    effect_->setUniform((*light).color(), "LightColor");
    effect_->setUniform((*light).angle(), "LightAngle");

    Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light).transform();
    effect_->setUniform(worldViewProj, "WorldViewProj");

    effect_->beginDraw();
    GraphicsInterface::setPass(effect_->pass()); 
    GraphicsInterface::setRenderState(true);
    spotLightModel_->render();
    effect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}