//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "meshData.h"
#include "GLTF.h"
#include "File.h"
#include "MathEngine.h"

using namespace Azul;
using namespace tinygltf;

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


Tri_index pyramid_triList[] =
{
	{  1,  0,  2},
	{  3,  2,  0},
	{  5,  4,  6},
	{  7,  5,  6},
	{  9,  8, 10},
	{ 11,  9, 10},
	{ 13, 12, 14},
	{ 15, 13, 14},
	{ 17, 16, 18},
	{ 19, 18, 16},
	{ 21, 20, 22},
	{ 23, 22, 20}
};

Vert_xyz  pyramidData_xyz[] =
{
	{-0.25f,   0.0f,  -0.25f  },
	{-0.25f,  -0.0f,  -0.25f  },
	{ 0.25f,  -0.0f,  -0.25f  },
	{  0.0f,   1.0f,   -0.0f  },
	{ 0.25f,  -0.0f,  -0.25f  },
	{ 0.25f,  -0.0f,   0.25f  },
	{  0.0f,   1.0f,   -0.0f  },
	{ 0.25f,   0.0f,   0.25f  },
	{ 0.25f,  -0.0f,   0.25f  },
	{-0.25f,  -0.0f,   0.25f  },
	{  0.0f,   1.0f,    0.0f  },
	{ -0.0f,   1.0f,    0.0f  },
	{-0.25f,  -0.0f,   0.25f  },
	{-0.25f,  -0.0f,  -0.25f  },
	{ -0.0f,   1.0f,    0.0f  },
	{ -0.0f,   1.0f,   -0.0f  },
	{-0.25f,  -0.0f,   0.25f  },
	{ 0.25f,  -0.0f,   0.25f  },
	{ 0.25f,  -0.0f,  -0.25f  },
	{-0.25f,  -0.0f,  -0.25f  },
	{ -0.0f,   1.0f,   -0.0f  },
	{  0.0f,   1.0f,   -0.0f  },
	{  0.0f,   1.0f,    0.0f  },
	{ -0.0f,   1.0f,    0.0f  }

};

Vert_nxnynz pyramidData_nxnynz[]
{
	{  -0.6f,   0.6f,  -0.6f  },
	{  -0.6f,  -0.6f,  -0.6f  },
	{   0.6f,  -0.6f,  -0.6f  },
	{   0.6f,   0.6f,  -0.6f  },
	{   0.6f,  -0.6f,  -0.6f  },
	{   0.6f,  -0.6f,   0.6f  },
	{   0.6f,   0.6f,  -0.6f  },
	{   0.6f,   0.6f,   0.6f  },
	{   0.6f,  -0.6f,   0.6f  },
	{  -0.6f,  -0.6f,   0.6f  },
	{   0.6f,   0.6f,   0.6f  },
	{  -0.6f,   0.6f,   0.6f  },
	{  -0.6f,  -0.6f,   0.6f  },
	{  -0.6f,  -0.6f,  -0.6f  },
	{  -0.6f,   0.6f,   0.6f  },
	{  -0.6f,   0.6f,  -0.6f  },
	{  -0.6f,  -0.6f,   0.6f  },
	{   0.6f,  -0.6f,   0.6f  },
	{   0.6f,  -0.6f,  -0.6f  },
	{  -0.6f,  -0.6f,  -0.6f  },
	{  -0.6f,   0.6f,  -0.6f  },
	{   0.6f,   0.6f,  -0.6f  },
	{   0.6f,   0.6f,   0.6f  },
	{  -0.6f,   0.6f,   0.6f  }

};

Vert_uv pyramidData_uv[] =
{
	{  0.0f,  0.0f,  },
	{  0.0f,  1.0f,  },
	{  1.0f,  1.0f,  },
	{  1.0f,  0.0f,  },
	{  0.0f,  1.0f,  },
	{  1.0f,  1.0f,  },
	{  0.0f,  0.0f,  },
	{  1.0f,  0.0f,  },
	{  1.0f,  1.0f,  },
	{  0.0f,  1.0f,  },
	{  1.0f,  0.0f,  },
	{  0.0f,  0.0f,  },
	{  0.0f,  0.0f,  },
	{  0.0f,  1.0f,  },
	{  1.0f,  0.0f,  },
	{  1.0f,  1.0f,  },
	{  0.0f,  0.0f,  },
	{  1.0f,  0.0f,  },
	{  1.0f,  1.0f,  },
	{  0.0f,  1.0f,  },
	{  0.0f,  1.0f,  },
	{  1.0f,  1.0f,  },
	{  1.0f,  0.0f,  },
	{  0.0f,  0.0f,  }
};


void CreatePyramidMesh()
{
	// runtime model
	meshData  runModel;

	runModel.pName = new char* [1];
	runModel.mode = new meshData::RENDER_MODE[1];
	runModel.mode[0] = meshData::RENDER_MODE::MODE_TRIANGLES;
	runModel.triCount = new unsigned int[1];
	runModel.vertCount = new unsigned int[1];
	runModel.vbo_vert = new vboData[1];
	runModel.vbo_norm = new vboData[1];
	runModel.vbo_uv = new vboData[1];
	runModel.vbo_index = new vboData[1];
	runModel.vbo_color = new vboData[1];
	runModel.text_color = new textureData[1];
	runModel.text_color[0].enabled = false;
	runModel.texCount = 0;
	runModel.meshCount = 1;
	runModel.nameCount = 1;
	runModel.animCount = 0;
	runModel.materialIndex = new unsigned int[1];
	runModel.materialIndex[0] = 0;

	//Set dynamic array data sizes
	runModel.anim_data = nullptr;

	// Name
	std::string BaseName = "PyramidMesh";

	//--------------------------------
	// GameEngine mapping - ge prefix
	// -------------------------------
	std::map<std::string, RetargetVBO> geAttrib;

	bool status = GLTF::GetGEAttribDefault(geAttrib);
	assert(status);

	unsigned int numTris = sizeof(pyramid_triList) / sizeof(pyramid_triList[0]);
	unsigned int numVerts = sizeof(pyramidData_xyz) / sizeof(pyramidData_xyz[0]);

	//---------------------------------
	// Model Name
	//---------------------------------
	const char* pMeshName = BaseName.c_str();
	runModel.pName[0] = new char[meshData::FILE_NAME_SIZE];
	memcpy_s(runModel.pName[0], meshData::FILE_NAME_SIZE, pMeshName, strlen(pMeshName));

	// Correct make Z dominate, correct postion
	Matrix M(Matrix::Rot1::X, MATH_PI2);
	for (size_t i = 0; i < numVerts; i++)
	{
		Vect v(pyramidData_xyz[i].x, pyramidData_xyz[i].y, pyramidData_xyz[i].z);
		v = v * M;
		pyramidData_xyz[i].x = v[x];
		pyramidData_xyz[i].y = v[y];
		pyramidData_xyz[i].z = v[z];

		Trace::out("%d: %f %f %f \n", i, pyramidData_xyz[i].x, pyramidData_xyz[i].y, pyramidData_xyz[i].z);
	}

	for (size_t i = 0; i < numVerts; i++)
	{
		Vect v(pyramidData_nxnynz[i].nx, pyramidData_nxnynz[i].ny, pyramidData_nxnynz[i].nz);
		v = v * M;
		pyramidData_nxnynz[i].nx = v[x];
		pyramidData_nxnynz[i].ny = v[y];
		pyramidData_nxnynz[i].nz = v[z];
	}

	//---------------------------------
	// Set vbo 
	//---------------------------------
	GLTF::SetCustomVBO(geAttrib.find("POSITION")->second.engine_index,
		runModel.vbo_vert[0],
		pyramidData_xyz,
		numVerts * sizeof(Vert_xyz),
		numVerts,
		vboData::VBO_COMPONENT::FLOAT,
		vboData::VBO_TYPE::VEC3,
		vboData::VBO_TARGET::ARRAY_BUFFER
	);
	runModel.vbo_vert[0].Print("vbo_vert");

	GLTF::SetCustomVBO(geAttrib.find("NORMAL")->second.engine_index,
		runModel.vbo_norm[0],
		pyramidData_nxnynz,
		numVerts * sizeof(Vert_nxnynz),
		numVerts,
		vboData::VBO_COMPONENT::FLOAT,
		vboData::VBO_TYPE::VEC3,
		vboData::VBO_TARGET::ARRAY_BUFFER
	);
	runModel.vbo_norm[0].Print("vbo_norm");

	GLTF::SetCustomVBO(geAttrib.find("TEXCOORD_0")->second.engine_index,
		runModel.vbo_uv[0],
		pyramidData_uv,
		numVerts * sizeof(Vert_uv),
		numVerts,
		vboData::VBO_COMPONENT::FLOAT,
		vboData::VBO_TYPE::VEC2,
		vboData::VBO_TARGET::ARRAY_BUFFER
	);
	runModel.vbo_uv[0].Print("vbo_uv");

	GLTF::SetCustomVBO_index(geAttrib.find("INDEX")->second.engine_index,
		runModel.vbo_index[0],
		pyramid_triList,
		numTris * sizeof(Tri_index),
		numTris,
		vboData::VBO_COMPONENT::UNSIGNED_INT,
		vboData::VBO_TYPE::SCALAR,
		vboData::VBO_TARGET::ELEMENT_ARRAY_BUFFER
	);
	runModel.vbo_index[0].Print("vbo_index");


	//--------------------------------
	// PolyCount
	//--------------------------------
	runModel.triCount[0] = numTris;
	runModel.vertCount[0] = numVerts;


	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	runModel.Print("mA");
	meshData_proto mA_proto;
	runModel.Serialize(mA_proto);

	Trace::out("\n");
	Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
	Trace::out("\n");


	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	// Create output name
	const char* pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
	assert(status);

	std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

	err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
	assert(err == File::Error::SUCCESS);

	std::string strOut;
	mA_proto.SerializeToString(&strOut);

	File::Write(fh, strOut.data(), strOut.length());
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	// -------------------------------
	// Read and recreate model data
	// -------------------------------

	err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD FileLength;
	err = File::Tell(fh, FileLength);
	assert(err == File::Error::SUCCESS);

	char* poNewBuff = new char[FileLength]();
	assert(poNewBuff);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, poNewBuff, FileLength);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	std::string strIn(poNewBuff, FileLength);
	meshData_proto mB_proto;

	mB_proto.ParseFromString(strIn);

	meshData mB;
	mB.Deserialize(mB_proto);
	mB.Print("mB");

	delete[] poNewBuff;

}



// --- End of File ---
