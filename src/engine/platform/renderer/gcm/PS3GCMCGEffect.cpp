#include "PS3GCMCGEffect.h"

#include <fstream>
#include <algorithm>
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

#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "maths/Matrix3x3.h"
#include "maths/Matrix4x4.h"

#include "Color3.h"

using namespace cell::Gcm;

#define BASED_ALIGN	128	

void PS3GCMCGEffect::load(const std::string& filePath) {
  std::string fullVertexShaderFilePath = filePath + ".gcm.vertex";
  std::string fullFragmentShaderFilePath = filePath + ".gcm.fragment";

  {
    File vertexShaderFile;
    vertexShaderFile.open(fullVertexShaderFilePath);

    vertexProgram_ = (CGprogram)((void*)vertexShaderFile.data());

    cellGcmCgInitProgram(vertexProgram_);

    unsigned int vpSize;
    cellGcmCgGetUCode(vertexProgram_, &vertexProgramAddress_, &vpSize);

    CGparameter positionParameter = cellGcmCgGetNamedParameter(vertexProgram_, "position");
    vertexPositionIndex_ = cellGcmCgGetParameterResource(vertexProgram_, positionParameter) - CG_ATTR0;

    CGparameter normalParameter = cellGcmCgGetNamedParameter(vertexProgram_, "normal");
    if (normalParameter) {
      normalIndex_ = cellGcmCgGetParameterResource(vertexProgram_, normalParameter) - CG_ATTR0;
    }

    CGparameter uvParameter = cellGcmCgGetNamedParameter(vertexProgram_, "texCoord");
    if (uvParameter) { 
      uvIndex_ = cellGcmCgGetParameterResource(vertexProgram_, uvParameter) - CG_ATTR0;
    }
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

    void *fpLocal = graphicsInterface->localAllocate(128, fpSize);	// 128B align
    memcpy(fpLocal, fpAddr, fpSize);

    CELL_GCMUTIL_CHECK_ASSERT(cellGcmAddressToOffset(fpLocal, &fragmentProgramOffset_));
  }

  {
    unsigned int registerCount = cellGcmCgGetRegisterCount(vertexProgram_);
    unsigned int properRegisterCount = std::max(registerCount, 5u);
    cellGcmCgSetRegisterCount(vertexProgram_, properRegisterCount); 
  }

  {
    unsigned int registerCount = cellGcmCgGetRegisterCount(fragmentProgram_);
    unsigned int properRegisterCount = std::max(registerCount, 5u);
    cellGcmCgSetRegisterCount(fragmentProgram_, properRegisterCount); 
  }
}

void PS3GCMCGEffect::beginDraw() {
  cellGcmSetVertexProgram(vertexProgram_, vertexProgramAddress_);
  cellGcmSetFragmentProgram(fragmentProgram_, fragmentProgramOffset_);

  IGraphicsInterface* rawInterface = GraphicsInterface::rawInterface();
  PS3GCMGraphicsInterface* graphicsInterface = static_cast<PS3GCMGraphicsInterface*>(rawInterface);
  graphicsInterface->setEffect(this);

  for (std::map<unsigned int, GCMSamplerState>::iterator i = samplerStates_.begin(); i != samplerStates_.end(); ++i) {
    GCMSamplerState samplerState = (*i).second;
    cellGcmSetTextureAddress((*i).first, samplerState.addressU, samplerState.addressV, samplerState.addressW, CELL_GCM_TEXTURE_UNSIGNED_REMAP_NORMAL, samplerState.comparisonFunc, 0);
    cellGcmSetTextureFilter((*i).first, 0, samplerState.minFilter, samplerState.magFilter, CELL_GCM_TEXTURE_CONVOLUTION_QUINCUNX);
  }
}

void PS3GCMCGEffect::endDraw() {
  static const unsigned int TEXTURE_SAMPLER_COUNT = 15;
  for (unsigned int i = 0; i < TEXTURE_SAMPLER_COUNT; i++) {
    cellGcmSetTextureControl(i, CELL_GCM_FALSE, 1*0xff, 1*0xff, CELL_GCM_TEXTURE_MAX_ANISO_1);
  }
}

void PS3GCMCGEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, uniformData.valuePtr(), fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, uniformData.valuePtr(), fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, uniformData.valuePtr(), fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
 {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, uniformData.valuePtr(), fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, uniformData.valuePtr(), fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, uniformData.valuePtr());
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, uniformData.valuePtr(), fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const {
  CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
  if (parameter) {
    cellGcmSetVertexProgramParameter(parameter, (float*)uniformData);
  }
}

void PS3GCMCGEffect::setUniform(int uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, (float*)&uniformData);
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, (float*)&uniformData, fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setUniform(float uniformData, const char* uniformName) const {
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(vertexProgram_, uniformName);
    if (parameter) {
      cellGcmSetVertexProgramParameter(parameter, &uniformData);
    }
  }
  {
    CGparameter parameter = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);
    if (parameter) {
      cellGcmSetFragmentProgramParameter(fragmentProgram_, parameter, &uniformData, fragmentProgramOffset_);
    }
  }
}

void PS3GCMCGEffect::setTexture(unsigned int textureId, const char* uniformName) {
  CGparameter texture = cellGcmCgGetNamedParameter(fragmentProgram_, uniformName);

  if (texture) {
    unsigned int textureUnit = cellGcmCgGetParameterResource(fragmentProgram_, texture) - CG_TEXUNIT0;

    IGraphicsInterface* rawInterface = GraphicsInterface::rawInterface();
    PS3GCMGraphicsInterface* graphicsInterface = static_cast<PS3GCMGraphicsInterface*>(rawInterface);
    graphicsInterface->setTexture(textureUnit, textureId);
  }
}

void PS3GCMCGEffect::setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) {

  GCMSamplerState samplerState;

  switch (compartisonFunction) {
    case COMPARISON_NONE:
      samplerState.comparisonFunc = CELL_GCM_TEXTURE_ZFUNC_NEVER;
      break;
    case COMPARISON_LESS:
      samplerState.comparisonFunc = CELL_GCM_TEXTURE_ZFUNC_LESS;
      break;
    case COMPARISON_GREATERTHAN_OR_EQUAL:
      samplerState.comparisonFunc = CELL_GCM_TEXTURE_ZFUNC_GEQUAL;
      break;
    case COMPARISON_LESS_SHADOW:
      samplerState.comparisonFunc = CELL_GCM_TEXTURE_ZFUNC_GREATER;
      break;
  }

  switch (addressMode) {
    case UV_ADDRESS_CLAMP:
      samplerState.addressU = CELL_GCM_TEXTURE_CLAMP;
      samplerState.addressV = CELL_GCM_TEXTURE_CLAMP;
      samplerState.addressW = CELL_GCM_TEXTURE_CLAMP_TO_EDGE;
      break;

    case UV_ADDRESS_WRAP: 
      samplerState.addressU = CELL_GCM_TEXTURE_WRAP;
      samplerState.addressV = CELL_GCM_TEXTURE_WRAP;
      samplerState.addressW = CELL_GCM_TEXTURE_CLAMP_TO_EDGE;
      break;
  } 

  switch(comparisonFilter) {
    case FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
      samplerState.minFilter = CELL_GCM_TEXTURE_LINEAR_NEAREST;
      samplerState.magFilter = CELL_GCM_TEXTURE_LINEAR_NEAREST;
      break;

    case FILTER_MIN_MAG_MIP_POINT:
      samplerState.minFilter = CELL_GCM_TEXTURE_NEAREST;
      samplerState.magFilter = CELL_GCM_TEXTURE_NEAREST;
      break;

    case FILTER_MIN_MAG_MIP_LINEAR:
      samplerState.minFilter = CELL_GCM_TEXTURE_LINEAR_LINEAR;
      samplerState.magFilter = CELL_GCM_TEXTURE_LINEAR;
      break;
  }

  samplerStates_[samplerSlot] = samplerState;
}

