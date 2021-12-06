#include "GLTF.h"
#include "File.h"
#include "md5.h"
#include "StringThis.h"
#include "textureDataConverter.h"
#include "vboDataConverter.h"
#include "BoneMesh.h"
#include "meshDataConverter.h"

using namespace Azul;

struct gfVect4
{
	float x;
	float y;
	float z;
	float w;
};

struct gfVect3
{
	float x;
	float y;
	float z;
};

bool GLTF::LoadBinary(Model& model, const char* const pFileName)
{
	TinyGLTF loader;
	std::string err;
	std::string warn;

	bool status = loader.LoadBinaryFromFile(&model, &err, &warn, pFileName);

	if (!warn.empty())
	{
		Trace::out2("Warn: %s\n", warn.c_str());
		//assert(false);
	}

	if (!err.empty())
	{
		Trace::out2("Err: %s\n", err.c_str());
		//assert(false);
	}

	if (!status)
	{
		Trace::out2("Failed to parse glTF\n");
		//assert(false);
	}

	return status;
}

bool GLTF::LoadASCII(Model& model, const char* const pFileName)
{
	TinyGLTF loader;
	std::string err;
	std::string warn;
	bool status = loader.LoadASCIIFromFile(&model, &err, &warn, pFileName);
	if (!warn.empty())
	{
		Trace::out("Warn: %s\n", warn.c_str());
		assert(false);
	}

	if (!err.empty())
	{
		Trace::out("Err: %s\n", err.c_str());
		assert(false);
	}

	if (!status)
	{
		Trace::out2("Failed to parse glTF\n");
		assert(false);
	}

	return status;
}

bool GLTF::LoadDataSizes(const Model& gltfModel, meshData& runModel, const size_t meshSize)
{
	size_t matSize = gltfModel.materials.size();

	//Set counts
	runModel.texCount = matSize;
	runModel.meshCount = meshSize;
	runModel.nameCount = meshSize;

	//Set dynamic array data sizes
	runModel.anim_data = new animData[runModel.animCount];
	runModel.materialIndex = new unsigned int[meshSize];
	runModel.nodeNumber = new unsigned int[meshSize];
	runModel.pName = new char* [meshSize];
	runModel.mode = new meshData::RENDER_MODE[meshSize];
	runModel.triCount = new unsigned int[meshSize];
	runModel.vertCount = new unsigned int[meshSize];
	runModel.vbo_vert = new vboData[meshSize];
	runModel.vbo_norm = new vboData[meshSize];
	runModel.vbo_uv = new vboData[meshSize];
	runModel.vbo_index = new vboData[meshSize];
	runModel.vbo_color = new vboData[meshSize];
	runModel.text_color = new textureData[meshSize];

	//Load animation size
	for(int meshIndex = 0; meshIndex < runModel.animCount; meshIndex++)
	{
		runModel.anim_data[meshIndex].frameBucketCount = gltfModel.accessors[0].count;
		runModel.anim_data[meshIndex].bone_data = new boneData[runModel.anim_data[meshIndex].frameBucketCount];
	}
	

	return true;
}

bool GLTF::LoadBones(const Model& gltfModel, int jointIndex, BoneMesh* Bone0)
{
	size_t JointTarget = jointIndex;  // Increment from 0:7 joints(bones)
	{
		//ChickenBot
		size_t inverseMatrixAccessorIndex	= gltfModel.skins[0].inverseBindMatrices;
		size_t weightAccessorIndex			= gltfModel.meshes[0].primitives[0].attributes.find("WEIGHTS_0")->second;
		size_t jointAccessorIndex			= gltfModel.meshes[0].primitives[0].attributes.find("JOINTS_0")->second;
		size_t indexAccessorIndex			= gltfModel.meshes[0].primitives[0].indices;  
		size_t posAccessorIndex				= gltfModel.meshes[0].primitives[0].attributes.find("POSITION")->second;
		size_t normsAccessorIndex			= gltfModel.meshes[0].primitives[0].attributes.find("NORMAL")->second;
		size_t texCoordAccessorIndex		= gltfModel.meshes[0].primitives[0].attributes.find("TEXCOORD_0")->second;

		unsigned char* pBuff = (unsigned char*)&gltfModel.buffers[0].data[0];

		// Joint
		Accessor JointAccessor = gltfModel.accessors[jointAccessorIndex];
		BufferView JointBuffView = gltfModel.bufferViews[(size_t)JointAccessor.bufferView];

		unsigned char* pJointBuff = pBuff + JointBuffView.byteOffset;
		assert(JointAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT);
		assert(JointAccessor.type == TINYGLTF_TYPE_VEC4);

		// Weight
		Accessor WeightAccessor = gltfModel.accessors[weightAccessorIndex];
		BufferView WeightBuffView = gltfModel.bufferViews[(size_t)WeightAccessor.bufferView];

		unsigned char* pWeightBuff = pBuff + WeightBuffView.byteOffset;
		assert(WeightAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(WeightAccessor.type == TINYGLTF_TYPE_VEC4);

		// InverseMatrix
		Accessor InverseAccessor = gltfModel.accessors[inverseMatrixAccessorIndex];
		BufferView InverseBuffView = gltfModel.bufferViews[(size_t)InverseAccessor.bufferView];

		unsigned char* pInverseMatrixBuff = pBuff + InverseBuffView.byteOffset;
		assert(InverseAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(InverseAccessor.type == TINYGLTF_TYPE_MAT4);

		// Verify the joint count, weight count, vert count all the same
		assert(WeightAccessor.count == JointAccessor.count);

		// Index
		Accessor IndexAccessor = gltfModel.accessors[indexAccessorIndex];
		BufferView IndexBuffView = gltfModel.bufferViews[(size_t)IndexAccessor.bufferView];

		unsigned char* pIndexBuff = pBuff + IndexBuffView.byteOffset;
		assert(IndexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT);
		assert(IndexAccessor.type == TINYGLTF_TYPE_SCALAR);

		// Pos
		Accessor PosAccessor = gltfModel.accessors[posAccessorIndex];
		BufferView PosBuffView = gltfModel.bufferViews[(size_t)PosAccessor.bufferView];

		unsigned char* pPosBuff = pBuff + PosBuffView.byteOffset;
		assert(PosAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(PosAccessor.type == TINYGLTF_TYPE_VEC3);

		// Norms
		Accessor NormsAccessor = gltfModel.accessors[normsAccessorIndex];
		BufferView NormsBuffView = gltfModel.bufferViews[(size_t)NormsAccessor.bufferView];

		unsigned char* pNormsBuff = pBuff + NormsBuffView.byteOffset;
		assert(NormsAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(NormsAccessor.type == TINYGLTF_TYPE_VEC3);

		// Tex Coord
		Accessor TexCoordAccessor = gltfModel.accessors[texCoordAccessorIndex];
		BufferView TexCoordBuffView = gltfModel.bufferViews[(size_t)TexCoordAccessor.bufferView];

		unsigned char* pTexCoordBuff = pBuff + TexCoordBuffView.byteOffset;
		assert(TexCoordAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		assert(TexCoordAccessor.type == TINYGLTF_TYPE_VEC2);

		size_t ElementCount;
		ElementCount = IndexAccessor.count / 3;

		// Convert to Unsigned int
		std::vector< iuVect3 > indexVector;
		isVect3* pisVect3 = (isVect3*)pIndexBuff;

		for (size_t i = 0; i < ElementCount; i++)
		{
			indexVector.push_back(iuVect3(pisVect3->x, pisVect3->y, pisVect3->z));
			pisVect3++;
		}
		std::vector< skin_weight_joint_index > WeightJoint;
		WeightJoint.reserve(WeightAccessor.count);

		AZUL_UNUSED_VAR(pInverseMatrixBuff);

		isVect4* pJointVect4 = (isVect4*)pJointBuff;
		fVect4* pWeightVect4 = (fVect4*)pWeightBuff;
		for (size_t i = 0; i < WeightAccessor.count; i++)
		{
			WeightJoint.push_back(skin_weight_joint_index());
			WeightJoint[i].index = i;
			WeightJoint[i].jointIndex = isVect4(pJointVect4->x,
				pJointVect4->y,
				pJointVect4->z,
				pJointVect4->w);
			WeightJoint[i].skinWeight = fVect4(pWeightVect4->x,
				pWeightVect4->y,
				pWeightVect4->z,
				pWeightVect4->w);
			pJointVect4++;
			pWeightVect4++;
		}

		for (size_t i = 0; i < WeightJoint.size(); i++)
		{
			assert(WeightJoint[i].jointIndex.y == 0);
			assert(WeightJoint[i].jointIndex.z == 0);
			assert(WeightJoint[i].jointIndex.w == 0);

			assert(WeightJoint[i].skinWeight.y == 0.0f);
			assert(WeightJoint[i].skinWeight.z == 0.0f);
			assert(WeightJoint[i].skinWeight.w == 0.0f);

			/*Trace::out("%d: Joint: %d Weight: %f \n",
				i,
				WeightJoint[i].jointIndex.x,
				WeightJoint[i].skinWeight.x
			);*/
		}

		size_t NodeIndex = (size_t)gltfModel.skins[0].joints[JointTarget];

		Bone0->vertCount = 0; // placeholder
		Bone0->jointIndex = JointTarget;
		Bone0->boneName = gltfModel.nodes[NodeIndex].name;

		Matrix* pInverseMatrix = (Matrix*)pInverseMatrixBuff;
		Bone0->inverseMatrix = pInverseMatrix[JointTarget];
		Bone0->corrected = false;

		fVect3* pPos = (fVect3*)pPosBuff;
		fVect3* pNorms = (fVect3*)pNormsBuff;
		fVect2* pTexCoord = (fVect2*)pTexCoordBuff;
		size_t count(0);
		size_t localIndex(0);

		for (size_t i = 0; i < WeightJoint.size(); i++)
		{
			// Filter to the target
			if (WeightJoint[i].jointIndex.x == JointTarget)
			{
				assert(WeightJoint[i].skinWeight.x == 1.0f);
				size_t JointIndex = WeightJoint[i].jointIndex.x;

				Bone0->l2gIndex.push_back(LocalToGlobalIndex(localIndex, i, JointIndex));
				Bone0->pos.push_back(pPos[i]);
				Bone0->norms.push_back(pNorms[i]);
				Bone0->text_coord.push_back(pTexCoord[i]);

				count++;
				localIndex++;
			}
		}
		// now Bone0.vertCount is correct.
		Bone0->vertCount = count;

		Trace::out("\n\n");
		for (size_t i = 0; i < Bone0->l2gIndex.size(); i++)
		{
			/*Trace::out("%d local: %d global: %d  joint: %d \n",
				i,
				Bone0->l2gIndex[i].localIndex,
				Bone0->l2gIndex[i].globalIndex,
				Bone0->l2gIndex[i].JointIndex);*/
		}
		/*Trace::out("\n\n");*/

		//---------------------------------------
		// FIX Index and store in BoneMesh
		//---------------------------------------
		int cc = 0;
		for (size_t i = 0; i < indexVector.size(); i++)
		{
			int f0 = -1;
			int f1 = -1;
			int f2 = -1;

			for (size_t j = 0; j < Bone0->l2gIndex.size(); j++)
			{
				if (indexVector[i].v0 == Bone0->l2gIndex[j].globalIndex)
				{
					f0 = (int)Bone0->l2gIndex[j].localIndex;
					break;
				}
			}
			for (size_t j = 0; j < Bone0->l2gIndex.size(); j++)
			{
				if (indexVector[i].v1 == Bone0->l2gIndex[j].globalIndex)
				{
					f1 = (int)Bone0->l2gIndex[j].localIndex;
					break;
				}
			}
			for (size_t j = 0; j < Bone0->l2gIndex.size(); j++)
			{
				if (indexVector[i].v2 == Bone0->l2gIndex[j].globalIndex)
				{
					f2 = (int)Bone0->l2gIndex[j].localIndex;
					break;
				}
			}

			if (f0 == -1 && f1 == -1 && f2 == -1)
			{
				continue;
			}
			else
			{
				/*Trace::out("%d: (%d) %d %d %d  %d %d %d\n",
					cc,
					i,
					indexVector[i].v0,
					indexVector[i].v1,
					indexVector[i].v2,
					f0, f1, f2);*/
				assert(f0 >= 0);
				assert(f1 >= 0);
				assert(f2 >= 0);
				Bone0->index.push_back(iuVect3((unsigned int)f0, (unsigned int)f1, (unsigned int)f2));
				cc++;
			}
		}

		// ----------------------------------------------------
		// Correct the verts and norms with inverse matrix
		// ----------------------------------------------------
		for (size_t i = 0; i < Bone0->pos.size(); i++)
		{
			Vect    v(Bone0->pos[i].x, Bone0->pos[i].y, Bone0->pos[i].z);
			Matrix  M(Bone0->inverseMatrix);
			Vect    vOut;

			vOut = v * M;

			Bone0->pos[i].x = vOut[x];
			Bone0->pos[i].y = vOut[y];
			Bone0->pos[i].z = vOut[z];
		}

		for (size_t i = 0; i < Bone0->norms.size(); i++)
		{
			Vect   v(Bone0->norms[i].x, Bone0->norms[i].y, Bone0->norms[i].z);
			Matrix  M(Bone0->inverseMatrix);
			Vect    vOut;

			vOut = v * M;
			vOut.norm();

			Bone0->norms[i].x = vOut[x];
			Bone0->norms[i].y = vOut[y];
			Bone0->norms[i].z = vOut[z];
		}

		Bone0->corrected = true;
	}

	return true;
}

bool GLTF::LoadBoneMesh(Model& gltfModel, meshData& runModel, std::vector<BoneMesh> bones, std::map<std::string, RetargetVBO> geAttrib, char* pBinaryBuff)
{
	bool status = true;

	status = GLTF::GetGEAttrib(geAttrib, gltfModel, 0);
	assert(status);

	for (size_t i = 0; i < bones.size(); i++) //For each mesh
	{
		runModel.materialIndex[i] = 0;
		runModel.mode[i] = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);
		runModel.pName[i] = new char[meshData::FILE_NAME_SIZE];
		memcpy_s(runModel.pName[i], meshData::FILE_NAME_SIZE, bones[i].boneName.c_str(), bones[i].boneName.length()+1);

		GLTF::SetVBO_BONE(gltfModel, geAttrib.find("POSITION")->second, runModel.vbo_vert[i],
			(char*)&bones[i].pos[0],
			bones[i].pos.size() * sizeof(fVect3),
			bones[i].pos.size());
		runModel.vbo_vert[i].Print("vbo_vert");
		runModel.vertCount[i] = runModel.vbo_vert[i].count;

		GLTF::SetVBO_BONE(gltfModel, geAttrib.find("NORMAL")->second, runModel.vbo_norm[i],
			(char*)&bones[i].norms[0],
			bones[i].norms.size() * sizeof(fVect3),
			bones[i].norms.size());
		runModel.vbo_norm[i].Print("vbo_norm");

		GLTF::SetVBO_BONE(gltfModel, geAttrib.find("TEXCOORD_0")->second, runModel.vbo_uv[i],
			(char*)&bones[i].text_coord[0],
			bones[i].text_coord.size() * sizeof(fVect2),
			bones[i].text_coord.size());
		runModel.vbo_uv[i].Print("vbo_uv");

		GLTF::SetVBO_BONE_index(gltfModel, geAttrib.find("INDEX")->second, runModel.vbo_index[i],
			(char*)&bones[i].index[0],
			bones[i].index.size() * sizeof(iuVect3),
			bones[i].index.size() * 3);
		runModel.vbo_index[i].Print("vbo_index");
		runModel.triCount[i] = runModel.vbo_index[i].count / 3;
	}

	return status;
}

bool GLTF::LoadBasicMesh(Model& gltfModel, meshData& runModel, std::map<std::string, RetargetVBO> geAttrib, char* pBinaryBuff)
{
	bool status = true;
	for (unsigned int i = 0; i < gltfModel.meshes.size(); i++)
	{
		runModel.pName[i] = new char[meshData::FILE_NAME_SIZE];
		runModel.materialIndex[i] = (unsigned int)gltfModel.meshes[i].primitives[0].material;

		status = GLTF::GetGEAttrib(geAttrib, gltfModel, i);
		assert(status);

		GLTF::SetVBO(gltfModel, geAttrib.find("POSITION")->second, runModel.vbo_vert[i], pBinaryBuff);
		runModel.vbo_vert[i].Print("vbo_vert", (int)i);
		runModel.vertCount[i] = runModel.vbo_vert[i].count;

		GLTF::SetVBO(gltfModel, geAttrib.find("NORMAL")->second, runModel.vbo_norm[i], pBinaryBuff);
		runModel.vbo_norm[i].Print("vbo_norm", (int)i);

		GLTF::SetVBO(gltfModel, geAttrib.find("TEXCOORD_0")->second, runModel.vbo_uv[i], pBinaryBuff);
		runModel.vbo_uv[i].Print("vbo_uv", (int)i);

		GLTF::SetVBO_Index(gltfModel, geAttrib.find("INDEX")->second, runModel.vbo_index[i], pBinaryBuff);
		runModel.vbo_index[i].Print("vbo_index", (int)i);
		runModel.triCount[i] = runModel.vbo_index[i].count / 3;

		GLTF::SetVBO(gltfModel, geAttrib.find("COLOR_0")->second, runModel.vbo_color[i], pBinaryBuff);
		runModel.vbo_color[i].Print("vbo_color", (int)i);

		//Render Mode
		runModel.mode[i] = meshDataConverter::GetMode(gltfModel.meshes[i].primitives[0].mode);
	}

	return status;
}

bool GLTF::GetGLBRawBuffer(char*& pBuff, unsigned int& BuffSize, const char* const pFileName)
{
	File::Handle fh;
	File::Error err;

	err = File::Open(fh, pFileName, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD FileSize(0);
	err = File::Tell(fh, FileSize);
	assert(err == File::Error::SUCCESS);

	// Cast it down to 32-bit size (limit 4GB)
	BuffSize = (unsigned int)FileSize;
	pBuff = new char[BuffSize]();
	assert(pBuff);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, pBuff, BuffSize);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	assert(pBuff);
	assert(BuffSize > 0);

	return true;
}

bool GLTF::GetGLBHeader(GLB_header& header, const char* const pBuff, unsigned int BuffSize)
{
	AZUL_UNUSED_VAR(BuffSize);
	GLB_header* pGlbHeader;

	pGlbHeader = (GLB_header*)&pBuff[0];
	assert(pGlbHeader);

	// boundary check
	assert((char*)(pGlbHeader + 1) < (pBuff + BuffSize));

	assert(pGlbHeader->version == 2);
	assert(pGlbHeader->magic == 0x46546C67);

	header = *pGlbHeader;

	return true;
}

bool GLTF::GetRawJSON(char*& pJSON, unsigned int& JsonSize, const char* const pBuff, unsigned int BuffSize)
{
	AZUL_UNUSED_VAR(BuffSize);
	// BEGINNING...
	GLB_header* pGlbHeader;

	pGlbHeader = (GLB_header*)&pBuff[0];
	assert(pGlbHeader);

	// boundary check
	assert((char*)(pGlbHeader + 1) < (pBuff + BuffSize));

	// Now this next is CHUNK header
	CHUNK_header* pChunkHdr;
	pChunkHdr = (CHUNK_header*)(pGlbHeader + 1);

	assert(pChunkHdr->chunkType == 0x4E4F534A);
	pJSON = (char*)pChunkHdr->chunkData;
	JsonSize = pChunkHdr->chunkLength;

	// boundary check - bottom of header
	assert((char*)(pChunkHdr + 1) < (pBuff + BuffSize));

	// boundary check - bottom of data
	assert(((char*)(pChunkHdr + 1) + pChunkHdr->chunkLength) < (pBuff + BuffSize));

	assert(pJSON);
	assert(JsonSize > 0);

	return true;
}

bool GLTF::GetBinaryBuffPtr(char*& pBinaryBuff, unsigned int& BinaryBuffSize, const char* const pBuff, unsigned int BuffSize)
{
	AZUL_UNUSED_VAR(BuffSize);
	// BEGINNING...
	GLB_header* pGlbHeader;

	pGlbHeader = (GLB_header*)&pBuff[0];
	assert(pGlbHeader);

	// Now this next is CHUNK header - JSON
	CHUNK_header* pChunkHdr;
	pChunkHdr = (CHUNK_header*)(pGlbHeader + 1);

	assert(pChunkHdr);
	assert(pChunkHdr->chunkType == 0x4E4F534A);

	// Now this next is CHUNK header - Binary
	pChunkHdr = (CHUNK_header*)((uint32_t)(pChunkHdr + 1) + pChunkHdr->chunkLength);

	assert(pChunkHdr->chunkType == 0x004E4942);

	BinaryBuffSize = pChunkHdr->chunkLength;
	pBinaryBuff = (char*)pChunkHdr->chunkData;

	assert(((char*)(pChunkHdr + 1) + BinaryBuffSize) <= (pBuff + BuffSize));

	assert(pBinaryBuff);
	assert(BinaryBuffSize > 0);

	return true;
}
bool GLTF::SetVBO(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBinaryBuff)
{
	vbo.enabled = retarget.enable;

	if (!vbo.enabled) return true;

	assert(retarget.model_index >= 0);
	// Get the accessor, buffer view
	auto accessor = gltfModel.accessors[(unsigned int)retarget.model_index];
	size_t buffIndex = (size_t)accessor.bufferView;
	auto bufferView = gltfModel.bufferViews[buffIndex];

	vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
	vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
	vbo.vboType = vboDataConverter::GetType(accessor.type);

	assert(retarget.engine_index >= 0);
	vbo.attribIndex = (unsigned int)retarget.engine_index;

	vbo.count = accessor.count;

	vbo.dataSize = bufferView.byteLength;

	// poData
	assert(pBinaryBuff);
	char* pBuffStart(nullptr);

	// Start address
	pBuffStart = pBinaryBuff + bufferView.byteOffset;

	// in case there's data
	delete[] vbo.poData;

	vbo.poData = new unsigned char[vbo.dataSize]();
	assert(vbo.poData);
	memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	//GLTF::PrintData(pBinaryBuff, bufferView.byteOffset, vbo.count, vbo.componentType, vbo.vboType);

	return true;
}

bool GLTF::SetVBO_Index(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBinaryBuff)
{
	vbo.enabled = retarget.enable;

	if (!vbo.enabled) return true;

	// Get the accessor, buffer view
	assert(retarget.model_index >= 0);
	auto accessor = gltfModel.accessors[(unsigned int)retarget.model_index];
	size_t buffIndex = (size_t)accessor.bufferView;
	auto bufferView = gltfModel.bufferViews[buffIndex];

	vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
	vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
	vbo.vboType = vboDataConverter::GetType(accessor.type);

	assert(retarget.engine_index >= 0);
	vbo.attribIndex = (unsigned int)retarget.engine_index;  // not used in index buffers
	vbo.count = accessor.count;
	vbo.dataSize = bufferView.byteLength;

	// poData
	assert(pBinaryBuff);
	char* pBuffStart(nullptr);

	// Start address
	pBuffStart = pBinaryBuff + bufferView.byteOffset;

	// in case there's data
	delete[] vbo.poData;

	if (vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
	{
		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	}
	else
	{
		unsigned int* pIndexData = new unsigned int[vbo.count]();
		unsigned int* pTmp = pIndexData;

		if (vbo.componentType == vboData::VBO_COMPONENT::BYTE)
		{
			byte* pNewType = (byte*)pBuffStart;

			for (unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = (unsigned int)~*pNewType++;
			}
		}
		else if (vbo.componentType == vboData::VBO_COMPONENT::SHORT)
		{
			short* pNewType = (short*)pBuffStart;

			for (unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = (unsigned int)~*pNewType++;
			}
		}
		else if (vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT)
		{
			unsigned short* pNewType = (unsigned short*)pBuffStart;

			for (unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = (unsigned int)*pNewType++;
			}
		}
		else if (vbo.componentType == vboData::VBO_COMPONENT::INT)
		{
			int* pNewType = (int*)pBuffStart;

			for (unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = (unsigned int)~*pNewType++;
			}
		}
		else if (vbo.componentType == vboData::VBO_COMPONENT::FLOAT)
		{
			float* pNewType = (float*)pBuffStart;

			for (unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = (unsigned int)*pNewType++;
			}
		}
		else if (vbo.componentType == vboData::VBO_COMPONENT::DOUBLE)
		{
			double* pNewType = (double*)pBuffStart;

			for (unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = (unsigned int)*pNewType++;
			}
		}
		else
		{
			assert(false);
		}

		// this is the output buffer
		//pIndexData = pTmp;
		vbo.poData = (unsigned char*)pIndexData;
		// update the data
		vbo.dataSize = vbo.count * sizeof(unsigned int);
		// update the component
		vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;
	}

	return true;
}

bool GLTF::SetTexture(Model& gltfModel, unsigned index, textureData& text, char* pBinaryBuff)
{
	text.enabled = true;

	if (strcmp(gltfModel.images[index].mimeType.c_str(), "image/png") == 0)
	{
		//assert(gltfModel.textures[index].source == TINYGLTF_IMAGE_FORMAT_PNG); //snowman_finish shows bmp
		text.textType = textureData::TEXTURE_TYPE::PNG;
	}
	else if (strcmp(gltfModel.images[index].mimeType.c_str(), "image/jpeg") == 0)
	{
		//assert(gltfModel.textures[index].source == TINYGLTF_IMAGE_FORMAT_JPEG); //snowman_finish shows bmp
		text.textType = textureData::TEXTURE_TYPE::JPEG;
	}
	else if (strcmp(gltfModel.images[index].mimeType.c_str(), "image/bmp") == 0)
	{
		//assert(gltfModel.textures[index].source == TINYGLTF_IMAGE_FORMAT_BMP); //snowman_finish shows bmp
		text.textType = textureData::TEXTURE_TYPE::BMP;
	}
	else if (strcmp(gltfModel.images[index].mimeType.c_str(), "image/gif") == 0)
	{
		text.textType = textureData::TEXTURE_TYPE::GIF;
	}

	text.magFilter = textureData::TEXTURE_MAG_FILTER::DEFAULT;
	text.minFilter = textureData::TEXTURE_MIN_FILTER::DEFAULT;
	text.wrapS = textureData::TEXTURE_WRAP::DEFAULT;
	text.wrapT = textureData::TEXTURE_WRAP::DEFAULT;
	text.pixel_type = textureDataConverter::GetComponent(gltfModel.images[index].pixel_type);
	text.width = (unsigned int)gltfModel.images[index].width;
	text.height = (unsigned int)gltfModel.images[index].height;
	text.component = (unsigned int)gltfModel.images[index].component;
	text.bits = (unsigned int)gltfModel.images[index].bits;

	// pFileName
	unsigned int len = gltfModel.images[index].name.length();
	assert(len < text.FILE_NAME_SIZE);
	memcpy_s(text.pFileName,
		text.FILE_NAME_SIZE,
		gltfModel.images[index].name.c_str(),
		len);

	//If image is decompressed
	if (gltfModel.images[index].as_is == false)
	{
		//at this point the data is decompressed into a raw buffer gltfModel
		text.dataSize = gltfModel.images[index].image.size();
		Trace::out("byteLength: %d \n", text.dataSize);
		//in case there's data
		delete[] text.poData;

		text.poData = new unsigned char[text.dataSize]();
		assert(text.poData);
		auto pStart = &gltfModel.images[index].image[0];
		memcpy_s(text.poData, text.dataSize, pStart, text.dataSize);
		//md5 here?
		MD5Output out;
		MD5Buffer(text.poData, text.dataSize, out);
		text.hash = out.dWord_0 ^ out.dWord_1 ^ out.dWord_2 ^ out.dWord_3;
	}
	else
	{
		// export the texture file in compressed mode
		unsigned int buffViewIndex = (unsigned int)gltfModel.images[index].bufferView;
		auto buffView = gltfModel.bufferViews[buffViewIndex];
		text.dataSize = buffView.byteLength;

		char* pBuffStart = pBinaryBuff + buffView.byteOffset;

		Trace::out("byteLength: %d \n", text.dataSize);
		Trace::out("byteOffset: %d \n", buffView.byteOffset);

		// in case there's data
		delete[] text.poData;

		text.poData = new unsigned char[text.dataSize]();
		assert(text.poData);
		memcpy_s(text.poData, text.dataSize, pBuffStart, text.dataSize);

		MD5Output out;
		MD5Buffer(text.poData, text.dataSize, out);
		text.hash = out.dWord_0 ^ out.dWord_1 ^ out.dWord_2 ^ out.dWord_3;
	}

	return true;
}

bool GLTF::SetVBO_BONE(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBuffStart, unsigned byteLength,
	unsigned count)
{
	// Get the accessor, buffer view
	vbo.enabled = retarget.enable;

	if (vbo.enabled)
	{
		assert(retarget.model_index >= 0);
		auto accessor = gltfModel.accessors[(unsigned int)retarget.model_index];
		size_t buffIndex = (size_t)accessor.bufferView;
		auto bufferView = gltfModel.bufferViews[buffIndex];

		vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
		vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
		vbo.vboType = vboDataConverter::GetType(accessor.type);

		assert(retarget.engine_index >= 0);
		vbo.attribIndex = (unsigned int)retarget.engine_index;

		vbo.count = count;
		vbo.dataSize = byteLength;

		assert(pBuffStart);

		// in case there's data
		delete[] vbo.poData;

		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	}

	return true;
}

bool GLTF::SetVBO_BONE_index(Model& gltfModel, RetargetVBO& retarget, vboData& vbo, char* pBuffStart,
	unsigned byteLength, unsigned count)
{
	// Get the accessor, buffer view
	vbo.enabled = retarget.enable;

	if (vbo.enabled)
	{
		assert(retarget.model_index >= 0);
		auto accessor = gltfModel.accessors[(unsigned int)retarget.model_index];
		size_t buffIndex = (size_t)accessor.bufferView;
		auto bufferView = gltfModel.bufferViews[buffIndex];

		vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
		//vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
		vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;
		vbo.vboType = vboDataConverter::GetType(accessor.type);

		assert(retarget.engine_index >= 0);
		vbo.attribIndex = (unsigned int)retarget.engine_index;

		vbo.count = count;
		vbo.dataSize = byteLength;

		assert(pBuffStart);

		// in case there's data
		delete[] vbo.poData;

		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	}

	return true;
}

bool GLTF::SetAnimDefaults(Model& gltfModel, meshData& runModel, std::vector<BoneMesh> bones)
{
	
	for (size_t meshIndex = 0; meshIndex < bones.size(); meshIndex++) //For each mesh
	{
		
		const int targetNodeIndex = gltfModel.skins[0].joints[meshIndex]; //Starts with 4
		Node target_nodes = gltfModel.nodes[targetNodeIndex];
		runModel.nodeNumber[meshIndex] = targetNodeIndex;

		Trace::out("Bone name: %s, joint: %d, index: %d\n", gltfModel.nodes[targetNodeIndex].name.c_str(), targetNodeIndex, meshIndex);

		//Loop through all frames to set all defaults
		for(size_t frameIndex = 0; frameIndex < runModel.anim_data[meshIndex].frameBucketCount; frameIndex++)
		{
			float* tmpFloats = new float[3];
			tmpFloats[0] = (float)target_nodes.translation[0];
			tmpFloats[1] = (float)target_nodes.translation[1];
			tmpFloats[2] = (float)target_nodes.translation[2];
			memcpy(runModel.anim_data[meshIndex].bone_data[frameIndex].pTranslation, tmpFloats, sizeof(float) * 3);
			delete[] tmpFloats;

			tmpFloats = new float[4];
			tmpFloats[0] = (float)target_nodes.rotation[0];
			tmpFloats[1] = (float)target_nodes.rotation[1];
			tmpFloats[2] = (float)target_nodes.rotation[2];
			tmpFloats[3] = (float)target_nodes.rotation[3];
			memcpy(runModel.anim_data[meshIndex].bone_data[frameIndex].pRotation, tmpFloats, sizeof(float) * 4);
			delete[] tmpFloats;

			tmpFloats = new float[3];
			tmpFloats[0] = (float)target_nodes.scale[0];
			tmpFloats[1] = (float)target_nodes.scale[1];
			tmpFloats[2] = (float)target_nodes.scale[2];
			memcpy(runModel.anim_data[meshIndex].bone_data[frameIndex].pScale, tmpFloats, sizeof(float) * 3);
			delete[] tmpFloats;
		}
	}

	return true;
}

bool GLTF::SetAnimData(Model& gltfModel, meshData& runModel, std::vector<BoneMesh> bones)
{
	//Set Defaults first
	SetAnimDefaults(gltfModel, runModel, bones);
	for (size_t meshIndex = 0; meshIndex < bones.size(); meshIndex++) //For each mesh
	{
		//Set Parent
		Node target_nodes = gltfModel.nodes[gltfModel.skins[0].joints[meshIndex]];
		for (auto it = target_nodes.children.begin(); it != target_nodes.children.end(); ++it)
		{
			GLTF::SetParentJoint(runModel, runModel.nodeNumber[meshIndex], (*it));
		}


		std::vector<AnimationChannel> animChannels = gltfModel.animations[0].channels;

		//Starting data pointer
		unsigned char* pBuffStart = (unsigned char*)&gltfModel.buffers[0].data[0];

		//Loop channels
		for(size_t channelsIndex = 0; channelsIndex < animChannels.size(); channelsIndex++)
		{
			//Current bone/mesh has a channel with animation
			if(animChannels[channelsIndex].target_node == runModel.nodeNumber[meshIndex])
			{
				//Accessor = channelsIndex+1;
				Accessor BoneAccessor = gltfModel.accessors[channelsIndex+1];
				BufferView BoneBuffView = gltfModel.bufferViews[(size_t)BoneAccessor.bufferView];
				unsigned char* pBuff = pBuffStart + BoneBuffView.byteOffset;

				if(animChannels[channelsIndex].target_path == "translation")
				{
					gfVect3* pVect3 = (gfVect3*)pBuff;
					for (size_t frameIndex = 0; frameIndex < runModel.anim_data[meshIndex].frameBucketCount; frameIndex++)
					{
						float* tmpFloat = new float[3];
						tmpFloat[0] = pVect3->x;
						tmpFloat[1] = pVect3->y;
						tmpFloat[2] = pVect3->z;
						delete[] runModel.anim_data[meshIndex].bone_data[frameIndex].pTranslation;
						runModel.anim_data[meshIndex].bone_data[frameIndex].pTranslation = new unsigned char[sizeof(float) * 3];
						memcpy(runModel.anim_data[meshIndex].bone_data[frameIndex].pTranslation, tmpFloat, sizeof(float) * 3);
						delete[] tmpFloat;
						pVect3++;
					}
				}
				else if (animChannels[channelsIndex].target_path == "rotation")
				{
					gfVect4* pVect4 = (gfVect4*)pBuff;
					
					for (size_t frameIndex = 0; frameIndex < runModel.anim_data[meshIndex].frameBucketCount; frameIndex++)
					{
						float* tmpFloat = new float[4];
						tmpFloat[0] = pVect4->x;
						tmpFloat[1] = pVect4->y;
						tmpFloat[2] = pVect4->z;
						tmpFloat[3] = pVect4->w;
						delete[] runModel.anim_data[meshIndex].bone_data[frameIndex].pRotation;
						runModel.anim_data[meshIndex].bone_data[frameIndex].pRotation = new unsigned char[sizeof(float) * 4];
						memcpy(runModel.anim_data[meshIndex].bone_data[frameIndex].pRotation, tmpFloat, sizeof(float) * 4);
						delete[] tmpFloat;
						pVect4++;
					}
				}
				else if (animChannels[channelsIndex].target_path == "scale")
				{
					gfVect3* pVect3 = (gfVect3*)pBuff;

					for (size_t frameIndex = 0; frameIndex < runModel.anim_data[meshIndex].frameBucketCount; frameIndex++)
					{
						float* tmpFloat = new float[3];
						tmpFloat[0] = pVect3->x;
						tmpFloat[1] = pVect3->y;
						tmpFloat[2] = pVect3->z;

						//Reset data
						delete[] runModel.anim_data[meshIndex].bone_data[frameIndex].pScale;
						runModel.anim_data[meshIndex].bone_data[frameIndex].pScale = new unsigned char[sizeof(float) * 3];
						memcpy(runModel.anim_data[meshIndex].bone_data[frameIndex].pScale, tmpFloat, sizeof(float) * 3);
						delete[] tmpFloat;
						pVect3++;
					}
				}
			}
		}
	}

	return true;
}

bool GLTF::SetParentJoint(meshData& runModel, int parentIndex, int childIndex)
{
	for(int i = 0; i < (int)runModel.meshCount; i++)
	{
		if(runModel.nodeNumber[i] == childIndex)
		{
			runModel.anim_data[i].parent = parentIndex;
		}
	}
	return true;
}

bool GLTF::SetCustomVBO(int engineAttribIndex, vboData& vbo, void* pData, unsigned sizeInBytes, unsigned count,
                        vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE type, vboData::VBO_TARGET target)
{
	vbo.enabled = true;

	vbo.targetType = target;
	vbo.componentType = componentType;
	vbo.vboType = type;

	assert(engineAttribIndex >= 0);
	vbo.attribIndex = (unsigned int)engineAttribIndex;
	vbo.count = count;
	vbo.dataSize = sizeInBytes;

	vbo.poData = new unsigned char[vbo.dataSize]();
	assert(vbo.poData);
	memcpy_s(vbo.poData, vbo.dataSize, pData, vbo.dataSize);

	GLTF::PrintData((char*)pData, 0, vbo.count, vbo.componentType, vbo.vboType);

	return true;
}

bool GLTF::SetCustomVBO_index(int engineAttribIndex, vboData& vbo, void* pData, unsigned sizeInBytes, unsigned count,
	vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE type, vboData::VBO_TARGET target)
{
	vbo.enabled = true;

	vbo.targetType = target;
	vbo.componentType = componentType;
	vbo.vboType = type;

	assert(engineAttribIndex >= 0);
	vbo.attribIndex = (unsigned int)engineAttribIndex;  // not used in index buffers
	vbo.count = count * 3;
	vbo.dataSize = sizeInBytes;

	vbo.poData = new unsigned char[vbo.dataSize]();
	assert(vbo.poData);
	memcpy_s(vbo.poData, vbo.dataSize, pData, vbo.dataSize);

	GLTF::PrintData((char*)vbo.poData, 0, vbo.count, vbo.componentType, vbo.vboType);

	return true;
}

bool GLTF::GetGEAttribDefault(std::map<std::string, RetargetVBO>& geAttrib)
{
	// Engine vbo attributes - hard coded in the shaders
	geAttrib["POSITION"] = RetargetVBO(0);
	geAttrib["NORMAL"] = RetargetVBO(1);
	geAttrib["TEXCOORD_0"] = RetargetVBO(2);
	geAttrib["INDEX"] = RetargetVBO(3);
	geAttrib["COLOR_0"] = RetargetVBO(4);

	return true;
}

bool GLTF::GetGEAttrib(std::map<std::string, RetargetVBO>& geAttrib, Model& gltfModel, unsigned int meshIndex)
{
	// Engine vbo attributes - hard coded in the shaders
	bool status = GLTF::GetGEAttribDefault(geAttrib);
	assert(status);

	//-------------------------------
	// Find the model's attributes
	//-------------------------------
	std::map<std::string, int> gltfAttributes;

	gltfAttributes["INDEX"] = gltfModel.meshes[meshIndex].primitives[0].indices;

	auto gltfAttrib = gltfModel.meshes[meshIndex].primitives[0].attributes;

	for (auto it = geAttrib.begin(); it != geAttrib.end(); it++)
	{
		auto it_model = gltfAttrib.find(it->first);
		if (it_model != gltfAttrib.end())
		{
			it->second.enable = true;
			it->second.model_index = it_model->second;
		}
		else if (it->first == "INDEX")
		{
			it->second.enable = true;
			it->second.model_index = gltfModel.meshes[0].primitives[0].indices;
		}
		else
		{
			// skip
			it->second.enable = false;
			it->second.model_index = -1;
		}
	}

	// Print it out to verify...
	for (auto it = geAttrib.begin(); it != geAttrib.end(); it++)
	{
		Trace::out("%s geAttrib(%10s)  m:%2d --> e:%d \n",
			it->second.enable ? " true" : "false",
			it->first.c_str(),
			it->second.model_index,
			it->second.engine_index);
	}

	Trace::out("\n");

	return true;
}

bool GLTF::GetAzulProtoType(const char*& pProtoFileType, meshData& _meshData)
{
	bool status = false;

	if (_meshData.vbo_vert == nullptr && _meshData.text_color == nullptr)
	{
		assert(false);
		return false;
	}
	else if (_meshData.vbo_vert == nullptr && _meshData.text_color != nullptr && _meshData.text_color[0].enabled)
	{
		pProtoFileType = ".t";
		status = true;
	}
	else if (_meshData.vbo_vert != nullptr && _meshData.vbo_vert[0].enabled && _meshData.text_color == nullptr)
	{
		pProtoFileType = ".m";
		status = true;
	}
	else if (_meshData.vbo_vert != nullptr && _meshData.text_color != nullptr)
	{
		if (_meshData.vbo_vert[0].enabled && _meshData.text_color[0].enabled)
		{
			pProtoFileType = ".mt";
			status = true;
		}
		else if (_meshData.vbo_vert[0].enabled && !_meshData.text_color[0].enabled)
		{
			pProtoFileType = ".m";
			status = true;
		}
		else if (!_meshData.vbo_vert[0].enabled && _meshData.text_color[0].enabled)
		{
			pProtoFileType = ".t";
			status = true;
		}
		else
		{
			assert(false);
			status = false;
		}
	}
	else
	{
		assert(false);
		status = false;
	}

	return status;
}

void GLTF::PrintData(char* pBinaryBuff, size_t byteOffset, size_t count, vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE vboType)
{
	Trace::out("\n");
	if (componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT && vboType == vboData::VBO_TYPE::SCALAR) // unsigned short
	{
		unsigned short* p = (unsigned short*)((uint32_t)pBinaryBuff + byteOffset);
		void* pstart = p;
		Trace::out("start: %p \n", p);
		for (size_t j = 0; j < count / 3; j++)
		{
			Trace::out("\t[%d]:  %3d %3d %3d \n", j, p[0], p[1], p[2]);
			p += 3;
		}
		void* pend = p;
		Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
		Trace::out("\n");
	}

	if (componentType == vboData::VBO_COMPONENT::UNSIGNED_INT && vboType == vboData::VBO_TYPE::SCALAR) // unsigned int
	{
		unsigned int* p = (unsigned int*)((uint32_t)pBinaryBuff + byteOffset);
		void* pstart = p;
		Trace::out("start: %p \n", p);
		for (size_t j = 0; j < count / 3; j++)
		{
			Trace::out("\t[%d]:  %3d %3d %3d \n", j, p[0], p[1], p[2]);
			p += 3;
		}
		void* pend = p;
		Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
		Trace::out("\n");
	}

	if (componentType == vboData::VBO_COMPONENT::FLOAT && vboType == vboData::VBO_TYPE::VEC4)
	{
		float* p = (float*)((uint32_t)pBinaryBuff + byteOffset);
		void* pstart = p;
		Trace::out("start: %p \n", p);
		for (size_t j = 0; j < count; j++)
		{
			Trace::out("\t[%d]:  %5.4f %5.4f %5.4f %5.4f \n", j, p[0], p[1], p[2], p[3]);
			p += 4;
		}
		void* pend = p;
		Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
		Trace::out("\n");
	}

	if (componentType == vboData::VBO_COMPONENT::FLOAT && vboType == vboData::VBO_TYPE::VEC3)
	{
		float* p = (float*)((uint32_t)pBinaryBuff + byteOffset);
		void* pstart = p;
		Trace::out("start: %p \n", p);
		for (size_t j = 0; j < count; j++)
		{
			Trace::out("\t[%d]:  %5.4f %5.4f %5.4f \n", j, p[0], p[1], p[2]);
			p += 3;
		}
		void* pend = p;
		Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
		Trace::out("\n");
	}

	if (componentType == vboData::VBO_COMPONENT::FLOAT && vboType == vboData::VBO_TYPE::VEC2)
	{
		float* p = (float*)((uint32_t)pBinaryBuff + byteOffset);

		for (size_t j = 0; j < count; j++)
		{
			Trace::out("\t[%d]:  %5.4f %5.4f \n", j, p[0], p[1]);
			p += 2;
		}

		Trace::out("\n");
	}
}

// --- End of File ---