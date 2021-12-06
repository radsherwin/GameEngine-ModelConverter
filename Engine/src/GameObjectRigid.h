//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SIMPLE_GAME_OBJECT_RIGID_H
#define SIMPLE_GAME_OBJECT_RIGID_H

#include "GameObject.h"
#include "AnimTime.h"

class GraphicsObjectHdr;

namespace Azul
{
	class GameObjectRigid : public GameObject
	{
	public:
		GameObjectRigid(GraphicsObjectHdr* pGraphicsObjectHdr);

		// Big four
		GameObjectRigid() = delete;
		GameObjectRigid(const GameObjectRigid&) = delete;
		GameObjectRigid& operator=(GameObjectRigid&) = delete;
		virtual ~GameObjectRigid() = default;

		virtual void Update(AnimTime currTime);

	private:

	};
}

#endif

// --- End of File ---