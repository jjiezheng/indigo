#include "ShadowMap.h"

#include "core/Standard.h"
#include "platform/MacPlatform.h"

#include "OpenGL.h"
#include "GLUtilities.h"
#include "ShaderAttribs.h"

#include "Shader.h"
#include "ShaderCache.h"

#include "Light.h"

void ShadowMap::init() {
  {
    Vector2 screenSize = MacPlatform::instance()->screen_size();
    
    glGenFramebuffers(1, &shadowFrameBuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFrameBuffer_);
    
    {
      glReadBuffer(GL_NONE);
      glDrawBuffer(GL_NONE);
    }
    
    {
      glGenRenderbuffers(1, &shadowRenderDepthBuffer_);
      glBindRenderbuffer(GL_RENDERBUFFER, shadowRenderDepthBuffer_);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLint)screenSize.x, (GLint)screenSize.y);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowRenderDepthBuffer_);
    }
    
    GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
    
    {
      glGenTextures(1, &shadowTexture_);
      glBindTexture(GL_TEXTURE_2D, shadowTexture_);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, (GLint)screenSize.x, (GLint)screenSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
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
    
    glGenVertexArrays(1, &depthDebugVertArray_);
    glBindVertexArray(depthDebugVertArray_);
    
    glGenBuffers(1, &depthDebugVertBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, depthDebugVertBuffer_);
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
    
    glGenBuffers(1, &depthDebugUVBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, depthDebugUVBuffer_);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_UV);
  }
}


void ShadowMap::begin(Light* light) {
  glBindFramebuffer(GL_FRAMEBUFFER, shadowFrameBuffer_);
  glPolygonOffset(2.5f, 10.0f);
  glEnable(GL_POLYGON_OFFSET_FILL);
  
  glClear(GL_DEPTH_BUFFER_BIT);  
  glCullFace(GL_FRONT);
  
}

void ShadowMap::end() {
  glDisable(GL_POLYGON_OFFSET_FILL);
  glCullFace(GL_BACK);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::debugDraw() {
  glBindVertexArray(depthDebugVertArray_);
  
  Shader* shader = ShaderCache::instance()->addShader("vt.vsh", "ft.fsh");
  shader->use();
  shader->set_uniform(0, "colorMap");
  
  Vector2 screenSize = MacPlatform::instance()->screen_size(); 
  Matrix4x4 projection = Matrix4x4::orthographic(0, screenSize.x, 0, screenSize.y, -1, 1000);  
  shader->set_uniform(projection, "projection");
  
  glBindTexture(GL_TEXTURE_2D, shadowTexture_);
  glDrawArrays(GL_TRIANGLES, 0, 6);    
}

void ShadowMap::bind(Shader* shader) {
  glBindTexture(GL_TEXTURE_2D, shadowTexture_);
  shader->set_uniform(0, "shadowMapTexture");
}
