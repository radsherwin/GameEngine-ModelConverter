#include "AnimationManager.h"

#include <PCSTreeForwardIterator.h>

#include "PCSTree.h"
#include "Clip.h"
#include "AnimController.h"
#include "meshData.h"
#include "ProtoMeshFactory.h"

using namespace Azul;

AnimationManager* AnimationManager::posInstance = nullptr;

AnimationManager::AnimationManager()
{
	this->poClipTree = new PCSTree();
	assert(this->poClipTree);

	Clip* pNullClip = new Clip();
	this->poClipTree->Insert(pNullClip, this->poClipTree->GetRoot());

	this->poAnimTree = new PCSTree();
	assert(this->poAnimTree);

	Animation* pNullAnimation = new Animation();
	this->poAnimTree->Insert(pNullAnimation, this->poAnimTree->GetRoot());

	this->poControllerTree = new PCSTree();
	assert(this->poControllerTree);

	AnimController* pNullController = new AnimController();
	this->poControllerTree->Insert(pNullController, this->poControllerTree->GetRoot());
}

AnimationManager::~AnimationManager()
{
	delete this->poClipTree;
	delete this->poAnimTree;
	delete this->poControllerTree;
}

void AnimationManager::Add(Animation** pAnimation, Clip::Name _clipName, int _numBones)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	Clip* pClip = new Clip(_clipName, _numBones, pAnimation);
	pMan->poClipTree->Insert(pClip, pMan->poClipTree->GetRoot());
}

void AnimationManager::Add(Animation* anim)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);
	pMan->poAnimTree->Insert(anim, pMan->poAnimTree->GetRoot());
}

void AnimationManager::SetClip(Clip::Name _clipName, AnimController::AnimName _animName)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	Clip* pClip = pMan->privFind(_clipName);
	assert(pClip);

	AnimController* pController = pMan->privFind(_animName);

	if (pController != nullptr) pController->SetClip(pClip);
}

void AnimationManager::AddController(AnimController::AnimName _animName, Skeleton* pSkel, Clip::Name _clip)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	Clip* pClip = pMan->privFind(_clip);
	assert(pClip);
	
	AnimTime delta = 0.1f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
	AnimController* pAnimController = new AnimController(delta, pClip, pSkel, _animName); //, pSkel);
	pMan->poControllerTree->Insert(pAnimController, pMan->poControllerTree->GetRoot());
}

void AnimationManager::IncreaseSpeed(float speed)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT) pTmp->IncreaseSpeed(speed);
		pNode = pForIter.Next();
	}
}

void AnimationManager::DecreaseSpeed(float speed)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT) pTmp->DecreaseSpeed(speed);
		pNode = pForIter.Next();
	}
}

void AnimationManager::Forward()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT) pTmp->Forward();
		pNode = pForIter.Next();
	}
}

void AnimationManager::Reverse()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT) pTmp->Reverse();
		pNode = pForIter.Next();
	}
}

void AnimationManager::PlayPause()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT) pTmp->PlayPause();
		pNode = pForIter.Next();
	}
}

void AnimationManager::Demo()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	//Update all controllers
	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT && pTmp->name != AnimController::AnimName::MESH1) pTmp->Hide();
		pNode = pForIter.Next();
	}
}

void AnimationManager::Demo2()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	//Update all controllers
	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if (pTmp->name != AnimController::AnimName::DEFAULT && pTmp->name != AnimController::AnimName::MESH1) pTmp->Show();
		pNode = pForIter.Next();
	}
}

void AnimationManager::Update()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	//Update all controllers
	PCSTree* pTree = pMan->poControllerTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	AnimController* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = (AnimController*)pForIter.CurrentItem();
		if(pTmp->name != AnimController::AnimName::DEFAULT) pTmp->Update();
		pNode = pForIter.Next();
	}


}

void AnimationManager::Create()
{
	// initialize the singleton here
	assert(posInstance == nullptr);

	// Do the initialization
	if (posInstance == nullptr)
	{
		posInstance = new AnimationManager();
	}
}

void AnimationManager::Destroy()
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSTree* pTree = pMan->poClipTree;
	PCSNode* pNode = nullptr;

	PCSTreeForwardIterator pForIter(pTree->GetRoot());
	pNode = pForIter.First();
	PCSNode* pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = pForIter.CurrentItem();

		pNode = pForIter.Next();
		delete pTmp;
	}

	pTree = pMan->poAnimTree;
	pNode = nullptr;

	pForIter = pTree->GetRoot();
	pNode = pForIter.First();
	pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = pForIter.CurrentItem();

		pNode = pForIter.Next();
		delete pTmp;
	}

	pTree = pMan->poControllerTree;
	pNode = nullptr;

	pForIter = pTree->GetRoot();
	pNode = pForIter.First();
	pTmp = nullptr;
	while (!pForIter.IsDone())
	{
		pTmp = pForIter.CurrentItem();

		pNode = pForIter.Next();
		delete pTmp;
	}

	delete AnimationManager::posInstance;
	AnimationManager::posInstance = nullptr;
}

AnimationManager* AnimationManager::privGetInstance()
{
	return posInstance;
}

Clip* AnimationManager::privFind(Clip::Name _clipName)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSNode* pRootNode = pMan->poClipTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode* pNode = pForwardIter.First();

	Clip* pClip = nullptr;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		pClip = (Clip*)pNode;
		if (pClip->GetClipName() == _clipName)
		{
			return pClip;
		}

		pNode = pForwardIter.Next();
	}

	return nullptr;
}

AnimController* AnimationManager::privFind(AnimController::AnimName _animName)
{
	AnimationManager* pMan = AnimationManager::privGetInstance();
	assert(pMan);

	PCSNode* pRootNode = pMan->poControllerTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode* pNode = pForwardIter.First();

	AnimController* pController = nullptr;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		pController = (AnimController*)pNode;
		if (pController->name == _animName)
		{
			return pController;
		}

		pNode = pForwardIter.Next();
	}

	return nullptr;
}