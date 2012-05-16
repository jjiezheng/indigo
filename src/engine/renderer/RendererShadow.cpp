#include "RendererShadow.h"

#include "core/Size.h"

#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"
#include "ShaderAttribs.h"
#include "ShaderAttribs.h"

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
      glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenSize.width, screenSize.height);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);
    }
    
    GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
    
    {
      glGenTextures(1, &shadowTexture_);
      glBindTexture(GL_TEXTURE_2D, shadowTexture_);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, screenSize.width, screenSize.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
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
        
    debugShader_.load("glsl/vt.vsh", "glsl/ft.fsh");
    debugShader_.bindAttribute(ATTRIB_VERTEX, "vertex");
    debugShader_.bindAttribute(ATTRIB_UV, "textureCoords");
    debugShader_.link();
    
    debugShader_.addUniform("colorMap");
    
    Matrix4x4 projection = Matrix4x4::orthographic(0, Window::screenWidth(), 0, Window::screenHeight(), -1, 1000);  
    debugShader_.setUniform(projection, "projection");
  }
}

void RendererShadow::render(const World& world, SceneContext& sceneContext) {
  /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
  glPolygonOffset(2.5f, 10.0f);
  glEnable(GL_POLYGON_OFFSET_FILL);
  
  glClear(GL_DEPTH_BUFFER_BIT);  
  glCullFace(GL_FRONT);
  
  std::vector<Light> lights = sceneContext.lights();
  std::vector<Light>::iterator lit = lights.begin();
  for (; lit != lights.end(); ++lit) {
    std::vector<Model>::const_iterator mit = world.begin();
    for (; mit != world.end(); ++mit) {
      (*mit).render(&(*lit), sceneContext);
    }
  }
  
  glDisable(GL_POLYGON_OFFSET_FILL);
  glCullFace(GL_BACK);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  sceneContext.setShadowTexture(shadowTexture_);
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glUseProgram(0);*/ 
}

void RendererShadow::renderDebug(SceneContext& sceneContext) {
  debugShader_.use();
  
  glActiveTexture(GL_TEXTURE0);
  debugShader_.setUniform(0, "colorMap");
  
  glBindTexture(GL_TEXTURE_2D, shadowTexture_);  
  glBindVertexArray(debugVertArray_);
  glDrawArrays(GL_TRIANGLES, 0, 6);    

  glUseProgram(0);
}