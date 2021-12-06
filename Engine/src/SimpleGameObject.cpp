//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "SimpleGameObject.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Mesh.h"

#include "FrameBucket.h"
#include "Anim.h"

namespace Azul
{
	extern FrameBucket* pHead;

	SimpleGameObject::SimpleGameObject(GraphicsObjectHdr* pGraphicsObjectHdr, GameObjectName _name)
		: GameObject(pGraphicsObjectHdr)
	{
		assert(pGraphicsObjectHdr);
		this->poTrans = new Vect(0.0f, 0.0f, 0.0f);
		this->poScale = new Vect(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0, 0, 0, 1);
		this->poLocal = new Matrix(Matrix::Special::Identity);
		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);
		assert(this->poLocal);
		this->index =1;
		this->poBoneOrientation = new Matrix(Matrix::Special::Identity);
		assert(poBoneOrientation);
		this->name = _name;
	}

	SimpleGameObject::~SimpleGameObject()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
		delete this->poLocal;
		delete this->poBoneOrientation;
	}

	void SimpleGameObject::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		Matrix T;
		Matrix S;
		Quat Q;

		// Get the parent matrix... if root, set to identity
		SimpleGameObject* pParentObject = (SimpleGameObject*)this->GetParent();
		Matrix matParent(Matrix::Special::Identity);
		if (pParentObject)
		{
			matParent = *pParentObject->poWorld;

			// REMEMBER this is for Animation and hierachy, you need to handle models differently
			// Get the result bone array, from there make the matrix
			Bone* bResult = pHead->poBone;

			T.set(Matrix::Trans::XYZ, bResult[index].T);
			S.set(Matrix::Scale::XYZ, bResult[index].S);
			Q = bResult[index].Q;
		}
		else
		{
			T.set(Matrix::Trans::XYZ, 0, 0, 0);
			S.set(Matrix::Scale::XYZ, 1, 1, 1);
			Q.set(Quat::Special::Identity);
		}

		//S.set(Matrix::Scale::XYZ, *this->poScale);
		//T.set(Matrix::Trans::XYZ, *this->poTrans);
		//Q = *this->poQuat;

		// world matrix
		*this->poLocal = S * Q * T;
		*this->poWorld = *poLocal * matParent;
	}

	void SimpleGameObject::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();
		//Set orientation
		SetAnimationPose(this);

		//Push to graphics obj
		//Matrix mTmp = *this->poBoneOrientation;

		GraphicsObjectHdr* tmp = this->poGraphicsObjHdr;
		while (tmp != nullptr)
		{
			if (this->mDrawEnable)
			{
				tmp->poGraphicsObject->SetWorld(*this->poWorld);
			}
			tmp = tmp->poNext;
		}
	}

	void SimpleGameObject::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void SimpleGameObject::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void SimpleGameObject::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void SimpleGameObject::SetQuat(const Quat& pQuat)
	{
		this->poQuat->set(pQuat);
	}

	void SimpleGameObject::SetScale(const Vect& pScale)
	{
		this->poScale->set(pScale);
	}

	void SimpleGameObject::SetTrans(const Vect& pTrans)
	{
		this->poTrans->set(pTrans);
	}

	void SimpleGameObject::SetIndex(int i)
	{
		this->index = i;
	}

	Matrix SimpleGameObject::GetBoneOrientation() const
	{
		//returns a copy
		return Matrix(*this->poBoneOrientation);
	}

	void SimpleGameObject::SetBoneOrientation(const Matrix& M)
	{
		*this->poBoneOrientation = M;
	}
}

// --- End of File ---