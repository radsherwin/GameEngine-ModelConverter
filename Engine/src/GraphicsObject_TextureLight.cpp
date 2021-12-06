//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "GraphicsObject_TextureLight.h"
#include "Mesh.h"
#include "TextureManager.h"
#include "Camera.h"
#include "CameraManager.h"
#include "ShaderObject.h"

using namespace Azul;


GraphicsObject_TextureLight::GraphicsObject_TextureLight(const Mesh* const _pMesh, const ShaderObject* const _pShaderObj, Texture::Name _name, Vect& LightColor, Vect& LightPos)
	: GraphicsObject(_pMesh, _pShaderObj),
	textName(_name)
{
	this->poLightColor = new Vect(LightColor);
	this->poLightPos = new Vect(LightPos);
	assert(poLightColor);
	assert(poLightPos);
}

GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
{
	delete this->poLightColor;
	delete this->poLightPos;
}

void GraphicsObject_TextureLight::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint* textureID = TextureManager::FindID(this->textName);
	//glBindTexture(GL_TEXTURE_2D, textureID[this->pMesh->texCount - 1 - this->pMesh->textureIDInt]);
	//glBindTexture(GL_TEXTURE_2D, textureID[this->pMesh->textureIDInt]);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphicsObject_TextureLight::SetDataGPU()
{
	// use this shader
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

	Vect light = *this->poLightPos;
	Vect color = *this->poLightColor;
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)&light);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)&color);
}

void GraphicsObject_TextureLight::Draw()
{
	//The starting point of the IBO
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_TextureLight::RestoreState()
{
	// undo the states you corrupted
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}



// ---  End of File ---