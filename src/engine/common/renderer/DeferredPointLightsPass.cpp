#include "DeferredPointLightsPass.h"

#include "GraphicsInterface.h"
#include "WorldLoader.h"

#include "IEffect.h"
#include "EffectCache.h"
#include "Model.h"

#include "PointLight.h"
#include "SceneContext.h"
#include "IViewer.h"

void DeferredPointLightsPass::init() {
  pointLightEffect_ = EffectCache::instance()->loadEffect("cgfx/deferred_lighting_point_light.hlsl");

  pointLightModel_ = new Model();
  WorldLoader().loadModel(pointLightModel_, "debug/sphere.model");
}

void DeferredPointLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);

  pointLightEffect_->setTexture(normalMapTexture_, "NormalMap");
  pointLightEffect_->setTexture(depthMapTexture_, "DepthMap");

  std::vector<PointLight> pointLights = sceneContext.pointLights();

  for (std::vector<PointLight>::iterator light = pointLights.begin(); light != pointLights.end(); ++light) {
		pointLightEffect_->beginDraw();

    Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light).transform();
    pointLightEffect_->setUniform(worldViewProj, "WorldViewProj");

    Matrix4x4 viewProjInv = (viewer->projection() * viewer->viewTransform()).inverse();
    pointLightEffect_->setUniform(viewProjInv, "ViewProjInv");

    pointLightEffect_->setUniform((*light).position(), "LightPosition");
    pointLightEffect_->setUniform((*light).radius(), "LightRadius");
    pointLightEffect_->setUniform((*light).color(), "LightColor");

    float distanceToLightCenter = viewer->position().distance((*light).position());
		CullMode cullMode = distanceToLightCenter >= (*light).radius() + viewer->nearDistance() ? CULL_MODE_FRONT : CULL_MODE_BACK;

		pointLightEffect_->commitBuffers();
    GraphicsInterface::setRenderState(cullMode);
    pointLightModel_->render();
  }
}