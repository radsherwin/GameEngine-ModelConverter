//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"



StringThis::StringThis(Texture::Name status)
{
	switch (status)
	{
	case Texture::Name::STONES:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::STONES));
		break;

	case Texture::Name::BONE_2:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::STONES));
		break;

	case Texture::Name::CHICKEN_BOT:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CHICKEN_BOT));
		break;

	case Texture::Name::RED_BRICK:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::RED_BRICK));
		break;

	case Texture::Name::DUCKWEED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::DUCKWEED));
		break;

	case Texture::Name::ROCKS:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::ROCKS));
		break;

	case Texture::Name::CRATE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CRATE));
		break;

	case Texture::Name::DOG_HOUSE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::DOG_HOUSE));
		break;

	case Texture::Name::AVOCADO:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::AVOCADO));
		break;

	case Texture::Name::BARRAMUNDI:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::BARRAMUNDI));
		break;

	case Texture::Name::SNOWMAN:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::SNOWMAN));
		break;

	case Texture::Name::ANTIQUE_CAMERA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::ANTIQUE_CAMERA));
		break;

	case Texture::Name::WATCH_TOWER:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::WATCH_TOWER));
		break;

	case Texture::Name::R2_D2:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::R2_D2));
		break;

	case Texture::Name::CORSET:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CORSET));
		break;

	case Texture::Name::POKE_BALL:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::POKE_BALL));
		break;

	case Texture::Name::BUGGY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::BUGGY));
		break;

	case Texture::Name::SPACE_FRIGATE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::SPACE_FRIGATE));
		break;

	case Texture::Name::PINK_ERROR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::PINK_ERROR));
		break;

	case Texture::Name::PROTO_LOAD:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::PROTO_LOAD));
		break;

	case Texture::Name::NOT_INITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::NOT_INITIALIZED));
		break;

	default:
		assert(false);
	}
}


StringThis::StringThis(Mesh::Name status)
{
	switch (status)
	{
	case Mesh::Name::CUBE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CUBE));
		break;

	case Mesh::Name::CRATE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CRATE));
		break;

	case Mesh::Name::PYRAMID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::PYRAMID));
		break;

	case Mesh::Name::CHICKEN_BOT:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CHICKEN_BOT));
		break;

	case Mesh::Name::BONE_A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_A));
		break;

	case Mesh::Name::BONE_B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_B));
		break;

	case Mesh::Name::BONE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE));
		break;

	case Mesh::Name::BONE_L:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_L));
		break;

	case Mesh::Name::BONE_L_001:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_L_001));
		break;

	case Mesh::Name::BONE_L_002:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_L_002));
		break;

	case Mesh::Name::BONE_R:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_R));
		break;

	case Mesh::Name::BONE_R_001:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_R_001));
		break;

	case Mesh::Name::BONE_R_002:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_R_002));
		break;

	case Mesh::Name::BONE_01:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_01));
		break;

	case Mesh::Name::SNOWMAN:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SNOWMAN));
		break;

	case Mesh::Name::SPACE_FRIGATE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPACE_FRIGATE));
		break;

	case Mesh::Name::POKE_BALL:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::POKE_BALL));
		break;

	case Mesh::Name::NOT_INITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NOT_INITIALIZED));
		break;

	case Mesh::Name::CAMERA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CAMERA));
		break;

	case Mesh::Name::SPHERE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPHERE));
		break;

	case Mesh::Name::NULL_MESH:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NULL_MESH));
		break;

	default:
		assert(false);
	}
}



StringThis::StringThis(ShaderObject::Name status)
{
	switch (status)
	{
	case ShaderObject::Name::NULL_SHADER:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::NULL_SHADER));
		break;

	case ShaderObject::Name::COLOR_POSITION:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COLOR_POSITION));
		break;

	case ShaderObject::Name::TEXTURE_SIMPLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::TEXTURE_SIMPLE));
		break;

	case ShaderObject::Name::TEXTURE_POINT_LIGHT:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::TEXTURE_POINT_LIGHT));
		break;

	case ShaderObject::Name::CONST_COLOR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::CONST_COLOR));
		break;

	case ShaderObject::Name::COLOR_SINGLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COLOR_SINGLE));
		break;

	case ShaderObject::Name::SPEC_LIGHTING:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::SPEC_LIGHTING));
		break;

	case ShaderObject::Name::UNINITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::UNINITIALIZED));
		break;

	default:
		assert(false);
	}
}

StringThis::StringThis(Camera::ID cameraID)
{
	switch (cameraID)
	{
	case Camera::ID::MAIN:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::MAIN));
		break;

	case Camera::ID::TOP:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::TOP));
		break;

	case Camera::ID::FORWARD:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::FORWARD));
		break;

	case Camera::ID::SIDE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::SIDE));
		break;

	case Camera::ID::NOT_INITIALIZED:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::NOT_INITIALIZED));
		break;

	default:
		assert(false);
	}
}


StringThis::operator char* ()
{
	return this->buffer;
}

// --- End of File ---