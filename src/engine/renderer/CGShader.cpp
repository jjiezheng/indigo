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

#include "OpenGL.h"
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
  
  cgGLSetOptimalOptions(profile);
  checkForCgError(context, "setting optimal options");
  
  printf("compiling shader %s\n", fullPath.c_str());
  CGprogram program = cgCreateProgramFromFile(context, CG_SOURCE, fullPath.c_str(), profile, "main", NULL);
  checkForCgError(context, "creating program from file");
  
  cgGLLoadProgram(program);  
  checkForCgError(context, "loading vertex program");
  
  return program;
}

void CGShader::load(const char* vertexShaderPath, const char* fragmentShaderPath) {  
  context_ = cgCreateContext();  
  checkForCgError(context_, "creating context");
  
  cgGLSetDebugMode(CG_FALSE);
  cgSetParameterSettingMode(context_, CG_DEFERRED_PARAMETER_SETTING);
  
  {
    std::string fullVertexPath = Path::pathForFile(vertexShaderPath);
    vertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
    checkForCgError(context_, "selecting vertex profile");

    cgGLSetOptimalOptions(vertexProfile);
    checkForCgError(context_, "setting optimal options");

    printf("compiling shader %s\n", fullVertexPath.c_str());
    vertexProgram = cgCreateProgramFromFile(context_, CG_SOURCE, fullVertexPath.c_str(), vertexProfile, "main", NULL);
    checkForCgError(context_, "creating program from file");

    cgGLLoadProgram(vertexProgram);  
    checkForCgError(context_, "loading vertex program");
  }

  {
    std::string fullFragmentPath = Path::pathForFile(fragmentShaderPath);
    fragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    checkForCgError(context_, "selecting fragment profile");

    cgGLSetOptimalOptions(fragmentProfile);
    checkForCgError(context_, "setting optimal options");

    printf("compiling shader %s\n", fullFragmentPath.c_str());
    fragmentProgram = cgCreateProgramFromFile(context_, CG_SOURCE, fullFragmentPath.c_str(), fragmentProfile, "main", NULL);
    checkForCgError(context_, "creating program from file");

    cgGLLoadProgram(fragmentProgram);  
    checkForCgError(context_, "loading fragment program");

    CGprogram programs[] = {vertexProgram, fragmentProgram};
    program_ = cgCombinePrograms(2, programs);

    cgGLLoadProgram(program_);
  }
}

void CGShader::link() {
  
}

void CGShader::use() const {
  cgGLLoadProgram(program_);
  cgGLBindProgram(program_);
  checkForCgError(context_, "binding vertex program");
  
  /*cgGLBindProgram(vertexProgram);
  checkForCgError(context_, "binding vertex program");*/

  cgGLEnableProfile(vertexProfile);
  checkForCgError(context_, "enabling vertex profile");

  /*cgGLBindProgram(fragmentProgram);
  checkForCgError(context_, "binding fragment program");*/

  cgGLEnableProfile(fragmentProfile);
  checkForCgError(context_, "enabling fragment profile"); 
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