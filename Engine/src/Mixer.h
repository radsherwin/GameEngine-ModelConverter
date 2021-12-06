//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MIXER_H
#define MIXER_H

#include "AnimTimer.h"
#include "Bone.h"

namespace Azul
{
	class Mixer
	{
	public:
		static void Blend(Bone* pResult,
			const Bone* pA,
			const Bone* pB,
			const float tS,
			const int numBones);
	};
}

#endif

// --- End of File ---