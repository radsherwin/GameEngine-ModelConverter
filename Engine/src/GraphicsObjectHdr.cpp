#include "GraphicsObjectHdr.h"

#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_ColorSpecLighting.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_Null.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_WireframeConstantColor.h"

GraphicsObjectHdr::GraphicsObjectHdr(GraphicsObject* _pGraphicsObj)
	: pNext(nullptr), poGraphicsObject(nullptr)
{
	this->poGraphicsObject = _pGraphicsObj;
}

GraphicsObjectHdr::GraphicsObjectHdr(const Mesh* const pMesh, const ShaderObject* const pShaderObj)
	: pNext(nullptr), poGraphicsObject(nullptr)
{
	this->poGraphicsObject = new GraphicsObject_Null(pMesh, pShaderObj);
}

GraphicsObjectHdr::GraphicsObjectHdr()
	: pNext(nullptr), poGraphicsObject(nullptr)
{}

GraphicsObjectHdr::~GraphicsObjectHdr()
{
	delete this->poGraphicsObject;
}

void GraphicsObjectHdr::Set_FlatTexture(const std::vector<Mesh*>pMesh, const ShaderObject* const pShaderObj,
	Texture::Name _name)
{
	for(auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_FlatTexture(*it, pShaderObj, _name));
	}
}

void GraphicsObjectHdr::Set_ConstColor(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj,
	Vect& color, Vect& pos)
{
	GraphicsObjectHdr* current = this->pNext;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_ConstColor(*it, pShaderObj, color, pos));
	}
}

void GraphicsObjectHdr::Set_ColorByPosition(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj)
{
	GraphicsObjectHdr* current = this->pNext;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_ColorByPosition(*it, pShaderObj));
	}
}

void GraphicsObjectHdr::Set_ColorSpecLighting(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj,
	Vect& color, Vect& pos)
{
	GraphicsObjectHdr* current = this->pNext;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_ColorSpecLighting(*it, pShaderObj, color, pos));
	}
}

void GraphicsObjectHdr::Set_Null(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj)
{
	GraphicsObjectHdr* current = this->pNext;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_Null(*it, pShaderObj));
	}
}

void GraphicsObjectHdr::Set_TextureLight(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj, Vect& color, Vect& pos, Texture::Name _name)
{
	int i = 0;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_TextureLight(*it, pShaderObj,_name,color,pos));
		i++;
	}
}

void GraphicsObjectHdr::Set_Wireframe(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj)
{
	GraphicsObjectHdr* current = this->pNext;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_Wireframe(*it, pShaderObj));
	}
}

void GraphicsObjectHdr::Set_WireframeConstColor(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj,
	const Vect& wireColor)
{
	GraphicsObjectHdr* current = this->pNext;
	for (auto it = pMesh.begin(); it != pMesh.end(); it++)
	{
		AddToEnd(new GraphicsObject_WireframeConstantColor(*it, pShaderObj, wireColor));
	}
}

//--------------------------------------------------------------------------------
// Non vector GraphicsObjects
//--------------------------------------------------------------------------------

void GraphicsObjectHdr::Set_FlatTexture(const Mesh* const pMesh, const ShaderObject* const pShaderObj,
	Texture::Name _name)
{
	this->poGraphicsObject = new GraphicsObject_FlatTexture(pMesh, pShaderObj, _name);
}

void GraphicsObjectHdr::Set_ConstColor(const Mesh* const pMesh, const ShaderObject* const pShaderObj, Vect& color,
	Vect& pos)
{
	this->poGraphicsObject = new GraphicsObject_ConstColor(pMesh,pShaderObj,color, pos);
}

void GraphicsObjectHdr::Set_ColorByPosition(const Mesh* const pMesh, const ShaderObject* const pShaderObj)
{
	this->poGraphicsObject = new GraphicsObject_ColorByPosition(pMesh,pShaderObj);
}

void GraphicsObjectHdr::Set_ColorSpecLighting(const Mesh* const pMesh, const ShaderObject* const pShaderObj,
	Vect& color, Vect& pos)
{
	this->poGraphicsObject = new GraphicsObject_ColorSpecLighting(pMesh, pShaderObj, color, pos);
}

void GraphicsObjectHdr::Set_Null(const Mesh* const pMesh, const ShaderObject* const pShaderObj)
{
	this->poGraphicsObject = new GraphicsObject_Null(pMesh, pShaderObj);
}

void GraphicsObjectHdr::Set_TextureLight(const Mesh* const pMesh, const ShaderObject* const pShaderObj, Vect& color, Vect& pos,
	Texture::Name _name)
{
	this->poGraphicsObject = new GraphicsObject_TextureLight(pMesh, pShaderObj, _name, color, pos);
}

void GraphicsObjectHdr::Set_Wireframe(const Mesh* const pMesh, const ShaderObject* const pShaderObj)
{
	this->poGraphicsObject = new GraphicsObject_Wireframe(pMesh, pShaderObj);
}

void GraphicsObjectHdr::Set_WireframeConstColor(const Mesh* const pMesh, const ShaderObject* const pShaderObj,
	const Vect& wireColor)
{
	this->poGraphicsObject = new GraphicsObject_WireframeConstantColor(pMesh, pShaderObj, wireColor);
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void GraphicsObjectHdr::Connect(GraphicsObject* _pGraphicsObj)
{
	this->poGraphicsObject = _pGraphicsObj;
}

void GraphicsObjectHdr::SetNext(GraphicsObjectHdr* _pNextHdr)
{
	this->pNext = _pNextHdr;
}

void GraphicsObjectHdr::AddToEnd(GraphicsObject* _pGraphicsObj)
{
	if(this->poGraphicsObject== nullptr)
	{
		this->poGraphicsObject = _pGraphicsObj;
	}
	else
	{
		GraphicsObjectHdr* tmp = this;
		while(tmp->pNext!= nullptr)
		{
			tmp = tmp->pNext;
		}

		if(tmp->pNext == nullptr)
		{
			tmp->pNext = new GraphicsObjectHdr(_pGraphicsObj);
		}
	}
}

GraphicsObjectHdr* GraphicsObjectHdr::GetNext()
{
	return this->pNext;
}


