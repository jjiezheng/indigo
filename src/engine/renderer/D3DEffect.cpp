#include "D3DEffect.h"

#include "io/File.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <assert.h>

#include <d3dx11effect.h>

#include "io/Log.h"

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

void D3DEffect::load(const std::string& filePath) {
  ID3D10Blob* effect = NULL;

  {
    ID3D10Blob* errors = NULL;
    HRESULT result = D3DX11CompileFromFile(filePath.c_str(), NULL, NULL, NULL, "fx_5_0", 0, 0, 0, &effect, &errors, NULL);
    if (errors) {
      LPVOID errorData = errors->GetBufferPointer();
      char* errorText = (char*)errorData;
      LOG(LOG_CHANNEL_SHADER, "%s", errorText);
      errors->Release();
    } 
    assert(SUCCEEDED(result) && effect);
  }

  {
    HRESULT result = D3DX11CreateEffectFromMemory(effect->GetBufferPointer(), effect->GetBufferSize(), 0, device_, &effect_);
    assert(SUCCEEDED(result));
  }

  effect->Release();

  ID3DX11EffectTechnique *technique = effect_->GetTechniqueByIndex(0);
  assert(technique && technique->IsValid());

  pass_ = technique->GetPassByIndex(0);
  assert(pass_ && pass_->IsValid());

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
  assert(result == S_OK);
}

void D3DEffect::beginDraw() {
  pass_->Apply(0, context_);
  context_->IASetInputLayout(layout_);
}

void D3DEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsMatrix()->SetMatrix(uniformData.valuePtr());
  }
}

void D3DEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsMatrix()->SetMatrix(uniformData.valuePtr());
  }
}

void D3DEffect::setUniform(const Color3& uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }
}

void D3DEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }
}

void D3DEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }
}

void D3DEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVector(uniformData.valuePtr());
  }
}

void D3DEffect::setUniform(const Vector4* uniformData, unsigned int uniformDataCount, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsVector()->SetFloatVectorArray((float*)uniformData, 0, uniformDataCount);
  }
}

void D3DEffect::setUniform(int uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsScalar()->SetInt(uniformData);
  }
}

void D3DEffect::setUniform(float uniformData, const char* uniformName) const {
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    variable->AsScalar()->SetFloat(uniformData);
  }
}

void D3DEffect::setTexture(unsigned int textureId, const char* uniformName) {
  Direct3D11GraphicsInterface* graphicsInterface = static_cast<Direct3D11GraphicsInterface*>(GraphicsInterface::rawInterface());
  ID3DX11EffectVariable* variable = effect_->GetVariableByName(uniformName);
  if (variable->IsValid()) {
    graphicsInterface->setTexture(textureId, variable);
  }
}
