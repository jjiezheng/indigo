#ifndef CubeFX_Label_h
#define CubeFX_Label_h

#include "SceneNode.h"
#include <vector>
#include "String.h"

class FontDescriptor;
class FontCharacter;
class Texture;

class Renderer;

class Label : public SceneNode {
  
public:
  
  static Label* label(const char* text, const char* fontFile);
  
public:
  
  void setText(const String& text);
  
  void queueRender(Renderer* renderer);
  
  void render(Shader* shader) const;
  
  void renderDebug() const;
  
private:
  
  Label() = default;
  
  void init(const char* fontFile);
  
  String text_;
  
  FontDescriptor* font_;
  Texture* texture_;
        
};

#endif
