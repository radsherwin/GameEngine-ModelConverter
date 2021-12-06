//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SIMPLE_GAME_OBJECT_ANIM_H
#define SIMPLE_GAME_OBJECT_ANIM_H

#include "GameObject.h"
#include "AnimTime.h"

namespace Azul
{
	class GameObjectAnim : public GameObject
	{
	public:
		GameObjectAnim(GraphicsObjectHdr* pGraphicsObjectHdr);

		// Big four
		GameObjectAnim() = delete;
		GameObjectAnim(const GameObjectAnim&) = delete;
		GameObjectAnim& operator=(GameObjectAnim&) = delete;
		virtual ~GameObjectAnim() = default;

		virtual void Update(AnimTime currTime);
		virtual void SetIndex(int i) = 0;

	public:
		int index;

	};
}

#endif

// --- End of File ---