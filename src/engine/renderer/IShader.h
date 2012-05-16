#ifndef ISHADER_H
#define ISHADER_H

class Light;
class Matrix4x4;
class Matrix3x3;
class Color3;
class Color4;
class Vector2;
class Vector3;
class Vector4;

class IShader {

public:
  
  virtual void load(const char* vertexShaderPath, const char* fragmentShaderPath) = 0;
  
  virtual void link() = 0;
  
  virtual void use() const = 0;
  
  virtual void bindAttribute(int attributeId, const char* attribute_name) = 0;
  
public:
  
  virtual void setUniform(const Matrix3x3& uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(const Matrix4x4& uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(const Color3& uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(const Color4& uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(const Vector3& uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(const Vector4& uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(int uniformData, const char* uniformName) const = 0;
  
  virtual void setUniform(float uniformData, const char* uniformName) const = 0;
  
  virtual void addUniform(const char* uniformName) = 0;
  
  virtual void setUniform(float* uniformData, size_t size, const char* uniformName) const = 0;

public:

  virtual void setTexture(int textureIndex, unsigned int textureId, const char* uniformName) = 0; 

  
};

#endif
