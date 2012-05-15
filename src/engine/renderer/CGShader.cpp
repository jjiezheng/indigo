#include "CGShader.h"

#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "app/Window.h"
#include "io/Log.h"
#include "io/File.h"
#include "io/Path.h"

#include "Color4.h"
#include "Color3.h"

#include <Cg/Cg.h>
#define CGGL_NO_OPENGL
#include <Cg/cgGL.h>


static void checkForCgError(CGcontext context, const char *situation) {
  CGerror error;
  const char *string = cgGetLastErrorString(&error);
  
  if (error != CG_NO_ERROR) {
    printf("%s: %s\n", situation, string);
    if (error == CG_COMPILER_ERROR) {
      printf("%s\n", cgGetLastListing(context));
    }
    exit(1);
  }
}

CGprogram loadCGProgram(CGcontext context, const std::string& fullPath, CGGLenum type);
CGprogram loadCGProgram(CGcontext context, const std::string& fullPath, CGGLenum type) {
  
  CGprofile profile = cgGLGetLatestProfile(type);
  checkForCgError(context, "selecting vertex profile");
  
//  cgGLSetOptimalOptions(profile);
//  checkForCgError(context, "setting optimal options");
  
  printf("compiling shader %s\n", fullPath.c_str());
  CGprogram program = cgCreateProgramFromFile(context, CG_SOURCE, fullPath.c_str(), profile, "main", NULL);
  checkForCgError(context, "creating program from file");
  
  cgGLLoadProgram(program);  
  checkForCgError(context, "loading vertex program");
  
  return program;
}

void CGShader::load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {  
  context_ = cgCreateContext();  
  checkForCgError(context_, "creating context");
  
  cgGLSetDebugMode(CG_FALSE);
  cgSetParameterSettingMode(context_, CG_DEFERRED_PARAMETER_SETTING);
  
  CGprogram programs[2];
  
  std::string fullVertexPath = Path::pathForFile(vertexShaderPath);
  programs[0] = loadCGProgram(context_, fullVertexPath, CG_GL_VERTEX);
    
  std::string fullFragPath = Path::pathForFile(fragmentShaderPath);
  programs[1] = loadCGProgram(context_, fullFragPath, CG_GL_FRAGMENT);
  
  program_ = cgCombinePrograms(2, programs);
  
  cgDestroyProgram(programs[1]);
  cgDestroyProgram(programs[0]);
}

void CGShader::link() {
  
}

void CGShader::use() const {
  cgGLBindProgram(program_);
}

void CGShader::bindAttribute(int attributeId, const char* attribute_name) {
  
}

void CGShader::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetMatrixParameterfr(parameter, uniformData.valuePtr());
}

void CGShader::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetMatrixParameterfr(parameter, uniformData.valuePtr());  
}

void CGShader::setUniform(const Color3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGShader::setUniform(const Color4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameter4fv(parameter, uniformData.valuePtr());
}

void CGShader::setUniform(const Vector3& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameter3fv(parameter, uniformData.valuePtr());
}

void CGShader::setUniform(const Vector4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameter4fv(parameter, uniformData.valuePtr());  
}

void CGShader::setUniform(int uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameter1i(parameter, uniformData);
}

void CGShader::setUniform(float uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameter1f(parameter, uniformData);
}

void CGShader::addUniform(const char* uniformName) {
  cgGetNamedParameter(program_, uniformName);
//  checkForCgError(context_, "could not get parameter");
}

void CGShader::setUniform(float* uniformData, size_t size, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  cgSetParameterValuefr(parameter, size, uniformData);
  
}