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

void DeferredSpotLightsPass::init(const CSize& screenSize) {
  shadowMapEffect_ = IEffect::effectFromFile("shaders/compiled/deferred_depth.shader");
  lightEffect_ = IEffect::effectFromFile("shaders/compiled/deferred_lighting_spot_light.shader");
  lightEffect_->setSamplerState(2, UV_ADDRESS_CLAMP, FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT, COMPARISON_LESS);

  spotLightRenderTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R8G8B8A8);
  spotLightRenderTarget_ = GraphicsInterface::createRenderTarget(spotLightRenderTexture_);

  accumulationEffect_ = IEffect::effectFromFile("shaders/compiled/deferred_light_composition.shader");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredSpotLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapRenderTarget, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Spot", Color4::ORANGE);

  {
    GraphicsInterface::beginPerformanceEvent("Clear", Color4::MAGENTA);

    GraphicsInterface::setRenderTarget(spotLightRenderTarget_, false);
    GraphicsInterface::clearRenderTarget(spotLightRenderTarget_, Color4::NOTHING);

    GraphicsInterface::endPerformanceEvent();
  }

  hash_map<int, std::vector<Mesh*> > meshes;
  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(meshes);
  }

  std::vector<SpotLight*> spotLights = sceneContext.spotLights();
  for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {

    GraphicsInterface::beginPerformanceEvent("Light", Color4::MAGENTA);

    if ((*light)->castsShadows()) {
      GraphicsInterface::beginPerformanceEvent("Shadow Map", Color4::BLUE);
      
      {
        GraphicsInterface::beginPerformanceEvent("Depth", Color4::GREY);

        GraphicsInterface::setViewport((*light)->shadowMapResolution());
        GraphicsInterface::setRenderTarget((*light)->shadowMapRenderTarget(), true, (*light)->shadowMapDepthTexture());
        GraphicsInterface::clearRenderTarget((*light)->shadowMapRenderTarget(), Color4::WHITE);
        GraphicsInterface::clearDepthTarget((*light)->shadowMapDepthTexture());

        hash_map<int, std::vector<Mesh*> >::iterator i = meshes.begin();
        for (; i != meshes.end(); ++i) {
          std::vector<Mesh*> effectMeshes = (*i).second;
          for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
            (*meshIt)->material().bind((*light)->projection(), (*light)->viewTransform(), (*meshIt)->localToWorld(), shadowMapEffect_);
           
            GraphicsInterface::setRenderState(true);
            shadowMapEffect_->beginDraw();
            (*meshIt)->render();
            shadowMapEffect_->endDraw();
          }
        }

        GraphicsInterface::setViewport(GraphicsInterface::screenSize());

        GraphicsInterface::endPerformanceEvent();
      }

      GraphicsInterface::endPerformanceEvent();
    }

    // render lighting
    {
      GraphicsInterface::beginPerformanceEvent("Lighting", Color4::BLUE);

      GraphicsInterface::setRenderTarget(spotLightRenderTarget_, false);

      lightEffect_->setUniform((*light)->castsShadows(), "ShadowsEnabled");

      Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
      lightEffect_->setUniform(viewer->viewTransform(), "View");
      lightEffect_->setUniform(viewProjection, "ViewProj");
      lightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

      lightEffect_->setUniform(viewer->projection().inverse(), "ProjInv");

      Matrix4x4 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
      //lightEffect_->setUniform(normalMatrix, "NormalMatrix"); 

      lightEffect_->setUniform(viewer->position(), "ViewPosition");

      Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light)->transform();
      lightEffect_->setUniform(worldViewProj, "WorldViewProj");

      Matrix4x4 worldView = viewer->viewTransform() * (*light)->transform();
      lightEffect_->setUniform(worldView, "WorldView");

      Matrix4x4 lightViewProj = (*light)->projection() * (*light)->viewTransform();
      lightEffect_->setUniform(lightViewProj, "LightViewProj");
      lightEffect_->setUniform(lightViewProj.inverse(), "LightViewProjRaw");

      CSize shadowMapResolution = (*light)->shadowMapResolution();
      Vector2 shadowMapSize(1.0f/shadowMapResolution.width, 1.0f/shadowMapResolution.height);
      lightEffect_->setUniform(shadowMapSize, "ShadowMapSize");


      lightEffect_->setUniform((*light)->position(), "LightPosition");
      lightEffect_->setUniform((*light)->direction(), "LightDirection");
      lightEffect_->setUniform((*light)->color(), "LightColor");

      lightEffect_->setUniform((*light)->outerAngle(), "LightOuterAngle");
      lightEffect_->setUniform((*light)->innerAngle(), "LightInnerAngle");

      unsigned int depthBufferId = GraphicsInterface::depthBufferTexture();
      lightEffect_->setTexture(depthBufferId, "DepthMap");
      lightEffect_->setTexture((*light)->shadowMapDepthTexture(), "ShadowMap");
      lightEffect_->setTexture(initStage.normalMap(), "NormalMap");

      GraphicsInterface::setRenderState(true);
      lightEffect_->beginDraw();
      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
      lightEffect_->endDraw();

      GraphicsInterface::endPerformanceEvent();
    }

    // accumulate into lightmap
    {
  
      GraphicsInterface::beginPerformanceEvent("Accumulation", Color4::BLUE);

      GraphicsInterface::setBlendState(IGraphicsInterface::ADDITIVE);
      GraphicsInterface::setRenderTarget(lightMapRenderTarget, false);
      accumulationEffect_->setTexture(spotLightRenderTexture_, "LightSourceMap");
      accumulationEffect_->setTexture(initStage.colorMap(), "ColorMap");
      GraphicsInterface::setRenderState(true);
      accumulationEffect_->beginDraw();
      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
      accumulationEffect_->endDraw();
      GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

      GraphicsInterface::endPerformanceEvent();
    }

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredSpotLightsPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Spot Light", spotLightRenderTexture_);
}
