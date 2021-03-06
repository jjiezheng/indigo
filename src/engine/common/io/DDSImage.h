#ifndef DDSIMAGE_H
#define DDSIMAGE_H

#include <string>

#include "dds.h"
#include "DDSMipLevel.h"

class DDSMipLevel;

class DDSImage {

public:
  
  ~DDSImage();

public:

	DDSImage()
		: numMipLevels(0)
		, data(0)
		, dataSize(0)
		, totalSize(0)
		, fourCC(0)
		, firstMipWidth(0)
		, firstMipHeight(0) { }

  
  void load(const std::string& filePath);
  
public:
  
  unsigned int numMipLevels;  
  DDSMipLevel** mipLevels;
  
  unsigned char* data;
  unsigned int dataSize;
	unsigned int totalSize;
  unsigned int fourCC;
	unsigned int firstMipWidth;
	unsigned int firstMipHeight;
};

#endif
