//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SKELETON_H
#define SKELETON_H

#include "GameObjectAnim.h"
#include "GameObjectBasic.h"

namespace Azul
{
	struct Bone;

	class Skeleton
	{
	public:
		struct Data
		{
			int index;
			int parentIndex;
			char name[64];
		};

	public:
		Skeleton(Mesh** SkeletonMesh, int numBones);

		Skeleton() = delete;
		Skeleton(const Skeleton&) = delete;
		Skeleton& operator = (const Skeleton&) = delete;
		~Skeleton();

		GameObjectAnim* GetFirstBone();
		Bone* BoneResult();

		void Show();
		void Hide();
		void SetPos(float x, float y, float z) const;

	private:
		void privSetAnimationHierarchy(Mesh** SkeletonMesh, Bone* pBoneResult);
		GameObjectAnim* privFindBoneByIndex(int index);

	private:
		GameObjectAnim* pFirstBone;
		GameObjectBasic* pPivot;
		Bone*			poBoneResult;
		int             numBones;
	};
}

#endif

// --- End of File ---