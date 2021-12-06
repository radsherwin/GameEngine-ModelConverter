//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H
#define GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H

#include "GraphicsObject.h"

namespace Azul
{
	class GraphicsObject_WireframeConstantColor :public GraphicsObject
	{
	public:
		GraphicsObject_WireframeConstantColor() = delete;
		GraphicsObject_WireframeConstantColor(const GraphicsObject_WireframeConstantColor&) = delete;
		GraphicsObject_WireframeConstantColor& operator = (const GraphicsObject_WireframeConstantColor&) = delete;
		virtual ~GraphicsObject_WireframeConstantColor();

		GraphicsObject_WireframeConstantColor(const Mesh* const mesh, const ShaderObject* const pShaderObj, const Vect& wireColor);

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

	public:
		// data:  place uniform instancing here
		Vect* poWireColor;

	};
}

#endif

// --- End of File ---