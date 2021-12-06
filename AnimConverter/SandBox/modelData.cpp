//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "modelData.h"

modelData::modelData()
	:	pModelName{0}, triCount(0), vbo_vert(), vbo_norm(), vbo_uv(),
		vbo_trilist(), text_color(), text_normal(), text_rough()
{
}

modelData::~modelData()
{

}

modelData::RENDER_MODE modelData::GetMode(int GLTF_TINY_VAL)
{
	RENDER_MODE renderMode;
	switch (GLTF_TINY_VAL)
	{

	case TINYGLTF_MODE_POINTS:
		renderMode = modelData::RENDER_MODE::MODE_POINTS;
		break;

	case TINYGLTF_MODE_LINE:
		renderMode = modelData::RENDER_MODE::MODE_LINE;
		break;

	case TINYGLTF_MODE_LINE_LOOP:
		renderMode = modelData::RENDER_MODE::MODE_LINE_LOOP;
		break;

	case TINYGLTF_MODE_LINE_STRIP:
		renderMode = modelData::RENDER_MODE::MODE_LINE_STRIP;
		break;

	case TINYGLTF_MODE_TRIANGLES:
		renderMode = modelData::RENDER_MODE::MODE_TRIANGLES;
		break;

	case TINYGLTF_MODE_TRIANGLE_STRIP:
		renderMode = modelData::RENDER_MODE::MODE_TRIANGLE_STRIP;
		break;

	case TINYGLTF_MODE_TRIANGLE_FAN:
		renderMode = modelData::RENDER_MODE::MODE_TRIANGLE_FAN;
		break;


	default:
		assert(false); //Failure
		renderMode = modelData::RENDER_MODE::DEFAULT;
		break;

	}

	return renderMode;
}

void modelData::Serialize(modelData_proto &out) const
{
	AZUL_UNUSED_VAR(out);

	vboData_proto *pVBO_proto;

	pVBO_proto = new vboData_proto();
	this->vbo_vert.Serialize(*pVBO_proto);
	out.set_allocated_vbo_vert(pVBO_proto);

	pVBO_proto = new vboData_proto();
	this->vbo_norm.Serialize(*pVBO_proto);
	out.set_allocated_vbo_norm(pVBO_proto);

	pVBO_proto = new vboData_proto();
	this->vbo_uv.Serialize(*pVBO_proto);
	out.set_allocated_vbo_uv(pVBO_proto);

	pVBO_proto = new vboData_proto();
	this->vbo_trilist.Serialize(*pVBO_proto);
	out.set_allocated_vbo_trilist(pVBO_proto);

	textureData_proto *pText_proto;

	pText_proto = new textureData_proto();
	this->text_color.Serialize(*pText_proto);
	out.set_allocated_text_color(pText_proto);

	pText_proto = new textureData_proto();
	this->text_normal.Serialize(*pText_proto);
	out.set_allocated_text_normal(pText_proto);

	pText_proto = new textureData_proto();
	this->text_rough.Serialize(*pText_proto);
	out.set_allocated_text_rough(pText_proto);

}

void modelData::Deserialize(const modelData_proto &in)
{
	this->vbo_vert.Deserialize(in.vbo_vert());
	this->vbo_norm.Deserialize(in.vbo_norm());
	this->vbo_uv.Deserialize(in.vbo_uv());
	this->vbo_trilist.Deserialize(in.vbo_trilist());
	
	this->text_color.Deserialize(in.text_color());
	this->text_normal.Deserialize(in.text_normal());
	this->text_rough.Deserialize(in.text_rough());
}

void modelData::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);

	Trace::out("\n");
	this->vbo_vert.Print("vbo_vert");
	Trace::out("\n");
	this->vbo_norm.Print("vbo_norm");
	Trace::out("\n");
	this->vbo_uv.Print("vbo_uv");
	Trace::out("\n");
	this->vbo_trilist.Print("vbo_trilist");
	Trace::out("\n");
	this->text_color.Print("text_color");
	Trace::out("\n");
	this->text_normal.Print("text_normal");
	Trace::out("\n");
	this->text_rough.Print("text_rough");
	Trace::out("\n");
}

// --- End of File ---


