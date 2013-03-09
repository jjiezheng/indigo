#include "OpenGLEffect.h"

#include "GLUtilities.h"

#include "io/File.h"
#include "maths/Matrix3x3.h"
#include "maths/Matrix4x4.h"
#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"

#include "renderer/GraphicsInterface.h"
#include "OpenGL32GraphicsInterface.h"
#include "renderer/ShaderSemantics.h"
#include "renderer/Color3.h"

#include <stdio.h>

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
  
  OpenGL32GraphicsInterface* graphicsInterface = (OpenGL32GraphicsInterface*)GraphicsInterface::rawInterface();
  std::string glslVersion = graphicsInterface->glslVersion();
  
  {
    std::string fullVertexShaderFilePath = filePath + ".glsl." + glslVersion + ".vertex";
    
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
    std::string fullfragmentShaderFilePath = filePath + ".glsl." + glslVersion + ".fragment";
    
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
  glBindAttribLocation(programId_, TEXCOORD1, "TEXCOORD1");
  glBindAttribLocation(programId_, TEXCOORD2, "TEXCOORD2");

  glBindFragDataLocation(programId_, 0, "cg_FragColor");

  glBindFragDataLocation(programId_, 1, "cg_FragData1");
  glBindFragDataLocation(programId_, 2, "cg_FragData2");
  glBindFragDataLocation(programId_, 3, "cg_FragData3");
  glBindFragDataLocation(programId_, 4, "cg_FragData4");

  glLinkProgram(programId_);
  GLUtilities::checkForError();
}

void OpenGLEffect::beginDraw() {
  glUseProgram(programId_);
  GLUtilities::checkForError();
}

void OpenGLEffect::commitBuffers() {
  
}

void OpenGLEffect::endDraw() {
#undef GPU_TRACE
#ifdef GPU_TRACE
  GLint maxTextureUnits = 0;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
  for (int i = 0; i < maxTextureUnits; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
#endif
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
 std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1 && uniformDataSize > 0) {
    glUniform4fv(uniformLocation, uniformDataSize, uniformData[0].valuePtr());
    GLUtilities::checkForError();
  } 
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
  GraphicsInterface::beginPerformanceEvent(std::string("Texture ") + uniformName);
  std::string internalUnformName = getInternalUniformName(uniformName);
  GLint uniformLocation = glGetUniformLocation(programId_, internalUnformName.c_str());
  if (uniformLocation > -1) {
    if (samplerBindings_.find(uniformLocation) == samplerBindings_.end()) {
      samplerBindings_[uniformLocation] = lastSamplerBinding_++;
    }
    GLint samplerId = samplerBindings_[uniformLocation];
    glActiveTexture(GL_TEXTURE0 + samplerId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(uniformLocation, samplerId);
    GLUtilities::checkForError();
  }
  GraphicsInterface::endPerformanceEvent();
}

void OpenGLEffect::setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) {

  glUseProgram(programId_);

  GLuint samplerId = 0;

  for (std::map<GLuint, GLuint>::const_iterator i = samplerBindings_.begin(); i != samplerBindings_.end(); ++i) {
    if ((*i).second == samplerSlot) {
      samplerId = (*i).first;
      break;
    }
  }

  GLint glAddressMode = GL_REPEAT;

  if (addressMode == UV_ADDRESS_CLAMP) {
    glAddressMode = GL_CLAMP_TO_EDGE;
  }

  //glSamplerParameteri(samplerId, GL_TEXTURE_WRAP_S, glAddressMode);
  //glSamplerParameteri(samplerId, GL_TEXTURE_WRAP_T, glAddressMode);

  GLUtilities::checkForError();
}

std::string OpenGLEffect::getInternalUniformName(const std::string uniformName) const {
  std::string internalName = std::string("_") + uniformName;
  return internalName;
}
