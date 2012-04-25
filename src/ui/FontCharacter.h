#ifndef FontCharacter_H_
#define FontCharacter_H_

#include "SceneNode.h"

class FontCharacterInfo;

class FontCharacter : public SceneNode {
  
public:
  
  static 
  FontCharacter* character(FontCharacterInfo* characterInfo);
  
public:
  
  Rectangle boundingBox() const;
  
public:
  
  void render(Shader *shader) const;
  
private:
  
  void init(FontCharacterInfo* characterInfo);
    
private:
  
  FontCharacter() = default;
  
private:
  
  GLuint vertexArray_;
  GLuint vertexBuffer_;
  GLuint uvBuffer_;
  Rectangle boundingBox_;
  
};

#endif
