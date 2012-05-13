#ifndef Sprite_H_
#define Sprite_H_

#include "renderer/SceneNode.h"
#include "renderer/Texture.h"

class Sprite : public SceneNode {
  
public:
  
  static Sprite* sprite(const char* filePath);
  
private:
  
  void init(const char* filePath);
  
public:
  
  void render(Camera *camera, Shader *shader, const glm::mat4 &transform) const;
  
  Rect boundingBox() const;
  
private:
  
  Sprite() { };
  
private:
  
  GLuint vertexBuffer_;
  GLuint textureBuffer_;
  
  Texture* texture_;
  
  Rect boundingBox_;
  
};

inline 
Rect Sprite::boundingBox() const {
  return boundingBox_;
}

#endif
