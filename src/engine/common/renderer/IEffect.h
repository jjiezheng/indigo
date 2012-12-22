#ifndef IEFFECT_H
#define IEFFECT_H

#include <string>
#include <vector>

class Matrix4x4;
class Matrix3x3;
class Color3;
class Color4;
class Vector2;
class Vector3;
class Vector4;

enum SAMPLER_UV_ADDRESS_MODE {
  UV_ADDRESS_CLAMP,
  UV_ADDRESS_WRAP
};

enum SAMPLER_COMPARISON_FILTER {
  FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
  FILTER_MIN_MAG_MIP_POINT,
  FILTER_MIN_MAG_MIP_LINEAR
};

enum SAMPLER_COMPARISON_FUNC {
  COMPARISON_NONE,
  COMPARISON_LESS,
  COMPARISON_LESS_SHADOW,
  COMPARISON_GREATERTHAN_OR_EQUAL,
};


class IEffect {

public:

  static const char* SHADER_FULLSCREEN_TEXTURE;

public:

  virtual ~IEffect() { };

public:

  static IEffect* effectFromFile(const std::string& relativeFilePath);

public:

  void load(const std::string& filePath, const char** args);

  virtual void load(const std::string& filePath) = 0;

public:

  virtual void beginDraw() = 0;

  virtual void endDraw() = 0;

public:

  virtual void setUniform(const Matrix3x3& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Matrix4x4& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Color3& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector2& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector3& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector4& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const = 0;

  virtual void setUniform(int uniformData, const char* uniformName) const = 0;

  virtual void setUniform(float uniformData, const char* uniformName) const = 0;

public:

  virtual void setTexture(unsigned int textureId, const char* uniformName) = 0;
  
  virtual void setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) = 0;
};

#endif
