//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BOUNDING_SPHERE_GAME_OBJECT_H
#define BOUNDING_SPHERE_GAME_OBJECT_H

#include "MathEngine.h"
#include "GameObject.h"
#include "AnimTime.h"

namespace Azul
{
	class BoundingSphereGameObject : public GameObject
	{
	public:
		BoundingSphereGameObject(GraphicsObjectHdr* graphicsObjectHdr);

		// Big four
		BoundingSphereGameObject() = delete;
		BoundingSphereGameObject(const BoundingSphereGameObject&) = delete;
		BoundingSphereGameObject& operator=(BoundingSphereGameObject&) = delete;
		virtual ~BoundingSphereGameObject();

		void SetBoundingSphereReference(GameObject* pGameObj);

		virtual void Update(AnimTime t) override;

	private:
		void privUpdate(AnimTime t);
		void privUpdateBoundingSphereReference(AnimTime currentTime);

		// Data: ------------------
		GameObject* pRefGameObj;

	public:
		Vect* poScale;
		Vect* poTrans;
	};

}

#endif

// --- End of File ---