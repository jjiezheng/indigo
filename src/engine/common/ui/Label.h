#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include <vector>

#include "renderer/Font.h"
#include "renderer/IGraphicsInterface.h"

class IEffect;
class Matrix4x4;

class Label {

public:

  Label()
    : labelEffect_(NULL)
    , lastDeltaTime_(1.0f/60.0f)
    , isDirty_(false) { };

public:

  static Label* labelWithFont(const std::string& fontFilePath);

private:

  void init();

public:

  void setText(const std::string& text);

public:

  void setPosition(int x, int y);

public:

  void render(const Matrix4x4& projection);

private:

  void loadFont(const std::string& fontFilePath);

private:

  IEffect* labelEffect_;
  
private:
  
  FrameBuffer labelFrameBuffer_;
  RenderTarget labelRenderTarget_;
  TextureId labelTexture_;
  VertexBuffer labelVertexBuffer_;

private:

  Font font_;

  std::vector<FontCharacter> characters_;
  std::vector<unsigned int> vertexBuffers_;
  
  CSize textureSize_;
  float lastDeltaTime_;
  bool isDirty_;

  std::string text_;

  int x_;
  int y_;

};

inline void Label::setPosition(int x, int y) {
  x_ = x;
  y_ = y;
}

#endif