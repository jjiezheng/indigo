#include "D3DEffect.h"

#include "io/File.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <assert.h>

#include <D3Dcompiler.h>

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

#include "memory/Allocation.h"

ID3D11Device* D3DEffect::device_ = NULL;
ID3D11DeviceContext* D3DEffect::context_ = NULL;

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

D3DEffect::~D3DEffect() {
  vertexShader_->Release();
  pixelShader_->Release();
  layout_->Release();

  for (std::vector<ConstantBuffer>::iterator i = pixelShaderConstantBuffers_.begin(); i != pixelShaderConstantBuffers_.end();) {
    SAFE_DELETE((*i).CPUBuffer);
    (*i).GPUBuffer->Release();
    i = pixelShaderConstantBuffers_.erase(i);
  }

  for (std::map<unsigned int, ID3D11SamplerState*>::iterator i = pixelShaderSamplers_.begin(); i != pixelShaderSamplers_.end();) {
    (*i).second->Release();
    i = pixelShaderSamplers_.erase(i);
  }

  for (std::vector<ConstantBuffer>::iterator i = vertexShaderConstantBuffers_.begin(); i != vertexShaderConstantBuffers_.end();) {
    SAFE_DELETE((*i).CPUBuffer);
    (*i).GPUBuffer->Release();
    i = vertexShaderConstantBuffers_.erase(i);
  }
}

void D3DEffect::fillConstantBuffer(ID3D10Blob* programData, std::vector<ConstantBuffer>& constantBufferList, std::map<std::string, ShaderTexture>& shaderTextures, std::map<unsigned int, ID3D11SamplerState*>& samplers) {
  ID3D11ShaderReflection* shaderReflection = NULL;
  HRESULT result = D3DReflect(programData->GetBufferPointer(), programData->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &shaderReflection);
  assert(SUCCEEDED(result) && shaderReflection);

  {
    D3D11_SHADER_DESC shaderDesc;
    HRESULT result = shaderReflection->GetDesc(&shaderDesc);
    assert(SUCCEEDED(result));

    unsigned int constantBuffers = shaderDesc.ConstantBuffers;
    for (unsigned int i = 0; i < constantBuffers; i++) {
      ID3D11ShaderReflectionConstantBuffer* reflectionConstantBuffer = shaderReflection->GetConstantBufferByIndex(i);

      ConstantBuffer constantBuffer;

      D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
      HRESULT result = reflectionConstantBuffer->GetDesc(&shaderBufferDesc);
      assert(SUCCEEDED(result));

      {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));

        bufferDesc.ByteWidth = shaderBufferDesc.Size;
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT result = device_->CreateBuffer(&bufferDesc, NULL, &constantBuffer.GPUBuffer);
        assert(SUCCEEDED(result));
      }

      {
        constantBuffer.CPUBuffer = new char[shaderBufferDesc.Size];
        constantBuffer.size = shaderBufferDesc.Size;
      }
     
      for (unsigned int j = 0; j < shaderBufferDesc.Variables; j++) {
        ID3D11ShaderReflectionVariable* reflectionVariable = reflectionConstantBuffer->GetVariableByIndex(j);

        D3D11_SHADER_VARIABLE_DESC shaderVariableDesc;
        HRESULT result = reflectionVariable->GetDesc(&shaderVariableDesc);
        assert(SUCCEEDED(result));

        ShaderUniform uniform;
        uniform.offset = shaderVariableDesc.StartOffset;
        uniform.size = shaderVariableDesc.Size;

        constantBuffer.uniforms[shaderVariableDesc.Name] = uniform;
      }

      constantBufferList.push_back(constantBuffer);          
    }

    unsigned int boundResources = shaderDesc.BoundResources;
    for (unsigned int i = 0; i < boundResources; i++) {
      D3D11_SHADER_INPUT_BIND_DESC bindDesc;
      HRESULT result = shaderReflection->GetResourceBindingDesc(i, &bindDesc);
      assert(SUCCEEDED(result));

      ShaderTexture texture;
      texture.slot = bindDesc.BindPoint;
      shaderTextures[bindDesc.Name] = texture;

      D3D11_SAMPLER_DESC samplerDesc;
      ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

      samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
      samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
      samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

      samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

      ID3D11SamplerState* samplerState = 0;
      result = device_->CreateSamplerState(&samplerDesc, &samplerState);
      assert(SUCCEEDED(result));

      std::map<unsigned int, ID3D11SamplerState*>::iterator samplerIt = samplers.find(bindDesc.BindPoint);
      if (samplerIt != samplers.end()) {
        (*samplerIt).second->Release();
      }

      samplers[bindDesc.BindPoint] = samplerState;
    }
  }
}

void D3DEffect::load(const std::string& filePath) {
  std::string fullVertexShaderFilePath = filePath + ".dx11.vertex";

  {
    ID3D10Blob* vertexProgram = NULL;
    ID3D10Blob* errors = NULL;

    {
      {
        File vertexShaderFile;
        vertexShaderFile.open(fullVertexShaderFilePath);

        HRESULT result = D3DCompile(vertexShaderFile.data(), vertexShaderFile.size(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0", 0, 0, &vertexProgram, &errors);
        if (errors) {
          LPVOID errorData = errors->GetBufferPointer();
          char* errorText = (char*)errorData;
          LOG(LOG_CHANNEL_SHADER, "%s", errorText);
          errors->Release();
        } 
        assert(SUCCEEDED(result) && vertexProgram);
      }

      {
        fillConstantBuffer(vertexProgram, vertexShaderConstantBuffers_, vertexShaderTextures_, pixelShaderSamplers_);
      }
    }

    {
      HRESULT result = device_->CreateVertexShader(vertexProgram->GetBufferPointer(), vertexProgram->GetBufferSize(), NULL, &vertexShader_);
      assert(SUCCEEDED(result));
    }

    {
      {
        D3D11_INPUT_ELEMENT_DESC ied[] = {
          {"POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
          {"NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
          {"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };


        HRESULT result = device_->CreateInputLayout(ied, 3, vertexProgram->GetBufferPointer(), vertexProgram->GetBufferSize(), &layout_); 
        assert(SUCCEEDED(result));
      }
    }
  }

    
  std::string fullPixelShaderFilePath = filePath + ".dx11.fragment";

  {
    ID3D10Blob* pixelProgram = NULL;
    ID3D10Blob* errors = NULL;

    {
      File fragmentShaderFile;
      fragmentShaderFile.open(fullPixelShaderFilePath);

      HRESULT result = D3DCompile(fragmentShaderFile.data(), fragmentShaderFile.size(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0", 0, 0, &pixelProgram, &errors);
      if (errors) {
        LPVOID errorData = errors->GetBufferPointer();
        char* errorText = (char*)errorData;
        LOG(LOG_CHANNEL_SHADER, "%s", errorText);
        errors->Release();
      } 
      assert(SUCCEEDED(result) && pixelProgram);
    }

    {
      fillConstantBuffer(pixelProgram, pixelShaderConstantBuffers_, pixelShaderTextures_, pixelShaderSamplers_);
    }

    {
      HRESULT result = device_->CreatePixelShader(pixelProgram->GetBufferPointer(), pixelProgram->GetBufferSize(), NULL, &pixelShader_);
      assert(SUCCEEDED(result));
    }
  }
}

void D3DEffect::commitShaderConstantBuffers(const std::vector<ConstantBuffer>& shaderConstantBuffers) {
   for (std::vector<ConstantBuffer>::const_iterator constantBufferIt = shaderConstantBuffers.begin(); constantBufferIt != shaderConstantBuffers.end(); ++constantBufferIt) {
     D3D11_MAPPED_SUBRESOURCE resource;
     HRESULT result = context_->Map((*constantBufferIt).GPUBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
     assert(SUCCEEDED(result));

     memcpy((char*)resource.pData, (*constantBufferIt).CPUBuffer, (*constantBufferIt).size);
     context_->Unmap((*constantBufferIt).GPUBuffer, 0);
   }
}

void D3DEffect::beginDraw() {
  context_->VSSetShader(vertexShader_, NULL, 0);
}

void D3DEffect::commitBuffers() {
	commitShaderConstantBuffers(vertexShaderConstantBuffers_);

	for (unsigned int i = 0; i < vertexShaderConstantBuffers_.size(); i++) {
		context_->VSSetConstantBuffers(i, 1, &vertexShaderConstantBuffers_[i].GPUBuffer);
	}

	context_->PSSetShader(pixelShader_, NULL, 0);

	commitShaderConstantBuffers(pixelShaderConstantBuffers_);

	for (unsigned int i = 0; i < pixelShaderConstantBuffers_.size(); i++) {
		context_->PSSetConstantBuffers(i, 1, &pixelShaderConstantBuffers_[i].GPUBuffer);
	}

	for (std::map<unsigned int, ID3D11SamplerState*>::iterator i = pixelShaderSamplers_.begin(); i != pixelShaderSamplers_.end(); ++i) {
		context_->PSSetSamplers((*i).first, 1, &(*i).second);
	}

	context_->IASetInputLayout(layout_);
}


void D3DEffect::endDraw() {
  ID3D11ShaderResourceView* emptyResourceView[5];
  ZeroMemory(emptyResourceView, sizeof(ID3D11ShaderResourceView) * 5);
  context_->PSSetShaderResources(0, 5, emptyResourceView);

  ID3D11SamplerState* emptySamplerState[5];
  ZeroMemory(emptySamplerState, sizeof(ID3D11SamplerState) * 5);
  context_->PSSetSamplers(0, 5, emptySamplerState); 
}

void D3DEffect::setConstant(const char* uniformName, void* uniformData) const {
  setConstantBufferValue(vertexShaderConstantBuffers_, uniformName, uniformData);
  setConstantBufferValue(pixelShaderConstantBuffers_, uniformName, uniformData);
}

void D3DEffect::setConstantBufferValue(const std::vector<ConstantBuffer>& constantBuffer, const std::string& uniformName, void* uniformData) const {
  std::string internalUniformName = std::string("_") + uniformName;

  for (std::vector<ConstantBuffer>::const_iterator constantBufferIt = constantBuffer.begin(); constantBufferIt != constantBuffer.end(); ++constantBufferIt) {
    std::map<std::string, ShaderUniform>::const_iterator shaderIt = (*constantBufferIt).uniforms.find(internalUniformName);

    if (shaderIt != (*constantBufferIt).uniforms.end()) {
      ShaderUniform uniform = (*shaderIt).second;
      memcpy((*constantBufferIt).CPUBuffer + uniform.offset, uniformData, uniform.size);
    }
  }
}

void D3DEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData.valuePtr());
}

void D3DEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData.valuePtr());
}

void D3DEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData.valuePtr());
}

void D3DEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData.valuePtr());
}

void D3DEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData.valuePtr());
}

void D3DEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData.valuePtr());
}

void D3DEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataCount, const char* uniformName) const {
  setConstant(uniformName, (void*)uniformData);
}

void D3DEffect::setUniform(int uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)&uniformData);
}

void D3DEffect::setUniform(float uniformData, const char* uniformName) const {
  setConstant(uniformName, (void*)&uniformData);
}

void D3DEffect::setTexture(unsigned int textureId, const char* uniformName) {
  std::string internalTextureName = std::string("_") + uniformName;
  std::map<std::string, ShaderTexture>::const_iterator textureIt = pixelShaderTextures_.find(internalTextureName);

  if (textureIt != pixelShaderTextures_.end()) {
    IGraphicsInterface* graphicsInterface = GraphicsInterface::rawInterface();
    Direct3D11GraphicsInterface* directXGraphicsInterface = static_cast<Direct3D11GraphicsInterface*>(graphicsInterface);

    unsigned int textureSlot = (*textureIt).second.slot;
    ID3D11SamplerState* samplerState = pixelShaderSamplers_[textureSlot];
    directXGraphicsInterface->setTexture(textureSlot, samplerState, textureId);
  }
}

void D3DEffect::setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction) {
  if (samplerSlot + 1 > pixelShaderSamplers_.size()) {
    return;
  }


  D3D11_SAMPLER_DESC samplerDesc;
  ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

  samplerDesc.MinLOD = 0;
  samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

  switch (addressMode) {
    case UV_ADDRESS_CLAMP:
      samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
      samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
      samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
      break;

    case UV_ADDRESS_WRAP: 
      samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
      samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
      samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
      break;
  }

  switch(comparisonFilter) {
    case FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
      samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
      break;

    case FILTER_MIN_MAG_MIP_POINT:
      samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
      break;

    case FILTER_MIN_MAG_MIP_LINEAR:
      samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
      break;
  }

  switch(compartisonFunction) {
    case COMPARISON_LESS:
      samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
      break;

    case COMPARISON_LESS_SHADOW:
      samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
      break;

    case COMPARISON_GREATERTHAN_OR_EQUAL:
      samplerDesc.ComparisonFunc = D3D11_COMPARISON_GREATER_EQUAL;
      break;
  }

  ID3D11SamplerState* samplerState = 0;
  HRESULT result = device_->CreateSamplerState(&samplerDesc, &samplerState);
  assert(SUCCEEDED(result));

  std::map<unsigned int, ID3D11SamplerState*>::iterator pixelShaderSamplersIt = pixelShaderSamplers_.find(samplerSlot);

  if (pixelShaderSamplersIt != pixelShaderSamplers_.end()) {
    (*pixelShaderSamplersIt).second->Release();
  }

  pixelShaderSamplers_[samplerSlot] = samplerState;
}