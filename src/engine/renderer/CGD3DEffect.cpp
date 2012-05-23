#include "CGD3DEffect.h"

#include <Cg/Cg.h>
#include <CG/cgD3D11.h>

#include "io/Log.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "Color3.h"

void CGD3DEffect::load(const std::string& filePath) {
  if (!context_) {
    context_ = cgCreateContext();
    cgD3D11RegisterStates(context_);
    cgD3D11SetManageTextureParameters(context_, CG_TRUE);
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

void CGD3DEffect::beginDraw() { 
  CGtechnique technique = cgGetFirstTechnique(effect_);
  CGpass pass = cgGetFirstPass(technique);
  cgSetPassState(pass);
}

void CGD3DEffect::endDraw() {
  CGtechnique technique = cgGetFirstTechnique(effect_);
  CGpass pass = cgGetFirstPass(technique);
  cgResetPassState(pass);
}

void CGD3DEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}

void CGD3DEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}

void CGD3DEffect::setUniform(const Vector4& uniformData, const char* uniformName) const { 
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}

void CGD3DEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}

void CGD3DEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}

void CGD3DEffect::setUniform(int uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}

void CGD3DEffect::setUniform(float uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
 
}

void CGD3DEffect::setTexture(unsigned int textureId, const char* uniformName) {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  
}