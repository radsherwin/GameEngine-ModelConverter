//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "Anim.h"

namespace Azul
{
	AnimController::AnimController(AnimTime delta, Clip* _pClip, Skeleton* pSkel, AnimName _animName)
		: name(_animName), poSkeleton(pSkel), bPause(false)
	{
		// Animatio n object
		this->poAnim = new Anim(_pClip, pSkel); //new Anim(_pClip, _pSkel);
		assert(this->poAnim);

		// TimerController
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->poTimerControl);
	}

	AnimController::AnimController()
		: name(AnimName::DEFAULT), poTimerControl(nullptr), poAnim(nullptr), poSkeleton(nullptr), bPause(false)
	{
	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete poTimerControl;
		delete this->poSkeleton;
	}

	void AnimController::SetClip(Clip* pClip) const
	{
		this->poAnim->pClip = pClip;
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl->SetMinTime(minTime);
		this->poTimerControl->SetMaxTime(maxTime);
		
	}

	void AnimController::IncreaseSpeed(float speed) const
	{
		this->poTimerControl->SetDeltaTime(this->poTimerControl->GetDeltaTime() * speed);
	}

	void AnimController::DecreaseSpeed(float speed) const
	{
		this->poTimerControl->SetDeltaTime(this->poTimerControl->GetDeltaTime() / speed);
	}

	void AnimController::Forward() const
	{
		this->poTimerControl->Forward();
	}

	void AnimController::Reverse() const
	{
		this->poTimerControl->Reverse();
	}

	void AnimController::PlayPause()
	{
		this->bPause = !this->bPause;
	}

	void AnimController::Show()
	{
		this->poSkeleton->Show();
	}

	void AnimController::Hide()
	{
		this->poSkeleton->Hide();
	}

	void AnimController::Update() const
	{
		if(bPause) return;

		this->poTimerControl->Update();

		// interpolate all bones
		this->poAnim->Animate(this->poTimerControl->GetCurrTime());
	}
}

// --- End of File ---