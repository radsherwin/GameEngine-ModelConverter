//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObjectHdr.h"
#include "GameObjectBasic.h"
#include "GameObjectManager.h"
#include "ShaderManager.h"
#include "Skeleton.h"

#include <PCSTreeForwardIterator.h>

#include "MeshNodeManager.h"
#include "GameObjectAnimSkeleton.h"
#include "GameObjectAnimSkin.h"
#include "Bone.h"

namespace Azul
{
	Skeleton::Skeleton(Mesh** SkeletonMesh, int _numBones)
		: pFirstBone(nullptr),
		numBones(_numBones)
	{
		this->poBoneResult = new Bone[(unsigned int)_numBones];
		this->privSetAnimationHierarchy(SkeletonMesh, this->poBoneResult);
		assert(pFirstBone);
	}

	Skeleton::~Skeleton()
	{
		delete[] this->poBoneResult;
	}

	GameObjectAnim* Skeleton::GetFirstBone()
	{
		assert(pFirstBone);
		return this->pFirstBone;
	}

	Bone* Skeleton::BoneResult()
	{
		return this->poBoneResult;
	}

	void Skeleton::Show()
	{
		GameObjectAnim* pObj = this->GetFirstBone();

		PCSTreeForwardIterator pIter(pObj);
		PCSNode* pNode = pIter.First();
		GameObjectAnim* pGameObj = nullptr;

		// walks the anim node does the pose for everything that
		while (pNode != nullptr)
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObjectAnim*)pNode;
			pGameObj->DrawEnable();
			pNode = pIter.Next();
		}
	}

	void Skeleton::Hide()
	{
		GameObjectAnim* pObj = this->GetFirstBone();

		PCSTreeForwardIterator pIter(pObj);
		PCSNode* pNode = pIter.First();
		GameObjectAnim* pGameObj = nullptr;

		// walks the anim node does the pose for everything that
		while (pNode != nullptr)
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObjectAnim*)pNode;
			pGameObj->DrawDisable();
			pNode = pIter.Next();
		}
	}

	void Skeleton::SetPos(float x, float y, float z) const
	{
		this->pPivot->SetTrans(x,y,z);
	}

	void Skeleton::privSetAnimationHierarchy(Mesh** SkeletonMesh, Bone* pBoneResult)
	{
		Vect pos(1, 1, 1);
		Vect color(1.0f, 1.0f, 1.0f, 1.0f);
		GraphicsObjectHdr* pGraphicsHdr;

		ShaderObject* pShaderObject_textureLight = ShaderManager::Find(ShaderObject::Name::TEXTURE_POINT_LIGHT);
		assert(pShaderObject_textureLight);

		ShaderObject* pShaderObject_texture = ShaderManager::Find(ShaderObject::Name::TEXTURE_POINT_LIGHT);
		assert(pShaderObject_texture);

		ShaderObject* pShaderNull = ShaderManager::Find(ShaderObject::Name::NULL_SHADER);
		assert(pShaderNull);

		//Add dummy pivot
		Mesh* pMeshNull = MeshNodeManager::Find(Mesh::Name::NULL_MESH);
		assert(pMeshNull);

		pGraphicsHdr = new GraphicsObjectHdr();
		pGraphicsHdr->Set_Null(pMeshNull, pShaderNull);
		GameObjectBasic* pPivot = new GameObjectBasic(pGraphicsHdr);
		pPivot->SetName("Pivot");
		pPivot->DrawDisable();
		pPivot->curRotZ = 1.5708f;
		pPivot->SetScale(40, 40, 40);
		pPivot->SetTrans(0, 0, 0);
		this->pPivot = pPivot;

		GameObjectManager::Add(pPivot, GameObjectManager::GetRoot());

		GameObjectAnim* pGameObj;

		//Root animation is treated differently

		//color.set(1.50f, 0.50f, 0.50f, 1.0f);
		pGraphicsHdr = new GraphicsObjectHdr();
		pGraphicsHdr->Set_TextureLight(SkeletonMesh[0], pShaderObject_textureLight, color, pos, Texture::Name::CHICKEN_BOT);
		pGameObj = new GameObjectAnimSkin(pGraphicsHdr, pBoneResult);
		pGameObj->SetIndex(SkeletonMesh[0]->pAnim->joint);
		pGameObj->SetName(SkeletonMesh[0]->pAnim->protoName.c_str());
		GameObjectManager::Add(pGameObj, pPivot);
		this->pFirstBone = pGameObj;

		for (int i = 1; i < this->numBones - 4; i++)
		{
			pGraphicsHdr = new GraphicsObjectHdr();
			pGraphicsHdr->Set_TextureLight(SkeletonMesh[i], pShaderObject_textureLight, color, pos, Texture::Name::CHICKEN_BOT);
			pGameObj = new GameObjectAnimSkin(pGraphicsHdr, pBoneResult);
			pGameObj->SetIndex(SkeletonMesh[i]->pAnim->joint);
			pGameObj->SetName(SkeletonMesh[i]->pAnim->protoName.c_str());
			GameObjectAnim* pParent = this->privFindBoneByIndex(SkeletonMesh[i]->pAnim->parent);
			GameObjectManager::Add(pGameObj, pParent);
		}
	}

	GameObjectAnim* Skeleton::privFindBoneByIndex(int index)
	{
		GameObjectAnim* pFound = nullptr;

		GameObjectAnim* pObj = this->GetFirstBone();

		// TODO - add test bed for an interator of a tree with only one node
		if (pObj->index == index)
		{
			pFound = pObj;
		}
		else
		{
			PCSTreeForwardIterator pIter(pObj);
			PCSNode* pNode = pIter.First();
			GameObjectAnim* pGameObj = nullptr;

			// walks the anim node does the pose for everything that
			while (pNode != nullptr)
			{
				assert(pNode);
				// Update the game object
				pGameObj = (GameObjectAnim*)pNode;
				if (pGameObj->index == index)
				{
					pFound = pGameObj;
					break;
				}
				pNode = pIter.Next();
			}
		}

		return pFound;
	}
}

// --- End of File ---