//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GLTF_H
#define GLTF_H

#include "tiny_gltf.h"
#include "meshData.h"

struct BoneMesh;
using namespace tinygltf;


struct GLB_header
{
	uint32_t magic;
	uint32_t version;
	uint32_t length;
};

struct CHUNK_header
{
	uint32_t chunkLength;
	uint32_t chunkType;
	unsigned char chunkData[];
};

struct RetargetVBO
{
	RetargetVBO()
		: enable(false),
	engine_index(-1),
	model_index(-1)
	{}

	RetargetVBO(int e)
		: enable(false),
		engine_index(e),
		model_index(-1)
	{}

	bool enable;
	int engine_index;
	int model_index;
};

class GLTF
{
public:
	static bool LoadBinary(Model &model, const char *const pFileName);
	static bool LoadASCII(Model& model, const char* const pFileName);

	static bool LoadDataSizes(const Model& gltfModel, meshData& runModel, const size_t meshSize);
	static bool LoadBones(const Model& gltfModel, int jointIndex, BoneMesh*);

	static bool LoadBoneMesh(Model& gltfModel, meshData& runModel, std::vector<BoneMesh> bones, std::map<std::string, RetargetVBO> geAttrib, char* pBinaryBuff);
	static bool LoadBasicMesh(Model& gltfModel, meshData& runModel, std::map<std::string, RetargetVBO> geAttrib, char* pBinaryBuff);

	static bool GetGLBRawBuffer(char *&pBuff, unsigned int &BuffSize, const char *const pFileName);
	static bool GetGLBHeader(GLB_header &header, const char *const pBuff, unsigned int BuffSize);
	static bool GetRawJSON(char *&pJSON, unsigned int &JsonSize, const char *const pBuff, unsigned int BuffSize);
	static bool GetBinaryBuffPtr(char *&pBinaryBuff, unsigned int& BinaryBuffSize, const char *const pBuff, unsigned int BuffSize);

	static bool SetVBO(Model &gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBinaryBuff);
	static bool SetVBO_Index(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBinaryBuff);
	static bool SetTexture(Model &gltfModel, unsigned int index, textureData& text, char* pBinaryBuff);

	static bool SetVBO_BONE(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBuffStart, unsigned int byteLength, unsigned int count);
	static bool SetVBO_BONE_index(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBuffStart, unsigned int byteLength, unsigned int count);

	//Animation
	static bool SetAnimDefaults(Model& gltfModel, meshData& runModel, std::vector<BoneMesh> bones);
	static bool SetAnimData(Model& gltfModel, meshData& runModel, std::vector<BoneMesh> bones);
	static bool SetParentJoint(meshData& runModel, int parentIndex, int childIndex);

	//Custom VBOs
	static bool SetCustomVBO(	int engineAttribIndex, vboData& vbo, void* pData, unsigned int sizeInBytes, unsigned int count,
								vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE type, vboData::VBO_TARGET target);
	static bool SetCustomVBO_index(	int engineAttribIndex, vboData& vbo, void* pData, unsigned int sizeInBytes, unsigned int count,
									vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE type, vboData::VBO_TARGET target);

	static bool GetGEAttribDefault(std::map<std::string, RetargetVBO>& geAttrib);
	static bool GetGEAttrib(std::map<std::string, RetargetVBO>& geAttrib, Model& gltfModel, unsigned int meshIndex);

	static bool GetAzulProtoType(const char*& pProtoFileType, meshData& _meshData);

	static void PrintData(char* pBinaryBuff, size_t byteOffset, size_t count, vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE vboType);
};

#endif

// --- End of File ---
