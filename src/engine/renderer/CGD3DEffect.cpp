#include "CGD3DEffect.h"

#include <Cg/Cg.h>
#include <CG/cgD3D10.h>
#include <CG/cgD3D11.h>

#include "io/Log.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
#include "Color3.h"

#include "GraphicsInterface.h"

void CGD3DEffect::initCG(ID3D11Device* device) {
  context_ = cgCreateContext();

  cgSetErrorCallback(&IEffect::onError);
  cgD3D11SetDevice(context_, device);
  cgD3D11RegisterStates(context_);
  cgD3D11SetManageTextureParameters(context_, CG_TRUE);
}

void CGD3DEffect::load(const std::string& filePath) {
  const char* args[] = {"-DDIRECTX=1", 0};
  IEffect::load(filePath, args);
}

void CGD3DEffect::beginDraw() {
  cgSetPassState(pass_);
}

void CGD3DEffect::resetStates() {
  cgResetPassState(pass_);
}

void CGD3DEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGD3DEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetParameter2fv(parameter, uniformData.valuePtr());
}

void CGD3DEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGD3DEffect::setUniform(const Vector4& uniformData, const char* uniformName) const { 
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetParameter4fv(parameter, uniformData.valuePtr());
}

void CGD3DEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGD3DEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGD3DEffect::setUniform(int uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetParameter1d(parameter, uniformData);
}

void CGD3DEffect::setUniform(float uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  cgSetParameter1f(parameter, uniformData);
}

void CGD3DEffect::setTexture(unsigned int textureId, const char* uniformName) {
  CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
  if (!parameter) return;
  GraphicsInterface::setTexture(textureId, parameter);
}
