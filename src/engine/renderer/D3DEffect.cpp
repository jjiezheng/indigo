#include "D3DEffect.h"

#include "io/File.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <assert.h>

#include <d3dx11effect.h>

#include "io/Log.h"

ID3D11Device* D3DEffect::device_ = NULL;

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
}

void D3DEffect::beginDraw() {

}

void D3DEffect::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(const Color3& uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(const Vector2& uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(const Vector3& uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(const Vector4& uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(int uniformData, const char* uniformName) const {

}

void D3DEffect::setUniform(float uniformData, const char* uniformName) const {

}

void D3DEffect::setTexture(unsigned int textureId, const char* uniformName) {

}
