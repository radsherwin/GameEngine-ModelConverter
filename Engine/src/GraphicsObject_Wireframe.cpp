//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mesh.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"
#include "Camera.h"
#include "CameraManager.h"

using namespace Azul;

GraphicsObject_Wireframe::GraphicsObject_Wireframe(const Mesh* const _pMesh, const ShaderObject* const _pShaderObj)
	: GraphicsObject(_pMesh, _pShaderObj)
{
	assert(this->pMesh);
	assert(this->pShaderObj);
	assert(this->poWorld);
}

void GraphicsObject_Wireframe::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Wireframe::SetDataGPU()
{
	// Draw Me: -----------------------------------------

	// use this shader
	this->pShaderObj->SetActive();

	// set the vao
	glBindVertexArray(this->GetMesh()->vao);

	// Set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	Camera* pCam = CameraManager::CurrentCamera();

	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
}

void GraphicsObject_Wireframe::Draw()
{
	//The starting point of the IBO (index buffer object)
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Wireframe::RestoreState()
{
	// Restore state
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// ---  End of File ---