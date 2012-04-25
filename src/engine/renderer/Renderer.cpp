#include "Renderer.h"

#include "ShaderCache.h"
#include "Shader.h"
#include "ShaderAttribs.h"

#include "SceneNode.h"
#include "Camera.h"
#include "Light.h"

#include "Model.h"
#include "Mesh.h"
#include "Material.h"

#include "DirectionalLight.h"
#include "PointLight.h"

#include "MacPlatform.h"

#include <iostream>

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
//  shadowMap_->init();
}

void Renderer::render(SceneNode *sceneNode) {  
  glClearColor(1.28, 0.28, 0.28, 1);
  
  sceneNode->queueRender(this);
  //renderShadowMap();
  render3d();
//  renderDebug();
//  renderUI();
  
  meshes_.clear();
  pointLights_.clear();
  directionalLights_.clear();
  lights_.clear();
  shadowLights_.clear();
  cameras_.clear();
  debugNodes_.clear();
  uiNodes_.clear();
}

void Renderer::renderShadowMap() {    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
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

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}

void Renderer::render3d() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  
  const int MAX_LIGHTS = 6;
  float lightPositions[MAX_LIGHTS*3];
  int lightPositionIndex = 0;
  for (Light* light : pointLights_) {
    lightPositions[lightPositionIndex++] = light->position().x;
    lightPositions[lightPositionIndex++] = light->position().y;
    lightPositions[lightPositionIndex++] = light->position().z;
  }
  
  float lightDirections[MAX_LIGHTS*3];
  int lightDirectionIndex = 0;
  for (DirectionalLight* light : directionalLights_) {
    lightDirections[lightDirectionIndex++] = light->direction().x;
    lightDirections[lightDirectionIndex++] = light->direction().y;
    lightDirections[lightDirectionIndex++] = light->direction().z;
  }    
  
  float aspectRatio = MacPlatform::instance()->aspect_ratio();
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, aspectRatio, 1.0f, 200.0f);
  
  for (Mesh* mesh : meshes_) {
    Material* material = mesh->material();
    Shader* shader = material->shader();
    shader->use();
//    shadowMap_->bind(shader);
    
    shader->set_uniform(projection, "projection");
    
    { // materials
      shader->set_uniform(material->ambient(), "ambient");
      shader->set_uniform(material->diffuse(), "diffuse");
      shader->set_uniform(material->specular(), "specular");
    }
  
    { // point lighting
      shader->set_uniform((int)pointLights_.size(), "numPointLights");      
      shader->set_uniform(lightPositions, lightPositionIndex, "lightPositions");
    }

    { // directional lighting
      shader->set_uniform((int)directionalLights_.size(), "numDirectionalLights");      
      shader->set_uniform(lightDirections, lightDirectionIndex, "lightDirections");
    }    
    
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
          mesh->render(shader);
        }
      }
    }
  }
  
//  shadowMap_->debugDraw();

  glDisable(GL_BLEND);
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
}

void Renderer::renderScene(Shader* shader) {
  for (Mesh* mesh : meshes_) {
    mesh->render(shader);
  }
}

void Renderer::renderDebug() {
  glEnable(GL_DEPTH_TEST);

  Shader* shader = ShaderCache::instance()->addShader("vmvp.vsh", "fc.fsh");
  shader->use();
  
  float aspectRatio = MacPlatform::instance()->aspect_ratio();
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, aspectRatio, 1.0f, 200.0f);    
  shader->set_uniform(projection, "projection");
  
  for (Camera* camera : cameras_) {
    shader->set_uniform(camera->viewTransform(), "view");
  
    for (SceneNode* node : debugNodes_) {
      node->renderDebug(shader);
    }    
  }
  
  glDisable(GL_DEPTH_TEST);
}
