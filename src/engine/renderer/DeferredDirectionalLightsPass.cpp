#include "DeferredDirectionalLightsPass.h"

#include <vector>

#include "GraphicsInterface.h"
#include "DirectionalLight.h"

#include "VertexDefinition.h"
#include "SceneContext.h"
#include "IEffect.h"
#include "IViewer.h"

void DeferredDirectionalLightsPass::init() {
  directionalLightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_directional_light.cgfx");
  
  VertexDef quadVertices[6];;
  quadVertices[0].vertex = Vector3(-1.0f, -1.0f, 0.0f);
  quadVertices[1].vertex = Vector3(1.0f, 1.0f, 0.0f);
  quadVertices[2].vertex = Vector3(-1.0f, 1.0f, 0.0f);
  quadVertices[3].vertex = Vector3(-1.0f, -1.0f, 0.0f);
  quadVertices[4].vertex = Vector3(1.0f, -1.0f, 0.0f);
  quadVertices[5].vertex = Vector3(1.0f, 1.0f, 0.0f);

  quadVertices[0].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[1].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[2].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[3].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[4].normal = Vector3(0.0f, 0.0f, 1.0f);
  quadVertices[5].normal = Vector3(0.0f, 0.0f, 1.0f);

  quadVertices[0].uv = Vector2(0.0f, 0.0f);
  quadVertices[1].uv = Vector2(1.0f, 1.0f);
  quadVertices[2].uv = Vector2(0.0f, 1.0f);
  quadVertices[3].uv = Vector2(0.0f, 0.0f);
  quadVertices[4].uv = Vector2(1.0f, 0.0f);
  quadVertices[5].uv = Vector2(1.0f, 1.0f);

  quadVbo_ = GraphicsInterface::createVertexBuffer(quadVertices, 6);
}

void DeferredDirectionalLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);

  std::vector<DirectionalLight> directionalLights = sceneContext.directionalLights();
  for (std::vector<DirectionalLight>::iterator light = directionalLights.begin(); light != directionalLights.end(); ++light) {
    directionalLightEffect_->setTexture(normalMapTexture_, "NormalMap");
    
    Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
    directionalLightEffect_->setUniform(viewProjection, "ViewProj");
    directionalLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");
    directionalLightEffect_->setUniform(halfPixel_, "HalfPixel");
    directionalLightEffect_->setUniform((*light).direction(), "LightDirection");
    directionalLightEffect_->setUniform((*light).color(), "LightColor");

    directionalLightEffect_->beginDraw();
    GraphicsInterface::setPass(directionalLightEffect_->pass()); 
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, 6);
    directionalLightEffect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}