#include "CreateAnimation.h"
#include "meshData.h"
#include "GLTF.h"
#include "File.h"
#include "BoneMesh.h"
#include "meshDataConverter.h"

using namespace Azul;
using namespace tinygltf;

void LoadDataSizesAnimation(const Model& gltfModel, meshData& runModel);

void CreateAnimation(const char* const pModelFileName, std::string pOutputFileName)
{
	bool status;
	tinygltf::Model gltfModel;
	//runtime Model
	meshData runModel;

	// Load the gltfModel
	Trace::out2("File name: %s\n", pModelFileName);
	status = GLTF::LoadBinary(gltfModel, pModelFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char* poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, pModelFileName);
	assert(status);

	//Get Binary Buffer address
	char* pBinaryBuff = nullptr;
	unsigned int BinaryBuffSize = 0;
	status = GLTF::GetBinaryBuffPtr(pBinaryBuff, BinaryBuffSize, poBuff, BuffSize);
	assert(status);

	//sizes
	size_t meshSize;

	//Loop thorough skins
	std::vector<BoneMesh> Bones;
	if (!gltfModel.skins.empty())
	{
		Bones.resize(gltfModel.skins[0].joints.size());
		runModel.animCount = Bones.size();
		for (size_t jointIndex = 0; jointIndex < gltfModel.skins[0].joints.size(); jointIndex++)
		{
			GLTF::LoadBones(gltfModel, jointIndex, &Bones[jointIndex]);
		}
	}
	else
	{
		assert(false);
	}

	LoadDataSizesAnimation(gltfModel, runModel);

	GLTF::SetAnimData(gltfModel, runModel, Bones);

	for (size_t i = 0; i < Bones.size(); i++) //For each mesh
	{
		runModel.pName[i] = new char[meshData::FILE_NAME_SIZE];
		memcpy_s(runModel.pName[i], meshData::FILE_NAME_SIZE, Bones[i].boneName.c_str(), Bones[i].boneName.length() + 1);
		runModel.mode[i] = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);
		runModel.vertCount[i] = 0;
		runModel.triCount[i] = 0;
		runModel.materialIndex[i] = 0;
	}

	delete[] poBuff;

	runModel.Print("mA");
	meshData_proto mA_proto;
	runModel.Serialize(mA_proto); //Update values in mA_proto to be equal to runModel

	Trace::out("\n");
	Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
	Trace::out("\n");

	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	std::string pProtoFileType = ".a";
	assert(status);

	pOutputFileName = pOutputFileName + pProtoFileType + ".proto.azul";

	err = File::Open(fh, pOutputFileName.c_str(), File::Mode::WRITE);
	assert(err == File::Error::SUCCESS);

	std::string strOut;
	mA_proto.SerializeToString(&strOut);

	//Write to the newly created "crate.proto.azul"(fh) the data from runModel/mA_proto
	File::Write(fh, strOut.data(), strOut.length());
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	// -------------------------------
	// Read and recreate model data
	// -------------------------------

	err = File::Open(fh, pOutputFileName.c_str(), File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD FileLength;
	err = File::Tell(fh, FileLength);
	assert(err == File::Error::SUCCESS);

	char* poNewBuff = new char[FileLength](); //poNewBuff is size of file "crate.proto.azul"
	assert(poNewBuff);

	err = File::Seek(fh, File::Position::BEGIN, 0); //seek back to beginning
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, poNewBuff, FileLength); //read data from file(fh) into poNewBuff
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

void LoadDataSizesAnimation(const Model& gltfModel, meshData& runModel)
{
	const size_t meshSize = gltfModel.skins[0].joints.size();

	const size_t matSize = 0;

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
	for (int meshIndex = 0; meshIndex < runModel.animCount; meshIndex++)
	{
		runModel.anim_data[meshIndex].frameBucketCount = gltfModel.accessors[0].count;
		runModel.anim_data[meshIndex].bone_data = new boneData[runModel.anim_data[meshIndex].frameBucketCount];
	}
}