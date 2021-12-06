//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Bone.h"
#include "Texture.h"
#include "PCSNode.h"

using namespace Azul;

class Animation : public PCSNode
{
public:
	Animation();
	Animation(Animation& copyMesh) = delete;
	Animation& operator = (Animation& copyMesh) = delete;
	virtual ~Animation();

public:
	std::vector<Bone> meshBone;
	std::string protoName;
	int frames;
	int joint;
	int parent;

};
#endif

// --- End of File ---