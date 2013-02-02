#include "DeferredDirectionalLightsPass.h"

#include <vector>

#include "maths/Vector2.h"
#include "maths/Matrix3x3.h"

#include "GraphicsInterface.h"
#include "DirectionalLight.h"

#include "SceneContext.h"
#include "IEffect.h"
#include "IViewer.h"

#include "Geometry.h"

#include "DeferredInitRenderStage.h"
#include "IDeferredRenderTargetContainer.h"

#include "memory/Allocation.h"

#include "EffectCache.h"

void DeferredDirectionalLightsPass::init(const CSize& screenSize) {
  directionalLightEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_lighting_directional_light.shader");
  quadVbo_ = Geometry::screenPlane();

  directionalLightRenderTexture_ = GraphicsInterface::createTexture(screenSize, IGraphicsInterface::R8G8B8A8);
  directionalLightRenderTarget_ = GraphicsInterface::createRenderTarget(directionalLightRenderTexture_);

  accumulationEffect_ = EffectCache::instance()->loadEffect("shaders/compiled/deferred_light_composition.shader");
  quadVbo_ = Geometry::screenPlane();
}

void DeferredDirectionalLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapRenderTarget, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Directional");
  
  {
    GraphicsInterface::beginPerformanceEvent("Lighting");

    GraphicsInterface::setRenderTarget(directionalLightRenderTarget_, false);

    std::vector<DirectionalLight> directionalLights = sceneContext.directionalLights();
    for (std::vector<DirectionalLight>::iterator light = directionalLights.begin(); light != directionalLights.end(); ++light) {
      directionalLightEffect_->beginDraw();

      directionalLightEffect_->setTexture(GraphicsInterface::depthBufferTexture(), "DepthMap");
      directionalLightEffect_->setTexture(initStage.normalMap(), "NormalMap");
      
      directionalLightEffect_->setUniform(viewer->viewTransform(), "View");
      Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
      directionalLightEffect_->setUniform(viewProjection, "ViewProj");
      directionalLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");
      directionalLightEffect_->setUniform(viewer->position(), "ViewPosition");
      directionalLightEffect_->setUniform((*light).direction(), "LightDirection");
      directionalLightEffect_->setUniform((*light).color(), "LightColor");

			directionalLightEffect_->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");

      //Matrix4x4 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
      directionalLightEffect_->setUniform(Matrix4x4::IDENTITY.mat3x3(), "NormalMatrix");

      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
      directionalLightEffect_->endDraw();
    }

    GraphicsInterface::endPerformanceEvent();
  }

  {
    GraphicsInterface::beginPerformanceEvent("Accumulation");

    GraphicsInterface::setBlendState(IGraphicsInterface::ADDITIVE);
    GraphicsInterface::setRenderTarget(lightMapRenderTarget, false);
    
    accumulationEffect_->beginDraw();
    accumulationEffect_->setTexture(directionalLightRenderTexture_, "LightSourceMap");
    accumulationEffect_->setTexture(initStage.colorMap(), "ColorMap");
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    accumulationEffect_->endDraw();
    GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}

void DeferredDirectionalLightsPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
  renderTargetContainer->addRenderTarget("Directional Light", directionalLightRenderTexture_);
}
