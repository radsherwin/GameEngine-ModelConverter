//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mesh.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "ShaderObject.h"
#include "Camera.h"
#include "CameraManager.h"

using namespace Azul;

GraphicsObject_WireframeConstantColor::GraphicsObject_WireframeConstantColor(const Mesh* const pMesh, const ShaderObject* const pShaderObj, const Vect& wireColor)
	: GraphicsObject(pMesh, pShaderObj)
{
	assert(pMesh);
	assert(pShaderObj);
	this->poWireColor = new Vect(wireColor);
}

GraphicsObject_WireframeConstantColor::~GraphicsObject_WireframeConstantColor()
{
	delete this->poWireColor;
}
void GraphicsObject_WireframeConstantColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphicsObject_WireframeConstantColor::SetDataGPU()
{
	// Draw Me: -----------------------------------------

	// set the vao
	glBindVertexArray(this->GetMesh()->vao);

	// Set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	// use this shader
	this->pShaderObj->SetActive();

	Camera* pCam = CameraManager::CurrentCamera();

	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);

	glUniform4fv(this->pShaderObj->GetLocation("wire_color"), 1, (float*)this->poWireColor);
}

void GraphicsObject_WireframeConstantColor::Draw()
{
	//The starting point of the IBO
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_WireframeConstantColor::RestoreState()
{
	// Restore state
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
}



// --- End of File ---