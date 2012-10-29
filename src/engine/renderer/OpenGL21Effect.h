#ifndef OPENGL21_EFFECT_H
#define OPENGL21_EFFECT_H

#include "IEffect.h"

class OpenGL21Effect : public IEffect {
  
public:
  
  void load(const std::string& filePath, const char** args);
  
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
  
};

#endif
