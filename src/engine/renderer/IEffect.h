#ifndef IEFFECT_H
#define IEFFECT_H

#include <string>
#include <vector>
#include <CG/cg.h>

class Matrix4x4;
class Matrix3x3;
class Color3;
class Color4;
class Vector2;
class Vector3;
class Vector4;

class IEffect {

public:

  IEffect()
    : activePassId_(0) { };

public:

  static IEffect* effectFromFile(const std::string& relativeFilePath);

public:

  void load(const std::string& filePath, const char** args);

  virtual void load(const std::string& filePath) = 0;

public:

  static void onError();

  static void handleError(CGcontext context, CGerror error, void *data);

public:

  virtual void beginDraw();

  virtual void resetStates();

  virtual void activatePass(unsigned int passId);

public:

  virtual void setUniform(const Matrix3x3& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Matrix4x4& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Color3& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector2& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector3& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector4& uniformData, const char* uniformName) const = 0;

  virtual void setUniform(const Vector4* uniformData, unsigned int uniformDataSize, const char* uniformName) const = 0;

  virtual void setUniform(int uniformData, const char* uniformName) const = 0;

  virtual void setUniform(float uniformData, const char* uniformName) const = 0;

  virtual void setTexture(unsigned int textureId, const char* uniformName) = 0;

public:

  unsigned int numPasses() const;

protected:

  static CGcontext context_;
  CGeffect effect_;
  std::vector<CGpass> passes_;
  CGtechnique technique_;
  unsigned int activePassId_;
};

inline unsigned int IEffect::numPasses() const {
  return passes_.size();
}


#endif
