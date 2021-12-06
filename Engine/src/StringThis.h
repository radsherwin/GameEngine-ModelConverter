//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef STRING_THIS_H
#define STRING_THIS_H

#include "Texture.h"
#include "Mesh.h"
#include "ShaderObject.h"
#include "Camera.h"

using namespace Azul;

class StringThis
{
public:
	static const unsigned int BUFFER_SIZE = 64;
public:

	StringThis(Texture::Name);
	StringThis(Mesh::Name);
	StringThis(ShaderObject::Name);
	StringThis(Camera::ID);

	operator char* ();

	// data:
	char buffer[BUFFER_SIZE];
};

#define StringMe(x)  ((char *)StringThis(x)) 

#endif

// --- End of File ---