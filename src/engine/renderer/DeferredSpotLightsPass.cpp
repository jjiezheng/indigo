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
#include "maths/Vector2.h"

#include "DeferredInitRenderStage.h"
#include "IDeferredRenderTargetContainer.h"

#include "serialization/BinaryModelDeserializer.h"
#include "io/Path.h"
#include "EffectCache.h"

#include "memory/Allocation.h"

void DeferredSpotLightsPass::init(const CSize& screenSize) {
  shadowDepthEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_depth.shader");

  lightEffectNoShadow_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_lighting_spot_light.shader");
  lightEffectNoShadow_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
  lightEffectNoShadow_->setSamplerState(1, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);

  lightEffectShadow_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_lighting_spot_light_shadow.shader");
  lightEffectShadow_->setSamplerState(0, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
  lightEffectShadow_->setSamplerState(1, UV_ADDRESS_CLAMP, FILTER_MIN_MAG_MIP_POINT, COMPARISON_NONE);
  lightEffectShadow_->setSamplerState(2, UV_ADDRESS_CLAMP, FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT, COMPARISON_LESS_SHADOW);
 
  spotLightRenderTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R8G8B8A8);
  spotLightRenderTarget_ = GraphicsInterface::createRenderTarget(spotLightRenderTexture_);

  accumulationEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_light_composition.shader");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredSpotLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapRenderTarget, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Spot");

  { // Shadow Map
    hash_map<IEffect*, std::vector<Mesh*> > meshes;
    std::vector<Model*>::iterator it = world.begin();
    for (; it != world.end(); ++it) {
      (*it)->visit(meshes);
    }

    std::vector<SpotLight*> spotLights = sceneContext.spotLights();

    for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {
      if ((*light)->castsShadows()) {
        SpotLight* spotLight = (*light);
        renderShadowMap(spotLight, meshes);
      }
    }
  }
  
  { // Lighting
    unsigned int lightIndex = 0;
    std::vector<SpotLight*> spotLights = sceneContext.spotLights();
    for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {

      GraphicsInterface::beginPerformanceEvent("Light " + lightIndex);

      SpotLight* spotLight = (*light);
      
      { // render lighting
        IEffect* lightEffect = (*light)->castsShadows() ? lightEffectShadow_ : lightEffectNoShadow_;
        renderLight(spotLight, lightEffect, viewer, initStage.normalMap());
      }
      
      { // accumulate into lightmap
        accumulateLight(spotLight, initStage.colorMap(), lightMapRenderTarget);
      }

      GraphicsInterface::endPerformanceEvent();
    }
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredSpotLightsPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Spot Light", spotLightRenderTexture_);
}

void DeferredSpotLightsPass::renderShadowMap(SpotLight* light, hash_map<IEffect*, std::vector<Mesh*> >& meshes) {
  GraphicsInterface::beginPerformanceEvent("Shadow Map");

  GraphicsInterface::setViewport(light->shadowMapResolution());

  GraphicsInterface::setRenderTarget(light->shadowMapRenderTarget(), true, light->shadowMapResolution(), light->shadowMapDepthTexture());

  GraphicsInterface::clearActiveColorBuffers(Color4::WHITE);
  GraphicsInterface::clearActiveDepthBuffer();

  hash_map<IEffect*, std::vector<Mesh*> >::iterator i = meshes.begin();
  for (; i != meshes.end(); ++i) {
    std::vector<Mesh*> effectMeshes = (*i).second;
    for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
      (*meshIt)->material().bind(light->projection(), light->viewTransform(), (*meshIt)->localToWorld(), shadowDepthEffect_);

      GraphicsInterface::setRenderState(true);
      shadowDepthEffect_->beginDraw();
      (*meshIt)->render();
      shadowDepthEffect_->endDraw();
    }
  }

  GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());

  GraphicsInterface::endPerformanceEvent();
}

void DeferredSpotLightsPass::renderLight(SpotLight* light, IEffect* lightEffect, IViewer* viewer, unsigned int normalMap) {
  GraphicsInterface::beginPerformanceEvent("Lighting");

  GraphicsInterface::setRenderTarget(spotLightRenderTarget_, false);
  GraphicsInterface::clearActiveColorBuffers(Color4::CORNFLOWERBLUE);

  if (light->castsShadows()) {
    CSize shadowMapResolution = light->shadowMapResolution();
    Vector2 shadowMapSize(1.0f/shadowMapResolution.width, 1.0f/shadowMapResolution.height);
    lightEffect->setUniform(shadowMapSize, "ShadowMapSize");
    lightEffect->setTexture(light->shadowMapDepthTexture(), "ShadowMap");
  }

  Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
  lightEffect->setUniform(viewer->viewTransform(), "View");
  lightEffect->setUniform(viewProjection, "ViewProj");
  lightEffect->setUniform(viewProjection.inverse(), "ViewProjInv");

  lightEffect->setUniform(viewer->projection().inverse(), "ProjInv");

//  Matrix4x4 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
  //lightEffect_->setUniform(normalMatrix, "NormalMatrix");

  lightEffect->setUniform(viewer->position(), "ViewerPosition");

  Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * light->transform();
  lightEffect->setUniform(worldViewProj, "WorldViewProj");

  Matrix4x4 worldView = viewer->viewTransform() * light->transform();
  lightEffect->setUniform(worldView, "WorldView");

  Matrix4x4 lightViewProj = light->projection() * light->viewTransform();
  lightEffect->setUniform(lightViewProj, "LightViewProj");
  lightEffect->setUniform(lightViewProj.inverse(), "LightViewProjRaw");

  float lightDistance = light->direction().length();
  float lightDistanceSquared = lightDistance * lightDistance;
  lightEffect->setUniform(1.0f / lightDistanceSquared, "LightDistance");

  lightEffect->setUniform(light->direction().inverse().normalize(), "DirectionToLight");

  lightEffect->setUniform(light->position(), "LightPosition");
  lightEffect->setUniform(light->direction().normalize(), "LightDirection");
  lightEffect->setUniform(light->color(), "LightColor");

  lightEffect->setUniform(light->outerAngle(), "LightOuterAngle");
  lightEffect->setUniform(light->innerAngle(), "LightInnerAngle");

	lightEffect->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");

  unsigned int depthBufferId = GraphicsInterface::depthBufferTexture();
  lightEffect->setTexture(depthBufferId, "DepthMap");

  lightEffect->setTexture(normalMap, "NormalMap");

  GraphicsInterface::setRenderState(true);
  lightEffect->beginDraw();
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  lightEffect->endDraw();

  GraphicsInterface::endPerformanceEvent();
}

void DeferredSpotLightsPass::accumulateLight(SpotLight* light, unsigned int colorMap, unsigned int lightMapRenderTarget) {
  GraphicsInterface::beginPerformanceEvent("Accumulation");

  GraphicsInterface::setBlendState(IGraphicsInterface::ADDITIVE);
  GraphicsInterface::setRenderTarget(lightMapRenderTarget, false);
  accumulationEffect_->setTexture(spotLightRenderTexture_, "LightSourceMap");
  accumulationEffect_->setTexture(colorMap, "ColorMap");
	
	accumulationEffect_->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");

  GraphicsInterface::setRenderState(true);
  accumulationEffect_->beginDraw();
  GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
  accumulationEffect_->endDraw();
  GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

  GraphicsInterface::endPerformanceEvent();
}
