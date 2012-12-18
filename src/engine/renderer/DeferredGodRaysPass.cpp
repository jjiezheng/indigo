#include "DeferredGodRaysPass.h"

#include "IDeferredRenderTargetContainer.h"

#include "IEffect.h"
#include "Geometry.h"

#include "SpotLight.h"
#include "SceneContext.h"
#include "IViewer.h"

//http://http.developer.nvidia.com/GPUGems3/gpugems3_ch13.html

void DeferredGodRaysPass::init(const CSize& screenSize) {
//  godRaysTexture_ = GraphicsInterface::createTexture(GraphicsInterface::backBufferSize(), IGraphicsInterface::R8G8B8A8);
//  godRaysRenderTarget_ = GraphicsInterface::createRenderTarget(godRaysTexture_);
//  godRaysEffect_ = IEffect::effectFromFile("shaders/compiled/deferred_god_rays.shader");
//
//  quadVbo_ = Geometry::screenPlane();
}

unsigned int DeferredGodRaysPass::render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("God Rays");

  { // Lighting
    syspool::vector<SpotLight*>::type spotLights = sceneContext.spotLights();
    for (std::vector<SpotLight*>::iterator light = spotLights.begin(); light != spotLights.end(); ++light) {
      GraphicsInterface::beginPerformanceEvent("Light");
      SpotLight* spotLight = (*light);

      GraphicsInterface::setRenderTarget(godRaysRenderTarget_, false);

      Vector4 lightPositionScreenSpace = viewer->projection() * viewer->viewTransform() * spotLight->position();
      lightPositionScreenSpace /= lightPositionScreenSpace.w;

      godRaysEffect_->setUniform(lightPositionScreenSpace, "LightPositionScreenSpace");

      godRaysEffect_->setTexture(inputMap, "ColorMap");

      godRaysEffect_->beginDraw();
      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
      godRaysEffect_->endDraw();

      GraphicsInterface::endPerformanceEvent();
    }
  }

  GraphicsInterface::endPerformanceEvent();

  return godRaysTexture_;
}

std::string DeferredGodRaysPass::passName() const {
  return "God Rays";
}

GraphicsInterface::TextureId DeferredGodRaysPass::passMap() const {
  return godRaysTexture_;
}

void DeferredGodRaysPass::collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) {
 renderTargetContainer->addRenderTarget("God Rays", godRaysTexture_);
}
