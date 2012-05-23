#include "RendererShadow.h"

#include "core/Size.h"

#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"
#include "ShaderAttribs.h"
#include "ShaderAttribs.h"
#include "IEffect.h"

#include "Texture.h"

#include "io/Log.h"
#include "io/Path.h"

void RendererShadow::init(const CSize &screenSize) {
{
    glGenFramebuffers(1, &frameBuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
    
    {
      glReadBuffer(GL_NONE);
      glDrawBuffer(GL_NONE);
    }
    
    {
      glGenRenderbuffers(1, &depthBuffer_);
      GLUtilities::checkForError();

      glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
      GLUtilities::checkForError();

      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenSize.width, screenSize.height);
      GLUtilities::checkForError();

      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);
      GLUtilities::checkForError();
    }
    
    GLUtilities::checkForError();
    GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
    
    {
      glGenTextures(1, &shadowTexture_);
      glGenTextures(1, &shadowTexture_);
      glBindTexture(GL_TEXTURE_2D, shadowTexture_);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, screenSize.width, screenSize.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
      
      float ones[] = {1, 1, 1, 1};
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, ones);
      
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTexture_, 0);
    }
    
    GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  
  {
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
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    
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
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_UV);

    std::string fullPath = Path::pathForFile("cgfx/diffuse_texture.cgfx");
    debugEffect_->load(fullPath.c_str());
         
  }
} 

void RendererShadow::render(IViewer* viewer, const World& world, SceneContext& sceneContext) {

  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
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
  glDisable(GL_CULL_FACE);
}

void RendererShadow::renderDebug(SceneContext& sceneContext) { 
  debugEffect_->beginDraw();

  debugEffect_->setTexture(shadowTexture_, "colorMapSampler");
  
  glBindVertexArray(debugVertArray_);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  debugEffect_->endDraw();
}