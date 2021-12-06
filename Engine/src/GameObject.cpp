//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Mesh.h"

namespace Azul
{

	GameObject::GameObject(GraphicsObjectHdr* pGraphicsObjectHdr, GameObjectName _name)
		: pSphere(nullptr), poGraphicsObjHdr(pGraphicsObjectHdr), name(_name), mDrawEnable(true)
	{
		this->poWorld = new Matrix(Matrix::Special::Identity);
		assert(poWorld);
		assert(pGraphicsObjectHdr != 0);
	}

	GameObject::~GameObject()
	{
		delete this->poWorld;
		//Ensure all graphics objects are deleted
		GraphicsObjectHdr* pTmp = this->poGraphicsObjHdr;
		while(pTmp !=nullptr)
		{
			GraphicsObjectHdr* pDeleteMe = pTmp;
			pTmp = pTmp->GetNext();
			delete pDeleteMe;
		}

	}

	Matrix* GameObject::GetWorld()
	{
		return this->poWorld;
	}

	GraphicsObjectHdr* GameObject::GetGraphicsObjectHdr()
	{
		return this->poGraphicsObjHdr;
	}

	GraphicsObject* GameObject::GetGraphicsObject()
	{
		return this->poGraphicsObjHdr->poGraphicsObject;
	}

	void GameObject::SetWorld(Matrix* _pWorld)
	{
		assert(_pWorld);
		*this->poWorld = *_pWorld;
	}

	GameObject::GameObjectName GameObject::GetObjectName() const
	{
		return this->name;
	}

	bool GameObject::IsHidden() const
	{
		return !this->mDrawEnable;
	}

	bool GameObject::IsBSphereHidden() const
	{
		return this->bSphereHidden;
	}

	void GameObject::SetBSphereHidden(bool _hide)
	{
		this->bSphereHidden = _hide;
	}

	void GameObject::baseUpdateBoundingSphere()
	{
		// Get the ref Sphere
		Sphere* pRefSphere = poGraphicsObjHdr->poGraphicsObject->GetMesh()->poRefSphere;
		assert(pRefSphere);

		// Get the curr Sphere
		Sphere* pCurrSphere = poGraphicsObjHdr->poGraphicsObject->poCurrSphere;
		assert(pCurrSphere);

		// Update... cntr process through the world
		// Assuming a uniform scaling
		Vect A = pRefSphere->cntr;
		Vect radius(1.0f, 0.0f, 0.0f);
		Vect B = A + radius;
		Vect A_out = A * (*this->poWorld);
		Vect B_out = B * (*this->poWorld);

		pCurrSphere->rad = (B_out - A_out).mag() * pRefSphere->rad;
		pCurrSphere->cntr = A_out;
	}

	void GameObject::Draw()
	{
		GraphicsObjectHdr* pGraphicsObjHdr = this->GetGraphicsObjectHdr();
		assert(pGraphicsObjHdr);
		while(pGraphicsObjHdr != nullptr)
		{
			if(this->mDrawEnable)
			{
				pGraphicsObjHdr->poGraphicsObject->Render();
			}
			pGraphicsObjHdr = pGraphicsObjHdr->pNext;
		}
		
	}

	void GameObject::DrawEnable()
	{
		this->mDrawEnable = true;
	}

	void GameObject::DrawDisable()
	{
		this->mDrawEnable = false;
	}
}



// --- End of File ---
