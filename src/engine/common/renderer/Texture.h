#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {

public:

  Texture() 
    : textureId_(0) { }

public:

  static const char* DiffuseTexture;
  
public:
  
  void init(const std::string& filePath);
  
public:
  
  unsigned int textureId() const;

	void setTextureId(unsigned int textureId);
    
private:
  
  unsigned int textureId_;
};

inline unsigned int Texture::textureId() const {
  return textureId_;
}

inline void Texture::setTextureId(unsigned int textureId) {
	textureId_ = textureId;
}

#endif
