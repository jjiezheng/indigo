#ifndef PS3GCMCGEFFECT_H
#define PS3GCMCGEFFECT_H

#include "IEffect.h"

#include <cell/gcm.h>

class PS3GCMCGEffect : public IEffect {

public:

  PS3GCMCGEffect()
    : vertexPositionIndex_(0) { }

public:

  virtual ~PS3GCMCGEffect() { };

public:

  void load(const std::string& filePath);

  void beginDraw();

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

  unsigned int vertexPositionIndex() const;

private:

  CGprogram vertexProgram_;
  CGprogram fragmentProgram_;

private:

  unsigned int vertexPositionIndex_;

  void* vertexProgramAddress_;
  unsigned int fragmentProgramOffset_;

};

inline unsigned int PS3GCMCGEffect::vertexPositionIndex() const {
  return vertexPositionIndex_;
}

#endif