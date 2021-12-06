//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "BoundingSphereGameObject.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "GraphicsObject_WireframeConstantColor.h"

namespace Azul
{
	BoundingSphereGameObject::BoundingSphereGameObject(GraphicsObjectHdr* pGraphicsObjectHdr)
		: GameObject(pGraphicsObjectHdr)
	{
		this->pRefGameObj = nullptr;
		this->poScale = new Vect();
		this->poTrans = new Vect();

		assert(pGraphicsObjectHdr);
		assert(this->poScale);
		assert(this->poTrans);
	}

	BoundingSphereGameObject::~BoundingSphereGameObject()
	{
		delete this->poScale;
		delete this->poTrans;
	}

	void BoundingSphereGameObject::SetBoundingSphereReference(GameObject* pGameObj)
	{
		this->pRefGameObj = pGameObj;
	}

	void BoundingSphereGameObject::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix

		Matrix Scale(Matrix::Scale::XYZ, *this->poScale);
		Matrix TransA(Matrix::Trans::XYZ, *this->poTrans);

		// world matrix
		*this->poWorld = Scale * TransA;

		//Flip the color based on CAMERA::MAIN
		Camera* pCam = CameraManager::Find(Camera::ID::MAIN);
		Sphere* pCurSphere = this->poGraphicsObjHdr->poGraphicsObject->poCurrSphere;

		//Architecture issue
		GraphicsObject_WireframeConstantColor* pGObj = (GraphicsObject_WireframeConstantColor*)this->poGraphicsObjHdr->poGraphicsObject;
		if(pCam->CullTest(*pCurSphere) == Camera::CullResult::CULL_OUTSIDE)
		{
			pGObj->poWireColor->set(1,0,0,1);
		}
		else
		{
			pGObj->poWireColor->set(0,1,0,1);
		}
	}

	void BoundingSphereGameObject::privUpdateBoundingSphereReference(AnimTime currentTime)
	{
		// incase the reference object wasn't updated first
		// update it now.

		this->pRefGameObj->Update(currentTime);

		// set the center and scale of bound box based on ref game object's world coord
		Sphere* pRefCurSphere = this->pRefGameObj->GetGraphicsObject()->poCurrSphere;
		this->poScale->set(pRefCurSphere->rad, pRefCurSphere->rad, pRefCurSphere->rad);
		this->poTrans->set(pRefCurSphere->cntr);
		Sphere* pCurSphere = this->GetGraphicsObject()->poCurrSphere;
		*pCurSphere = *pRefCurSphere;
	}

	void BoundingSphereGameObject::Update(AnimTime currentTime)
	{
		this->mDrawEnable = this->pRefGameObj->IsHidden() || this->bSphereHidden;
		// Set Translation & Scale from reference
		this->privUpdateBoundingSphereReference(currentTime);

		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// push to graphics object
		this->poGraphicsObjHdr->poGraphicsObject->SetWorld(*this->poWorld);
	}

}

// --- End of File ---
