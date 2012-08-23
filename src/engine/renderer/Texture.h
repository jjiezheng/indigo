#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {

public:

  static const char* DiffuseTexture;
  
public:
  
  void init(const char* filePath);
  
public:
  
  unsigned int textureId() const;
    
private:
  
  unsigned int textureId_;
};

inline unsigned int Texture::textureId() const {
  return textureId_;
}

#endif
