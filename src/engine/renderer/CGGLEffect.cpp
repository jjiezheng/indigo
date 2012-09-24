#include "CGGLEffect.h"

#include "OpenGL.h"
#include <Cg/Cg.h>
#include <Cg/cgGL.h>

#include "io/Log.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
#include "Color3.h"
#include "GraphicsInterface.h"

CGcontext CGGLEffect::context_ = 0;

void CGGLEffect::onError() {
// 	CGerror error;
// 	const char *errorString = cgGetLastErrorString(&error);
// 	LOG(LOG_CHANNEL_SHADER, errorString);
// 
// 	const char* errorListing = cgGetLastListing(context_);
// 	if (errorListing) {
// 		LOG(LOG_CHANNEL_SHADER, errorListing);
// 	}
}

void CGGLEffect::handleError(CGcontext context, CGerror error, void *data) {
// 	LOG(LOG_CHANNEL_SHADER, "%s", cgGetErrorString(error));
// 
// 	const char* errorListing = cgGetLastListing(context_);
// 	if (errorListing) {
// 		LOG(LOG_CHANNEL_SHADER, errorListing);
// 	}
}

void CGGLEffect::initCG() {
//   context_ = cgCreateContext();
//   cgSetErrorCallback(&CGGLEffect::onError);
//   cgGLRegisterStates(context_);
//   cgGLSetManageTextureParameters(context_, GL_TRUE);
}

void CGGLEffect::load(const std::string& filePath) {
  /*const char* args[] = {"-DOPENGL=1", 0};*/
}

void CGGLEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetParameter2fv(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Vector4& uniformData, const char* uniformName) const { 
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetParameter4fv(parameter, uniformData.valuePtr()); 
}

void CGGLEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const {

}

void CGGLEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGGLEffect::setUniform(int uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetParameter1d(parameter, uniformData);
}

void CGGLEffect::setUniform(float uniformData, const char* uniformName) const {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   cgGLSetParameter1f(parameter, uniformData);
}

void CGGLEffect::setTexture(unsigned int textureId, const char* uniformName) {
//   CGparameter parameter = cgGetNamedEffectParameter(effect_, uniformName);
//   if (!parameter) return;
//   GraphicsInterface::setTexture(textureId, parameter);
}
