//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObjectBoundingSphere.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "GraphicsObject_WireframeConstantColor.h"


namespace Azul
{
	GameObjectBoundingSphere::GameObjectBoundingSphere(GraphicsObjectHdr *pGraphicsObjectHdr)
		: GameObjectRigid(pGraphicsObjectHdr)
	{
		this->pRefGameObj = nullptr;
		this->poScale = new Vect();
		this->poTrans = new Vect();

		assert(pGraphicsObjectHdr);
		assert(this->poScale);
		assert(this->poTrans);
	}

	GameObjectBoundingSphere::~GameObjectBoundingSphere()
	{
		delete this->poScale;
		delete this->poTrans;
	}

	void GameObjectBoundingSphere::SetBoundingSphereReference(GameObject *pGameObj)
	{
		this->pRefGameObj = pGameObj;
	}

	void GameObjectBoundingSphere::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix

		Matrix Scale(Matrix::Scale::XYZ, *this->poScale);
		Matrix TransA(Matrix::Trans::XYZ, *this->poTrans);

		// world matrix
		*this->poWorld = Scale * TransA;


		// Flip the color based on camera_0
		Camera *pCam = CameraManager::Find(Camera::ID::MAIN);
		Sphere *pCurrSphere = this->poGraphicsObjHdr->poGraphicsObject->poCurrSphere;

		// Architecture issue... this doesn't feel good.
		GraphicsObject_WireframeConstantColor *pGObj = (GraphicsObject_WireframeConstantColor *)this->poGraphicsObjHdr->poGraphicsObject;
		if(pCam->CullTest(*pCurrSphere) == Camera::CullResult::CULL_OUTSIDE)
		{
			pGObj->poWireColor->set(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			pGObj->poWireColor->set(0.0f, 1.0f, 0.0f, 1.0f);
		}


	}

	void GameObjectBoundingSphere::privUpdateBoundingSphereReference(AnimTime currentTime)
	{
		// incase the reference object wasn't updated first
		// update it now.

		this->pRefGameObj->Update(currentTime);

		// set the center and scale of bound box based on ref game object's world coord
		Sphere *pRefCurrSphere = this->pRefGameObj->GetGraphicsObject()->poCurrSphere;
		this->poScale->set(pRefCurrSphere->rad, pRefCurrSphere->rad, pRefCurrSphere->rad);
		this->poTrans->set(pRefCurrSphere->cntr);

		Sphere *pCurrSphere = this->GetGraphicsObject()->poCurrSphere;
		*pCurrSphere = *pRefCurrSphere;
	}

	void GameObjectBoundingSphere::Update(AnimTime currentTime)
	{
		// Set Translation & Scale from reference
		this->privUpdateBoundingSphereReference(currentTime);

		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// push to graphics object
		this->poGraphicsObjHdr->poGraphicsObject->SetWorld(*this->poWorld);
	}

}

// --- End of File ---
