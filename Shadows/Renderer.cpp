#include "Renderer.h"

#include "ShaderCache.h"
#include "Shader.h"
#include "SceneNode.h"
#include "Light.h"
#include "Model.h"
#include "Camera.h"

#include "MacPlatform.h"

#include <iostream>
#include "ShaderAttribs.h"

#include "GLUtilities.h"

Renderer* Renderer::renderer() {
  Renderer* renderer = new Renderer();
  renderer->init();
  return renderer;
}

void Renderer::init() {
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
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenSize.x, screenSize.y);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowRenderDepthBuffer_);
    }
    
    GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);

    {
      glGenTextures(1, &shadowTexture_);
      glBindTexture(GL_TEXTURE_2D, shadowTexture_);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
      float ones[] = {1, 1, 1, 1};
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, ones);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screenSize.x, screenSize.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

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

void Renderer::render(SceneNode *sceneNode) {
  sceneNode->render(this);
  
  glClearColor(1, 0, 0, 1);

  render3d();
  renderUI();
}

void Renderer::render3d() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  // render shadow map   
  {
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFrameBuffer_);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glCullFace(GL_FRONT);
    
    for (Light* light : shadowLights_) {
      Shader* shader = ShaderCache::instance()->addShader("vmvp.vsh", "fc.fsh");
      shader->use();
      
      float aspectRatio = MacPlatform::instance()->aspect_ratio();
      glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
      shader->set_uniform(projection, "projection");
      shader->set_uniform(light->transform(), "view");
      
      glPolygonOffset(2.5f, 10.0f);
      glEnable(GL_POLYGON_OFFSET_FILL);
      renderScene(shader);
      glDisable(GL_POLYGON_OFFSET_FILL);
    }
    
    glCullFace(GL_BACK);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // render scene from active camera
  
  {
    Shader* shader = ShaderCache::instance()->addShader("vmvps.vsh", "fcs.fsh");
    shader->use();
    
    float aspectRatio = MacPlatform::instance()->aspect_ratio();
    glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
    shader->set_uniform(projection, "projection");
    
    {
      if (shadowLights_.size()) {
        glBindTexture(GL_TEXTURE_2D, shadowTexture_);
        shader->set_uniform(0, "shadowMapTexture");
        
        Light* light = shadowLights_[0];
        
        Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.5f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.5f, 0.0f,
                               0.5f, 0.5f, 0.5f, 1.0f);
        
        Matrix4x4 lightMatrix = offsetMatrix * projection * light->transform();
        shader->set_uniform(lightMatrix, "lightMatrix");
      }
    }
    
    {  
      for (Camera* camera : cameras_) {      
        shader->set_uniform(camera->transform(), "view");
        renderScene(shader);
      }
    }
  }
  
  //  // render debug shadow map
  //    
  //  {   
  //    glBindVertexArray(depthDebugVertArray_);
  //    
  //    Shader* shader = ShaderCache::instance()->addShader("vt.vsh", "ft.fsh");
  //    shader->use();
  //    shader->set_uniform(0, "colorMap");
  //    
  //    float aspectRatio = MacPlatform::instance()->aspect_ratio();
  //    glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
  //    shader->set_uniform(projection, "projection");
  //    
  //    glBindTexture(GL_TEXTURE_2D, shadowTexture_);
  //    glDrawArrays(GL_TRIANGLES, 0, 6);    
  //  }
  
  
  models_.clear();
  lights_.clear();
  shadowLights_.clear();
  cameras_.clear();
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);  
}

void Renderer::renderUI() {
  Shader* shader = ShaderCache::instance()->addShader("vmpt.vsh", "ft.fsh");
  shader->use();

  Vector2 screenSize = MacPlatform::instance()->screen_size();
  glm::mat4 projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
  shader->set_uniform(projection, "projection");

  for (SceneNode* node : uiNodes_) {
    node->render(shader);
  }
  
  uiNodes_.clear();
}

void Renderer::renderScene(Shader* shader) {
  for (Model* model : models_) {
    model->render(shader);
  }
}
