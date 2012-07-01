#include "Box.h"

#include "IEffect.h"

#include "GraphicsInterface.h"
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

/*  vertexBuffer = GraphicsInterface::createVertexBuffer(vertices, NULL, NULL, VERTEX_LENGTH);
  effect_ = GraphicsInterface::createEffect();
  std::string fullEffectPath = Path::pathForFile("cgfx/simple.cgfx");
  effect_->load(fullEffectPath);*/
}

void Box::render() {
  effect_->beginDraw();
  GraphicsInterface::drawVertexBuffer(vertexBuffer, VERTEX_COUNT);
  effect_->resetStates(); 
}