#include "Effect.h"

#include "OpenGL.h"
#include <Cg/Cg.h>
#define CGGL_NO_OPENGL
#include <Cg/cgGL.h>

#include "io/Log.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"

CGcontext Effect::context_ = 0;

void Effect::load(const std::string& filePath) {
  if (!context_) {
    context_ = cgCreateContext();
    cgGLRegisterStates(context_);
  }

  effect_ = cgCreateEffectFromFile(context_, filePath.c_str(), NULL);
  LOG(LOG_CHANNEL_SHADER, "opening cgfx file %s", filePath.c_str());

  if (!effect_) {
    LOG(LOG_CHANNEL_SHADER, "Failed to open cgfx file %s", filePath.c_str());
  } 

  CGtechnique technique = cgGetFirstTechnique(effect_);
  if (cgValidateTechnique(technique) == CG_FALSE) {
      LOG(LOG_CHANNEL_SHADER, "Technique %s did not validate. Skipping.", cgGetTechniqueName(technique));
  }

  CGparameter parameter = cgGetFirstEffectParameter(effect_);
  while(parameter) {
    const char* parameterName = cgGetParameterName(parameter);
    parameters_[parameterName] = parameter;
    LOG(LOG_CHANNEL_SHADER, "Parameter: %s", parameterName);
    parameter = cgGetNextParameter(parameter);
  }
}

void Effect::beginDraw() { 
  CGtechnique technique = cgGetFirstTechnique(effect_);
  CGpass pass = cgGetFirstPass(technique);
  cgSetPassState(pass);
}

void Effect::endDraw() {
  CGtechnique technique = cgGetFirstTechnique(effect_);
  CGpass pass = cgGetFirstPass(technique);
  cgResetPassState(pass);
  cgGetNextPass(pass);
}

void Effect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return;
  cgGLSetParameter3fv((*it).second, uniformData.valuePtr());
}

void Effect::setUniform(const Vector4& uniformData, const char* uniformName) const { 
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return;
  cgGLSetParameter4fv((*it).second, uniformData.valuePtr()); 
}

void Effect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return;
  cgGLSetMatrixParameterfr((*it).second, uniformData.valuePtr());
}

void Effect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return;
  cgGLSetMatrixParameterfr((*it).second, uniformData.valuePtr());
}

void Effect::setUniform(int uniformData, const char* uniformName) const {
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return; 
  cgGLSetParameter1d((*it).second, uniformData);
}

void Effect::setUniform(float uniformData, const char* uniformName) const {
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return;
  cgGLSetParameter1f((*it).second, uniformData);
}

void Effect::setTexture(int textureIndex, unsigned int textureId, const char* uniformName) {
  std::map<std::string, CGparameter>::const_iterator it = parameters_.find(uniformName);
  if (it == parameters_.end()) return;

  glActiveTexture(GL_TEXTURE0 + textureIndex);
  glBindTexture(GL_TEXTURE_2D, textureId);

  cgGLSetTextureParameter((*it).second, textureId);
  //cgSetSamplerState((*it).second);
  cgGLEnableTextureParameter((*it).second);
}