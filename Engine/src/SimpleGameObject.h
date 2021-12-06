//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SIMPLE_GAME_OBJECT_H
#define SIMPLE_GAME_OBJECT_H

#include "GameObject.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"

namespace Azul
{
	class SimpleGameObject : public GameObject
	{
	public:
		SimpleGameObject(GraphicsObjectHdr* graphicsObjectHdr, GameObjectName _name = GameObjectName::NOT_INITIALIZED);

		// Big four
		SimpleGameObject() = delete;
		SimpleGameObject(const SimpleGameObject&) = delete;
		SimpleGameObject& operator=(SimpleGameObject&) = delete;
		virtual ~SimpleGameObject();

		virtual void Update(AnimTime t);

		void SetScale(float sx, float sy, float sz);
		void SetQuat(float qx, float qy, float qz, float qw);
		void SetTrans(float x, float y, float z);

		void SetScale(const Vect& pScale);
		void SetQuat(const Quat& pQuat);
		void SetTrans(const Vect& pTrans);
		void SetIndex(int i);

		Matrix GetBoneOrientation(void) const;
		void SetBoneOrientation(const Matrix& M);

	private:
		void privUpdate(AnimTime t);

	public:   // add accessors later
		Vect* poScale;
		Quat* poQuat;
		Vect* poTrans;
		Matrix* poLocal;
		int index;
		Matrix* poBoneOrientation;

	};

}

#endif

// --- End of File ---