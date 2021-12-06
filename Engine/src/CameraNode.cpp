//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraNode.h"
#include "Camera.h"

namespace Azul
{
	CameraNode::CameraNode()
	{
		this->poCamera = nullptr;
	}

	CameraNode::~CameraNode()
	{
		delete this->poCamera;
	}

	void CameraNode::set(Camera* pCamera)
	{
		assert(pCamera);
		this->poCamera = pCamera;
	}

}

// --- End of File ---