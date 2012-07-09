#include "DeferredDirectionalLightsPass.h"

#include <vector>

#include "GraphicsInterface.h"
#include "DirectionalLight.h"

#include "SceneContext.h"
#include "IEffect.h"
#include "IViewer.h"

#include "Geometry.h"

void DeferredDirectionalLightsPass::init() {
  directionalLightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_directional_light.hlsl");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredDirectionalLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);

  std::vector<DirectionalLight> directionalLights = sceneContext.directionalLights();
  for (std::vector<DirectionalLight>::iterator light = directionalLights.begin(); light != directionalLights.end(); ++light) {
    directionalLightEffect_->setTexture(normalMapTexture_, "NormalMap");
    
    Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
    directionalLightEffect_->setUniform(viewProjection, "ViewProj");
    directionalLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");
    directionalLightEffect_->setUniform((*light).direction(), "LightDirection");
    directionalLightEffect_->setUniform((*light).color(), "LightColor");

    directionalLightEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
    directionalLightEffect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}