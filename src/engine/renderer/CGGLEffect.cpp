#include "CGGLEffect.h"

#include "OpenGL.h"
#include <Cg/Cg.h>
#define CGGL_NO_OPENGL
#include <Cg/cgGL.h>

#include "io/Log.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "Color3.h"

void CGGLEffect::load(const std::string& filePath) {
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

void CGGLEffect::beginDraw() { 
  CGtechnique technique = cgGetFirstTechnique(effect_);
  CGpass pass = cgGetFirstPass(technique);
  cgSetPassState(pass);
}

void CGGLEffect::endDraw() {
  CGtechnique technique = cgGetFirstTechnique(effect_);
  CGpass pass = cgGetFirstPass(technique);
  cgResetPassState(pass);
}

void CGGLEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Vector4& uniformData, const char* uniformName) const { 
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter4fv(parameter, uniformData.valuePtr()); 
}

void CGGLEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(int uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter1d(parameter, uniformData);
}

void CGGLEffect::setUniform(float uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetParameter1f(parameter, uniformData);
}

void CGGLEffect::setTexture(unsigned int textureId, const char* uniformName) {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgGLSetTextureParameter(parameter, textureId);
}