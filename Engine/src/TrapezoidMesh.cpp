//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TrapezoidMesh.h"
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

	/*{ 1, 0,4 },
	{ 2, 0,1 },
	{ 3, 0,2 },
	{ 4, 0,3 },
	{ 4, 2,1 },
	{ 4, 3,2 }*/

	
	{ 2, 1, 0 },	//A
	{ 10, 9, 8 },	//B
	{ 9, 10,11 },	//D
	{ 4, 5, 3 },	//F
	{ 10, 12, 13 },	//E
	{ 12, 10, 8 },	//C
	{ 1, 2, 6 },	//G
	{ 7, 6, 2 },	//H
	{ 5, 6, 7 },	//I	
	{ 3, 5, 7 }     //J

};

#define MODEL_DATA_NUM_VERTS (sizeof(modelData)/sizeof(Vert_xyzuvn))

Vert_xyzuvn  modelData[] =
{

	{  0.0f,  0.5f,  1.0f,		0.5f, 0.0f,		 0.0f, 0.8f, 0.18f }, //0
	{ -0.5f, -0.5f,  1.0f,		0.0f, 1.0f,		 0.0f,  0.5f, 0.15f }, //1
	{  0.5f, -0.5f,  1.0f,		1.0f, 1.0f,	     1.19f, 0.3f, 0.13f}, //2
	{  0.5f, -0.5f, -1.0f,		1.0f, 0.0f,		 1.05f,  0.76f, -0.23f }, //3
	{  0.0f,  0.5f, -1.0f,		0.5f, 1.0f,		 0.0f,  0.89f,  -0.1f }, //4
	{ -0.5f, -0.5f, -1.0f,		0.0f, 0.0f,		-0.85f,  0.8f, -0.19f },  //5
	{ -0.5f, -0.5f,  0.0f,		0.0f, 0.5f,		0.0f,  0.0f, 0.0f },  //6
	{  0.5f, -0.5f,  0.0f,		1.0f, 0.5f,		0.0f,  0.33f, 0.0f },  //7
	{  0.0f,  0.5f,  1.0f,		0.33f, 1.0f,		 0.0f, 0.8f, 0.18f }, //8
	{  0.5f, -0.5f,  1.0f,		0.66f, 1.0f,	     1.19f, 0.3f, 0.13f}, //9
	{  0.0f,  0.5f, -1.0f,		0.33f, 0.0f,		 0.0f,  0.89f,  -0.1f }, //10
	{  0.5f, -0.5f, -1.0f,		0.66f, 0.0f,		 1.05f,  0.76f, -0.23f }, //11
	{ -0.5f, -0.5f,  1.0f,		0.0f, 1.0f,		 0.0f,  0.5f, 0.15f }, //12
	{ -0.5f, -0.5f, -1.0f,		0.0f, 0.0f,		-0.85f,  0.8f, -0.19f }  //13

};

#endif

void TrapezoidMesh::privCreateVAO(const char* const pMeshFileName)
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
	strncpy_s(meshHdr.objName, MeshFileHdr::OBJECT_NAME_SIZE, "Trapezoid", _TRUNCATE);

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

TrapezoidMesh::TrapezoidMesh(const char* const pMeshFileName)
	: Mesh()
{
	assert(pMeshFileName);
	this->privCreateVAO(pMeshFileName);
}

TrapezoidMesh::~TrapezoidMesh()
{
	// remove anything dynamic here
}


// --- End of File ---