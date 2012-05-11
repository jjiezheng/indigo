#ifndef TextureCache_H_
#define TextureCache_H_

#include <map>

class Texture;

class TextureCache {
  
public:
  
  static
  TextureCache* instance();
  
public:
  
  Texture* addTexture(const char* filePath);
  
private:
  
  TextureCache() { };
  
private:
  
  std::map<const char*, Texture*> textures_;
  
};

#endif
