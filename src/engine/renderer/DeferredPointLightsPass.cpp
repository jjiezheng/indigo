#include "DeferredPointLightsPass.h"

#include "GraphicsInterface.h"
#include "WorldLoader.h"

#include "IEffect.h"
#include "Model.h"

#include "PointLight.h"
#include "SceneContext.h"
#include "IViewer.h"

void DeferredPointLightsPass::init() {
  pointLightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_point_light.cgfx");

  pointLightModel_ = new Model();
  WorldLoader().loadModel(pointLightModel_, "debug/sphere.dae");
}

void DeferredPointLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);
  pointLightEffect_->setUniform(halfPixel_, "HalfPixel");

  pointLightEffect_->setTexture(normalMapTexture_, "NormalMap");
  pointLightEffect_->setTexture(depthMapTexture_, "DepthMap");
  pointLightEffect_->setTexture(shadowMapTexture_, "ShadowMap");

  std::vector<PointLight> pointLights = sceneContext.pointLights();

  for (std::vector<PointLight>::iterator light = pointLights.begin(); light != pointLights.end(); ++light) {
    Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light).transform();
    pointLightEffect_->setUniform(worldViewProj, "WorldViewProj");

    Matrix4x4 viewProjInv = (viewer->projection() * viewer->viewTransform()).inverse();
    pointLightEffect_->setUniform(viewProjInv, "ViewProjInv");

    pointLightEffect_->setUniform((*light).position(), "LightPosition");
    pointLightEffect_->setUniform((*light).radius(), "LightRadius");
    pointLightEffect_->setUniform((*light).color(), "LightColor");

    float distanceToLightCenter = viewer->position().distance((*light).position());
    bool cullBackFaces = distanceToLightCenter >= (*light).radius() + viewer->nearDistance();

    pointLightEffect_->beginDraw();
    GraphicsInterface::setPass(pointLightEffect_->pass()); 
    GraphicsInterface::setRenderState(cullBackFaces);
    pointLightModel_->render();
    GraphicsInterface::setRenderState(true);
    pointLightEffect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}