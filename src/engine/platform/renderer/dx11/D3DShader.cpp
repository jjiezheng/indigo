#include "D3DShader.h"

#include "io/File.h"

#include <D3D11.h>
#include <D3DX11.h>
#include <assert.h>

#include "io/Log.h"

ID3D11Device* D3DShader::device_ = NULL;
ID3D11DeviceContext* D3DShader::context_ = NULL;

void D3DShader::compile(const char* entryPoint, const char* profile, const char* filePath, ID3DBlob** outputBlob) {
  ID3D10Blob* error = NULL;
  HRESULT result = D3DX11CompileFromFile(filePath, NULL, NULL, entryPoint, profile, 0, 0, NULL, outputBlob, &error, NULL);
  if (error) {
    LPVOID errorData = error->GetBufferPointer();
    char* errorText = (char*)errorData;
    LOG(LOG_CHANNEL_SHADER, "%s", errorText);
  }
  assert(result == S_OK);
}

void D3DShader::load(const std::string& filePath) {
  {
    ID3DBlob* vertexShaderBuffer = NULL;
    compile("vs", "vs_4_0", filePath.c_str(), &vertexShaderBuffer);

    HRESULT result = device_->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader_);
    assert(result == S_OK);
  }
  
  {
    ID3DBlob* pixelShaderBuffer = NULL;
    compile("ps", "ps_4_0", filePath.c_str(), &pixelShaderBuffer);

    HRESULT result = device_->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader_);
    assert(result == S_OK);
  }
}

void D3DShader::beginDraw() {
  context_->VSSetShader(vertexShader_, NULL, 0);
  context_->PSSetShader(pixelShader_, NULL, 0);
}

void D3DShader::setUniform(const Matrix3x3& uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(const Matrix4x4& uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(const Color3& uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(const Vector2& uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(const Vector3& uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(const Vector4& uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(int uniformData, const char* uniformName) const {

}

void D3DShader::setUniform(float uniformData, const char* uniformName) const {

}

void D3DShader::setTexture(unsigned int textureId, const char* uniformName) {

}
