#include "Box.h"

#include "platform/MacPlatform.h"
#include "resource/ResourceCache.h"

#include "OpenGL.h"
#include "Shader.h"
#include "ShaderAttribs.h"
#include "Renderer.h"

static const int VERTEX_SIZE = 3;
static const int VERTEX_LENGTH = 18;

Box* Box::box() {
  Box* box = new Box();
  box->init();
  return box;
}

void Box::init() {
  GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
  };
  
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);
  
  glGenBuffers(1, &vertexBuffer);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH * sizeof(float), &vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(ATTRIB_VERTEX, VERTEX_SIZE, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  
  glBindVertexArray(0);
  
  {
    ShaderResource* resource = ResourceCache::instance()->load_shader("vmvp.vsh", "f.fsh");
    
    shader_.compile_vertex(resource->vertex_source());
    shader_.compile_fragment(resource->fragment_source());
    
    shader_.bind_attribute(ATTRIB_VERTEX, "vertex");
    
    shader_.link();    
    
    shader_.add_uniform("model");
    shader_.add_uniform("view");
    shader_.add_uniform("projection");    
  }
}

void Box::queueRender(Renderer* renderer) {
}

void Box::render() const {
  shader_.use();
  glBindVertexArray(vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, 6);   
}
