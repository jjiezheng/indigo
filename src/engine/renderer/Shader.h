#ifndef CubeFX_Shader_h
#define CubeFX_Shader_h

#include <string>

#include "core/Standard.h"

#include "OpenGL.h"

class Light;
class ShaderResource;
class Matrix4x4;
class Matrix3x3;
class Color4;

class Shader {
  
public:
  
  static 
  Shader* shader(const ShaderResource* shader_resource);
  
public:
  
  void compile_vertex(const std::string& vertex_source);
  
  void compile_fragment(const std::string& fragment_source);
  
public:
  
  void link();
  
  void use() const;
  
  void bind_attribute(int attribute_id, const char* attribute_name);
  
public:
  
  void set_uniform(const MAT3& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const MAT4& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const Matrix3x3& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const Matrix4x4& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const Color3& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const Color4& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const VEC3& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const glm::vec4& uniform_data, const char* uniform_name) const;
  
  void set_uniform(int uniform_data, const char* uniform_name) const;
  
  void set_uniform(float uniform_data, const char* uniform_name) const;
  
  void add_uniform(const char* uniform_name);
  
  void set_uniform(float* uniform_data, size_t size, const char* uniform_name) const;
    
private:
  
  GLuint compile_shader(const std::string& shader_source, GLint type);
  
  GLuint program;
  GLuint vertex;
  GLuint fragment;
  
  std::map<std::string, GLint> uniforms;
  
};

#endif
