#include "DeferredDirectionalLightsPass.h"

#include <vector>

#include "maths/Matrix3x3.h"

#include "GraphicsInterface.h"
#include "DirectionalLight.h"

#include "SceneContext.h"
#include "IEffect.h"
#include "IViewer.h"

#include "Geometry.h"

#include "DeferredInitRenderStage.h"

void DeferredDirectionalLightsPass::init(const CSize& screenSize) {
  directionalLightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_directional_light.hlsl");
  quadVbo_ = Geometry::screenPlane();

  directionalLightRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  directionalLightRenderTarget_ = GraphicsInterface::createRenderTarget(directionalLightRenderTexture_);

  accumulationEffect_ = IEffect::effectFromFile("cgfx/deferred_light_composition.hlsl");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredDirectionalLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapRenderTarget, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Directional", Color4::GREEN);
  
  {
    GraphicsInterface::beginPerformanceEvent("Lighting", Color4::ORANGE);

    GraphicsInterface::setRenderTarget(directionalLightRenderTarget_, false);

    std::vector<DirectionalLight> directionalLights = sceneContext.directionalLights();
    for (std::vector<DirectionalLight>::iterator light = directionalLights.begin(); light != directionalLights.end(); ++light) {
      directionalLightEffect_->setTexture(initStage.depthMap(), "DepthMap");
      directionalLightEffect_->setTexture(initStage.normalMap(), "NormalMap");
      
      directionalLightEffect_->setUniform(viewer->viewTransform(), "View");
      Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
      directionalLightEffect_->setUniform(viewProjection, "ViewProj");
      directionalLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");
      directionalLightEffect_->setUniform(viewer->position(), "ViewPosition");
      directionalLightEffect_->setUniform((*light).direction(), "LightDirection");
      directionalLightEffect_->setUniform((*light).color(), "LightColor");

      Matrix4x4 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
      directionalLightEffect_->setUniform(normalMatrix, "NormalMatrix");

      directionalLightEffect_->beginDraw();
      GraphicsInterface::setRenderState(true);
      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);
    }

    GraphicsInterface::endPerformanceEvent();
  }

  // accumulate into LightMap
  {
    GraphicsInterface::beginPerformanceEvent("Accumulation", Color4::ORANGE);

    GraphicsInterface::setRenderTarget(lightMapRenderTarget, false);
    accumulationEffect_->setTexture(directionalLightRenderTexture_, "LightSourceMap");
    accumulationEffect_->setTexture(initStage.colorMap(), "ColorMap");
    accumulationEffect_->beginDraw();
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT);

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}