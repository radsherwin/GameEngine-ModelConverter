//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mixer.h"
#include "MathApp.h"

namespace Azul
{
	void Mixer::Blend(Bone* pResult,
		const Bone* pA,
		const Bone* pB,
		const float tS,
		int numBones)
	{

		// Interpolate to tS time, for all bones
		for (int i = 0; i < numBones; i++)
		{
			// interpolate ahoy!
			VectApp::Lerp(pResult->T, pA->T, pB->T, tS);
			QuatApp::Slerp(pResult->Q, pA->Q, pB->Q, tS);
			VectApp::Lerp(pResult->S, pA->S, pB->S, tS);

			// advance the pointer
			pA++;
			pB++;
			pResult++;
		}

	}

}

// --- End of File ---