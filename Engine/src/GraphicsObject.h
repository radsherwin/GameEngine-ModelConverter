//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "RenderMaterial.h"
#include "BoundingSphere.h"

using namespace Azul;

class Mesh;

class GraphicsObject : public RenderMaterial
{
public:
	GraphicsObject(const Mesh* const mesh, const ShaderObject* const pShaderObj);

	GraphicsObject() = delete;
	GraphicsObject(const GraphicsObject&) = delete;
	GraphicsObject& operator = (const GraphicsObject&) = delete;
	virtual ~GraphicsObject();

	void Render();
	void SetWorld(Azul::Matrix& _world);

	const Mesh* GetMesh() const;
	Matrix& GetWorld();
	Sphere* poCurrSphere;

protected:
	const Mesh* pMesh;
	Matrix* poWorld;
	const ShaderObject* pShaderObj;
};

#endif

// --- End of File ---