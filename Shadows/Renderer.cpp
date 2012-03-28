#include "Renderer.h"

#include "ShaderCache.h"
#include "Shader.h"
#include "SceneNode.h"
#include "Light.h"
#include "Model.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"

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
  
  glClearColor(1.28, 0.28, 0.28, 1);

  render3d();
//  renderUI();
}

void Renderer::render3d() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  // render shadow map
  {
    Shader* shader = ShaderCache::instance()->addShader("vmvp.vsh", "fc.fsh");
    shader->use();
    
    float aspectRatio = MacPlatform::instance()->aspect_ratio();
    Matrix4x4 projection = Matrix4x4::perspective(45.0f, aspectRatio, 1.0f, 200.0f);    
    shader->set_uniform(projection, "projection");

    for (Light* light : shadowLights_) {
      shader->set_uniform(light->viewTransform(), "view");
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
    
    { // point lighting
      shader->set_uniform((int)pointLights_.size(), "numPointLights");
      
      const int MAX_LIGHTS = 6;
      float lightPositions[MAX_LIGHTS*3];
      int lightPositionIndex = 0;
      for (Light* light : pointLights_) {
        lightPositions[lightPositionIndex++] = light->position().x;
        lightPositions[lightPositionIndex++] = light->position().y;
        lightPositions[lightPositionIndex++] = light->position().z;
      }
      shader->set_uniform(lightPositions, lightPositionIndex, "lightPositions");
    }
    
    { // directional lighting
      shader->set_uniform((int)directionalLights_.size(), "numDirectionalLights");
      
      const int MAX_LIGHTS = 6;
      float lightDirections[MAX_LIGHTS*3];
      int lightDirectionIndex = 0;
      for (DirectionalLight* light : directionalLights_) {
        lightDirections[lightDirectionIndex++] = light->direction().x;
        lightDirections[lightDirectionIndex++] = light->direction().y;
        lightDirections[lightDirectionIndex++] = light->direction().z;
      }    
      shader->set_uniform(lightDirections, lightDirectionIndex, "lightDirections");
    }    
    
    float aspectRatio = MacPlatform::instance()->aspect_ratio();
    Matrix4x4 projection = Matrix4x4::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
    shader->set_uniform(projection, "projection");
    shadowMap_->bind(shader);
    
    for (Light* light : lights_) {
      if (light->castsShadows()) {
        Matrix4x4 offsetMatrix(0.5f, 0.0f, 0.0f, 0.5f,
                               0.0f, 0.5f, 0.0f, 0.5f,
                               0.0f, 0.0f, 0.5f, 0.5f,
                               0.0f, 0.0f, 0.0f, 1.0f);
        
        Matrix4x4 lightMatrix = offsetMatrix * projection * light->viewTransform();
        shader->set_uniform(lightMatrix, "lightMatrix");
        
        for (Camera* camera : cameras_) {
          shader->set_uniform(camera->viewTransform(), "view");
          renderScene(shader);
        }
      }
    }
  }
  
  shadowMap_->debugDraw();
  
  models_.clear();
  pointLights_.clear();
  directionalLights_.clear();
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
