#ifndef SCENE_CONTEXT_H
#define SCENE_CONTEXT_H

#include "Light.h"
#include "Color4.h"
#include "FogTypes.h"

class SceneContext {
  
public:
  
  SceneContext() 
    : shadowTexture_(0)
    , fogStart_(0)
    , fogEnd_(0)
    , fogFactor_(0) { }
  
public:
  
  void addLight(const Light& light);
  
  std::vector<Light> lights() const;
  
public:
    
  void setShadowTexture(GLuint shadowTexture);
  
  GLuint shadowTexture() const;
  
public:
  
  void setFog(FogType fogType, float fogFactor, float fogStart, float fogEnd, const Color4& fogColor);
  
  FogType fogType() const;
  float fogFactor() const;
  Color4 fogColor() const;
  float fogStart() const;
  float fogEnd() const;
  
private:
  
  std::vector<Light> lights_;
  GLuint shadowTexture_;
  float fogStart_;
  float fogEnd_;
  FogType fogType_;
  float fogFactor_;
  Color4 fogColor_;
  
};

inline void SceneContext::setFog(FogType fogType, float fogFactor, float fogStart, float fogEnd, const Color4 &fogColor) {
  fogType_ = fogType;
  fogFactor_ = fogFactor;
  fogStart_ = fogStart;
  fogEnd_ = fogEnd;
  fogColor_ = fogColor;
}

inline FogType SceneContext::fogType() const {
  return fogType_;
}

inline float SceneContext::fogFactor() const {
  return fogFactor_;
}

inline Color4 SceneContext::fogColor() const {
  return fogColor_;
}

inline float SceneContext::fogStart() const {
  return fogStart_;
}

inline float SceneContext::fogEnd() const {
  return fogEnd_;
}

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
