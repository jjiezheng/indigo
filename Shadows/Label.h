#ifndef CubeFX_Label_h
#define CubeFX_Label_h

#include "SceneNode.h"
#include <vector>

class FontDescriptor;
class FontCharacter;
class Texture;

class Label : public SceneNode {
  
public:
  
  static Label* label(const char* text, const char* fontFile);
  
public:
  
  void setText(const char* text);
  
  void render(Camera* camera, Shader* shader, const Matrix4x4& transform) const;
  
private:
  
  Label() = default;
  
  void init(const char* fontFile);
  
  std::string text_;
  std::vector<FontCharacter*> characters_;
  
  FontDescriptor* font_;
  Texture* texture_;
        
};

#endif
