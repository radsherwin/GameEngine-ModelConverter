//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObjectBasic.h"
#include "Mesh.h"
#include "Anim.h"

namespace Azul
{

	GameObjectBasic::GameObjectBasic(GraphicsObjectHdr* pGraphicsObjectHdr)
		: GameObjectRigid(pGraphicsObjectHdr)
	{
		assert(pGraphicsObjectHdr);
		this->poTrans = new Vect(0.0f, 0.0f, 0.0f);
		this->poScale = new Vect(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0.0f, 0.0f, 0.0f, 1.0f);

		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);

		this->deltaX = 0.0f;
		this->deltaY = 0.0f;
		this->deltaZ = 0.0f;
		this->curRotX = 0.0f;
		this->curRotY = 0.0f;
		this->curRotZ = 0.0f;
	}

	GameObjectBasic::~GameObjectBasic()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
	}

	void GameObjectBasic::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		Matrix T(Matrix::Trans::XYZ, *this->poTrans);
		Matrix S(Matrix::Scale::XYZ, *this->poScale);
		Quat   Q(*this->poQuat);

		curRotX += deltaX;
		curRotY += deltaY;
		curRotZ += deltaZ;

		Matrix Rx(Matrix::Rot1::X, curRotX);
		Matrix Ry(Matrix::Rot1::Y, curRotY);
		Matrix Rz(Matrix::Rot1::Z, curRotZ);

		// world matrix
		*this->poWorld = S * Q * Rx * Ry * Rz * T;
	}

	void GameObjectBasic::Update(AnimTime currentTime)
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

	void GameObjectBasic::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectBasic::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectBasic::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectBasic::SetScale(Vect& r)
	{
		*this->poScale = r;
	}

	void GameObjectBasic::SetQuat(Quat& r)
	{
		*this->poQuat = r;
	}

	void GameObjectBasic::SetTrans(Vect& r)
	{
		*this->poTrans = r;
	}

}

// --- End of File ---