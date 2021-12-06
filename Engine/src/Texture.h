//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>

#include "sb7.h"
#include "DLink.h"

class Texture : public DLink
{
public:
	static const unsigned int TEXTURE_ASSET_NAME_SIZE = 64;

public:
	enum class Name
	{
		NOT_INITIALIZED,
		STONES,
		BONE_2,
		RED_BRICK,
		CHICKEN_BOT,
		DUCKWEED,
		ROCKS,
		CRATE,
		AVOCADO,
		BARRAMUNDI,
		DOG_HOUSE,
		SNOWMAN,
		ANTIQUE_CAMERA,
		WATCH_TOWER,
		R2_D2,
		CORSET,
		POKE_BALL,
		BUGGY,
		SPACE_FRIGATE,
		PINK_ERROR,
		PROTO_LOAD
		
	};

public:
	Texture();
	Texture(const Texture&) = default;
	Texture& operator=(const Texture&) = default;
	virtual ~Texture() override;

	void Set(const char* const _assetName,
		Name _name,
		GLuint* _TextureID,
		GLenum minFilter,
		GLenum magFilter,
		GLenum wrapModeS,
		GLenum wrapModeT);


	virtual char* GetName() override;
	virtual bool Compare(DLink* pTarget) override;
	virtual void Dump() override;
	virtual void Wash() override;

private:
	//char assetName[TEXTURE_ASSET_NAME_SIZE];
	std::vector<std::array<char, TEXTURE_ASSET_NAME_SIZE>> assetName;

public:
	Name name;
	GLuint* textureID;
	std::vector<GLenum> minFilter;
	std::vector<GLenum> magFilter;
	std::vector<GLenum> wrapModeS;
	std::vector<GLenum> wrapModeT;
};

#endif
