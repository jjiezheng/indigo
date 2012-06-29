#include "DeferredSpotLightsPass.h"

#include <vector>

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"
#include "SpotLight.h"

#include "IViewer.h"

#include "Model.h"
#include "WorldLoader.h"

#include "maths/Trigonometry.h"

#include <vector>
#include "World.h"

#include "maths/Matrix3x3.h"

void DeferredSpotLightsPass::init() {
  shadowMapEffect_ = IEffect::effectFromFile("cgfx/deferred_depth.cgfx");
  lightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_spot_light.cgfx");

  spotLightModel_ = new Model();
  WorldLoader().loadModel(spotLightModel_, "debug/cone.dae");
}

void DeferredSpotLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {

  stdext::hash_map<int, std::vector<Mesh*>> meshes;
  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(meshes);
  }

  std::vector<SpotLight*> spotLights = sceneContext.spotLights();
  for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {    

    GraphicsInterface::clearBuffer(Color4::WHITE);
    GraphicsInterface::setRenderTarget(shadowMapRenderTarget_, true);

    // create shadowmap
    stdext::hash_map<int, std::vector<Mesh*>>::iterator i = meshes.begin();
    for (; i != meshes.end(); ++i) {
      std::vector<Mesh*> effectMeshes = (*i).second;
      for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
        (*meshIt)->material().bind((*light)->projection(), (*light)->viewTransform(), (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, shadowMapEffect_);
        shadowMapEffect_->beginDraw();
        GraphicsInterface::setPass(shadowMapEffect_->pass()); 
        GraphicsInterface::setRenderState(false);
        (*meshIt)->render();
        shadowMapEffect_->resetStates();
      }
    }

    GraphicsInterface::resetRenderTarget();

    // run lighting

    GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);
    lightEffect_->setUniform(halfPixel_, "HalfPixel");

    lightEffect_->setTexture(normalMapTexture_, "NormalMap");
    lightEffect_->setTexture(depthMapTexture_, "DepthMap");
    lightEffect_->setTexture(shadowMapTexture_, "ShadowMap");

    Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
    lightEffect_->setUniform(viewProjection, "ViewProj");
    lightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

    Matrix4x4 worldLight = (*light)->projection() * (*light)->viewTransform();
    lightEffect_->setUniform(worldLight, "LightViewProj");

    lightEffect_->setUniform(halfPixel_, "HalfPixel");
    lightEffect_->setUniform((*light)->position(), "LightPosition");
    lightEffect_->setUniform((*light)->direction(), "LightDirection");
    lightEffect_->setUniform((*light)->color(), "LightColor");
    lightEffect_->setUniform((*light)->innerAngle() / 2.0f, "LightInnerAngle");
    lightEffect_->setUniform((*light)->outerAngle() / 2.0f, "LightOuterAngle");
    lightEffect_->setUniform((*light)->decay(), "LightDecay");

    Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light)->transform();
    lightEffect_->setUniform(worldViewProj, "WorldViewProj");

    lightEffect_->beginDraw();
    GraphicsInterface::setPass(lightEffect_->pass()); 
    GraphicsInterface::setRenderState(true);
    spotLightModel_->render();
    lightEffect_->resetStates();

    GraphicsInterface::resetRenderTarget();
  }
}