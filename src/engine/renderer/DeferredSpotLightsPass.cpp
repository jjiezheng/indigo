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

#include "DeferredInitRenderStage.h"

#include "serialization/BinaryModelDeserializer.h"
#include "io/Path.h"

void DeferredSpotLightsPass::init(const CSize& screenSize) {
  shadowMapEffect_ = IEffect::effectFromFile("cgfx/deferred_depth.hlsl");
  lightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_spot_light.hlsl");

  std::string coneModelPath = Path::pathForFile("debug/cone.modelbinary");
  spotLightModel_ = BinaryModelDeserializer::deserialize(coneModelPath);

  gaussianBlur_.init(screenSize, 16);

  spotLightRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  spotLightRenderTarget_ = GraphicsInterface::createRenderTarget(spotLightRenderTexture_);

  accumulationEffect_ = IEffect::effectFromFile("cgfx/deferred_light_composition.hlsl");
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

  stdext::hash_map<int, std::vector<Mesh*> > meshes;
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

        GraphicsInterface::setRenderTarget((*light)->shadowMapRenderTarget(), true);
        GraphicsInterface::clearRenderTarget((*light)->shadowMapRenderTarget(), Color4::WHITE);

        stdext::hash_map<int, std::vector<Mesh*> >::iterator i = meshes.begin();
        for (; i != meshes.end(); ++i) {
          std::vector<Mesh*> effectMeshes = (*i).second;
          for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
            (*meshIt)->material().bind((*light)->projection(), (*light)->viewTransform(), (*meshIt)->localToWorld(), shadowMapEffect_);
           
            shadowMapEffect_->beginDraw();
            GraphicsInterface::setRenderState(true);
            (*meshIt)->render();
          }
        }

        GraphicsInterface::endPerformanceEvent();
      }

      {
        GraphicsInterface::beginPerformanceEvent("Blur", Color4::GREY);
        gaussianBlur_.render((*light)->shadowMapTexture());
        GraphicsInterface::endPerformanceEvent();
      }

      GraphicsInterface::endPerformanceEvent();
    }

    // render lighting
    {
      GraphicsInterface::beginPerformanceEvent("Lighting", Color4::BLUE);

      GraphicsInterface::setRenderTarget(spotLightRenderTarget_, false);

      lightEffect_->setTexture(initStage.normalMap(), "NormalMap");
      lightEffect_->setTexture(initStage.depthMap(), "DepthMap");
      lightEffect_->setTexture(gaussianBlur_.outputTexture(), "ShadowMap");

      lightEffect_->setUniform((*light)->castsShadows(), "ShadowsEnabled");

      Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
      lightEffect_->setUniform(viewer->viewTransform(), "View");
      lightEffect_->setUniform(viewProjection, "ViewProj");
      lightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

      lightEffect_->setUniform(viewer->projection().inverse(), "ProjInv");

      Matrix4x4 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
      lightEffect_->setUniform(normalMatrix, "NormalMatrix");

      lightEffect_->setUniform(viewer->position(), "ViewPosition");

      Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * (*light)->transform();
      lightEffect_->setUniform(worldViewProj, "WorldViewProj");

      Matrix4x4 worldView = viewer->viewTransform() * (*light)->transform();
      lightEffect_->setUniform(worldView, "WorldView");

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

      GraphicsInterface::endPerformanceEvent();
    }

    // accumulate into lightmap
    {
      GraphicsInterface::beginPerformanceEvent("Accumulation", Color4::BLUE);

      GraphicsInterface::setRenderTarget(lightMapRenderTarget, false);
      accumulationEffect_->setTexture(spotLightRenderTexture_, "LightSourceMap");
      accumulationEffect_->setTexture(initStage.colorMap(), "ColorMap");
      accumulationEffect_->beginDraw();
      GraphicsInterface::setRenderState(true);
      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);

      GraphicsInterface::endPerformanceEvent();
    }

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}