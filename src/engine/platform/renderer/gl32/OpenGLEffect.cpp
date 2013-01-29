#include "OpenGLEffect.h"

#include "GLUtilities.h"

#include "io/File.h"

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
  
  glLinkProgram(programId_);
  GLUtilities::checkForError();
  printLog("", programId_);
}

void OpenGLEffect::beginDraw() {
  glUseProgram(programId_);
}

void OpenGLEffect::endDraw() {
  
}

void OpenGLEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(int uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setUniform(float uniformData, const char* uniformName) const {
  
}

void OpenGLEffect::setTexture(unsigned int textureId, const char* uniformName) {
  
}

void OpenGLEffect::setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) {
  
}
