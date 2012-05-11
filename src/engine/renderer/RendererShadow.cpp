#include "RendererShadow.h"

#include "maths/Vector2.h"

#include "GLUtilities.h"

#include "World.h"
#include "Model.h"

#include "SceneContext.h"
#include "ShaderAttribs.h"

#include "ResourceCache.h"
#include "ShaderResource.h"
#include "ShaderAttribs.h"

void RendererShadow::init(const Vector2 &screenSize) {
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
        
    ShaderResource* resource = ResourceCache::instance()->load_shader("vt.vsh", "ft.fsh");
    debugShader_.compile_vertex(resource->vertex_source());
    debugShader_.compile_fragment(resource->fragment_source());
    debugShader_.bind_attribute(ATTRIB_VERTEX, "vertex");
    debugShader_.bind_attribute(ATTRIB_UV, "textureCoords");
    debugShader_.link();
    
    debugShader_.add_uniform("colorMap");
    
    Vector2 screenSize = MacPlatform::instance()->screen_size(); 
    Matrix4x4 projection = Matrix4x4::orthographic(0, screenSize.x, 0, screenSize.y, -1, 1000);  
    debugShader_.set_uniform(projection, "projection");
  }
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

void RendererShadow::renderDebug(SceneContext& sceneContext) {
  debugShader_.use();
  
  glActiveTexture(GL_TEXTURE0);
  debugShader_.set_uniform(0, "colorMap");
  
  glBindTexture(GL_TEXTURE_2D, shadowTexture_);  
  glBindVertexArray(debugVertArray_);
  glDrawArrays(GL_TRIANGLES, 0, 6);    
}