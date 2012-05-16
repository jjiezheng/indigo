#ifndef CGSHADER_H
#define CGSHADER_H

#include "IShader.h"

#include <Cg/Cg.h>

class CGShader : public IShader {
  
public:
  
  void load(const char* vertexShaderPath, const char* fragmentShaderPath);
  
  void link();
  
  void use() const;
  
  void bindAttribute(int attributeId, const char* attribute_name);
  
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

public:

  void setTexture(int textureIndex, unsigned int textureId, const char* uniformName);
  
private:
  
  CGcontext context_;
  CGprogram program_;
  
};

#endif
