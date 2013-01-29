#include "OpenGLEffect.h"

#include "GLUtilities.h"

#include "io/File.h"
#include "maths/Matrix3x3.h"
#include "maths/Matrix4x4.h"
#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"

#include "ShaderSemantics.h"
#include "Color3.h"

void printLog(const std::string& filePath, GLuint obj) {
	int infologLength = 0;
	const int maxLength = 256;
  
	char infoLog[maxLength];
  
	if (glIsShader(obj)) {
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
  }
	else {
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
  }
  
	if (infologLength > 0) {
		printf("%s\n%s\n", filePath.c_str(), infoLog);
  }
}

void OpenGLEffect::load(const std::string& filePath) {
  programId_ = glCreateProgram();
  
  {
    std::string fullVertexShaderFilePath = filePath + ".gl32.vertex";
    
    File shaderFile;
    shaderFile.open(fullVertexShaderFilePath);
    
    GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
    
    const GLchar* shaderSource = shaderFile.data();
    GLint shaderSourceLength = shaderFile.size();
    
    glShaderSource(shaderId, 1, &shaderSource, &shaderSourceLength);
    GLUtilities::checkForError();
    
    glCompileShader(shaderId);
    GLUtilities::checkForError();
    printLog(fullVertexShaderFilePath, shaderId);
    
    glAttachShader(programId_, shaderId);
    GLUtilities::checkForError();
  }

  {
    std::string fullfragmentShaderFilePath = filePath + ".gl32.fragment";
    
    File shaderFile;
    shaderFile.open(fullfragmentShaderFilePath);
    
    GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    
    const GLchar* shaderSource = shaderFile.data();
    GLint shaderSourceLength = shaderFile.size();
    
    glShaderSource(shaderId, 1, &shaderSource, &shaderSourceLength);
    GLUtilities::checkForError();
    
    glCompileShader(shaderId);
    GLUtilities::checkForError();
    printLog(fullfragmentShaderFilePath, shaderId);
    
    glAttachShader(programId_, shaderId);
    GLUtilities::checkForError();
  }
  
  glBindAttribLocation(programId_, NORMAL, "NORMAL");
  glBindAttribLocation(programId_, TEXCOORD0, "TEXCOORD0");

  glLinkProgram(programId_);
  GLUtilities::checkForError();
}

void OpenGLEffect::beginDraw() {
  glUseProgram(programId_);
}

void OpenGLEffect::endDraw() {
  
}

void OpenGLEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform3fv(uniformLocation, 4, uniformData.valuePtr());
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform4fv(uniformLocation, 4, uniformData.valuePtr());
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform3fv(uniformLocation, 1, uniformData.valuePtr());
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform2fv(uniformLocation, 1, uniformData.valuePtr());
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform3fv(uniformLocation, 1, uniformData.valuePtr());
    GLUtilities::checkForError();
  }  
}

void OpenGLEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform4fv(uniformLocation, 1, uniformData.valuePtr());
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(int uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform1i(uniformLocation, uniformData);
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setUniform(float uniformData, const char* uniformName) const {
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    glUniform1f(uniformLocation, uniformData);
    GLUtilities::checkForError();
  }
}

void OpenGLEffect::setTexture(unsigned int textureId, const char* uniformName) {
  
  
}

void OpenGLEffect::setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) {
  
}

std::string OpenGLEffect::getInternalUniformName(const std::string uniformName) const {
  std::string internalName = std::string("_") + uniformName;
  return internalName;
}
