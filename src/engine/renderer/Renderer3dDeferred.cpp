#include "Renderer3dDeferred.h"

#include "Model.h"
#include "World.h"
#include "Camera.h"
#include "IEffect.h"
#include "SceneContext.h"

#include "GraphicsInterface.h"
#include "EffectCache.h"
#include "VertexDefinition.h"
#include "WorldLoader.h"

#include "maths/Matrix3x3.h"
#include <hash_map>

void Renderer3dDeferred::init(const CSize& screenSize) {
  halfPixel_.x = 0.5f / screenSize.width;
  halfPixel_.y = 0.5f / screenSize.height;

  colorMapTexture_ = GraphicsInterface::createTexture(screenSize);
  colorRenderTarget_ = GraphicsInterface::createRenderTarget(colorMapTexture_);

  normalMapTexture_ = GraphicsInterface::createTexture(screenSize);
  normalRenderTarget_ = GraphicsInterface::createRenderTarget(normalMapTexture_);

  depthMapTexture_ = GraphicsInterface::createTexture(screenSize);
  depthRenderTarget_ = GraphicsInterface::createRenderTarget(depthMapTexture_);

  lightMapTexture_ = GraphicsInterface::createTexture(screenSize);
  pointLightRenderTarget_ = GraphicsInterface::createRenderTarget(lightMapTexture_);

  directionalLightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_directional_light.cgfx");
  pointLightModel_ = new Model();
  WorldLoader().loadModel(pointLightModel_, "debug/sphere.dae");

  finalEffect_ = IEffect::effectFromFile("cgfx/deferred_final_composition.cgfx");

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

  finalQuadVBOId_ = GraphicsInterface::createVertexBuffer(quadVertices, 6);
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  renderGeometry(viewer, world, sceneContext);
  renderLights(viewer, world, sceneContext);
  renderFinal(viewer, world, sceneContext); 
}

void Renderer3dDeferred::renderGeometry(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  unsigned int renderTargets[] = {colorRenderTarget_, normalRenderTarget_, depthRenderTarget_};
  GraphicsInterface::setRenderTarget(renderTargets, 3);

  GraphicsInterface::clearRenderTarget(colorRenderTarget_, Color3::BLACK);
  GraphicsInterface::clearRenderTarget(normalRenderTarget_, Color3::BLACK);
  GraphicsInterface::clearRenderTarget(depthRenderTarget_, Color3::WHITE);

  stdext::hash_map<int, std::vector<Mesh*>> effects;

  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(effects);
  }

  stdext::hash_map<int, std::vector<Mesh*>>::iterator i = effects.begin();
  for (; i != effects.end(); ++i) {

    unsigned int effectId = (*i).first;
    IEffect* effect = EffectCache::instance()->getEffect(effectId);

    std::vector<Mesh*> effectMeshes = (*i).second;
    for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
      (*meshIt)->material().bind(viewer, (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, effect);

      effect->beginDraw();
      GraphicsInterface::setPass(effect->pass()); 
      GraphicsInterface::setRenderState(true);
      (*meshIt)->render();
      effect->resetStates();
    }
  }

  GraphicsInterface::resetRenderTarget();
}

void Renderer3dDeferred::renderLights(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(&pointLightRenderTarget_, 1);
  GraphicsInterface::clearRenderTarget(pointLightRenderTarget_, Color3::BLACK);

  //GraphicsInterface::resetRenderTarget();
 // GraphicsInterface::clearBuffer(Color3::RED);

  Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();

  directionalLightEffect_->setTexture(normalMapTexture_, "NormalMap");
  //directionalLightEffect_->setTexture(depthMapTexture_, "DepthMap");

  directionalLightEffect_->setUniform(viewProjection, "ViewProj");
  directionalLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");
  directionalLightEffect_->setUniform(halfPixel_, "HalfPixel");

  std::vector<DirectionalLight> directionalLights = sceneContext.directionalLights();
  for (std::vector<DirectionalLight>::iterator light = directionalLights.begin(); light != directionalLights.end(); ++light) {
    directionalLightEffect_->setUniform((*light).direction(), "LightDirection");
    directionalLightEffect_->setUniform((*light).color(), "LightColor");

    directionalLightEffect_->beginDraw();
    GraphicsInterface::setPass(directionalLightEffect_->pass()); 
    GraphicsInterface::setRenderState(true);
    GraphicsInterface::drawVertexBuffer(finalQuadVBOId_, 6);
    directionalLightEffect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}

void Renderer3dDeferred::renderFinal(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(sceneContext.backgroundColor());
  finalEffect_->beginDraw();
  finalEffect_->setTexture(colorMapTexture_, "ColorMap");
  finalEffect_->setTexture(lightMapTexture_, "LightMap");
  finalEffect_->setUniform(halfPixel_, "HalfPixel");
  GraphicsInterface::setPass(finalEffect_->pass()); 
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(finalQuadVBOId_, 6);
  finalEffect_->resetStates();
}
