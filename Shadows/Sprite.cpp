#include "Sprite.h"

#include "ShaderAttribs.h"
#include "Texture.h"
#include "TextureCache.h"
#include "Shader.h"

Sprite* Sprite::sprite(const char* filePath) {
  Sprite* sprite = new Sprite();
  sprite->init(filePath);
  return sprite;
}

void Sprite::init(const char *filePath) {
  texture_ = TextureCache::instance()->addTexture(filePath);
  
  float height = texture_->height();
  float width = texture_->width();
  
  boundingBox_.width = width;
  boundingBox_.height = height;
  
  float verts[] = {
    width,  height, 0.0f,
    0.0f,   height, 0.0f,
    0.0f,   0.0f,   0.0f,
    
    0.0f,   0.0f,   0.0f,
    width,  0.0f,   0.0f,
    width,  height, 0.0f,
  };
  
  glGenBuffers(1, &vertexBuffer_);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
  glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), verts, GL_STATIC_DRAW);
}

void Sprite::render(Camera *camera, Shader *shader, const glm::mat4 &transform) const {
  texture_->render(shader);
  
  glm::mat4 finalTransform = glm::translate(transform, position_);
  shader->set_uniform(finalTransform, "model");
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableClientState(GL_VERTEX_ARRAY);
  
  glDisableVertexAttribArray(ATTRIB_VERTEX);
  
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}