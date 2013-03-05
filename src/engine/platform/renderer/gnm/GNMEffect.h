#ifndef GNMEFFECT_H
#define GNMEFFECT_H

#include "IEffect.h"

#include <map>

class GNMEffect : public IEffect {

public:

  GNMEffect() { }

public:

  virtual ~GNMEffect() { };

public:

  void load(const std::string& filePath);

  void beginDraw();

	void commitBuffers();

  void endDraw();

  void setUniform(const Matrix3x3& uniformData, const char* uniformName) const;

  void setUniform(const Matrix4x4& uniformData, const char* uniformName) const;

  void setUniform(const Color3& uniformData, const char* uniformName) const;

  void setUniform(const Vector2& uniformData, const char* uniformName) const;

  void setUniform(const Vector3& uniformData, const char* uniformName) const;

  void setUniform(const Vector4& uniformData, const char* uniformName) const;
  
  void setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const;

  void setUniform(int uniformData, const char* uniformName) const;

  void setUniform(float uniformData, const char* uniformName) const;

  void setTexture(unsigned int textureId, const char* uniformName);

public:

  unsigned int vertexPositionIndex() const;

  unsigned int normalIndex() const;

  unsigned int uvIndex() const;

  void setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction);

};
#endif
