//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GraphicsObjectHdr.h"
#include "PCSNode.h"
#include "AnimTime.h"

namespace Azul
{
	class GameObject : public PCSNode
	{
	public:
		enum class GameObjectName
		{
			CUBE,
			CRATE,
			SNOWMAN,
			SPACE_FRIGATE,
			DOG_HOUSE,
			DOG_HOUSE2,
			AVOCADO,
			BARRAMUNDI,
			ANTIQUE_CAMERA,
			WATCH_TOWER,
			WATCH_TOWER2,
			CORSET,
			CORSET2,
			POKE_BALL,
			SPHERE,
			NULL_OBJ,
			NOT_INITIALIZED
		};

		GameObject() = delete;
		GameObject(const GameObject&) = delete;
		GameObject& operator = (const GameObject&) = delete;
		virtual ~GameObject();

		GameObject(GraphicsObjectHdr* graphicsObjectHdr, GameObjectName _name = GameObjectName::NOT_INITIALIZED);

		virtual void Update(AnimTime t) = 0;
		virtual void Draw();

		void DrawEnable();
		void DrawDisable();

		//Set/Get
		GraphicsObjectHdr* GetGraphicsObjectHdr();
		GraphicsObject*	GetGraphicsObject();
		Matrix* GetWorld();

		void SetWorld(Matrix* pWorld);
		GameObjectName GetObjectName() const;
		bool IsHidden() const;
		bool IsBSphereHidden() const;
		void SetBSphereHidden(bool _hide);

	protected:
		void baseUpdateBoundingSphere();
		Matrix* poWorld;
		Sphere* pSphere;
		GraphicsObjectHdr* poGraphicsObjHdr;
		GameObjectName name;
		bool mDrawEnable;
		bool bSphereHidden;		

	};
}



#endif


// --- End of File ---
