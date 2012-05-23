#ifndef CGD3DEFFECT_H
#define CGD3DEFFECT_H

#include "IEffect.h"

class CGD3DEffect : public IEffect {

public:

  void load(const std::string& filePath);

  void beginDraw();

  void endDraw();

public:

  void setUniform(const Matrix3x3& uniformData, const char* uniformName) const;

  void setUniform(const Matrix4x4& uniformData, const char* uniformName) const;

  void setUniform(const Color3& uniformData, const char* uniformName) const;

  void setUniform(const Vector3& uniformData, const char* uniformName) const;

  void setUniform(const Vector4& uniformData, const char* uniformName) const;

  void setUniform(int uniformData, const char* uniformName) const;

  void setUniform(float uniformData, const char* uniformName) const;

  void setTexture(unsigned int textureId, const char* uniformName);
  
};

#endif
