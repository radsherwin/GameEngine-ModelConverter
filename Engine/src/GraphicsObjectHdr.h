#ifndef GRAPHICS_OBJECT_HDR_H
#define GRAPHICS_OBJECT_HDR_H

#include <vector>

#include "GraphicsObject.h"
#include "Texture.h"
#include "Vect.h"

using namespace Azul;

class GraphicsObjectHdr
{
public:
	GraphicsObjectHdr(GraphicsObject* _pGraphicsObj);
	GraphicsObjectHdr(const Mesh* const pMesh, const ShaderObject* const);

	GraphicsObjectHdr();
	GraphicsObjectHdr(const GraphicsObjectHdr&) = delete;
	GraphicsObjectHdr& operator=(const GraphicsObjectHdr&) = delete;
	virtual ~GraphicsObjectHdr();

	void Set_FlatTexture(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj, Texture::Name _name = Texture::Name::PINK_ERROR);
	void Set_ConstColor(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj, Azul::Vect& color, Azul::Vect& pos);
	void Set_ColorByPosition(const std::vector<Mesh*> mesh, const ShaderObject* const pShaderObj);
	void Set_ColorSpecLighting(const std::vector<Mesh*> _pMesh, const ShaderObject* const _pShaderObj, Azul::Vect& color, Azul::Vect& pos);
	void Set_Null(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj);
	void Set_TextureLight(const std::vector<Mesh*> pMesh, const ShaderObject* const pShaderObj, Azul::Vect& color, Azul::Vect& pos, Texture::Name  _name = Texture::Name::PINK_ERROR);
	void Set_Wireframe(const std::vector<Mesh*> _pMesh, const ShaderObject* const _pShaderObj);
	void Set_WireframeConstColor(const std::vector<Mesh*> mesh, const ShaderObject* const pShaderObj, const Vect& wireColor);

	//Non vector version
	void Set_FlatTexture(const Mesh* const pMesh, const ShaderObject* const pShaderObj, Texture::Name _name = Texture::Name::PINK_ERROR);
	void Set_ConstColor(const Mesh* const pMesh, const ShaderObject* const pShaderObj, Azul::Vect& color, Azul::Vect& pos);
	void Set_ColorByPosition(const Mesh* const mesh, const ShaderObject* const pShaderObj);
	void Set_ColorSpecLighting(const Mesh* const _pMesh, const ShaderObject* const _pShaderObj, Azul::Vect& color, Azul::Vect& pos);
	void Set_Null(const Mesh* const pMesh, const ShaderObject* const pShaderObj);
	void Set_TextureLight(const Mesh* const pMesh, const ShaderObject* const pShaderObj, Azul::Vect& color, Azul::Vect& pos, Texture::Name  _name = Texture::Name::PINK_ERROR);
	void Set_Wireframe(const Mesh* const _pMesh, const ShaderObject* const _pShaderObj);
	void Set_WireframeConstColor(const Mesh* const mesh, const ShaderObject* const pShaderObj, const Vect& wireColor);

	void Connect(GraphicsObject* _pGraphicsObj);
	void SetNext(GraphicsObjectHdr* _pNextHdr);
	void AddToEnd(GraphicsObject* _pGraphicsObj);

	GraphicsObjectHdr* GetNext();


	GraphicsObjectHdr* pNext;
	GraphicsObject* poGraphicsObject;
};

#endif
