//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_BASIC_H
#define GAME_OBJECT_BASIC_H

#include "GameObjectRigid.h"
#include "MathEngine.h"
#include "AnimTime.h"

namespace Azul
{
	class GameObjectBasic : public GameObjectRigid
	{
	public:
		GameObjectBasic(GraphicsObjectHdr* pGraphicsObjectHdr);

		// Big four
		GameObjectBasic() = delete;
		GameObjectBasic(const GameObjectBasic&) = delete;
		GameObjectBasic& operator=(GameObjectBasic&) = delete;
		virtual ~GameObjectBasic();

		virtual void Update(AnimTime currTime);

		void SetScale(float sx, float sy, float sz);
		void SetQuat(float qx, float qy, float qz, float qw);
		void SetTrans(float x, float y, float z);

		void SetScale(Vect& r);
		void SetQuat(Quat& r);
		void SetTrans(Vect& r);

	private:
		void privUpdate(AnimTime currTime);

	public:   // add accessors later
		Vect* poScale;
		Quat* poQuat;
		Vect* poTrans;
		float deltaX;
		float deltaY;
		float deltaZ;
		float curRotX;
		float curRotY;
		float curRotZ;
	};
}

#endif

// --- End of File ---