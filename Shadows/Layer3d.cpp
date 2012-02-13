#include "Layer3d.h"

#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include "ShaderCache.h"

void Layer3d::init() {
}

void Layer3d::addLight(Light *light) {
  lights_.push_back(light);
}

void Layer3d::addCamera(Camera *camera) {
  cameras_.push_back(camera);
}

void Layer3d::render(Camera *camera, Shader *shader, const glm::mat4 &transform) const {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  unsigned long lightPositionsSize = lights_.size() * 3;
  float lightPositions[lightPositionsSize];
  
  for (int i = 0; i < lights_.size(); i++) {
    Light* light = lights_[i];
    int startIndex = i * 3;
    lightPositions[startIndex] = light->position().x;
    lightPositions[startIndex+1] = light->position().y;
    lightPositions[startIndex+2] = light->position().z;
  }
  
  Shader* sceneShader = Shader::shader("vmvpc.vsh", "fcl.fsh");
  sceneShader->use();
  sceneShader->set_uniform(lightPositions, lightPositionsSize, "lightPositions");
  sceneShader->set_uniform((int)lights_.size(), "numLights");
  
  for (Camera* camera : cameras_) {
    camera->render(sceneShader);
    SceneNode::render(camera, sceneShader, transform);
    
    Shader* lightDebugShader = ShaderCache::instance()->addShader("vmvp.vsh", "fc.fsh");
    lightDebugShader->use();
    for (Light* light : lights_) {
      camera->render(lightDebugShader);
      light->render(camera, lightDebugShader);
    }    
  }
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

}