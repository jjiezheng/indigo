#include "Box.h"

#include "OpenGL.h"
#include "IEffect.h"
#include "ShaderAttribs.h"

#include "app/Window.h"

static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;
static const int VERTEX_COUNT = 6;

void Box::init() {
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    
    -0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };

  vertexBuffer = Window::createVertexBuffer(vertices, NULL, NULL, VERTEX_LENGTH);
  effect_ = Window::createEffect();
  effect_->load("cgfx/diffuse.cgfx");
}

void Box::render() {
  effect_->beginDraw();
  Window::drawVertexBuffer(vertexBuffer, VERTEX_COUNT);
  effect_->endDraw(); 
}


  /*glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);
  
  glGenBuffers(1, &vertexBuffer);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(ATTRIB_VERTEX, VERTEX_SIZE, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);*/
  
//  glBindVertexArray(0);
  
//  {
//    shader_.load("glsl/v.vsh", "glsl/f.fsh");    
//    shader_.bindAttribute(ATTRIB_VERTEX, "vertex");
//    shader_.link();    
//  }
 // {
    //cgShader_.load("cg/vertex.cg", "cg/fragment_diffuse_flat_green.cg");
//    cgShader_.bindAttribute(ATTRIB_VERTEX, "position");
    //cgShader_.link();    
 // }

  //  shader_.use();
  //cgShader_.use();
  /*glBindVertexArray(vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, 6);*/  