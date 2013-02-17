#ifndef OPENGL_EFFECT_H
#define OPENGL_EFFECT_H

#include <map>

#include "OpenGL.h"

#include "renderer/IEffect.h"

class OpenGLEffect : public IEffect {
  
public:
  
  virtual ~OpenGLEffect() { };
  
public:
  
  OpenGLEffect()
    : programId_(0)
    , lastSamplerBinding_(0) { };
  
public:
  
  void load(const std::string& filePath);
  
public:
  
  void beginDraw();
  
  void endDraw();
  
public:
  
  void setUniform(const Matrix3x3& uniformData, const char* uniformName) const;
  
  void setUniform(const Matrix4x4& uniformData, const char* uniformName) const;
  
  void setUniform(const Color3& uniformData, const char* uniformName) const;
  
  void setUniform(const Vector2& uniformData, const char* uniformName) const;
  
  void setUniform(const Vector3& uniformData, const char* uniformName) const;
  
  void setUniform(const Vector4& uniformData, const char* uniformName) const;
  
  void setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const;
  
  void setUniform(int uniformData, const char* uniformName) const;
  
  void setUniform(float uniformData, const char* uniformName) const;
  
public:
  
  void setTexture(unsigned int textureId, const char* uniformName);
  
  void setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction);
  
private:
  
  std::string getInternalUniformName(const std::string uniformName) const;
  
public:
  
  GLuint programId_;
  
private:

  unsigned int lastSamplerBinding_;
  std::map<GLuint, GLuint> samplerBindings_;
  
};


#endif
