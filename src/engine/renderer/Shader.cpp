#include "Shader.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"

#include "io/Log.h"
#include "io/File.h"
#include "io/Path.h"

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

void Shader::bindAttribute(int attributeId, const char* attribute_name) { 
}

void Shader::load(const char* vertexShaderPath, const char* fragmentShaderPath) {
  std::string vert_path = Path::pathForFile(vertexShaderPath);
  std::string frag_path = Path::pathForFile(fragmentShaderPath);

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

void Shader::setUniform(const Color3& uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform3fv(uniform_id, 1, uniformData.valuePtr());
  }    
}

void Shader::setUniform(const Color4& uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform4fv(uniform_id, 1, uniformData.valuePtr());
  }    
}


void Shader::setUniform(const Vector3& uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform3fv(uniform_id, 1, uniformData.valuePtr());
  }    
}

void Shader::setUniform(const Vector4& uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform4fv(uniform_id, 1, uniformData.valuePtr());
  }    
}

void Shader::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniformMatrix3fv(uniform_id, 1, GL_TRUE, uniformData.valuePtr());
  }
}

void Shader::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniformMatrix4fv(uniform_id, 1, GL_TRUE, uniformData.valuePtr());
  }
}

void Shader::addUniform(const char* uniformName) {
  LOG(LOG_CHANNEL_SHADER, "Adding uniform %s", uniformName);
  GLint uniform_id = glGetUniformLocation(program, uniformName);
  uniforms.insert(std::make_pair(uniformName, uniform_id));
}

void Shader::setUniform(int uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform1i(uniform_id, uniformData);
  }  
}

void Shader::setUniform(float uniformData, const char* uniformName) const {
  std::map<std::string, GLint>::const_iterator uniformIt = uniforms.find(uniformName);
  if (uniformIt != uniforms.end()) {
    GLint uniform_id = (*uniformIt).second;
    glUniform1f(uniform_id, uniformData);
  }  
}

void Shader::setUniform(float* uniformData, size_t size, const char* uniformName) const {
  GLint uniform_id = glGetUniformLocation(program, uniformName);
  glUniform3fv(uniform_id, (GLsizei)size, uniformData);
}