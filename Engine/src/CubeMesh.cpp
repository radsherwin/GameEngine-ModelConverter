//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CubeMesh.h"
#include "MeshFileHdr.h"
#include "File.h"
#include "BoundingSphere.h"

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

struct Tri_index
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;
};

Tri_index triList[] =
{
	{  1,  0,  2 },
	{  4,  3,  5 },
	{  7,  6,  8 },
	{ 10,  9, 11 },
	{ 13, 12, 14 },
	{ 16, 15, 17 },
	{ 19, 18, 20 },
	{ 22, 21, 23 },
	{ 25, 24, 26 },
	{ 28, 27, 29 },
	{ 31, 30, 32 },
	{ 34, 33, 35 }
};


Vert_xyz  cubeData_xyz[] =
{
	// Triangle 0
	{ -0.25f,  0.25f, -0.25f },
	{ -0.25f, -0.25f, -0.25f },
	{ 0.25f, -0.25f,  -0.25f },

	// Triangle 1
	{ 0.25f,  -0.25f, -0.25f },
	{ 0.25f,   0.25f, -0.25f },
	{ -0.25f,  0.25f, -0.25f },

	// Triangle 2
	{ 0.25f, -0.25f, -0.25f },
	{ 0.25f, -0.25f,  0.25f },
	{ 0.25f,  0.25f, -0.25f },

	// Triangle 3
	{ 0.25f, -0.25f,  0.25f },
	{ 0.25f,  0.25f,  0.25f },
	{ 0.25f,  0.25f, -0.25f },

	// Triangle 4
	{ 0.25f, -0.25f,  0.25f },
	{ -0.25f, -0.25f, 0.25f },
	{ 0.25f,  0.25f,  0.25f },

	// Triangle 5
	{ -0.25f, -0.25f,  0.25f },
	{ -0.25f,  0.25f,  0.25f },
	{ 0.25f,   0.25f,  0.25f },

	// Triangle 6
	{ -0.25f, -0.25f,  0.25f },
	{ -0.25f, -0.25f, -0.25f },
	{ -0.25f,  0.25f,  0.25f },

	// Triangle 7
	{ -0.25f, -0.25f, -0.25f },
	{ -0.25f,  0.25f, -0.25f },
	{ -0.25f,  0.25f,  0.25f },

	// Triangle 8
	{ -0.25f, -0.25f,  0.25f },
	{ 0.25f, -0.25f,   0.25f },
	{ 0.25f, -0.25f,  -0.25f },

	// Triangle 9
	{ 0.25f, -0.25f,  -0.25f },
	{ -0.25f, -0.25f, -0.25f },
	{ -0.25f, -0.25f,  0.25f },

	// Triangle 10
	{ -0.25f,  0.25f, -0.25f },
	{ 0.25f,  0.25f,  -0.25f },
	{ 0.25f,  0.25f,   0.25f },

	// Triangle 11
	{ 0.25f,  0.25f,   0.25f },
	{ -0.25f,  0.25f,  0.25f },
	{ -0.25f,  0.25f, -0.25f }
};

Vert_uv  cubeData_uv[] =
{
	// Triangle 0
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },

	// Triangle 1
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },

	// Triangle 2
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 0.0f },

	// Triangle 3
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },

	// Triangle 4
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 5
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },

	// Triangle 6
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 7
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 8
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },

	// Triangle 9
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },

	// Triangle 10
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 11
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f }
};

Vert_nxnynz  cubeData_nxnynz[] =
{
	// Triangle 0
	{ -0.6f,  0.6f, -0.6f },
	{ -0.6f, -0.6f, -0.6f },
	{  0.6f,  -0.6f, -0.6f },

	// Triangle 1
	{  0.6f, -0.6f, -0.6f },
	{  0.6f,  0.6f, -0.6f },
	{ -0.6f,  0.6f, -0.6f },

	// Triangle 2
	{  0.6f, -0.6f, -0.6f },
	{  0.6f, -0.6f,  0.6f },
	{  0.6f,  0.6f, -0.6f },

	// Triangle 3
	{  0.6f, -0.6f,  0.6f },
	{  0.6f,  0.6f,  0.6f },
	{  0.6f,  0.6f, -0.6f },

	// Triangle 4
	{  0.6f, -0.6f, 0.6f },
	{ -0.6f, -0.6f, 0.6f },
	{  0.6f,  0.6f, 0.6f },

	// Triangle 5
	{ -0.6f, -0.6f, 0.6f },
	{ -0.6f,  0.6f, 0.6f },
	{  0.6f,  0.6f, 0.6f },

	// Triangle 6
	{ -0.6f, -0.6f,  0.6f },
	{ -0.6f, -0.6f, -0.6f },
	{ -0.6f,  0.6f,  0.6f },

	// Triangle 7
	{ -0.6f, -0.6f, -0.6f },
	{ -0.6f,  0.6f, -0.6f },
	{ -0.6f,  0.6f,  0.6f },

	// Triangle 8
	{ -0.6f, -0.6f,  0.6f },
	{  0.6f, -0.6f,  0.6f },
	{  0.6f, -0.6f, -0.6f },

	// Triangle 9
	{  0.6f, -0.6f, -0.6f },
	{ -0.6f, -0.6f, -0.6f },
	{ -0.6f, -0.6f,  0.6f },

	// Triangle 10
	{ -0.6f, 0.6f, -0.6f },
	{  0.6f, 0.6f, -0.6f },
	{  0.6f, 0.6f,  0.6f },

	// Triangle 11
	{  0.6f, 0.6f,  0.6f },
	{ -0.6f, 0.6f,  0.6f },
	{ -0.6f, 0.6f, -0.6f }
};

void CubeMesh::privCreateVAO(const char* const pMeshFileName)
{
	// future proofing it for a file
	assert(pMeshFileName);
	AZUL_UNUSED_VAR(pMeshFileName);
	
	this->numTris =  sizeof(triList) / sizeof(triList[0]);
	this->numVerts = sizeof(cubeData_xyz) / sizeof(cubeData_xyz[0]);
	// Find Bounding Volume - quick hack
	
	Vect* pVerts = new Vect[(unsigned int)this->numVerts];
	for (int i = 0; i < this->numVerts; i++)
	{
		pVerts[i].set(cubeData_xyz[i].x, cubeData_xyz[i].y, cubeData_xyz[i].z);
		//Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
	}

	assert(this->poRefSphere);
	this->poRefSphere->RitterSphere(pVerts, this->numVerts);
	//Trace::out("Ritter: cntr:%f %f %f \n   rad: %f \n", this->poRefSphere->cntr[x], this->poRefSphere->cntr[y], this->poRefSphere->cntr[z], this->poRefSphere->rad);
	//Trace::out("\n");

	delete[] pVerts;

	// Data is in RAM...
	// Configure and send data to GPU

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

	glGenBuffers(1, &this->vbo_index);
	assert(this->vbo_index != 0);

	// Load the verts data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->numVerts), cubeData_xyz, GL_STATIC_DRAW);

	// Vert data is location: 0  (used in vertex shader)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Load the norms data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_nxnynz) * this->numVerts), cubeData_nxnynz, GL_STATIC_DRAW);

	// normals data in location 1 (used in vertex shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_nxnynz), 0);
	glEnableVertexAttribArray(1);

	// Load the texts data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texts);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv) * this->numVerts), cubeData_uv, GL_STATIC_DRAW);

	// Texture data is location: 2  (used in vertex shader)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Load the index data: ---------------------------------------------------------

	// Bind our 2nd VBO as being the active buffer and storing index ) 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

	// Copy the index data to our buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), triList, GL_STATIC_DRAW);
}

CubeMesh::CubeMesh(const char* const pMeshFileName)
	: Mesh()
{
	assert(pMeshFileName);
	this->privCreateVAO(pMeshFileName);
}

CubeMesh::~CubeMesh()
{
	// remove anything dynamic here
}


// --- End of File ---