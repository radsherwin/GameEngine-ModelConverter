#include "textureDataHelper.h"

GLenum textureDataHelper::Get(textureData::TEXTURE_WRAP w)
{
	GLenum res;
	switch(w)
	{
		case textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE:
			res = GL_CLAMP_TO_EDGE;
			break;
		case textureData::TEXTURE_WRAP::WRAP_MIRRORED_REPEAT:
			res = GL_MIRRORED_REPEAT;
			break;
		case textureData::TEXTURE_WRAP::WRAP_REPEAT:
			res = GL_REPEAT;
			break;
		default:
			assert(false);
			res = GL_CLAMP_TO_EDGE;
	}

	return res;
}

GLenum textureDataHelper::Get(textureData::TEXTURE_MIN_FILTER min)
{
	GLenum res;

	switch (min)
	{
		case textureData::TEXTURE_MIN_FILTER::MIN_NEAREST:
			res = GL_NEAREST;
			break;

		case textureData::TEXTURE_MIN_FILTER::MIN_LINEAR:
			res = GL_LINEAR;
			break;

		case textureData::TEXTURE_MIN_FILTER::MIN_NEAREST_MIPMAP_NEAREST:
			res = GL_NEAREST_MIPMAP_NEAREST;
			break;

		case textureData::TEXTURE_MIN_FILTER::MIN_LINEAR_MIPMAP_NEAREST:
			res = GL_LINEAR_MIPMAP_NEAREST;
			break;

		case textureData::TEXTURE_MIN_FILTER::MIN_NEAREST_MIPMAP_LINEAR:
			res = GL_NEAREST_MIPMAP_LINEAR;
			break;

		case textureData::TEXTURE_MIN_FILTER::MIN_LINEAR_MIPMAP_LINEAR:
			res = GL_LINEAR_MIPMAP_LINEAR;
			break;

		default:
			res = GL_LINEAR;
			break;
	}

	return res;
}

GLenum textureDataHelper::Get(textureData::TEXTURE_MAG_FILTER mag)
{
	GLenum res;

	switch (mag)
	{
		case textureData::TEXTURE_MAG_FILTER::MAG_NEAREST:
			res = GL_NEAREST;
			break;

		case textureData::TEXTURE_MAG_FILTER::MAG_LINEAR:
			res = GL_LINEAR;
			break;

		default:
			res = GL_LINEAR;
			break;
	}

	return res;
}
