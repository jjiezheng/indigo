#include "DeferredSpotLightsPass.h"

#include <vector>

#include "IViewer.h"
#include "IEffect.h"
#include "GraphicsInterface.h"
#include "SceneContext.h"
#include "SpotLight.h"
#include "Model.h"
#include "WorldLoader.h"
#include "Geometry.h"
#include "World.h"

#include "maths/Trigonometry.h"
#include "maths/Matrix3x3.h"

void DeferredSpotLightsPass::init() {
  shadowMapEffect_ = IEffect::effectFromFile("cgfx/deferred_depth.hlsl");
  lightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_spot_light.hlsl");

  spotLightModel_ = new Model();
  WorldLoader().loadModel(spotLightModel_, "debug/cone.dae");

  CSize screenSize = GraphicsInterface::screenSize(); 
  gaussianBlur_.init(screenSize, 16);
}

void DeferredSpotLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {

  stdext::hash_map<int, std::vector<Mesh*>> meshes;
  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(meshes);
  }

  std::vector<SpotLight*> spotLights = sceneContext.spotLights();
  for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {

   if ((*light)->castsShadows()) {
      // create shadowmap
      GraphicsInterface::clearBuffer(Color4::WHITE);
      GraphicsInterface::setRenderTarget((*light)->shadowMapRenderTarget(), true);
      GraphicsInterface::clearRenderTarget((*light)->shadowMapRenderTarget(), Color4::WHITE);

      stdext::hash_map<int, std::vector<Mesh*>>::iterator i = meshes.begin();
      for (; i != meshes.end(); ++i) {
        std::vector<Mesh*> effectMeshes = (*i).second;
        for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
          (*meshIt)->material().bind((*light)->projection(), (*light)->viewTransform(), (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, shadowMapEffect_);
         
          shadowMapEffect_->beginDraw();
          GraphicsInterface::setRenderState(true);
          (*meshIt)->render();
          shadowMapEffect_->resetStates();
        }
      }

      GraphicsInterface::resetRenderTarget();

      gaussianBlur_.render((*light)->shadowMapTexture());
    }

    // run lighting
    {
      GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);

      lightEffect_->setTexture(normalMapTexture_, "NormalMap");
      lightEffect_->setTexture(depthMapTexture_, "DepthMap");
      lightEffect_->setTexture(gaussianBlur_.outputTexture(), "ShadowMap");

      lightEffect_->setUniform((*light)->castsShadows(), "ShadowsEnabled");

      Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
      lightEffect_->setUniform(viewProjection, "ViewProj");
      lightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

      Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light)->transform();
      lightEffect_->setUniform(worldViewProj, "WorldViewProj");

      Matrix4x4 lightViewProj = (*light)->projection() * (*light)->viewTransform();
      lightEffect_->setUniform(lightViewProj, "LightViewProj");

      lightEffect_->setUniform((*light)->position(), "LightPosition");
      lightEffect_->setUniform((*light)->direction(), "LightDirection");
      lightEffect_->setUniform((*light)->color(), "LightColor");
      lightEffect_->setUniform((*light)->innerAngle() / 2.0f, "LightInnerAngle");
      lightEffect_->setUniform((*light)->outerAngle() / 2.0f, "LightOuterAngle");
      lightEffect_->setUniform((*light)->decay(), "LightDecay");

      lightEffect_->beginDraw();
      GraphicsInterface::setRenderState(false);
      spotLightModel_->render();
      lightEffect_->resetStates();

      GraphicsInterface::resetRenderTarget();
    }
  }
}