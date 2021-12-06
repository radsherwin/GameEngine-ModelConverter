//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_SPEC_H
#define GRAPHICS_OBJECT_SPEC_H

#include "GraphicsObject.h"

using namespace Azul;

class GraphicsObject_ColorSpecLighting :public GraphicsObject
{
public:
	GraphicsObject_ColorSpecLighting(const Mesh* const _pMesh, const ShaderObject* const _pShaderObj, Vect& LightColor, Vect& LightPos);
	GraphicsObject_ColorSpecLighting() = delete;
	GraphicsObject_ColorSpecLighting(const GraphicsObject_ColorSpecLighting&) = delete;
	GraphicsObject_ColorSpecLighting& operator = (const GraphicsObject_ColorSpecLighting&) = delete;
	virtual ~GraphicsObject_ColorSpecLighting();

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here
	Vect* poLightColor;
	Vect* poLightPos;
};



#endif

// ---  End of File ---