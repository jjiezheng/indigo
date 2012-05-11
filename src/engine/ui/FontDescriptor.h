#ifndef CubeFX_FontDescriptor_h
#define CubeFX_FontDescriptor_h

#include "core/Standard.h"

struct FontCharacterInfo {
  
  int width;
  int height;
  int x;
  int y;
  int char_id;
  int offset_x;
  int offset_y;
  int sheet_width;
  int sheet_height;
};

class FontDescriptorResource;

class FontDescriptor {
  
public:
  
  static FontDescriptor* descriptor(const char* fontFile);
  
private:
  
  void init(const char* fontFile);
  
private:
  
  FontDescriptor() 
	  ;
  
public:
  
  FontCharacterInfo charInfo(char character);
  
  void addCharInfo(const FontCharacterInfo& char_info);
  
  int width();
  
  int height();
  
  std::string asset();
  
private:
  
  
  std::map<char, FontCharacterInfo> char_info_;
  
  int width_;
  int height_;
  std::string asset_;
  
};

inline
int FontDescriptor::width() {
  return width_;
}

inline
int FontDescriptor::height() {
  return height_;
}

inline
std::string FontDescriptor::asset() {
  return asset_;
}

#endif
