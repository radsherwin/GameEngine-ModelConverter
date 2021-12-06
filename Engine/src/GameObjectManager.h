//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include "PCSTree.h"
#include "AnimTime.h"

namespace Azul
{

	// Singleton
	class GameObjectManager
	{
	public:
		static void Add(GameObject* pObj, GameObject* pParent);
		static void Draw(void);
		static void Update(AnimTime currentTime);
		static void Hide(GameObject::GameObjectName _name);
		static void Show(GameObject::GameObjectName _name);
		static void FlipBSphere();

		static GameObject* GetRoot(void);
		static PCSTree* GetPCSTree();

		static void Destroy();
		~GameObjectManager();
		GameObjectManager(const GameObjectManager&) = delete;
		GameObjectManager& operator=(const GameObjectManager&) = delete;

	private:
		GameObjectManager();
		static GameObject* privFind(GameObject::GameObjectName _name);
		static GameObjectManager* privGetInstance();

		// data
		PCSTree* poRootTree;
		bool bIsSphereHidden;
	};

}

#endif


// --- End of File ---