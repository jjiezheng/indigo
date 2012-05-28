#ifndef DDSIMAGE_H
#define DDSIMAGE_H

#include <string>

class DDSMipLevel;

class DDSImage {

public:
  
  ~DDSImage();
  
  void load(const std::string& filePath);
  
public:
  
  unsigned int numMipLevels;  
  DDSMipLevel** mipLevels;
  
  unsigned char* data;
  unsigned int dataSize;
  unsigned int fourCC;
  std::string filePath;
};

#endif
