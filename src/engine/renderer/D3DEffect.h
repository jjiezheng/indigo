#ifndef D3DEFFECT_H
#define D3DEFFECT_H

#include <map>

#include "IEffect.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11InputLayout;
struct ID3D11Buffer;

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D10Blob;
struct ID3D11SamplerState;

struct ShaderTexture {
  unsigned int slot;
};

struct ShaderUniform {
  unsigned int size;
  unsigned int offset;
};

struct ConstantBuffer {
  std::map<std::string, ShaderUniform> uniforms;
  unsigned int size;
  ID3D11Buffer* GPUBuffer;
  char* CPUBuffer;

  ConstantBuffer()
    : CPUBuffer(0) 
    , GPUBuffer(0) { }
};

class D3DEffect : public IEffect {

public:

  ~D3DEffect();

public:

  static void setDevice(ID3D11Device* device, ID3D11DeviceContext* context);

public:

  void load(const std::string& filePath);

public:

  void beginDraw();

  void endDraw();

public:

  void setUniform(const Matrix3x3& uniformData, const char* uniformName) const;

  void setUniform(const Matrix4x4& uniformData, const char* uniformName) const;

  void setUniform(const Color3& uniformData, const char* uniformName) const;

  void setUniform(const Vector2& uniformData, const char* uniformName) const;

  void setUniform(const Vector3& uniformData, const char* uniformName) const;

  void setUniform(const Vector4& uniformData, const char* uniformName) const;

  void setUniform(const Vector4* uniformData, unsigned int uniformDataCount, const char* uniformName) const;

  void setUniform(int uniformData, const char* uniformName) const;

  void setUniform(float uniformData, const char* uniformName) const;

  void setTexture(unsigned int textureId, const char* uniformName);

  void setSamplerState(unsigned int samplerSlot, SAMPLER_UV_ADDRESS_MODE addressMode, SAMPLER_COMPARISON_FILTER comparisonFilter, SAMPLER_COMPARISON_FUNC compartisonFunction);

private:

  static ID3D11Device* device_;
  static ID3D11DeviceContext* context_;

private:

  ID3D11VertexShader* vertexShader_;
  ID3D11PixelShader* pixelShader_;

private:

  std::map<std::string, ShaderTexture> vertexShaderTextures_;
  std::vector<ConstantBuffer> vertexShaderConstantBuffers_;

private:

  std::vector<ConstantBuffer> pixelShaderConstantBuffers_;
  std::map<std::string, ShaderTexture> pixelShaderTextures_;
  std::map<unsigned int, ID3D11SamplerState*> pixelShaderSamplers_;

private:

  ID3D11InputLayout* layout_;

private:

  void setConstant(const char* uniformName, void* uniformData) const;

  void setConstantBufferValue(const std::vector<ConstantBuffer>& constantBuffer, const std::string& uniformName, void* uniformData) const;

  void fillConstantBuffer(ID3D10Blob* programData, std::vector<ConstantBuffer>& constantBufferList, std::map<std::string, ShaderTexture>& shaderTextures, std::map<unsigned int, ID3D11SamplerState*>& samplers);

  void commitShaderConstantBuffers(const std::vector<ConstantBuffer>& shaderConstantBuffers);  

};

inline void D3DEffect::setDevice(ID3D11Device* device, ID3D11DeviceContext* context) {
  device_ = device;
  context_ = context;
}

#endif
