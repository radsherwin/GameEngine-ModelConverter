//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject_FlatTexture.h"
#include "TextureManager.h"
#include "Mesh.h"
#include "Camera.h"
#include "CameraManager.h"

using namespace Azul;


GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(const Mesh* const _pMesh, const ShaderObject* const _pShaderObj, Texture::Name _name)
	: GraphicsObject(_pMesh, _pShaderObj), textName(_name)
{
	assert(this->pMesh);
	assert(this->pShaderObj);
	assert(this->poWorld);
	
}

void GraphicsObject_FlatTexture::SetState()
{
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture
	const GLuint* textureID = TextureManager::FindID(this->textName);

	if(this->textName == Texture::Name::PINK_ERROR) glBindTexture(GL_TEXTURE_2D, textureID[0]);
	else glBindTexture(GL_TEXTURE_2D, textureID[this->pMesh->textureIDInt]);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);  
}

void GraphicsObject_FlatTexture::SetDataGPU()
{
	// use this shader
	this->pShaderObj->SetActive();

	// set the vao
	//turn to loop
	glBindVertexArray(this->GetMesh()->vao);

	Camera* pCam = CameraManager::CurrentCamera();

	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();
	

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
}

void GraphicsObject_FlatTexture::Draw()
{
	//the starting point of the IBO
	//turn to loop
	//glDepthFunc(GL_ALWAYS);
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_FlatTexture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

//--- End of File -------------------------------------------------------------
