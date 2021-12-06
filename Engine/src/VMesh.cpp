//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VMesh.h"
#include "MeshFileHdr.h"
#include "File.h"

using namespace Azul;

struct Vert_xyzuvn
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float nx;
	float ny;
	float nz;
};

struct Tri_index
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;
};

#define WRITE_DATA_TO_FILE 0

#if WRITE_DATA_TO_FILE

#define TRILIST_NUM_TRIANGLES (sizeof(triList)/sizeof(Tri_index))

Tri_index triList[] =
{

	{ 3, 2, 1 },	//fA
	{ 1, 0, 3 },	//fB
	{ 20, 16, 18 },	//fC
	{ 18, 22, 20 },	//fD
	{ 21, 17, 16 },	//fE
	{ 16, 20, 21 },	//fF
	{ 21, 23, 17 },	//fG
	{ 23, 19, 17 },	//fH
	{ 6, 7, 5 },	//fI	
	{ 5, 4, 6 },    //fJ
	{ 8, 9, 10 },	//fK
	{ 10, 11, 8 },	//fL
	{ 28, 24, 26 },	//fM
	{ 26, 30, 28 },	//fN
	{ 29, 25, 24 },	//fO
	{ 24, 28, 29 },	//fP
	{ 29, 31, 25 },	//fQ
	{ 31, 27, 25 },	//fR
	{ 13, 12, 15 },	//fS	
	{ 15, 14, 13 }, //fT
	{ 23, 18, 19 }, //fU
	{ 23, 22, 18 }, //fV
	{ 26, 27, 31 }, //fW
	{ 31, 30, 26 }  //fX


	// A 0
	// B 1
	// C 2
	// D 3
	// E 4
	// F 5
	// G 6
	// H 7
	// I 8
	// J 9
	
	// K 10
	// L 11
	// M 12
	// N 13
	// O 14
	// P 15
	// Q 16
	// R 17
	// S 18
	// T 19

};

#define MODEL_DATA_NUM_VERTS (sizeof(modelData)/sizeof(Vert_xyzuvn))

Vert_xyzuvn  modelData[] =
{

	{ -0.5f,  0.5f,  1.0f,		1.0f, 0.0f,		 0.0f, 0.0f, 0.038f		}, //A
	{  0.5f,  0.5f,  1.0f,		1.0f, 1.0f,		 0.25f,  -1.0f, 0.125f		}, //B
	{  0.5f,  1.0f,  1.0f,		1.0f, 1.0f,	     0.0f, -1.98f, 0.0f		}, //C
	{ -0.5f,  1.0f,  1.0f,		0.0f, 1.0f,		 0.167f,  0.0f, 0.083f  }, //D
	{  0.5f,  1.0f, -1.0f,		1.0f, 0.25f,		 0.18f,  0.0f,  -0.045f	}, //E
	{  0.5f,  0.5f, -1.0f,		1.0f, 0.25f,		0.285f,  0.0f, -0.07f	}, //F
	{ -0.5f,  1.0f, -1.0f,		0.0f, 0.25f,		0.0f,  0.8f, -0.1f		}, //G
	{ -0.5f,  0.5f, -1.0f,		0.0f, 0.25f,		-0.285f,  1.14f, -0.0714f		}, //H
	{ -0.5f, -1.0f,  1.0f,		0.0f, 0.75f,	-1.62f, 1.519f, 0.656f		}, //I
	{  0.5f, -1.0f,  1.0f,		1.0f, 0.75f,    -1.058f, -0.806f, -0.378f		}, //J
	{  0.5f, -1.5f,  0.75f,		1.0f, 0.7f,	-0.48f,  -1.39f,  -0.513f	}, //K
	{ -0.5f, -1.5f,  0.75f,		0.0f, 0.7f,	-0.79f,  -0.013f, 0.0269f	}, //L
	{ -0.5f,  0.0f, -1.75f,		0.0f, 0.0f,		 -0.91f,  1.28f, 0.633f		}, //M
	{ -0.5f,  0.5f, -1.0f,		0.0f, 0.25f,		-1.695f,  1.055f, 0.3839f	}, //N
	{  0.5f,  0.5f, -1.0f,		1.0f, 0.25f,		-1.334f,  0.4669f, 0.0347f	}, //O
	{  0.5f,  0.0f, -1.75f,		1.0f, 0.0f,		-0.636f,  -0.037f, 0.074f	},  //P
	
	{ -0.5f,  1.0f,  1.0f,		0.0f, 1.0f,		 0.167f,  0.0f, 0.083f  }, //16
	{  0.5f,  1.0f,  1.0f,		1.0f, 1.0f,	     0.0f, -1.98f, 0.0f		}, //17
	{ -0.5f,  0.5f,  1.0f,		1.0f, 0.0f,		 0.0f, 0.0f, 0.038f		}, //18
	{  0.5f,  0.5f,  1.0f,		1.0f, 1.0f,		 0.25f,  -1.0f, 0.125f		}, //19
	{ -0.5f,  1.0f, -1.0f,		0.0f, 0.25f,		0.0f,  0.8f, -0.1f		}, //20
	{  0.5f,  1.0f, -1.0f,		1.0f, 0.25f,		 0.18f,  0.0f,  -0.045f	}, //21
	{ -0.5f,  0.5f, -1.0f,		0.0f, 0.25f,		-0.285f,  1.14f, -0.0714f		}, //22
	{  0.5f,  0.5f, -1.0f,		1.0f, 0.25f,		0.285f,  0.0f, -0.07f	}, //23
	{ -0.5f, -1.0f,  1.0f,		0.0f, 0.75f,	-1.62f, 1.519f, 0.656f		}, //24
	{  0.5f, -1.0f,  1.0f,		1.0f, 0.75f,    -1.058f, -0.806f, -0.378f		}, //25
	{ -0.5f, -1.5f,  0.75f,		0.0f, 0.7f,	-0.79f,  -0.013f, 0.0269f	}, //26
	{  0.5f, -1.5f,  0.75f,		1.0f, 0.7f,	-0.48f,  -1.39f,  -0.513f	}, //27
	{ -0.5f,  0.5f, -1.0f,		0.0f, 0.25f,		-1.695f,  1.055f, 0.3839f	}, //28
	{  0.5f,  0.5f, -1.0f,		1.0f, 0.25f,		-1.334f,  0.4669f, 0.0347f	}, //29
	{ -0.5f,  0.0f, -1.75f,		0.0f, 0.0f,		 -0.91f,  1.28f, 0.633f		}, //30
	{  0.5f,  0.0f, -1.75f,		1.0f, 0.0f,		-0.636f,  -0.037f, 0.074f	},  //31


};

#endif

void VMesh::privCreateVAO(const char* const pMeshFileName)
{
	// future proofing it for a file
	assert(pMeshFileName);

	//File stuff
	File::Handle fh;
	File::Error ferror;

	//create a header
	MeshFileHdr meshHdr;

#if WRITE_DATA_TO_FILE

	this->numVerts = MODEL_DATA_NUM_VERTS;
	this->numTris = TRILIST_NUM_TRIANGLES;

	//object name
	strncpy_s(meshHdr.objName, MeshFileHdr::OBJECT_NAME_SIZE, "VMesh", _TRUNCATE);

	//vertex buffer
	meshHdr.numVerts = this->numVerts;
	meshHdr.vertBufferOffset = 0;

	//trilist index
	meshHdr.numTriList = this->numTris;
	meshHdr.triListBufferOffset = 0;

	//write to a data file
	ferror = File::Open(fh, pMeshFileName, File::Mode::READ_WRITE);
	assert(ferror == File::Error::SUCCESS);

	//write the header
	ferror = File::Write(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	//write the vert buffer data
	ferror = File::Tell(fh, meshHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, modelData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	//write index buffer
	ferror = File::Tell(fh, meshHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, triList, sizeof(Tri_index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	//Finish the write
	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	//rewind and overwrite mesh hdr
	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	//VERIFY

	MeshFileHdr meshHdr2;

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &meshHdr2, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	assert(memcmp(&meshHdr, &meshHdr2, sizeof(MeshFileHdr)) == 0);

	//CLOSE

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

#endif

	//Read the data from the file ONLY
	ferror = File::Open(fh, pMeshFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	//Read the hdr
	ferror = File::Read(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	//using the hdr, allocate the space for the buffers
	this->numVerts = meshHdr.numVerts;
	this->numTris = meshHdr.numTriList;

	//allocate the buffers
	Vert_xyzuvn* pMeshData = new Vert_xyzuvn[(unsigned int)meshHdr.numVerts];
	Tri_index* pTriList = new Tri_index[(unsigned int)meshHdr.numTriList];

	// Read verts
	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, pMeshData, sizeof(Vert_xyzuvn) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	//Read trilist
	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, pTriList, sizeof(Tri_index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	//Data is in ram
	//Configure and send data to GPU

	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	// Create a VBO
	glGenBuffers(1, &this->vbo_verts);
	assert(this->vbo_verts != 0);

	glGenBuffers(1, &this->vbo_index);
	assert(this->vbo_index != 0);


	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyzuvn) * this->numVerts), pMeshData, GL_STATIC_DRAW);

	// Define an array of generic vertex attribute data
	// Vert data is location: 0  (used in vertex shader)
		//         Todo --> make a table or enum not {0,1,2}
	void* offsetVert = (void*)((unsigned int)&pMeshData[0].x - (unsigned int)pMeshData);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetVert);
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertex shader)
	void* offsetTex = (void*)((unsigned int)&pMeshData[0].u - (unsigned int)pMeshData);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetTex);
	glEnableVertexAttribArray(1);

	// normals data in location 2 (used in vertex shader
	void* offsetNorm = (void*)((unsigned int)&pMeshData[0].nx - (unsigned int)pMeshData);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyzuvn), offsetNorm);
	glEnableVertexAttribArray(2);

	delete pMeshData;

	//load the index data

	//bind our 2nd VBO as being the active buffer and storing index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

	//copy the index data to our buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), pTriList, GL_STATIC_DRAW);

	delete pTriList;
}

VMesh::VMesh(const char* const pMeshFileName)
	: Mesh()
{
	assert(pMeshFileName);
	this->privCreateVAO(pMeshFileName);
}

VMesh::~VMesh()
{
	// remove anything dynamic here
}


// --- End of File ---