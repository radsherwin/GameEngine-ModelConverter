//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_ColorByPosition.h"
#include "Camera.h"
#include "CameraManager.h"

using namespace Azul;


GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(const Mesh* const mesh, const ShaderObject* const pShaderObj)
	: GraphicsObject(mesh, pShaderObj)
{
	assert(this->pMesh);
	assert(this->pShaderObj);
	assert(this->poWorld);
}

void GraphicsObject_ColorByPosition::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_ColorByPosition::SetDataGPU()
{
	this->pShaderObj->SetActive();

	// set the vao
	glBindVertexArray(this->GetMesh()->vao);

	Camera* pCam = CameraManager::CurrentCamera();

	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
}

void GraphicsObject_ColorByPosition::Draw()
{
	//the starting point of the IBO
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
	
}

void GraphicsObject_ColorByPosition::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}


// --- End of File ---