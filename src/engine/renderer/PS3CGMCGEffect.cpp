#include "PS3CGMCGEffect.h"

#include <fstream>
#include "json/reader.h"

#include <Cg/cg.h>
#include <cell/gcm.h>

#include <sysutil/sysutil_sysparam.h>

#include "gcmutil_error.h"

#include "io/Log.h"
#include "io/Path.h"
#include "io/File.h"

#include "IGraphicsInterface.h"
#include "GraphicsInterface.h"
#include "PS3GCMGraphicsInterface.h"

#include "maths/Matrix4x4.h"

#define BASED_ALIGN	128	

void PS3GCMCGEffect::load(const std::string& filePath) {

  std::string fullVertexShaderFilePath;
  std::string fullFragmentShaderFilePath;

  {
    std::ifstream effectFile;
    effectFile.open(filePath.c_str());

    json::Object effectJSONObject;
    json::Reader::Read(effectJSONObject, effectFile);

    json::String vertexFileJSONObject = effectJSONObject["targets"]["gcm"]["vertex"];
    std::string vertexShaderFilePath = vertexFileJSONObject.Value();
    fullVertexShaderFilePath = Path::pathForFile(vertexShaderFilePath);

    json::String fragmentFileJSONObject = effectJSONObject["targets"]["gcm"]["fragment"];
    std::string fragmentShaderFilePath = fragmentFileJSONObject.Value();
    fullFragmentShaderFilePath = Path::pathForFile(fragmentShaderFilePath);
  }

  {
    File vertexShaderFile;
    vertexShaderFile.open(fullVertexShaderFilePath);

    vertexProgram_ = (CGprogram)((void*)vertexShaderFile.data());

    cellGcmCgInitProgram(vertexProgram_);

    unsigned int vpSize;
    cellGcmCgGetUCode(vertexProgram_, &vertexProgramAddress_, &vpSize);

    CGparameter positionParameter = cellGcmCgGetNamedParameter(vertexProgram_, "position");
    vertexPositionIndex_ = cellGcmCgGetParameterResource(vertexProgram_, positionParameter) - CG_ATTR0;
  }
  
  {
    File fragmentShaderFile;
    fragmentShaderFile.open(fullFragmentShaderFilePath);

    fragmentProgram_ = (CGprogram)((void*)fragmentShaderFile.data());

    cellGcmCgInitProgram(fragmentProgram_);

    void *fpAddr;
    unsigned int fpSize;

    cellGcmCgGetUCode(fragmentProgram_, &fpAddr, &fpSize);

    IGraphicsInterface* rawInterface = GraphicsInterface::rawInterface();
    PS3GCMGraphicsInterface* graphicsInterface = static_cast<PS3GCMGraphicsInterface*>(rawInterface);

    void *fpLocal = graphicsInterface->localAllocate(fpSize);	// 128B align
    memcpy(fpLocal, fpAddr, fpSize);

    CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(fpLocal, &fragmentProgramOffset_));
  }
}

void PS3GCMCGEffect::beginDraw() {
  cell::Gcm::cellGcmSetVertexProgram(vertexProgram_, vertexProgramAddress_);
  cell::Gcm::cellGcmSetFragmentProgram(fragmentProgram_, fragmentProgramOffset_);

  IGraphicsInterface* rawInterface = GraphicsInterface::rawInterface();
  PS3GCMGraphicsInterface* graphicsInterface = static_cast<PS3GCMGraphicsInterface*>(rawInterface);
  graphicsInterface->setEffect(this);
}

void PS3GCMCGEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
  if (parameter) {
    cell::Gcm::cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
  }
}

void PS3GCMCGEffect::setUniform(const Color3& uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(int uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setUniform(float uniformData, const char* uniformName) const {

}

void PS3GCMCGEffect::setTexture(unsigned int textureId, const char* uniformName) {

}