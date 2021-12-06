//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "meshData.h"

meshData::meshData()
	:	pVersion{0},
		mode{ nullptr },
		nodeNumber(nullptr),
		triCount(nullptr),
		vertCount(nullptr),
		vbo_vert(nullptr),
		vbo_norm(nullptr),
		vbo_uv(nullptr),
		vbo_index(nullptr),
		text_color(nullptr),
		materialIndex(nullptr),
		meshCount(0),
		texCount(0),
		nameCount(0),
		animCount(0)
{

	strcpy_s(this->pVersion, meshData::VERSION_NUM_BYTES, meshData::PROTO_VERSION);
	//Make sure version is within the bytes for serialization
	assert(strlen(this->pVersion) < meshData::VERSION_NUM_BYTES);
}

meshData::~meshData()
{
	delete[] this->mode;
	delete[] this->nodeNumber;
	delete[] this->triCount;
	delete[] this->vertCount;
	delete[] this->vbo_vert;
	delete[] this->vbo_norm;
	delete[] this->vbo_uv;
	delete[] this->vbo_index;
	delete[] this->vbo_color;
	delete[] this->text_color;
	delete[] this->materialIndex;
	delete[] this->anim_data;

	for(int i = 0; i < (int)this->nameCount;i++)
	{
		delete[] this->pName[i];
	}

	delete[] this->pName;
}

void meshData::Serialize(meshData_proto& out) const
{
	vboData_proto* pVBO_proto;

	std::string sVersion((const char*)this->pVersion, meshData::VERSION_NUM_BYTES);
	out.set_pversion(sVersion);

	out.set_meshcount(this->meshCount);
	out.set_texcount(this->texCount);
	out.set_animcount(this->animCount);
	out.set_namecount(this->nameCount);

	for(int i = 0; i < (int)this->animCount; i++)
	{
		animData_proto* pAnim = new animData_proto();
		this->anim_data[i].Serialize(*pAnim);
		out.mutable_anim_data()->AddAllocated(pAnim);
	}
	
	

	if(this->pName != nullptr)
	{
		for(int i = 0; i < (int)this->nameCount; i++)
		{
			std::string sName((const char*)this->pName[i], FILE_NAME_SIZE);
			out.add_pname(sName);
		}
		
	}

	for (unsigned int i = 0; i < this->meshCount; i++)
	{
		out.add_mode((meshData_proto_RENDER_MODE)(this->mode[i]));

		out.add_tricount(this->triCount[i]);
		out.add_vertcount(this->triCount[i]);

		out.add_nodenumber(this->nodeNumber[i]);

		out.add_materialindex(this->materialIndex[i]);

		pVBO_proto = new vboData_proto();
		this->vbo_vert[i].Serialize(*pVBO_proto);
		out.mutable_vbo_vert()->AddAllocated(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_norm[i].Serialize(*pVBO_proto);
		out.mutable_vbo_norm()->AddAllocated(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_uv[i].Serialize(*pVBO_proto);
		out.mutable_vbo_uv()->AddAllocated(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_index[i].Serialize(*pVBO_proto);
		out.mutable_vbo_index()->AddAllocated(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_color[i].Serialize(*pVBO_proto);
		out.mutable_vbo_color()->AddAllocated(pVBO_proto);
		
	}

	textureData_proto* pText_proto;
	for (unsigned int i = 0; i < this->texCount; i++)
	{
		pText_proto = new textureData_proto();
		this->text_color[i].Serialize(*pText_proto);
		out.mutable_text_color()->AddAllocated(pText_proto);
		
	}
}

void meshData::Deserialize(const meshData_proto& in)
{
	// CHECK the Version
	memcpy_s(this->pVersion, meshData::VERSION_NUM_BYTES, in.pversion().data(), meshData::VERSION_NUM_BYTES);
	assert(strcmp(this->pVersion, meshData::PROTO_VERSION) == 0);

	//Counts
	this->texCount = in.texcount();
	this->meshCount = in.meshcount();

	this->nameCount = in.namecount();
	this->animCount = in.animcount();

	if(in.meshcount() == 0)
	{
		this->materialIndex = nullptr;
		this->mode = nullptr;
		this->triCount = nullptr;
		this->vertCount = nullptr;
		this->vbo_vert = nullptr;
		this->vbo_norm = nullptr;
		this->vbo_uv = nullptr;
		this->vbo_index = nullptr;
		this->vbo_color = nullptr;
		this->nodeNumber = nullptr;
	}
	else
	{
		this->mode = new RENDER_MODE[in.meshcount()];
		this->triCount = new unsigned int[in.meshcount()];
		this->vertCount = new unsigned int[in.meshcount()];
		this->vbo_vert = new vboData[in.meshcount()];
		this->vbo_norm = new vboData[in.meshcount()];
		this->vbo_uv = new vboData[in.meshcount()];
		this->vbo_index = new vboData[in.meshcount()];
		this->vbo_color = new vboData[in.meshcount()];
		this->materialIndex = new unsigned int[in.meshcount()];
		this->nodeNumber = new unsigned int[in.animcount()];

		for (int i = 0; i < (int)this->meshCount; i++)
		{
			this->mode[i] = (RENDER_MODE)in.mode(i);
			this->triCount[i] = in.tricount(i);
			this->vertCount[i] = in.vertcount(i);
			this->vbo_vert[i].Deserialize(in.vbo_vert(i));
			this->vbo_norm[i].Deserialize(in.vbo_norm(i));
			this->vbo_uv[i].Deserialize(in.vbo_uv(i));
			this->vbo_index[i].Deserialize(in.vbo_index(i));
			this->vbo_color[i].Deserialize(in.vbo_color(i));
			this->materialIndex[i] = in.materialindex(i);
			this->nodeNumber[i] = in.nodenumber(i);
		}
	}
	

	if (in.texcount() == 0)
	{
		
		this->text_color = nullptr;
	}
	else
	{
		
		this->text_color = new textureData[in.texcount()];
		for (int i = 0; i < (int)this->texCount; i++)
		{
			this->text_color[i].Deserialize(in.text_color(i));
		}
	}
		

	if(in.animcount() == 0)
	{
		this->anim_data = nullptr;
	}
	else 
	{
		this->anim_data = new animData[in.animcount()];
		
		for (int i = 0; i < (int)in.animcount(); i++)
		{
			this->anim_data[i].Deserialize(in.anim_data(i));
		}

	}
	if(in.namecount()==0)
	{
		this->pName = nullptr;
	}
	{
		this->pName = new char* [in.namecount()];
		for (int i = 0; i < (int)this->nameCount; i++)
		{
			this->pName[i] = new char[FILE_NAME_SIZE];
			memcpy_s(this->pName[i], FILE_NAME_SIZE, in.pname(i).data(), in.pname(i).length());

		}
	}

	
}

void meshData::Print(const char* const _pName) const
{
	Trace::out("%s: \n", _pName);

	for (int i = 0; i < (int)this->meshCount; i++)
	{
		Trace::out("version: %s \n", this->pVersion);
		Trace::out("\n");
		if (i < (int)this->nameCount) Trace::out("pName: %s \n", this->pName[i]);
		this->vbo_vert[i].Print("vbo_vert", i);
		Trace::out("\n");
		this->vbo_norm[i].Print("vbo_norm", i);
		Trace::out("\n");
		this->vbo_uv[i].Print("vbo_uv", i);
		Trace::out("\n");
		this->vbo_index[i].Print("vbo_index", i);
		Trace::out("\n");
		this->vbo_color[i].Print("vbo_color", i);
		Trace::out("\n");
		

	}
	for (int i = 0; i < (int)this->texCount; i++)
	{
		this->text_color[i].Print("text_color", i);
		Trace::out("\n");
	}

	for(int i = 0; i < (int)this->animCount; i++)
	{
		this->anim_data[i].Print("anim_data", i);
		Trace::out("\n");
	}

}

// --- End of File ---


