#ifndef SKYDOME_H
#define SKYDOME_H

#include "GraphicsInterface.h"
#include <string>

class Matrix4x4;
class Model;

class SkyDome {

public:

  SkyDome()
    : skyTexture(0)
    , skyDomeModel_(0)
    , skyEffect_(0) { }

public:

  void load(const std::string& skyDomeModelPath);

  void render(const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& model);

private:

  GraphicsInterface::TextureId skyTexture;

  Model* skyDomeModel_;
  IEffect* skyEffect_;

};

#endif