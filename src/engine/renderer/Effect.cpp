#include "Effect.h"

#include <CG/cg.h>
#include <CG/cgGL.h>

#include "io/Log.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"

void Effect::load(const std::string& filePath)
{
  context_ = cgCreateContext();
  cgGLRegisterStates(context_);
  CGeffect effect = cgCreateEffectFromFile(context_, filePath.c_str(), NULL);
  LOG(LOG_CHANNEL_SHADER, "opening cgfx file %s", filePath.c_str());

  if (!effect) {
    LOG(LOG_CHANNEL_SHADER, "Failed to open cgfx file %s", filePath.c_str());
  }

  technique_ = cgGetFirstTechnique(effect);
  if (cgValidateTechnique(technique_) == CG_FALSE) {
      LOG(LOG_CHANNEL_SHADER, "Technique %s did not validate. Skipping.", cgGetTechniqueName(technique_));
  }

  CGparameter parameter = cgGetFirstEffectParameter(effect);
  while(parameter)
  {
    const char* parameterName = cgGetParameterName(parameter);
    LOG(LOG_CHANNEL_SHADER, "%s", parameterName);
    parameter = cgGetNextParameter(parameter);
  }

  pass_ = cgGetFirstPass(technique_);
}

void Effect::beginDraw() { 
  cgSetPassState(pass_);
}

void Effect::endDraw() {
  cgResetPassState(pass_);
  cgGetNextPass(pass_);
}

void Effect::setUniform(const Color3& uniformData, const char* uniformName) const {

}

void Effect::setUniform(const Color4& uniformData, const char* uniformName) const {
  
}


void Effect::setUniform(const Vector3& uniformData, const char* uniformName) const {

}

void Effect::setUniform(const Vector4& uniformData, const char* uniformName) const {

}

void Effect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {

}

void Effect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  if (parameter) {
    cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
  }
}

void Effect::setUniform(int uniformData, const char* uniformName) const {

}

void Effect::setUniform(float uniformData, const char* uniformName) const {
 
}

void Effect::setUniform(float* uniformData, size_t size, const char* uniformName) const {

}