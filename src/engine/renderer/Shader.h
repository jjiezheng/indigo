#ifndef CubeFX_Shader_h
#define CubeFX_Shader_h

#include <string>

#include "core/Standard.h"

#include "OpenGL.h"
#include "IShader.h"

class Shader : public IShader {
      
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
  
  void compile_vertex(const std::string& vertex_source);
  
  void compile_fragment(const std::string& fragment_source);
  
  GLuint compile_shader(const std::string& shader_source, GLint type);
  
  GLuint program;
  GLuint vertex;
  GLuint fragment;
  
  std::map<std::string, GLint> uniforms;
  
};

#endif
