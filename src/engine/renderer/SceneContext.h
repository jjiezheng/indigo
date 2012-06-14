#ifndef SCENE_CONTEXT_H
#define SCENE_CONTEXT_H

#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"
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
  
  void addDirectionalLight(const DirectionalLight& light);
  
  std::vector<DirectionalLight> directionalLights() const;

public:

  void addPointLight(const PointLight& light);

  std::vector<PointLight> pointLights() const;

  
public:
    
  void setShadowTexture(unsigned int shadowTexture);
  
  unsigned int shadowTexture() const;
  
public:
  
  Color3 backgroundColor() const;
  
  void setBackgroundColor(const Color3& color);
  
public:
  
  void setFog(FogType fogType, float fogFactor, float fogStart, float fogEnd, const Color4& fogColor);
  
  FogType fogType() const;
  float fogFactor() const;
  Color4 fogColor() const;
  float fogStart() const;
  float fogEnd() const;
  
private:
  
  std::vector<DirectionalLight> directionalLights_;
  std::vector<PointLight> pointLights_;
  
  unsigned int shadowTexture_;
  float fogStart_;
  float fogEnd_;
  FogType fogType_;
  float fogFactor_;
  Color4 fogColor_;
  Color3 backgroundColor_;
    
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

inline void SceneContext::setShadowTexture(unsigned int shadowTexture) {
  shadowTexture_ = shadowTexture;
}

inline unsigned int SceneContext::shadowTexture() const {
  return shadowTexture_;
}

inline void SceneContext::addDirectionalLight(const DirectionalLight& light) {
  directionalLights_.push_back(light);
}

inline std::vector<DirectionalLight> SceneContext::directionalLights() const {
  return directionalLights_;
}

inline void SceneContext::addPointLight(const PointLight& light) {
  pointLights_.push_back(light);
}

inline std::vector<PointLight> SceneContext::pointLights() const {
  return pointLights_;
}

inline Color3 SceneContext::backgroundColor() const {
  return backgroundColor_;
}

inline void SceneContext::setBackgroundColor(const Color3 &backgroundColor) {
  backgroundColor_ = backgroundColor;
}

#endif
