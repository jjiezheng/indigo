#ifndef DDSIMAGE_H
#define DDSIMAGE_H

class DDSMipLevel;

class DDSImage {

public:
  
  ~DDSImage();
  
  void load(const char* filePath);
  
public:
  
  unsigned int numMipLevels;  
  DDSMipLevel** mipLevels;
  
  unsigned char* data;
  unsigned int fourCC;
};

#endif
