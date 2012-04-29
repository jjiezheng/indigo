#include "RendererShadow.h"

#include "Vector2.h"
#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"

void RendererShadow::init(const Vector2 &screenSize) {
  glGenFramebuffers(1, &frameBuffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
  
  {
    glReadBuffer(GL_NONE);
    glDrawBuffer(GL_NONE);
  }
  
  {
    glGenRenderbuffers(1, &depthBuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenSize.x, screenSize.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);
  }
  
  GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
  
  {
    glGenTextures(1, &shadowTexture_);
    glBindTexture(GL_TEXTURE_2D, shadowTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, screenSize.x, screenSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    
    float ones[] = {1, 1, 1, 1};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, ones);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTexture_, 0);
  }
  
  GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RendererShadow::render(const World& world, SceneContext& sceneContext) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
  glPolygonOffset(2.5f, 10.0f);
  glEnable(GL_POLYGON_OFFSET_FILL);
  
  glClear(GL_DEPTH_BUFFER_BIT);  
  glCullFace(GL_FRONT);
  
  std::vector<Light> lights = sceneContext.lights();
 
  for (const Light& light : lights) {  
    for (Model* node : world) {
      node->render(&light, sceneContext);
    }
  }
  
  glDisable(GL_POLYGON_OFFSET_FILL);
  glCullFace(GL_BACK);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  sceneContext.setShadowTexture(shadowTexture_);
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}