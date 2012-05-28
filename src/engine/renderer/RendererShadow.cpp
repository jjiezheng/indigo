#include "RendererShadow.h"

#include "core/Size.h"

#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"
#include "ShaderSemantics.h"
#include "IEffect.h"

#include "Texture.h"

#include "io/Log.h"
#include "io/Path.h"

#include "GraphicsInterface.h"

void RendererShadow::init(const CSize &screenSize) {
  shadowMap_ = GraphicsInterface::createShadowMap(screenSize);
} 

void RendererShadow::render(IViewer* viewer, const World& world, SceneContext& sceneContext) {
  GraphicsInterface::bindShadowMap(shadowMap_);
  GraphicsInterface::clearBuffer(Color3(0, 0, 0));

  std::vector<Model>::const_iterator mit = world.begin();
  for (; mit != world.end(); ++mit) {
    (*mit).render(viewer, sceneContext);
  }
  //sceneContext.setShadowTexture(shadowMap_);*/
  
  glDisable(GL_POLYGON_OFFSET_FILL);
  glCullFace(GL_BACK);

  GraphicsInterface::clearBuffer(Color3(0, 0, 0));
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0); 
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  
  glDisable(GL_DEPTH_TEST); 
  glDisable(GL_CULL_FACE);
  
}

void RendererShadow::renderDebug(SceneContext& sceneContext) { 
  /*debugEffect_->beginDraw();

  debugEffect_->setTexture(shadowTexture_, "colorMapSampler");
  
  glBindVertexArray(debugVertArray_);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  debugEffect_->endDraw();*/
}