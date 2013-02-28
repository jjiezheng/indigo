#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "core/Size.h"

class IEffect;
class Matrix4x4;

class Sprite {

public:

  Sprite()
    : effect_(NULL) 
  { }

public:

  static Sprite* fromFile(const std::string& spriteFilePath);

public:

  void render(const Matrix4x4& projection, const Matrix4x4& model);

public:

	CSize size() const;

private:

  void init(const std::string& spriteFilePath);

private:

  unsigned int textureId_;
  unsigned int vertexBuffer_;

	CSize size_;

  IEffect* effect_;

};

inline CSize Sprite::size() const {
	return size_;
}

#endif