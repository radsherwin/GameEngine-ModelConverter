//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "textureDataConverter.h"

textureData::TEXTURE_PIXEL_TYPE textureDataConverter::GetComponent(int GLTF_TINY_VAL)
{
	textureData::TEXTURE_PIXEL_TYPE vboComponent;

	switch (GLTF_TINY_VAL)
	{

	case TINYGLTF_COMPONENT_TYPE_BYTE:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::BYTE;
		break;

	case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::BYTE;
		break;

	case TINYGLTF_COMPONENT_TYPE_SHORT:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::UNSIGNED_SHORT;
		break;

	case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::UNSIGNED_SHORT;
		break;

	case TINYGLTF_COMPONENT_TYPE_INT:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::INT;
		break;

	case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::UNSIGNED_INT;
		break;

	case TINYGLTF_COMPONENT_TYPE_FLOAT:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::FLOAT;
		break;

	case TINYGLTF_COMPONENT_TYPE_DOUBLE:
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::DOUBLE;
		break;

	default:
		assert(false);
		vboComponent = textureData::TEXTURE_PIXEL_TYPE::DEFAULT;
		break;

	}

	return vboComponent;
}

// --- End of File ---

