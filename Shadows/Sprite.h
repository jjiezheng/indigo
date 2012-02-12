#ifndef Sprite_H_
#define Sprite_H_

#include "SceneNode.h"
#include "Texture.h"

class Sprite : public SceneNode {
  
public:
  
  static Sprite* sprite(const char* filePath);
  
private:
  
  void init(const char* filePath);
  
public:
  
  void render(Camera *camera, Shader *shader, const glm::mat4 &transform) const;
  
  Rectangle boundingBox() const;
  
private:
  
  Sprite() = default;
  
private:
  
  GLuint vertexBuffer_;
  GLuint textureBuffer_;
  
  Texture* texture_;
  
  Rectangle boundingBox_;
  
};

inline 
Rectangle Sprite::boundingBox() const {
  return boundingBox_;
}

#endif
