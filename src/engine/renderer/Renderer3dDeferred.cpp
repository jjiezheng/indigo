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
  colorRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  colorRenderTarget_ = GraphicsInterface::createRenderTarget(colorRenderTexture_);

  normalRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  normalRenderTarget_ = GraphicsInterface::createRenderTarget(normalRenderTexture_);

  depthRenderTexture_ = GraphicsInterface::createTexture(screenSize);
  depthRenderTarget_ = GraphicsInterface::createRenderTarget(depthRenderTexture_);

  pointLightTexture_ = GraphicsInterface::createTexture(screenSize);
  pointLightRenderTarget_ = GraphicsInterface::createRenderTarget(pointLightTexture_);

  pointLightEffect_ = IEffect::effectFromFile("cgfx/deferred_lighting_point_light.cgfx");
  pointLightModel_ = new Model();
  WorldLoader().loadModel(pointLightModel_, "debug/sphere.dae");

  finalEffect_ = IEffect::effectFromFile("cgfx/deferred_final_composition.cgfx");

  VertexDef finalQuadVertices[6];;
  finalQuadVertices[0].vertex = Vector3(-1.0f, -1.0f, 0.0f);
  finalQuadVertices[1].vertex = Vector3(1.0f, 1.0f, 0.0f);
  finalQuadVertices[2].vertex = Vector3(-1.0f, 1.0f, 0.0f);
  finalQuadVertices[3].vertex = Vector3(-1.0f, -1.0f, 0.0f);
  finalQuadVertices[4].vertex = Vector3(1.0f, -1.0f, 0.0f);
  finalQuadVertices[5].vertex = Vector3(1.0f, 1.0f, 0.0f);

  finalQuadVertices[0].normal = Vector3(0.0f, 0.0f, 1.0f);
  finalQuadVertices[1].normal = Vector3(0.0f, 0.0f, 1.0f);
  finalQuadVertices[2].normal = Vector3(0.0f, 0.0f, 1.0f);
  finalQuadVertices[3].normal = Vector3(0.0f, 0.0f, 1.0f);
  finalQuadVertices[4].normal = Vector3(0.0f, 0.0f, 1.0f);
  finalQuadVertices[5].normal = Vector3(0.0f, 0.0f, 1.0f);

  finalQuadVertices[0].uv = Vector2(0.0f, 0.0f);
  finalQuadVertices[1].uv = Vector2(1.0f, 1.0f);
  finalQuadVertices[2].uv = Vector2(0.0f, 1.0f);
  finalQuadVertices[3].uv = Vector2(0.0f, 0.0f);
  finalQuadVertices[4].uv = Vector2(1.0f, 0.0f);
  finalQuadVertices[5].uv = Vector2(1.0f, 1.0f);

  finalQuadVBOId_ = GraphicsInterface::createVertexBuffer(finalQuadVertices, 6);
}

void Renderer3dDeferred::render(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  renderGeometry(viewer, world, sceneContext);
  renderLights(viewer, world, sceneContext);
  renderFinal(viewer, world, sceneContext); 
}

void Renderer3dDeferred::renderGeometry(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  unsigned int renderTargets[] = {colorRenderTarget_, normalRenderTarget_, depthRenderTarget_};
  GraphicsInterface::setRenderTarget(renderTargets, 3);

  GraphicsInterface::clearRenderTarget(colorRenderTarget_, Color3::CORNFLOWERBLUE);
  GraphicsInterface::clearRenderTarget(normalRenderTarget_, Color3::GREY);
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

  Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();

  pointLightEffect_->setUniform(viewProjection, "ViewProj");
  pointLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");

  std::vector<Light> lights = sceneContext.lights();
  for (std::vector<Light>::iterator light = lights.begin(); light != lights.end(); ++light) {
    pointLightEffect_->setUniform((*light).position(), "LightPosition");
    pointLightEffect_->setUniform((*light).color(), "LightColor");

    Matrix4x4 world = (*light).transform();
    pointLightEffect_->setUniform(world, "World");

    Matrix4x4 worldView = viewer->viewTransform() * world;
    pointLightEffect_->setUniform(worldView, "WorldView");

    Matrix4x4 worldViewProjection = viewer->projection() * viewer->viewTransform() * world;
    pointLightEffect_->setUniform(worldViewProjection, "WorldViewProj");

    pointLightEffect_->beginDraw();
    GraphicsInterface::setPass(pointLightEffect_->pass()); 
    GraphicsInterface::setRenderState(true);
    pointLightModel_->render();
    pointLightEffect_->resetStates();
  }

  GraphicsInterface::resetRenderTarget();
}

void Renderer3dDeferred::renderFinal(IViewer* viewer, World& world, const SceneContext& sceneContext) {
  GraphicsInterface::clearBuffer(sceneContext.backgroundColor());
  finalEffect_->beginDraw();
  finalEffect_->setTexture(colorRenderTexture_, "ColorMap");
  GraphicsInterface::setPass(finalEffect_->pass()); 
  GraphicsInterface::setRenderState(true);
  GraphicsInterface::drawVertexBuffer(finalQuadVBOId_, 6);
  finalEffect_->resetStates();
}
