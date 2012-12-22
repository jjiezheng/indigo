#include "DDSImage.h"

#include <stdio.h>
#include <stdlib.h>

#include "core/String.h"
#include "io/Path.h"
#include "io/dds.h"
#include "io/Endian.h"
#include "platform/PlatformDefs.h"

#include "DDSMipLevel.h"

#ifdef PLATFORM_WINDOWS
  #pragma warning(disable:4996)
#endif

DDSImage::~DDSImage() {
	for (unsigned int i = 0; i < numMipLevels; i++) {
		delete mipLevels[i];
	}
	free(data);
}

void DDSImage::load(const std::string& filePath) {
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

	firstMipWidth = swap_uint32(*(unsigned int*)&(header[12]));
	firstMipHeight = swap_uint32(*(unsigned int*)&(header[8]));
	
	unsigned int linearSize = swap_uint32(*(unsigned int*)&(header[16]));

	numMipLevels = swap_uint32(*(unsigned int*)&(header[24]));
	numMipLevels = numMipLevels ? numMipLevels : 1;

	fourCC = swap_uint32(*(unsigned int*)&(header[80]));

	dataSize = numMipLevels > 1 ? linearSize * 2 : linearSize;

	unsigned int textureDataSize = dataSize * sizeof(unsigned char);
	data = (unsigned char*)malloc(textureDataSize);

	fread(data, 1, dataSize, fp);
	fclose(fp);

	unsigned int blockSize = (fourCC == FOURCC_DXT1) ? 8 : 16;
	unsigned int offset = 0;

	mipLevels = new DDSMipLevel*[numMipLevels];

	unsigned int width = firstMipWidth;
	unsigned int height = firstMipHeight;

	for (unsigned int level = 0; level < numMipLevels && (width || height); ++level) {
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		DDSMipLevel* mipLevel = new DDSMipLevel();
		mipLevel->size = size;
		mipLevel->width = width;
		mipLevel->height = height;
		mipLevel->offset = offset;
		mipLevels[level] = mipLevel;
		totalSize += size;
		offset += size;
		width  /= 2;
		height /= 2;
	}

	dataSize = linearSize;
}