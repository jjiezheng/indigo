#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <CG/cg.h>

class Matrix4x4;
class Matrix3x3;
class Color3;
class Color4;
class Vector2;
class Vector3;
class Vector4;

class Effect {

public:

  void load(const std::string& filePath);

  void beginDraw();

  void endDraw();

public:

  void setUniform(const Matrix3x3& uniformData, const char* uniformName) const;

  void setUniform(const Matrix4x4& uniformData, const char* uniformName) const;

  void setUniform(const Color3& uniformData, const char* uniformName) const;

  void setUniform(const Color4& uniformData, const char* uniformName) const;

  void setUniform(const Vector3& uniformData, const char* uniformName) const;

  void setUniform(const Vector4& uniformData, const char* uniformName) const;

  void setUniform(int uniformData, const char* uniformName) const;

  void setUniform(float uniformData, const char* uniformName) const;

  void addUniform(const char* uniformName);

  void setUniform(float* uniformData, size_t size, const char* uniformName) const;

private:

  CGcontext context_;
  CGtechnique technique_; 
  CGpass pass_;
  CGprogram program_;
};


#endif
