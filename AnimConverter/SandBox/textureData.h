//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#include "textureData.pb.h"

class textureData
{
public:
	static const unsigned int FILE_NAME_SIZE = 64;

public:
	enum class TEXTURE_EFORMAT
	{
		EFORMAT_BGR = 0,
		EFORMAT_RGB = 1,
		EFORMAT_RGBA = 2,
		EFORMAT_BGRA = 3,
		DEFAULT = EFORMAT_RGBA
	};

	enum class TEXTURE_NCOMPONENT
	{
		NCOMPONENT_BGR = 0,
		NCOMPONENT_RGB = 1,
		NCOMPONENT_RGBA = 2,
		NCOMPONENT_BGRA = 3,
		DEFAULT = NCOMPONENT_RGBA
	};

	enum class TEXTURE_TYPE
	{
		JPEG = 0,
		PNG,
		BMP,
		GIF,
		TGA,
		DEFAULT = PNG
	};

	enum class TEXTURE_MAG_FILTER
	{
		MAG_NEAREST = 0,
		MAG_LINEAR = 1,
		DEFAULT = MAG_LINEAR
	};

	enum class TEXTURE_MIN_FILTER
	{
		MIN_NEAREST = 0,
		MIN_LINEAR,
		MIN_NEAREST_MIPMAP_NEAREST,
		MIN_LINEAR_MIPMAP_NEAREST,
		MIN_NEAREST_MIPMAP_LINEAR,
		MIN_LINEAR_MIPMAP_LINEAR,
		DEFAULT = MIN_LINEAR
	};

	enum class TEXTURE_WRAP
	{
		WRAP_CLAMP_TO_EDGE = 0,
		WRAP_MIRRORED_REPEAT,
		WRAP_REPEAT,
		DEFAULT = WRAP_CLAMP_TO_EDGE
	};

	enum class TEXTURE_PIXEL_TYPE
	{
		BYTE = 0,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		FLOAT,
		DOUBLE,
		DEFAULT = UNSIGNED_BYTE
	};

public:
	textureData();
	textureData(const textureData &);
	textureData &operator = (const textureData &);
	~textureData();

	textureData(    bool				_enabled,
					TEXTURE_TYPE        textType,
					TEXTURE_MAG_FILTER  magFilter,
					TEXTURE_MIN_FILTER  minFilter,
					TEXTURE_WRAP        wrapS,
					TEXTURE_WRAP        wrapT,
					TEXTURE_PIXEL_TYPE	pixelType,
					TEXTURE_EFORMAT		eFormat,
					TEXTURE_NCOMPONENT	nComponent,
					unsigned int		width,
					unsigned int		height,
					unsigned int		component,
					unsigned int		bits,
					bool				as_is,
					const char			*pFileName,
					unsigned int		dataSize,
					unsigned int		_hash,
					unsigned char		*poData);

	// Serialization 
	void Serialize(textureData_proto &out) const;
	void Deserialize(const textureData_proto &in);

	void Print(const char *const pName) const;
	void Print(const char* const pName, const int _count) const;

public:
	bool				enabled;
	TEXTURE_TYPE        textType;
	TEXTURE_MAG_FILTER  magFilter;
	TEXTURE_MIN_FILTER  minFilter;
	TEXTURE_WRAP        wrapS;
	TEXTURE_WRAP        wrapT;
	TEXTURE_PIXEL_TYPE	pixel_type;

	TEXTURE_EFORMAT		eFormat;
	TEXTURE_NCOMPONENT	nComponent;

	unsigned int		width;
	unsigned int		height;

	unsigned int		component; //bits per channel: //1 = grey / 2 = grey, alpha / 3 = red, green, blue / 4 = red, green blue, alpha
	unsigned int		bits; //bits per channel 8, 16, 32 per color
	bool				as_is;
	char                pFileName[FILE_NAME_SIZE];
	unsigned int        dataSize;
	unsigned int		hash;
	unsigned char      *poData;

};

#endif

// --- End of File ---
