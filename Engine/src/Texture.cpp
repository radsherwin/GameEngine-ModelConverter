//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Texture.h"

#include <array>

#include "StringThis.h"

Texture::Texture()
	: name(Name::NOT_INITIALIZED),
	textureID(0),
	minFilter(0),
	magFilter(0),
	wrapModeS(0),
	wrapModeT(0)
{
	this->assetName.resize(1);
	minFilter.push_back((GLenum)GL_LINEAR);
	magFilter.push_back((GLenum)GL_LINEAR);
	wrapModeS.push_back((GLenum)GL_CLAMP_TO_EDGE);
	wrapModeT.push_back((GLenum)GL_CLAMP_TO_EDGE);
}


Texture::~Texture()
{
	delete[] textureID;
}


void Texture::Set(const char* const _assetName,
	Name _name,
	GLuint* _TextureID,
	GLenum _minFilter,
	GLenum _magFilter,
	GLenum _wrapModeS,
	GLenum _wrapModeT)
{
	
	this->name = _name;
	this->magFilter.push_back(_magFilter);
	this->minFilter.push_back(_minFilter);
	this->wrapModeS.push_back(_wrapModeS);
	this->wrapModeT.push_back(_wrapModeT);
	this->textureID = _TextureID;
	this->assetName.resize(this->magFilter.size());
	memcpy(this->assetName.at(this->magFilter.size()-1).data(), _assetName, TEXTURE_ASSET_NAME_SIZE - 1);
}

bool Texture::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Texture* pDataB = (Texture*)pTarget;

	bool status = false;

	if (this->name == pDataB->name)
	{
		status = true;
	}

	return status;
}

void Texture::Dump()
{
	Trace::out("      Texture(%p)\n", this);

	// Data:
	Trace::out("      Name: %s \n", StringMe(this->name));
	
	//Trace::out("         x: %d \n", this->x);

	DLink::Dump();
}

void Texture::Wash()
{

}

char* Texture::GetName()
{
	// todo - Hack understand why is this needed for print and fix...
	static char pTmp[128];
	strcpy_s(pTmp, 128, StringMe(this->name));
	return pTmp;
}

// --- End of File ---