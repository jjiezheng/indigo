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
  
  {
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
  
  {
    float uvs[] = {
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
    };
    
    glGenBuffers(1, &textureBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer_);
    glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(float), uvs, GL_STATIC_DRAW);
  }
}

void Sprite::render(Camera *camera, Shader *shader, const glm::mat4 &transform) const {
  if (!isVisible_) return;
  texture_->render(shader);
  
  glm::mat4 finalTransform = glm::translate(transform, position_);
  shader->set_uniform(finalTransform, "model");
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer_);
  glEnableVertexAttribArray(ATTRIB_UV);
  glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisableVertexAttribArray(ATTRIB_VERTEX);
  
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}
