#ifndef TEXTURE_DATA_HELPER_H
#define TEXTURE_DATA_HELPER_H

#include "textureData.h"
#include "sb7.h"

class textureDataHelper
{
public:
	static GLenum Get(textureData::TEXTURE_WRAP w);
	static GLenum Get(textureData::TEXTURE_MIN_FILTER min);
	static GLenum Get(textureData::TEXTURE_MAG_FILTER mag);
};

#endif
