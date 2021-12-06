//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <sb7.h>

#include "CameraMesh.h"
#include "CameraManager.h"
#include "Camera.h"

namespace Azul
{
	struct Vert_uv
	{
		float u;
		float v;
	};

	struct Vert_nxnynz
	{
		float nx;
		float ny;
		float nz;
	};

	struct Vert_xyz
	{
		float x;
		float y;
		float z;
	};


	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	void CameraMesh::update()
	{
		this->privCreateVAO(0);
	}

	void CameraMesh::privCreateVAO(const char* const modelFileName)
	{

#define TRILIST_NUM_TRIANGLES (sizeof(triList)/sizeof(Tri_index))
#define SPHERE_DATA_NUM_VERTS (sizeof(pVerts_xyz)/sizeof(Vert_xyz))

		Vert_xyz pVerts_xyz[9];
		Vert_nxnynz pVerts_nxnynz[9];
		Vert_uv pVerts_uv[9];

		Tri_index triList[8];

		pVerts_xyz[0].x = -0.000000f;
		pVerts_xyz[0].y = 0.000000f;
		pVerts_xyz[0].z = 0.500000f;
		pVerts_nxnynz[0].nx = 0.000000f;
		pVerts_nxnynz[0].ny = 0.000000f;
		pVerts_nxnynz[0].nz = 0.000000f;
		pVerts_uv[0].u = 0.000000f;
		pVerts_uv[0].v = 0.000000f;


		triList[0].v0 = 0;
		triList[0].v1 = 1;
		triList[0].v2 = 2;

		triList[1].v0 = 0;
		triList[1].v1 = 2;
		triList[1].v2 = 3;

		triList[2].v0 = 0;
		triList[2].v1 = 3;
		triList[2].v2 = 4;

		triList[3].v0 = 0;
		triList[3].v1 = 4;
		triList[3].v2 = 1;

		// far
		triList[4].v0 = 1;
		triList[4].v1 = 2;
		triList[4].v2 = 3;

		// far
		triList[5].v0 = 3;
		triList[5].v1 = 4;
		triList[5].v2 = 1;

		// near
		triList[6].v0 = 5;
		triList[6].v1 = 6;
		triList[6].v2 = 7;

		// near
		triList[7].v0 = 7;
		triList[7].v1 = 8;
		triList[7].v2 = 5;

		Vect vTmp;

		Camera* pCam = CameraManager::Find(Camera::ID::MAIN);
		pCam->updateCamera();

		pCam->getPos(vTmp);
		pVerts_xyz[0].x = vTmp[x];
		pVerts_xyz[0].y = vTmp[y];
		pVerts_xyz[0].z = vTmp[z];
		pVerts_nxnynz[0].nx = 0.000000f;
		pVerts_nxnynz[0].ny = 0.000000f;
		pVerts_nxnynz[0].nz = 0.000000f;
		pVerts_uv[0].u = 0.000000f;
		pVerts_uv[0].v = 0.000000f;

		pCam->getFarTopRight(vTmp);
		pVerts_xyz[1].x = vTmp[x];
		pVerts_xyz[1].y = vTmp[y];
		pVerts_xyz[1].z = vTmp[z];
		pVerts_nxnynz[1].nx = 0.000000f;
		pVerts_nxnynz[1].ny = 0.000000f;
		pVerts_nxnynz[1].nz = 0.000000f;
		pVerts_uv[1].u = 0.000000f;
		pVerts_uv[1].v = 0.000000f;

		pCam->getFarTopLeft(vTmp);
		pVerts_xyz[2].x = vTmp[x];
		pVerts_xyz[2].y = vTmp[y];
		pVerts_xyz[2].z = vTmp[z];
		pVerts_nxnynz[2].nx = 0.000000f;
		pVerts_nxnynz[2].ny = 0.000000f;
		pVerts_nxnynz[2].nz = 0.000000f;
		pVerts_uv[2].u = 0.000000f;
		pVerts_uv[2].v = 0.000000f;

		pCam->getFarBottomLeft(vTmp);
		pVerts_xyz[3].x = vTmp[x];
		pVerts_xyz[3].y = vTmp[y];
		pVerts_xyz[3].z = vTmp[z];
		pVerts_nxnynz[3].nx = 0.000000f;
		pVerts_nxnynz[3].ny = 0.000000f;
		pVerts_nxnynz[3].nz = 0.000000f;
		pVerts_uv[3].u = 0.000000f;
		pVerts_uv[3].v = 0.000000f;

		pCam->getFarBottomRight(vTmp);
		pVerts_xyz[4].x = vTmp[x];
		pVerts_xyz[4].y = vTmp[y];
		pVerts_xyz[4].z = vTmp[z];
		pVerts_nxnynz[4].nx = 0.000000f;
		pVerts_nxnynz[4].ny = 0.000000f;
		pVerts_nxnynz[4].nz = 0.000000f;
		pVerts_uv[4].u = 0.000000f;
		pVerts_uv[4].v = 0.000000f;

		pCam->getNearTopRight(vTmp);
		pVerts_xyz[5].x = vTmp[x];
		pVerts_xyz[5].y = vTmp[y];
		pVerts_xyz[5].z = vTmp[z];
		pVerts_nxnynz[5].nx = 0.000000f;
		pVerts_nxnynz[5].ny = 0.000000f;
		pVerts_nxnynz[5].nz = 0.000000f;
		pVerts_uv[5].u = 0.000000f;
		pVerts_uv[5].v = 0.000000f;

		pCam->getNearTopLeft(vTmp);
		pVerts_xyz[6].x = vTmp[x];
		pVerts_xyz[6].y = vTmp[y];
		pVerts_xyz[6].z = vTmp[z];
		pVerts_nxnynz[6].nx = 0.000000f;
		pVerts_nxnynz[6].ny = 0.000000f;
		pVerts_nxnynz[6].nz = 0.000000f;
		pVerts_uv[6].u = 0.000000f;
		pVerts_uv[6].v = 0.000000f;

		pCam->getNearBottomLeft(vTmp);
		pVerts_xyz[7].x = vTmp[x];
		pVerts_xyz[7].y = vTmp[y];
		pVerts_xyz[7].z = vTmp[z];
		pVerts_nxnynz[7].nx = 0.000000f;
		pVerts_nxnynz[7].ny = 0.000000f;
		pVerts_nxnynz[7].nz = 0.000000f;
		pVerts_uv[7].u = 0.000000f;
		pVerts_uv[7].v = 0.000000f;

		pCam->getNearBottomRight(vTmp);
		pVerts_xyz[8].x = vTmp[x];
		pVerts_xyz[8].y = vTmp[y];
		pVerts_xyz[8].z = vTmp[z];
		pVerts_nxnynz[8].nx = 0.000000f;
		pVerts_nxnynz[8].ny = 0.000000f;
		pVerts_nxnynz[8].nz = 0.000000f;
		pVerts_uv[8].u = 0.000000f;
		pVerts_uv[8].v = 0.000000f;

		// future proofing it for a file
		AZUL_UNUSED_VAR(modelFileName);

		this->numVerts = SPHERE_DATA_NUM_VERTS;
		this->numTris = TRILIST_NUM_TRIANGLES;

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
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->numVerts), pVerts_xyz, GL_STATIC_DRAW);

		// Vert data is location: 0  (used in vertex shader)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
		glEnableVertexAttribArray(0);

		// Load the norms data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_nxnynz) * this->numVerts), pVerts_nxnynz, GL_STATIC_DRAW);

		// normals data in location 1 (used in vertex shader
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_nxnynz), 0);
		glEnableVertexAttribArray(1);

		// Load the texts data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv) * this->numVerts), pVerts_uv, GL_STATIC_DRAW);

		// Texture data is location: 2  (used in vertex shader)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
		glEnableVertexAttribArray(2);

		// Load the index data: ---------------------------------------------------------

		// Bind our 2nd VBO as being the active buffer and storing index ) 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

		// Copy the index data to our buffer 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), triList, GL_STATIC_DRAW);

	}

	CameraMesh::CameraMesh(const char* const modelFileName)
		: Mesh()
	{
		this->privCreateVAO(modelFileName);
	}

	CameraMesh::~CameraMesh()
	{
		// remove anything dynamic here
	}

}

// --- End of File ---