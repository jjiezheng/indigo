#ifndef SCENE_CONTEXT_H
#define SCENE_CONTEXT_H

#include "Light.h"

class SceneContext {
  
public:
  
  SceneContext() 
    : shadowTexture_(0) { }
  
public:
  
  void addLight(const Light& light);
  
  std::vector<Light> lights() const;
  
public:
  
  void setShadowTexture(GLuint shadowTexture);
  
  GLuint shadowTexture() const;
  
private:
  
  std::vector<Light> lights_;
  GLuint shadowTexture_;
  
};

inline void SceneContext::setShadowTexture(GLuint shadowTexture) {
  shadowTexture_ = shadowTexture;
}

inline GLuint SceneContext::shadowTexture() const {
  return shadowTexture_;
}

inline void SceneContext::addLight(const Light& light) {
  lights_.push_back(light);
}

inline std::vector<Light> SceneContext::lights() const {
  return lights_;
}

#endif
