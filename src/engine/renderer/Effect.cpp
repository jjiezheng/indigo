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
    cgGLSetManageTextureParameters(context_, GL_TRUE);
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
}

void Effect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter3fv(parameter, uniformData.valuePtr());
}

void Effect::setUniform(const Vector4& uniformData, const char* uniformName) const { 
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter4fv(parameter, uniformData.valuePtr()); 
}

void Effect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void Effect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void Effect::setUniform(int uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter1d(parameter, uniformData);
}

void Effect::setUniform(float uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter1f(parameter, uniformData);
}

void Effect::setTexture(unsigned int textureId, const char* uniformName) {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetTextureParameter(parameter, textureId);
}