#include "DeferredFXAAPass.h"

#include "IEffect.h"

#include "VertexDefinition.h"

#include "GraphicsInterface.h"
#include "SceneContext.h"

void DeferredFXAAPass::init() {
  finalEffect_ = IEffect::effectFromFile("cgfx/deferred_fxaa.cgfx");

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

void DeferredFXAAPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(sceneContext.backgroundColor());
  finalEffect_->beginDraw();

  finalEffect_->setTexture(finalRenderTexture_, "FinalMap");
  finalEffect_->setUniform(halfPixel_, "HalfPixel");

  CSize screenSize = GraphicsInterface::screenSize();
  Vector2 screenSizeInv;
  screenSizeInv.x = 1.0f / screenSize.width;
  screenSizeInv.y = 1.0f / screenSize.height;
  finalEffect_->setUniform(screenSizeInv, "ScreenSizeInv");

  GraphicsInterface::setPass(finalEffect_->pass()); 
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(quadVbo_, 6);
  finalEffect_->resetStates();
}
