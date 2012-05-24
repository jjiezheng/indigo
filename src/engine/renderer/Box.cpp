#include "Box.h"

#include "IEffect.h"
#include "ShaderAttribs.h"

#include "app/Window.h"
#include "io/Path.h"

static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;
static const int VERTEX_COUNT = 6;

void Box::init() {
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,

    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };
/*  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    
    -0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };*/

  vertexBuffer = Window::createVertexBuffer(vertices, NULL, NULL, VERTEX_LENGTH);
  effect_ = Window::createEffect();
  std::string fullEffectPath = Path::pathForFile("cgfx/simple.cgfx");
  effect_->load(fullEffectPath);
}

void Box::render() {
  effect_->beginDraw();
  Window::setPass(effect_->pass());
  Window::drawVertexBuffer(vertexBuffer, VERTEX_COUNT);
  effect_->endDraw(); 
}