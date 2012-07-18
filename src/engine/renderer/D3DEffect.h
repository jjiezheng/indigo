#ifndef D3DEFFECT_H
#define D3DEFFECT_H

#include "IEffect.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3DX11Effect;
struct ID3DX11EffectPass;
struct ID3D11InputLayout;

class D3DEffect : public IEffect {

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

  void setUniform(const Vector4* uniformData, unsigned int uniformDataCount, const char* uniformName) const;

  void setUniform(int uniformData, const char* uniformName) const;

  void setUniform(float uniformData, const char* uniformName) const;

  void setTexture(unsigned int textureId, const char* uniformName);

private:

  static ID3D11Device* device_;
  static ID3D11DeviceContext* context_;

  ID3DX11Effect* effect_;
  ID3DX11EffectPass* pass_;
  ID3D11InputLayout* layout_;

};

inline void D3DEffect::setDevice(ID3D11Device* device, ID3D11DeviceContext* context) {
  device_ = device;
  context_ = context;
}

#endif
