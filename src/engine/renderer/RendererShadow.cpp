#include "RendererShadow.h"

#include "core/Size.h"

#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"
#include "GraphicsInterface.h"

#include "IEffect.h"
#include "io/Path.h"

#include "maths/Matrix3x3.h"

#include "ShaderSemantics.h"

#include "IViewer.h"

void RendererShadow::init(const CSize &screenSize) {
  shadowTexture_ = GraphicsInterface::createTexture(CSize(1008, 730));
  renderTarget_ = GraphicsInterface::createRenderTarget(shadowTexture_);
  depthShader = GraphicsInterface::createEffect();
  std::string effectPath = Path::pathForFile("cgfx/depth.cgfx");
  depthShader->load(effectPath);
} 

void RendererShadow::renderToShadowMap(IViewer* viewer, World& world, SceneContext& sceneContext) {
  GraphicsInterface::setRenderTarget(&renderTarget_, 1, true);
  GraphicsInterface::clearRenderTarget(renderTarget_, Color4::WHITE);

  stdext::hash_map<int, std::vector<Mesh*>> meshes;
 
  std::vector<Model*>::iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it)->visit(meshes);
  }

  stdext::hash_map<int, std::vector<Mesh*>>::iterator i = meshes.begin();
  for (; i != meshes.end(); ++i) {
    std::vector<Mesh*> effectMeshes = (*i).second;
    for (std::vector<Mesh*>::iterator meshIt = effectMeshes.begin(); meshIt != effectMeshes.end(); ++meshIt) {
      (*meshIt)->material().bind(viewer->projection(), viewer->viewTransform(), (*meshIt)->localToWorld(), Matrix4x4::IDENTITY.mat3x3(), sceneContext, depthShader);

      depthShader->beginDraw();
      GraphicsInterface::setPass(depthShader->pass()); 
      GraphicsInterface::setRenderState(false);
      (*meshIt)->render();

      depthShader->resetStates();
    }
  }

  sceneContext.setShadowTexture(shadowTexture_);
  GraphicsInterface::resetRenderTarget();
}
