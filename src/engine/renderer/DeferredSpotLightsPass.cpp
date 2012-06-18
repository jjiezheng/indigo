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

#include "maths/Trigonometry.h"

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

  std::vector<SpotLight*> spotLights = sceneContext.spotLights();

  for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {    
    Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
    effect_->setUniform(viewProjection, "ViewProj");
    effect_->setUniform(viewProjection.inverse(), "ViewProjInv");

    effect_->setUniform(halfPixel_, "HalfPixel");
    effect_->setUniform((*light)->position(), "LightPosition");
    effect_->setUniform((*light)->direction(), "LightDirection");
    effect_->setUniform((*light)->color(), "LightColor");
    effect_->setUniform((*light)->innerAngle() / 2.0f, "LightInnerAngle");
    effect_->setUniform((*light)->outerAngle() / 2.0f, "LightOuterAngle");
    effect_->setUniform((*light)->decay(), "LightDecay");

    Vector4 direction = (*light)->direction();

    static float bla = 0.0f;
    bla += 0.01f;
    direction.x = cos(bla);
    direction.y = sin(bla);

    (*light)->setDirection(direction);

    Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light)->transform();
    effect_->setUniform(worldViewProj, "WorldViewProj");

    effect_->beginDraw();
    GraphicsInterface::setPass(effect_->pass()); 
    GraphicsInterface::setRenderState(true);
    spotLightModel_->render();
    effect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}