#include "DDSImage.h"

#include <stdio.h>

#include "core/String.h"
#include "io/Path.h"
#include "io/dds.h"
#include "DDSMipLevel.h"

#pragma warning(disable:4996) 

DDSImage::~DDSImage() {
  for (unsigned int i = 0; i < numMipLevels; i++) {
    delete mipLevels[i];
  }
  free(data);
}

void DDSImage::load(const std::string& filePath) {
  this->filePath = filePath;
  unsigned char header[124];
  
  FILE *fp = fopen(filePath.c_str(), "rb");
  if (fp == NULL) {
    LOG(LOG_CHANNEL_IO, "Failed to load %s", filePath.c_str());
    return;
  }
  
  char filecode[4];
  fread(filecode, 1, 4, fp);
  if (strncmp(filecode, "DDS ", 4) != 0) {
    fclose(fp);
    return;
  }
  
  fread(&header, 124, 1, fp); 
  
  unsigned int height = *(unsigned int*)&(header[8 ]);
  unsigned int width = *(unsigned int*)&(header[12]);
  unsigned int linearSize = *(unsigned int*)&(header[16]);
  
  numMipLevels = *(unsigned int*)&(header[24]);
  fourCC = *(unsigned int*)&(header[80]);
  
  dataSize = numMipLevels > 1 ? linearSize * 2 : linearSize;
  data = (unsigned char*)malloc(dataSize * sizeof(unsigned char));
  
  fread(data, 1, dataSize, fp);
  fclose(fp);
  
  unsigned int blockSize = (fourCC == FOURCC_DXT1) ? 8 : 16;
  unsigned int offset = 0;
  
  mipLevels = new DDSMipLevel*[numMipLevels];
  
  for (unsigned int level = 0; level < numMipLevels && (width || height); ++level) {
    unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
    DDSMipLevel* mipLevel = new DDSMipLevel();
    mipLevel->size = size;
    mipLevel->width = width;
    mipLevel->height = height;
    mipLevel->offset = offset;
    mipLevels[level] = mipLevel;
    offset += size;
    width  /= 2;
    height /= 2;
  }

  dataSize = linearSize;
}