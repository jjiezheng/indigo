#ifndef SPRITE_H
#define SPRITE_H

#include <string>

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

  void render(const Matrix4x4& projection);

private:

  void init(const std::string& spriteFilePath);

private:

  unsigned int textureId_;
  unsigned int vertexBuffer_;

  IEffect* effect_;

};

#endif