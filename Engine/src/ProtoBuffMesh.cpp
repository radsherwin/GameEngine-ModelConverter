//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ProtoBuffMesh.h"

#include "AnimationManager.h"
#include "TextureManager.h"
#include "MeshFileHdr.h"
#include "File.h"

using namespace Azul;

struct Vert_xyz
{
	float x;
	float y;
	float z;
};

struct Vert_nxnynz
{
	float nx;
	float ny;
	float nz;
};

struct Vert_uv
{
	float u;
	float v;
};

struct Vert_color
{
	float r;
	float g;
	float b;
	float a;
};

ProtoBuffMesh::ProtoBuffMesh(meshData& mB, unsigned int index)
	: Mesh()
{
	this->privCreateVAO(mB, index);
}

ProtoBuffMesh::~ProtoBuffMesh()
{
	// remove anything dynamic here
}

void ProtoBuffMesh::privCreateVAO(meshData& mB, unsigned int index)
{
	Trace::out("Building mesh: %s %d\n", mB.pName[index], index);

	this->pAnim = new Animation();
	this->pAnim->parent = mB.anim_data[index].parent;
	this->pAnim->joint = mB.nodeNumber[index];
	this->pAnim->frames = mB.anim_data[index].frameBucketCount;
	this->pAnim->protoName = mB.pName[index];

	Bone tmp;
	this->pAnim->meshBone.reserve(mB.anim_data[index].frameBucketCount);
	for(int i = 0; i < mB.anim_data[index].frameBucketCount; i++)
	{
		float* pTrans = (float*)&mB.anim_data[index].bone_data[i].pTranslation[0];
		tmp.T.set(*&pTrans[0], *&pTrans[1], *&pTrans[2]);

		float* pQuat = (float*)&mB.anim_data[index].bone_data[i].pRotation[0];
		tmp.Q.set(*&pQuat[0], *&pQuat[1], *&pQuat[2], *&pQuat[3]);

		float* pScale = (float*)&mB.anim_data[index].bone_data[i].pScale[0];
		tmp.S.set(*&pScale[0], *&pScale[1], *&pScale[2]);

		this->pAnim->meshBone.push_back(tmp);
	}
	AnimationManager::Add(this->pAnim);

	if(mB.materialIndex == nullptr)
	{
		this->textureIDInt = 0;
	}
	else 
	{
		this->textureIDInt = mB.materialIndex[index];
	}
	this->texCount = (int)mB.texCount;

	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	// Create a VBO
	glGenBuffers(1, &this->vbo_verts);
	assert(this->vbo_verts != 0);

	glGenBuffers(1, &this->vbo_norms);
	assert(this->vbo_norms != 0);

	glGenBuffers(1, &this->vbo_texts);
	assert(this->vbo_texts != 0);

	glGenBuffers(1, &this->vbo_color);
	assert(this->vbo_color != 0);

	glGenBuffers(1, &this->vbo_index);
	assert(this->vbo_index != 0);

	// General stuff

	assert(mB.mode[index] == meshData::RENDER_MODE::MODE_TRIANGLES);

	this->numTris = (int)mB.triCount[index];
	this->numVerts = (int)mB.vertCount[index];

	assert(this->numTris > 0);
	assert(this->numVerts > 0);

	// Load the verts data: ---------------------------------------------------------
	if (mB.vbo_vert != nullptr && mB.vbo_vert[index].enabled)
	{
		assert(mB.vbo_vert[index].targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

		// load the data to the GPU
		assert(mB.vbo_vert[index].poData);
		assert(mB.vbo_vert[index].dataSize > 0);
		assert(mB.vbo_vert[index].count * sizeof(Vert_xyz) == mB.vbo_vert[index].dataSize);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_vert[index].dataSize), mB.vbo_vert[index].poData, GL_STATIC_DRAW);

		// Vert data is location: 0  (used in vertex shader)
		assert(0 == mB.vbo_vert[index].attribIndex);
		assert(mB.vbo_vert[index].vboType == vboData::VBO_TYPE::VEC3);
		assert(mB.vbo_vert[index].componentType == vboData::VBO_COMPONENT::FLOAT);
		glVertexAttribPointer(mB.vbo_vert[index].attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
		glEnableVertexAttribArray(mB.vbo_vert[index].attribIndex);

		//Get Verts for Bounding Sphere
		Vert_xyz* meshXYZ = (Vert_xyz*)(mB.vbo_vert[index].poData);
		Vect* pVerts = new Vect[mB.vbo_vert[index].count];
		for (int i = 0; i < (int)mB.vbo_vert[index].count; i++)
		{
			pVerts[i].set(meshXYZ[i].x, meshXYZ[i].y, meshXYZ[i].z);
			//Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
		}

		assert(this->poRefSphere);
		this->poRefSphere->RitterSphere(pVerts, (int)mB.vbo_vert[index].count);

		//Cleaning up verts
		delete[] pVerts;
	}
	else
	{
		this->poRefSphere = nullptr;
	}

	// Load the norms data: ---------------------------------------------------------

	if (mB.vbo_norm != nullptr && mB.vbo_norm[index].enabled)
	{
		assert(mB.vbo_norm[index].targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

		// load the data to the GPU
		assert(mB.vbo_norm[index].poData);
		assert(mB.vbo_norm[index].dataSize > 0);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_norm[index].dataSize), mB.vbo_norm[index].poData, GL_STATIC_DRAW);

		// normals data in location 1 (used in vertex shader)
		assert(1 == mB.vbo_norm[index].attribIndex);
		assert(mB.vbo_norm[index].vboType == vboData::VBO_TYPE::VEC3);
		assert(mB.vbo_norm[index].componentType == vboData::VBO_COMPONENT::FLOAT);
		glVertexAttribPointer(mB.vbo_norm[index].attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_nxnynz), 0);
		glEnableVertexAttribArray(mB.vbo_norm[index].attribIndex);
	}


	// Load the texts data: ---------------------------------------------------------

	if (mB.vbo_uv != nullptr && mB.vbo_uv[index].enabled)
	{
		assert(mB.vbo_uv[index].targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texts);

		// load the data to the GPU
		assert(mB.vbo_uv[index].poData);
		assert(mB.vbo_uv[index].dataSize > 0);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_uv[index].dataSize), mB.vbo_uv[index].poData, GL_STATIC_DRAW);

		// Texture data is location: 2  (used in vertex shader)
		assert(2 == mB.vbo_uv[index].attribIndex);
		assert(mB.vbo_uv[index].vboType == vboData::VBO_TYPE::VEC2);
		assert(mB.vbo_uv[index].componentType == vboData::VBO_COMPONENT::FLOAT);
		glVertexAttribPointer(mB.vbo_uv[index].attribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
		glEnableVertexAttribArray(mB.vbo_uv[index].attribIndex);
	}

	// Load the color data: ---------------------------------------------------------

	if (mB.vbo_color != nullptr && mB.vbo_color[index].enabled)
	{
		assert(mB.vbo_color[index].targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_color);

		// load the data to the GPU
		assert(mB.vbo_color[index].poData);
		assert(mB.vbo_color[index].dataSize > 0);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_color[index].dataSize), mB.vbo_color[index].poData, GL_STATIC_DRAW);

		// Texture data is location: 4  (used in vertex shader)
		assert(4 == mB.vbo_color[index].attribIndex);
		assert(mB.vbo_color[index].vboType == vboData::VBO_TYPE::VEC4);
		assert(mB.vbo_color[index].componentType == vboData::VBO_COMPONENT::FLOAT);
		glVertexAttribPointer(mB.vbo_color[index].attribIndex, 4, GL_FLOAT, GL_FALSE, sizeof(Vert_color), 0);
		glEnableVertexAttribArray(mB.vbo_color[index].attribIndex);
	}

	// Load the index data: ---------------------------------------------------------
	if (mB.vbo_index != nullptr && mB.vbo_index[index].enabled)
	{
		// Bind our 2nd VBO as being the active buffer and storing index ) 
		assert(mB.vbo_index[index].targetType == vboData::VBO_TARGET::ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

		// Copy the index data to our buffer 
		assert(mB.vbo_index[index].vboType == vboData::VBO_TYPE::SCALAR);
		assert(mB.vbo_index[index].componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);
		assert(mB.vbo_index[index].dataSize > 0);
		assert(mB.vbo_index[index].poData);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_index[index].dataSize), mB.vbo_index[index].poData, GL_STATIC_DRAW);
	}

}



// --- End of File ---
