//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H

#include "AnimTimer.h"

namespace Azul
{
	class TimerController
	{
	public:
		TimerController(AnimTime Delta, AnimTime Min, AnimTime Max);
		TimerController() = delete;
		TimerController(const TimerController&) = delete;
		TimerController& operator = (const TimerController&) = delete;
		~TimerController() = default;

		void Update();

		void SetCurrTime(const AnimTime time);
		AnimTime GetCurrTime() const;

		void SetDeltaTime(const AnimTime time);
		AnimTime GetDeltaTime() const;

		void SetMaxTime(const AnimTime time);
		AnimTime GetMaxTime() const;

		void SetMinTime(const AnimTime time);
		AnimTime GetMinTime() const;

		void Forward();
		void Reverse();

	private:
		AnimTime tCurr;
		AnimTime tDelta;
		AnimTime tMax;
		AnimTime tMin;
		bool bReverse;
	};
}

#endif

// --- End of File ---
