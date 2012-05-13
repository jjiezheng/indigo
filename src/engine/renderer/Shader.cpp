#include "Shader.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "io/Log.h"
#include "io/File.h"
#include "platform/Platform.h"

#include "Color4.h"
#include "ShaderAttribs.h"

GLuint Shader::compile_shader(const std::string& shader_source, GLint type) {
  GLuint shader = glCreateShader(type);
  const char* source = shader_source.c_str();
  glShaderSource(shader, 1, &source, 0);
  glCompileShader(shader);
  
  GLint logLength;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0) {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetShaderInfoLog(shader, logLength, &logLength, log);
    LOG("Shader compile log: %s", log);
    free(log);
  }

  GLint status = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  
  if (status == 0) {
    glDeleteShader(shader);
    LOG(LOG_CHANNEL_SHADER, "Error compiling shader");
  }

  return shader;
}

void Shader::compile_vertex(const std::string& vertex_source) {
  program = glCreateProgram();

  vertex = compile_shader(vertex_source, GL_VERTEX_SHADER);
}

void Shader::compile_fragment(const std::string& fragment_source) {
  fragment = compile_shader(fragment_source, GL_FRAGMENT_SHADER);
}

void Shader::bind_attribute(int attribute_id, const char* attribute_name) {
  LOG(LOG_CHANNEL_SHADER, "Binding attribute %s", attribute_name);
  glBindAttribLocation(program, attribute_id, attribute_name);
}

void Shader::load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  std::string vert_path = Platform::path_for_file(vertexShaderPath);
  std::string frag_path = Platform::path_for_file(fragmentShaderPath);

  std::string vertex = File(vert_path).data();
  std::string fragment = File(frag_path).data();
  
  compile_vertex(vertex);
  compile_fragment(fragment);
}

void Shader::link() {
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  
  GLint status;
  glLinkProgram(program);
#if defined(DEBUG)
  GLint logLength;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength > 0)
  {
    GLchar *log = (GLchar *)malloc(logLength);
    glGetProgramInfoLog(program, logLength, &logLength, log);
    LOG("Program link log:\n%s", log);
    free(log);
  }
#endif
  
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == 0) {
    LOG(LOG_CHANNEL_SHADER, "Error linking shader program");
  }
}

void Shader::use() const {
  glUseProgram(program);
}

void Shader::set_uniform(const Color3& uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform3fv(uniform_id, 1, uniform_data.valuePtr());
  }    
}

void Shader::set_uniform(const Color4& uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform4fv(uniform_id, 1, uniform_data.valuePtr());
  }    
}


void Shader::set_uniform(const Vector3& uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform3fv(uniform_id, 1, uniform_data.valuePtr());
  }    
}

void Shader::set_uniform(const Matrix3x3& uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniformMatrix3fv(uniform_id, 1, GL_TRUE, uniform_data.valuePtr());
  }
}

void Shader::set_uniform(const Matrix4x4& uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniformMatrix4fv(uniform_id, 1, GL_TRUE, uniform_data.valuePtr());
  }
}

void Shader::add_uniform(const char* uniform_name) {
  LOG(LOG_CHANNEL_SHADER, "Adding uniform %s", uniform_name);
  GLint uniform_id = glGetUniformLocation(program, uniform_name);
  uniforms.insert(std::make_pair(uniform_name, uniform_id));
}

void Shader::set_uniform(int uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform1i(uniform_id, uniform_data);
  }  
}

void Shader::set_uniform(float uniform_data, const char* uniform_name) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniform_name);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform1f(uniform_id, uniform_data);
  }  
}

void Shader::set_uniform(float* uniform_data, size_t size, const char* uniform_name) const {
  GLint uniform_id = glGetUniformLocation(program, uniform_name);
  glUniform3fv(uniform_id, (GLsizei)size, uniform_data);
}