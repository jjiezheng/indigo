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
 // shadowMap_ = GraphicsInterface::createShadowMap(screenSize);  

  /*{
    GLfloat vertices[] = {
      -1.0f, -1.0f, 0.0f,
      -0.5f, -1.0f, 0.0f,
      -1.0f, -0.5f, 0.0f,
      
      -1.0f, -0.5f, 0.0f,
      -0.5f, -1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f,
    };
    
    glGenVertexArrays(1, &debugVertArray_);
    glBindVertexArray(debugVertArray_);
    
    glGenBuffers(1, &debugVertBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, debugVertBuffer_);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(POSITION);
    
    GLfloat uvs[] = {
      0.0f, 0.0f,
      1.0f, 0.0f,
      0.0f, 1.0f,
      0.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 1.0f
    }; 
    
    glGenBuffers(1, &debugUVBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, debugUVBuffer_);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(TEXCOORD0, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(TEXCOORD0);

    std::string fullPath = Path::pathForFile("cgfx/diffuse_texture.cgfx");
    debugEffect_->load(fullPath.c_str());
         
  }*/
} 

void RendererShadow::render(IViewer* viewer, const World& world, SceneContext& sceneContext) {
 /* GraphicsInterface::bindShadowMap(shadowMap_);
  std::vector<Model>::const_iterator mit = world.begin();
  for (; mit != world.end(); ++mit) {
    (*mit).render(viewer, sceneContext);
  }*/
  
  /*glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //glPolygonOffset(2.5f, 10.0f);
  glEnable(GL_POLYGON_OFFSET_FILL);
  
  glClear(GL_DEPTH_BUFFER_BIT);  
  glCullFace(GL_FRONT);

  std::vector<Model>::const_iterator mit = world.begin();
  for (; mit != world.end(); ++mit) {
    (*mit).render(viewer, sceneContext);
  }
  
  glDisable(GL_POLYGON_OFFSET_FILL);
  glCullFace(GL_BACK);
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0); 
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  
  sceneContext.setShadowTexture(shadowTexture_);
  
  glDisable(GL_DEPTH_TEST); 
  glDisable(GL_CULL_FACE);*/
}

void RendererShadow::renderDebug(SceneContext& sceneContext) { 
  /*debugEffect_->beginDraw();

  debugEffect_->setTexture(shadowTexture_, "colorMapSampler");
  
  glBindVertexArray(debugVertArray_);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  debugEffect_->endDraw();*/
}