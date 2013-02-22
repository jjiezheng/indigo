#ifndef PS3GCMCGEFFECT_H
#define PS3GCMCGEFFECT_H

#include "IEffect.h"

#include <cell/gcm.h>
#include <map>

struct GCMSamplerState {
  uint8_t addressU;
  uint8_t addressV;
  uint8_t addressW;

  uint8_t minFilter;
  uint8_t magFilter;

  uint8_t comparisonFunc;
};


class PS3GCMCGEffect : public IEffect {

public:

  PS3GCMCGEffect()
    : vertexPositionIndex_(0)
    , normalIndex_(0)
    , uvIndex_(0) { }

public:

  virtual ~PS3GCMCGEffect() { };

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


private:

  CGprogram vertexProgram_;
  CGprogram fragmentProgram_;

private:

  unsigned int vertexPositionIndex_;
  unsigned int normalIndex_;
  unsigned int uvIndex_;

  void* vertexProgramAddress_;
  unsigned int fragmentProgramOffset_;

private:

  std::map<unsigned int, GCMSamplerState> samplerStates_;

};

inline unsigned int PS3GCMCGEffect::vertexPositionIndex() const {
  return vertexPositionIndex_;
}

inline unsigned int PS3GCMCGEffect::normalIndex() const {
  return normalIndex_;
}

inline unsigned int PS3GCMCGEffect::uvIndex() const {
  return uvIndex_;
}

#endif
