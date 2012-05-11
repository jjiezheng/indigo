#ifndef FontCharacter_H_
#define FontCharacter_H_

#include "renderer/OpenGL.h"
#include "renderer/SceneNode.h"

class FontCharacterInfo;

class FontCharacter : public SceneNode {
  
public:
  
  static 
  FontCharacter* character(FontCharacterInfo* characterInfo);
  
public:
  
  Rect boundingBox() const;
  
public:
  
  void render(Shader *shader) const;
  
private:
  
  void init(FontCharacterInfo* characterInfo);
    
private:
  
  FontCharacter() { };
  
private:
  
  GLuint vertexArray_;
  GLuint vertexBuffer_;
  GLuint uvBuffer_;
  Rect boundingBox_;
  
};

#endif
