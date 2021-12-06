//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "NullMesh.h"

#include "GameObject.h"
#include "GameObjectRigid.h"
#include "GameObjectManager.h"
#include "PCSTreeForwardIterator.h"

#include "MeshNodeManager.h"
#include "ShaderManager.h"

namespace Azul
{
	void GameObjectManager::Add(GameObject* pObj, GameObject* pParent)
	{
		assert(pObj);
		assert(pParent);

		// Get singleton
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();

		// insert object to root
		pGOM->poRootTree->Insert(pObj, pParent);
	}


	void GameObjectManager::Destroy()
	{
		// Get singleton
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();
		assert(pGOM);

		PCSTree* pTree = pGOM->poRootTree;
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
	}

	void GameObjectManager::Update(AnimTime currentTime)
	{
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();
		assert(pGOM);

		PCSNode* pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForwardIter(pRootNode);
		PCSNode* pNode = pForwardIter.First();

		GameObject* pGameObj = nullptr;

		while (!pForwardIter.IsDone())
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObject*)pNode;
			pGameObj->SetBSphereHidden(pGOM->bIsSphereHidden);
			pGameObj->Update(currentTime);

			pNode = pForwardIter.Next();
		}
	}

	void GameObjectManager::Hide(GameObject::GameObjectName _name)
	{
		GameObject* gObj = privFind(_name);
		gObj->DrawDisable();
	}

	void GameObjectManager::Show(GameObject::GameObjectName _name)
	{
		GameObject* gObj = privFind(_name);
		gObj->DrawEnable();
	}

	void GameObjectManager::FlipBSphere()
	{
		GameObjectManager* pMan = GameObjectManager::privGetInstance();
		assert(pMan);
		pMan->bIsSphereHidden = !pMan->bIsSphereHidden;
	}

	GameObject* GameObjectManager::GetRoot()
	{
		// Get singleton
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();
		assert(pGOM);

		GameObject* pGameObj = (GameObject*)pGOM->poRootTree->GetRoot();
		assert(pGameObj);

		return pGameObj;
	}

	PCSTree* GameObjectManager::GetPCSTree()
	{
		// Get singleton
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();
		assert(pGOM);

		return pGOM->poRootTree;
	}

	GameObject* GameObjectManager::privFind(GameObject::GameObjectName _name)
	{
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();
		assert(pGOM);

		PCSNode* pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForwardIter(pRootNode);
		PCSNode* pNode = pForwardIter.First();

		GameObject* pGameObj = nullptr;

		while (!pForwardIter.IsDone())
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObject*)pNode;
			if(pGameObj->GetObjectName() == _name)
			{
				return pGameObj;
			}

			pNode = pForwardIter.Next();
		} 
	}

	void GameObjectManager::Draw()
	{
		GameObjectManager* pGOM = GameObjectManager::privGetInstance();
		assert(pGOM);

		PCSNode* pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForwardIter(pRootNode);
		PCSNode* pNode = pForwardIter.First();

		GameObject* pGameObj = nullptr;

		while (!pForwardIter.IsDone())
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObject*)pNode;
			pGameObj->Draw();

			pNode = pForwardIter.Next();
		}
	}

	GameObjectManager::GameObjectManager()
	{
		// Create the root node (null object)
		NullMesh* pMesh = new NullMesh(nullptr);
		MeshNodeManager::Add(Mesh::Name::NULL_MESH, pMesh);

		ShaderObject* pShader = ShaderManager::Add(ShaderObject::Name::NULL_SHADER, "../src/GLSL/nullRender");
		GraphicsObjectHdr* pGraphicsObjectHdr = new GraphicsObjectHdr(pMesh, pShader);
		GameObjectRigid* pGameRoot = new GameObjectRigid(pGraphicsObjectHdr);
		pGameRoot->SetName("GameObject_Root");

		// Create the tree
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		// Attach the root node
		this->poRootTree->Insert(pGameRoot, this->poRootTree->GetRoot());

		this->bIsSphereHidden = false;
	}

	GameObjectManager::~GameObjectManager()
	{
		delete this->poRootTree;
	}

	GameObjectManager* GameObjectManager::privGetInstance(void)
	{
		// This is where its actually stored (BSS section)
		static GameObjectManager gom;
		return &gom;
	}

}

// --- End of File ---