//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "Anim.h"
#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Skeleton.h"

namespace Azul
{
	class AnimController : public PCSNode
	{
	public:
		enum class AnimName
		{
			MESH1 = 0,
			MESH2,
			MESH3,
			MESH4,
			DEFAULT
		};
		AnimController(AnimTime delta, Clip* _pClip, Skeleton* pSkel, AnimName _animName);
		AnimController();
		AnimController(const AnimController&) = delete;
		AnimController& operator = (const AnimController&) = delete;
		virtual ~AnimController();

		void SetClip(Clip* pClip) const;
		void IncreaseSpeed(float speed) const;
		void DecreaseSpeed(float speed) const;
		void Forward() const;
		void Reverse() const;

		void PlayPause();
		void Show();
		void Hide();

		void Update() const;

		AnimName name;
	private:
		
		TimerController* poTimerControl;
		Anim* poAnim;
		Skeleton* poSkeleton;
		bool bPause;

	};
}

#endif

// --- End of File ---