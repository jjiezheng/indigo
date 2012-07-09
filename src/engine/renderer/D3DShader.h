#ifndef D3DSHADER_H
#define D3DSHADER_H

#include "IEffect.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11PixelShader;
struct ID3D11VertexShader;

#include <D3Dcommon.h>

class D3DShader : public IEffect {

public:

  static void setDevice(ID3D11Device* device, ID3D11DeviceContext* context);

public:

  void load(const std::string& filePath);

public:

  void beginDraw();

public:

  void setUniform(const Matrix3x3& uniformData, const char* uniformName) const;

  void setUniform(const Matrix4x4& uniformData, const char* uniformName) const;

  void setUniform(const Color3& uniformData, const char* uniformName) const;

  void setUniform(const Vector2& uniformData, const char* uniformName) const;

  void setUniform(const Vector3& uniformData, const char* uniformName) const;

  void setUniform(const Vector4& uniformData, const char* uniformName) const;

  void setUniform(int uniformData, const char* uniformName) const;

  void setUniform(float uniformData, const char* uniformName) const;

  void setTexture(unsigned int textureId, const char* uniformName);

private:

  void compile(const char* entryPoint, const char* profile, const char* filePath, ID3DBlob** outputBlob);

private:

  static ID3D11Device* device_;
  static ID3D11DeviceContext* context_;

private:

  ID3D11PixelShader* pixelShader_;
  ID3D11VertexShader* vertexShader_;

};

inline void D3DShader::setDevice(ID3D11Device* device, ID3D11DeviceContext* context) {
  context_ = context;
  device_ = device;
}

#endif
