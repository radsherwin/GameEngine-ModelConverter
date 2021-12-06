#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H
#include "AnimController.h"
#include "Mesh.h"
#include "Clip.h"
#include "Skeleton.h"

namespace Azul
{
	class AnimTime;
	class PCSTree;
	class AnimController;
	class AnimationManager

	{
	public:
		
		AnimationManager();
		AnimationManager(const AnimationManager&) = delete;
		AnimationManager& operator=(const AnimationManager&) = delete;
		~AnimationManager();

		//static void Add(Mesh** pMesh, Clip::Name _clipName, int _numBones);
		static void Add(Animation** pAnimation, Clip::Name _clipName, int _numBones);
		static void Add(Animation* anim);

		static void SetClip(Clip::Name _clipName, AnimController::AnimName _animName);
		static void AddController(AnimController::AnimName _animName, Skeleton* pSkel, Clip::Name _clip);

		static void IncreaseSpeed(float speed);
		static void DecreaseSpeed(float speed);
		static void Forward();
		static void Reverse();
		static void PlayPause();

		static void Demo();
		static void Demo2();

		static void Update();
		static void Create();
		static void Destroy();

	private:
		static AnimationManager* privGetInstance();
		static Clip* privFind(Clip::Name _clipName);
		static AnimController* privFind(AnimController::AnimName _animName);

	public:
		PCSTree* poClipTree;
		PCSTree* poAnimTree;
		PCSTree* poControllerTree;

	private:
		static AnimationManager* posInstance;


	};
}

#endif