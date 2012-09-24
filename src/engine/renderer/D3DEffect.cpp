#include "D3DEffect.h"

#include "io/File.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <assert.h>

#include <D3Dcompiler.h>

#include <fstream>
#include "json/reader.h"

//#include <d3dx11effect.h>

#include "io/Log.h"
#include "io/Path.h"

#include "Color3.h"

#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "maths/Matrix3x3.h"
#include "maths/Matrix4x4.h"

#include "GraphicsInterface.h"

#include "Direct3D11GraphicsInterface.h"

ID3D11Device* D3DEffect::device_ = NULL;
ID3D11DeviceContext* D3DEffect::context_ = NULL;

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

void D3DEffect::load(const std::string& filePath) {
  std::string fullVertexShaderPath;
  std::string fullFragmentShaderPath;

  {
    std::ifstream effectFile;
    effectFile.open(filePath.c_str());

    json::Object effectJSONObject;
    json::Reader::Read(effectJSONObject, effectFile);

    json::String vertexFileJSONObject = effectJSONObject["targets"]["dx11"]["vertex"];
    std::string vertexShaderFilePath = vertexFileJSONObject.Value();
    fullVertexShaderPath = Path::pathForFile(vertexShaderFilePath);

    json::String fragmentFileJSONObject = effectJSONObject["targets"]["dx11"]["fragment"];
    std::string fragmentShaderFilePath = fragmentFileJSONObject.Value();
    fullFragmentShaderPath = Path::pathForFile(fragmentShaderFilePath);
  }

  {
    ID3D10Blob* vertexProgram = NULL;
    ID3D10Blob* errors = NULL;

    {

      File vertexShaderFile;
      vertexShaderFile.open(fullVertexShaderPath);

      HRESULT result = D3DCompile(vertexShaderFile.data(), vertexShaderFile.size(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "vs", "vs_5_0", 0, 0, &vertexProgram, &errors);
      if (errors) {
        LPVOID errorData = errors->GetBufferPointer();
        char* errorText = (char*)errorData;
        LOG(LOG_CHANNEL_SHADER, "%s", errorText);
        errors->Release();
      } 
      assert(SUCCEEDED(result) && vertexProgram);
    }

    {
      HRESULT result = device_->CreateVertexShader(vertexProgram->GetBufferPointer(), vertexProgram->GetBufferSize(), NULL, &vertexShader_);
    }
  }

  {
    
  }

  {
    ID3D10Blob* fragmentProgram = NULL;
    ID3D10Blob* errors = NULL;

    File fragmentShaderFile;
    fragmentShaderFile.open(fullFragmentShaderPath);

    HRESULT result = D3DCompile(fragmentShaderFile.data(), fragmentShaderFile.size(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "ps", "ps_5_0", 0, 0, &fragmentProgram, &errors);
    if (errors) {
      LPVOID errorData = errors->GetBufferPointer();
      char* errorText = (char*)errorData;
      LOG(LOG_CHANNEL_SHADER, "%s", errorText);
      errors->Release();
    } 
    assert(SUCCEEDED(result) && fragmentProgram);
  }

  /*
  D3DX11_PASS_SHADER_DESC effectDesc;
  pass_->GetVertexShaderDesc(&effectDesc);
  
  D3DX11_EFFECT_SHADER_DESC shaderDesc;
  effectDesc.pShaderVariable->GetShaderDesc(effectDesc.ShaderIndex, &shaderDesc);

  D3D11_INPUT_ELEMENT_DESC ied[] = {
    {"POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
  };
    
  
  HRESULT result = device_->CreateInputLayout(ied, 3, shaderDesc.pBytecode, shaderDesc.BytecodeLength, &layout_); 
  assert(result == S_OK);*/
}

void D3DEffect::beginDraw() {
/*  context_->VSSetConstantBuffers()
  context_->VSSetShader(vertexShader_, NULL, 0);*/
  /*pass_->Apply(0, context_);
  context_->IASetInputLayout(layout_);*/
}

void D3DEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsMatrix()->SetMatrix(uniformData.valuePtr());
  }*/
}

void D3DEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsMatrix()->SetMatrix(uniformData.valuePtr());
  }*/
}

void D3DEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }*/
}

void D3DEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }*/
}

void D3DEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }*/
}

void D3DEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }*/
}

void D3DEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataCount, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVectorArray((float*)uniformData, 0, uniformDataCount);
  }*/
}

void D3DEffect::setUniform(int uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsScalar()->SetInt(uniformData);
  }*/
}

void D3DEffect::setUniform(float uniformData, const char* uniformName) const {
  /*ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsScalar()->SetFloat(uniformData);
  }*/
}

void D3DEffect::setTexture(unsigned int textureId, const char* uniformName) {
  /*Direct3D11GraphicsInterface* graphicsInterface = static_cast<Direct3D11GraphicsInterface*>(GraphicsInterface::rawInterface());
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    graphicsInterface->setTexture(textureId, variable);
  }*/
}
