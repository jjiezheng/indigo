#include "DeferredSpotLightsPass.h"

#include <vector>

#include "IEffect.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"

#include "SpotLight.h"

#include "IViewer.h"

#include "VertexDefinition.h"

void DeferredSpotLightsPass::init() {
  effect_ = IEffect::effectFromFile("cgfx/deferred_lighting_spot_light.cgfx");

  VertexDef quadVertices[6];
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

void DeferredSpotLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(lightMapRenderTarget_, false);
  effect_->setUniform(halfPixel_, "HalfPixel");

  //effect_->setTexture(normalMapTexture_, "NormalMap");
  //effect_->setTexture(depthMapTexture_, "DepthMap");

  std::vector<SpotLight> spotLights = sceneContext.spotLights();

  for (std::vector<SpotLight>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {
    Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light).transform();
    effect_->setUniform(worldViewProj, "WorldViewProj");

    effect_->beginDraw();
    GraphicsInterface::setPass(effect_->pass()); 
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, 6);
    effect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}