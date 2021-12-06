//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObjectAnimSkin.h"
#include "Mesh.h"
#include "Anim.h"
#include "Bone.h"

namespace Azul
{
	GameObjectAnimSkin::GameObjectAnimSkin(GraphicsObjectHdr* pGraphicsObjectHdr, Bone* _pBoneResult)
		: GameObjectAnim(pGraphicsObjectHdr)
	{
		assert(pGraphicsObjectHdr);
		this->poTrans = new Vect(0.0f, 0.0f, 0.0f);
		this->poScale = new Vect(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0.0f, 0.0f, 0.0f, 1.0f);
		this->poLocal = new Matrix(Matrix::Special::Identity);
		this->poBoneOrientation = new Matrix(Matrix::Special::Identity);
		this->pBoneResult = _pBoneResult;
		assert(_pBoneResult);
		assert(poBoneOrientation);
		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);
		assert(this->poLocal);
	}

	GameObjectAnimSkin::~GameObjectAnimSkin()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
		delete this->poLocal;
		delete this->poBoneOrientation;
	}

	void GameObjectAnimSkin::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		//Trace::out("index: %d \n", index);

		Matrix T;
		Matrix S;
		Quat   Q;

		// Get the parent matrix... if root, set to identity
		GameObjectAnimSkin* pParentObject = (GameObjectAnimSkin*)this->GetParent();
		Matrix matParent(Matrix::Special::Identity);
		
		
		if (pParentObject)
		{
			matParent = *pParentObject->poWorld;

			// REMEMBER this is for Animation and hierachy, you need to handle models differently
			// Get the result bone array, from there make the matrix

			T.set(Matrix::Trans::XYZ, this->pBoneResult[index].T);
			S.set(Matrix::Scale::XYZ, this->pBoneResult[index].S);
			Q = this->pBoneResult[index].Q;
		}
		else
		{
			T.set(Matrix::Trans::XYZ, 0, 0, 0);
			S.set(Matrix::Scale::XYZ, 1, 1, 1);
			Q.set(Quat::Special::Identity);
		}
		// world matrix
		*this->poLocal = S * Q * T;
		*this->poWorld = *poLocal * matParent;

	}

	void GameObjectAnimSkin::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		GraphicsObjectHdr* tmp = this->poGraphicsObjHdr;
		while (tmp != nullptr)
		{
			if (!this->IsHidden())
			{
				tmp->poGraphicsObject->SetWorld(*this->poWorld);
			}
			tmp = tmp->pNext;
		}
	}

	void GameObjectAnimSkin::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectAnimSkin::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectAnimSkin::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectAnimSkin::SetIndex(int i)
	{
		this->index = i;
	}

	void GameObjectAnimSkin::SetScale(Vect& r)
	{
		*this->poScale = r;
	}

	void GameObjectAnimSkin::SetQuat(Quat& r)
	{
		*this->poQuat = r;
	}

	void GameObjectAnimSkin::SetTrans(Vect& r)
	{
		*this->poTrans = r;
	}

	void GameObjectAnimSkin::SetBoneOrientation(const Matrix& tmp)
	{
		*this->poBoneOrientation = tmp;
	}

	Matrix GameObjectAnimSkin::GetBoneOrientation(void) const
	{
		// return a copy...
		return Matrix(*this->poBoneOrientation);
	}
}

// --- End of File ---