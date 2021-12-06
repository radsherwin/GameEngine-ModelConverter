//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CLIP_H
#define CLIP_H

#include <vector>

#include "Animation.h"
#include "AnimTime.h"
#include "PCSNode.h"
#include "Bone.h"

class Mesh;

namespace Azul
{
	struct FrameBucket;
	class Clip : public PCSNode
	{
	public:
		enum class Name
		{
			WALK = 0,
			DIE_LEFT,
			SHOT_DOWN,
			HIT_RIGHT,
			RUN,
			NULL_CLIP,
			DEFAULT
		};

		struct FrameBucket
		{
			~FrameBucket()
			{
				delete[] poBone;
			}
			FrameBucket* nextBucket;
			FrameBucket* prevBucket;
			AnimTime      KeyTime;
			Bone* poBone;
			char          pad[4];
		};
	public:
		Clip(Clip::Name, int _numBones, Animation* pAnimation[8]);

		Clip();
		Clip(const Clip&) = delete;
		Clip& operator = (const Clip&) = delete;
		virtual ~Clip();

		Name GetClipName() const;
		AnimTime GetTotalTime();
		void AnimateBones(AnimTime tCurr, Bone* pResult);
		static void Print(std::vector<Mesh*> pMesh, int frameIndex);

	private:
		void privSetAnimationData(Animation** pMesh);
		AnimTime privFindMaxTime();
		

	private:
		Name		 name;
		int          numBones;
		int          numFrames;
		AnimTime     TotalTime;
		FrameBucket* poHead;
		Bone* boneData;
	};
}

#endif

//--- End of File ---