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

static const char* kFEntryPointName = "fmain";
static const char* kVEntryPointName = "vmain";


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

CGprogram loadCGProgram(CGcontext context, const std::string& fullPath, CGGLenum type, const char* entryPoint);
CGprogram loadCGProgram(CGcontext context, const std::string& fullPath, CGGLenum type, const char* entryPoint) {
	CGprofile profile = cgGLGetLatestProfile(type);
	checkForCgError(context, "selecting profile");

	cgGLSetOptimalOptions(profile);
	checkForCgError(context, "setting optimal options");

	printf("compiling shader %s\n", fullPath.c_str());
	CGprogram program = cgCreateProgramFromFile(context, CG_SOURCE, fullPath.c_str(), profile, entryPoint, NULL);
	checkForCgError(context, "creating program from file");

	cgGLLoadProgram(program);  
	checkForCgError(context, "loading program");
  
  return program;
}

void CGShader::load(const char* vertexShaderPath, const char* fragmentShaderPath) {  
  context_ = cgCreateContext();  
  checkForCgError(context_, "creating context");
  
  cgGLSetDebugMode(CG_TRUE);
  cgSetParameterSettingMode(context_, CG_DEFERRED_PARAMETER_SETTING);

  std::string fullVertexPath = Path::pathForFile(vertexShaderPath);
  CGprogram vertexProgram = loadCGProgram(context_, fullVertexPath, CG_GL_VERTEX, kVEntryPointName);
  
  std::string fullFragmentPath = Path::pathForFile(fragmentShaderPath);
  CGprogram fragmentProgram = loadCGProgram(context_, fullFragmentPath, CG_GL_FRAGMENT, kFEntryPointName);

  CGprogram programs[] = {vertexProgram, fragmentProgram};
  checkForCgError(context_, "combining programs");
  program_ = cgCombinePrograms(2, programs);

  cgGLLoadProgram(program_);
}

void CGShader::link() {
 
}

void CGShader::addUniform(const char* uniformName) {

}

void CGShader::bindAttribute(int attributeId, const char* attribute_name) {

}

void CGShader::use() const {
  cgGLLoadProgram(program_);
  checkForCgError(context_, "loading program");

  cgGLBindProgram(program_);
  checkForCgError(context_, "binding shader program");

  cgGLEnableProgramProfiles(program_);
  checkForCgError(context_, "enable program profiles");
}

void CGShader::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
 
}

void CGShader::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  if (parameter) {
    cgGLSetMatrixParameterfr(parameter, uniformData.valuePtr());
  }
}

void CGShader::setUniform(const Color3& uniformData, const char* uniformName) const {
 
}

void CGShader::setUniform(const Color4& uniformData, const char* uniformName) const {
 
}

void CGShader::setUniform(const Vector3& uniformData, const char* uniformName) const {
  
}

void CGShader::setUniform(const Vector4& uniformData, const char* uniformName) const {
  
}

void CGShader::setUniform(int uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  if (parameter) {
   // cgGLSetParameter1d(parameter, uniformData);
  }
//
//  if (uniformName == "colorMap") {
//    //cgGLSetTextureParameter(parameter, uniformData);
//  }
}

void CGShader::setUniform(float uniformData, const char* uniformName) const {
  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  if (parameter) {
    cgGLSetParameter1f(parameter, uniformData);
  }
}

void CGShader::setUniform(float* uniformData, size_t size, const char* uniformName) const {
 
}

void CGShader::setTexture(int textureIndex, unsigned int textureId, const char* uniformName) {
  glActiveTexture(GL_TEXTURE0 + textureIndex);
  glBindTexture(GL_TEXTURE_2D, textureId);

  CGparameter parameter = cgGetNamedParameter(program_, uniformName);
  if (parameter) {
    cgGLSetTextureParameter(parameter, textureId);
    cgGLEnableTextureParameter(parameter);
  }
}