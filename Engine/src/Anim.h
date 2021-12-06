//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"

namespace Azul
{
	class Skeleton;
	class Clip;
#define NUM_BONES 12
	

	class Anim
	{
	public:
		Anim(Clip* pClip, Skeleton* pSkel);
		Anim() = default;
		Anim(const Anim&) = delete;
		Anim& operator=(const Anim&) = delete;
		~Anim();

		void Animate(AnimTime tCurr);
		AnimTime FindMaxTime();
		static void PoseSkeleton(GameObjectAnimSkeleton* node);
		Clip* pClip;
	private:
		
		Bone* pBoneResult;
		int numBones;
	};
}

#endif

// --- End of File ---