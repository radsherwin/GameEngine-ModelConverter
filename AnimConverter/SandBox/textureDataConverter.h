//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef TEXTURE_DATA_CONVERTER_H
#define TEXTURE_DATA_CONVERTER_H

#include "textureData.h"
#include "tiny_gltf.h"

class textureDataConverter
{
public:

	static textureData::TEXTURE_PIXEL_TYPE GetComponent(int GLTF_TINY_VAL);

};

#endif

// --- End of File ---