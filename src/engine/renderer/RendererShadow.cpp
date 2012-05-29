#include "RendererShadow.h"

#include "core/Size.h"

#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"
#include "GraphicsInterface.h"

void RendererShadow::init(const CSize &screenSize) {
  shadowMap_ = GraphicsInterface::createShadowMap(screenSize);
} 

void RendererShadow::renderToShadowMap(IViewer* viewer, const World& world, SceneContext& sceneContext) {
  GraphicsInterface::bindShadowMap(shadowMap_);
  
  std::vector<Model>::const_iterator mit = world.begin();
  for (; mit != world.end(); ++mit) {
    (*mit).render(viewer, sceneContext);
  }

  GraphicsInterface::unBindShadowMap(shadowMap_);
  sceneContext.setShadowTexture(shadowMap_);
}