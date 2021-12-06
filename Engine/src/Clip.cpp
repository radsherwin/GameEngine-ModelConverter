//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Clip.h"
#include "Mixer.h"
#include "MeshNodeManager.h"

namespace Azul
{
	Clip::Clip(Clip::Name clipName, int _numBones, Animation** pAnimation)
		: name(clipName),
		numBones(_numBones),
		numFrames(0),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr)
	{
		this->privSetAnimationData(pAnimation);
		this->TotalTime = this->privFindMaxTime();
	}

	Clip::Clip()
		: name(Clip::Name::NULL_CLIP),
		numBones(0),
		numFrames(0),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr)
	{
	}

	Clip::~Clip()
	{
		FrameBucket* pTmp = poHead;

		while (pTmp != nullptr)
		{
			FrameBucket* pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}
	}

	Clip::Name Clip::GetClipName() const
	{
		return this->name;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket* pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}

	void Clip::AnimateBones(AnimTime tCurr, Bone* pResult)
	{
		// First one
		FrameBucket* pTmp = this->poHead;

		// Find which key frames
		while (tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket* pA = pTmp->prevBucket;
		FrameBucket* pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->numBones);
	}

	void Clip::Print(std::vector<Mesh*> pMesh, int frameIndex)
	{
		Bone bone;
		int joint;
		Trace::out("------------CLIP.CPP------------\n");

		for (size_t meshIndex = 0; meshIndex < pMesh.size(); meshIndex++)
		{
			bone = pMesh[meshIndex]->pAnim->meshBone[frameIndex];
			joint = pMesh[meshIndex]->pAnim->joint;

			Trace::out("KeyFrame: %d\n", frameIndex);
			Trace::out("Joint name: %s, joint index: %d\n", pMesh[meshIndex]->pAnim->protoName.c_str(), joint);
			Trace::out("T[%d]: %f %f %f\n", joint, bone.T.x(), bone.T.y(), bone.T.z());
			Trace::out("Q[%d]: %f %f %f %f\n", joint, bone.Q.qx(), bone.Q.qy(), bone.Q.qz(), bone.Q.real());
			Trace::out("S[%d]: %f %f %f\n", joint, bone.S.x(), bone.S.y(), bone.S.z());
		}
	}

	float scale = 1.0f;
	void Clip::privSetAnimationData(Animation** pAnimation)
	{
		// --------  Result Frame  ----------------------

		FrameBucket* pTmp;

		FrameBucket* pPrev = nullptr;

		this->numFrames = pAnimation[0]->frames;

		// --------  Frame 0  ----------------------------
		//pBone_Mesh->frames
		for (int frameIndex = 0; frameIndex < numFrames; frameIndex++)
		{
			FrameBucket* pTmp0 = new FrameBucket();
			pTmp0->prevBucket = pPrev;
			pTmp0->nextBucket = nullptr;
			pTmp0->KeyTime = frameIndex * AnimTime(AnimTime::Duration::FILM_24_FRAME);
			pTmp0->poBone = new Bone[(unsigned int)this->numBones];
			if (pPrev == nullptr) this->poHead = pTmp0;
			else pPrev->nextBucket = pTmp0;

			pTmp = pTmp0;
			pPrev = pTmp0;

			pTmp->poBone[0].T = Vect(0.0f, 0.0f, 0.0f);         // Padding avoids remapping
			pTmp->poBone[0].Q = Quat(0.0f, 0.0f, 0.0f, 1.0f);   // Padding avoids remapping
			pTmp->poBone[0].S = Vect(1.0f, 1.0f, 1.0f);         // Padding avoids remapping

			pTmp->poBone[1].T = Vect(0.0f, 0.0f, 0.0f);         // Padding avoids remapping
			pTmp->poBone[1].Q = Quat(0.0f, 0.0f, 0.0f, 1.0f);	// Padding avoids remapping
			pTmp->poBone[1].S = Vect(1.0f, 1.0f, 1.0f);			// Padding avoids remapping

			pTmp->poBone[2].T = Vect(0.0f, 0.0f, 0.0f);         // Padding avoids remapping
			pTmp->poBone[2].Q = Quat(0.0f, 0.0f, 0.0f, 1.0f);	// Padding avoids remapping
			pTmp->poBone[2].S = Vect(1.0f, 1.0f, 1.0f);			// Padding avoids remapping

			pTmp->poBone[3].T = Vect(0.0f, 0.0f, 0.0f);         // Padding avoids remapping
			pTmp->poBone[3].Q = Quat(0.0f, 0.0f, 0.0f, 1.0f);	// Padding avoids remapping
			pTmp->poBone[3].S = Vect(1.0f, 1.0f, 1.0f);			// Padding avoids remapping

			pTmp->poBone[4] = pAnimation[0]->meshBone[frameIndex];
			pTmp->poBone[4].S = scale * pTmp->poBone[4].S;
			pTmp->poBone[5] = pAnimation[1]->meshBone[frameIndex];
			pTmp->poBone[6] = pAnimation[2]->meshBone[frameIndex];
			pTmp->poBone[7] = pAnimation[3]->meshBone[frameIndex];
			pTmp->poBone[8] = pAnimation[4]->meshBone[frameIndex];
			pTmp->poBone[9] = pAnimation[5]->meshBone[frameIndex];
			pTmp->poBone[10] = pAnimation[6]->meshBone[frameIndex];
			pTmp->poBone[11] = pAnimation[7]->meshBone[frameIndex];
		}
	}
}

// --- End of File ---