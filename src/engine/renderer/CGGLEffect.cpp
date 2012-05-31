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
#include "GraphicsInterface.h"

void CGGLEffect::initCG() {
  context_ = cgCreateContext();
  cgSetErrorCallback(&IEffect::onError);
  cgGLRegisterStates(context_);
  cgGLSetManageTextureParameters(context_, GL_TRUE);
}

void CGGLEffect::beginDraw() { 
  CGpass pass = cgGetFirstPass(technique_);
  cgSetPassState(pass);
}

void CGGLEffect::resetStates() {
  CGpass pass = cgGetFirstPass(technique_);
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
  cgSetSamplerState(parameter);
}
