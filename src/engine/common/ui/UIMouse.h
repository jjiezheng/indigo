#ifndef UI_MOUSE_H
#define UI_MOUSE_H

#include <string>

#include "renderer/Control.h"

class Sprite;

class UIMouse : public Control {

public:

  static UIMouse* mouse(const std::string& cursorPath);

public:

  void render(const Matrix4x4& projection);

  void update(float dt);

private:

  void init(const std::string& cursorPath);

private:

  Sprite* sprite_;

};

#endif