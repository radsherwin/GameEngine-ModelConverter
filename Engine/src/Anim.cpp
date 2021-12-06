//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Anim.h"
#include "MathApp.h"
#include "Mixer.h"
#include "Clip.h"
#include "Skeleton.h"

namespace Azul
{
	Anim::Anim(Clip* pClip, Skeleton* pSkel)
		: pClip(nullptr),
		pBoneResult(pSkel->BoneResult()),
		numBones(NUM_BONES)
	{
		
		this->pClip = pClip;
		assert(pClip);
	}

	Anim::~Anim()
	{
	}

	AnimTime Anim::FindMaxTime()
	{
		assert(pClip);
		return this->pClip->GetTotalTime();
	}

	void Anim::Animate(AnimTime tCurr)
	{
		this->pClip->AnimateBones(tCurr, this->pBoneResult);
	}

	void Anim::PoseSkeleton(GameObjectAnimSkeleton* node)
	{
		// safety
		assert(node);

		// Now get the world matrices
		GameObjectAnimSkeleton* childNode = (GameObjectAnimSkeleton*)node->GetChild();
		GameObjectAnimSkeleton* parentNode = node;

		// Normal.. valid child
		if (parentNode != nullptr && childNode != nullptr)
		{
			// starting point
			Vect start(0.0f, 0.0f, 0.0f);

			//  At this point, Find the two bones initial positions in world space
			//  Now get the length and directions
			Vect ptA = start * *parentNode->GetWorld();
			Vect ptB = start * *childNode->GetWorld();

			// direction between the anchor points of the respective bones
			Vect dir = ptB - ptA;

			// length of the bone 0
			float mag = dir.mag();

			Matrix S(Matrix::Scale::XYZ, 1, 1, mag);
			Quat Q(Quat::Orient::LocalToWorld, dir.getNorm(), Vect(0.0f, 1.0f, 0.0f));
			Matrix T(Matrix::Trans::XYZ, ptA);
			Matrix BoneOrient = S * Q * T;
			parentNode->SetBoneOrientation(BoneOrient);
		}

		// deal with last node, when there isn't a terminal node
		if (parentNode != nullptr && childNode == nullptr)
		{
			// get the parent's parent  -> grandParent
			GameObjectAnimSkin* grandParentNode = (GameObjectAnimSkin*)parentNode->GetParent();
			assert(grandParentNode);
			Vect pTmp1 = Vect(0, 0, 0) * *grandParentNode->GetWorld();
			Vect pTmp2 = Vect(0, 0, 0) * *parentNode->GetWorld();
			Vect dir = pTmp2 - pTmp1;
			float mag = dir.mag();

			Vect pTmp3 = Vect(0, 0, 0) * *parentNode->GetWorld();
			Vect pTmp4 = Vect(1, 0, 0) * *parentNode->GetWorld();
			dir = pTmp4 - pTmp3;

			Matrix S(Matrix::Scale::XYZ, 1.0f, 1.0f, 0.1f * mag);
			Matrix R(Matrix::Orient::LocalToWorld, dir.getNorm(), Vect(0.0f, 1.0f, 0.0f));
			Matrix T(Matrix::Trans::XYZ, pTmp2);

			Matrix mTmp = S * R * T;
			parentNode->SetBoneOrientation(mTmp);
		}
	}
}

//--- End of File ----