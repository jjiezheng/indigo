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
#include "ShadowMap.h"

Renderer::Renderer() 
  : shadowMap_(new ShadowMap) {
  
}

Renderer* Renderer::renderer() {
  Renderer* renderer = new Renderer();
  renderer->init();
  return renderer;
}

void Renderer::init() {
  shadowMap_->init();
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
    Shader* shader = ShaderCache::instance()->addShader("vmvp.vsh", "fc.fsh");
    shader->use();
    
    float aspectRatio = MacPlatform::instance()->aspect_ratio();
    glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 1.0f, 400.0f);
    shader->set_uniform(projection, "projection");
    
    for (Light* light : shadowLights_) {
      shader->set_uniform(light->transform(), "view");
      shadowMap_->begin(light);
      renderScene(shader);  
      shadowMap_->end();
    }
  }
    
  // render scene from active camera  
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* shader = ShaderCache::instance()->addShader("vmvpcs.vsh", "fcls.fsh");
    shader->use();
    
    shader->set_uniform((int)shadowLights_.size(), "numLights");
    
    float lightPositions[shadowLights_.size()*3];
    int lightPositionIndex = 0;
    for (Light* light : shadowLights_) {
      lightPositions[lightPositionIndex++] = light->position().x;
      lightPositions[lightPositionIndex++] = light->position().y;
      lightPositions[lightPositionIndex++] = light->position().z;
    }
    shader->set_uniform(lightPositions, lightPositionIndex, "lightPositions");
    
    float aspectRatio = MacPlatform::instance()->aspect_ratio();
    glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
    shader->set_uniform(projection, "projection");
    
    for (Light* light : shadowLights_) {
      if (shadowLights_.size()) {
        shadowMap_->bind(shader);
        
        Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.5f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.5f, 0.0f,
                               0.5f, 0.5f, 0.5f, 1.0f);
        
        Matrix4x4 lightMatrix = offsetMatrix * projection * light->transform();
        shader->set_uniform(lightMatrix, "lightMatrix");
        
        for (Camera* camera : cameras_) {      
          shader->set_uniform(camera->transform(), "view");
          renderScene(shader);
        }
      }
    }
  }
  
  shadowMap_->debugDraw();
  
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
