#include "Scene.h"

#include "Standard.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"
#include "ShaderCache.h"

void Scene::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
}

void Scene::render() {
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  for (SceneNode* child : children_) {
    child->render(0, 0, glm::mat4(1.0f));
  }
  
//  float lightPositions[lights_.size()];
//  
//  for (int i = 0; i < lights_.size(); i++) {
//    Light* light = lights_[i];
//    int startIndex = i * 3;
//    lightPositions[startIndex] = light->position().x;
//    lightPositions[startIndex+1] = light->position().y;
//    lightPositions[startIndex+2] = light->position().z;
//  }
//  
//  Shader* sceneShader = Shader::shader("mvpc.vsh", "color_light.fsh");
//  sceneShader->use();
//  sceneShader->set_uniform(lightPositions, lights_.size(), "lightPositions");
//  sceneShader->set_uniform((int)lights_.size(), "numLights");
//  
//  for (Camera* camera : cameras_) {
//    camera->render(sceneShader);
//    SceneNode::render(camera, sceneShader);
//
//    Shader* lightDebugShader = ShaderCache::instance()->addShader("mvp.vsh", "basic.fsh");
//    lightDebugShader->use();
//    for (Light* light : lights_) {
//      camera->render(lightDebugShader);
//      light->render(camera, lightDebugShader);
//    }    
//  }
}

void Scene::addLight(Light *light) {
  lights_.push_back(light);
}

void Scene::addCamera(Camera *camera) {
  cameras_.push_back(camera);
}
