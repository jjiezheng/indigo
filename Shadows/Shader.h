#ifndef CubeFX_Shader_h
#define CubeFX_Shader_h

#include <string>

#include "Standard.h"

class Light;
class ShaderResource;

class Shader {
  
public:
  
  static Shader* shader(const char* vertexPath, const char* fragmentPath);
  
  static Shader* shader(const ShaderResource* shader_resource);
  
  void compile_vertex(const std::string& vertex_source);
  
  void compile_fragment(const std::string& fragment_source);
  
  void link();
  
  void use() const;
  
  void bind_attribute(INT attribute_id, const char* attribute_name);
  
  void set_uniform(const MAT3& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const MAT4& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const VEC3& uniform_data, const char* uniform_name) const;
  
  void set_uniform(const glm::vec4& uniform_data, const char* uniform_name) const;
  
  void set_uniform(INT uniform_data, const char* uniform_name) const;
  
  void add_uniform(const char* uniform_name);
  
  void set_uniform(float* uniform_data, size_t size, const char* uniform_name) const;
  
    
private:
  
  Shader();
  
  GLuint compile_shader(const std::string& shader_source, GLint type);
  
  GLuint program;
  GLuint vertex;
  GLuint fragment;
  
  std::map<std::string, GLint> uniforms;
  
};

#endif
