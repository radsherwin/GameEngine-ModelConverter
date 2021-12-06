//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CreateTexture.h"
#include "GLTF.h"
#include "meshData.h"
#include "File.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "BoneMesh.h"
#include "CreateAnimation.h"
#include "PyramidMesh.h"

using namespace tinygltf;
using namespace Azul;
using json = nlohmann::json;

int main(int argc, char* argv[])
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	//CreatePyramidMesh();
	bool status;
	tinygltf::Model gltfModel;

	//File names
	std::string pModelFileName = "./Models/";
	std::string pOutputFileName;
	std::string pTextureFileName = "./Models/Textures/";
	bool bHasTexture = false;
	bool bHasInput = false;
	bool bAnimationOnly = false;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0) //Help
		{
			Trace::out2("-h: Display help instructions on the screen\n-i: Name of the model to load\n-o: Name of the exported file\n-a: Name of the animation to load. Do not use with -i");
			google::protobuf::ShutdownProtobufLibrary();
			return 0;
		}

		if (i + 1 != argc)
		{
			if (strcmp(argv[i], "-i") == 0) //Input model name
			{
				pModelFileName += (std::string)argv[i + 1];  
				i++;    // Move to the next flag
				bHasInput = true;
			}
			else if (strcmp(argv[i], "-o") == 0) // Output filename
			{
				pOutputFileName = (std::string)argv[i + 1]; 
				i++;    // Move to the next flag
			}
			else if (strcmp(argv[i], "-t") == 0) //Texture
			{
				pTextureFileName += (std::string)argv[i + 1];
				bHasTexture = true;
				i++;
			}
			else if(strcmp(argv[i], "-a") == 0) //Animation only
			{
				if(bHasInput) assert(false);
				pModelFileName += (std::string)argv[i+1];
				i++;
				bAnimationOnly = true;
			}
		}
	}

	if(bAnimationOnly)
	{
		CreateAnimation(pModelFileName.c_str(), pOutputFileName.c_str());
		google::protobuf::ShutdownProtobufLibrary();
		return 0;
	}

	//If custom texture is passed:
	if (bHasTexture)
	{
		CreateTexturePNG(pTextureFileName.c_str(), pOutputFileName.c_str());
	}

	if(!bHasInput)
	{
		google::protobuf::ShutdownProtobufLibrary();
		return 0;
	}

	//runtime Model
	meshData runModel;

	// Load the gltfModel
	Trace::out2("File name: %s\n", pModelFileName.c_str());
	status = GLTF::LoadBinary(gltfModel, pModelFileName.c_str());
	assert(status);

	// Read glb into memory (raw buffer)
	char* poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, pModelFileName.c_str());
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
		//runModel.animCount[nodes[jointIndex].child
		meshSize = gltfModel.skins[0].joints.size();
		Bones.resize(gltfModel.skins[0].joints.size());
		runModel.animCount = Bones.size();
		for (size_t jointIndex = 0; jointIndex < gltfModel.skins[0].joints.size(); jointIndex++)
		{
			GLTF::LoadBones(gltfModel, jointIndex, &Bones[jointIndex]);
		}
	}
	else
	{
		meshSize = gltfModel.meshes.size();
	}

	status = GLTF::LoadDataSizes(gltfModel, runModel, meshSize);
	assert(status);

	//-------------------------------------------------
	// Fill out the runtime Model data
	//-------------------------------------------------

		//--------------------------------
		// GameEngine mapping - ge prefix
		// -------------------------------
	std::map<std::string, RetargetVBO> geAttrib;

	GLTF::SetAnimData(gltfModel, runModel, Bones);

	//---------------------------------
	// Set vbo
	//---------------------------------
	if (gltfModel.skins.size() > 0 && !Bones.empty())
	{
		status = GLTF::LoadBoneMesh(gltfModel, runModel, Bones, geAttrib, pBinaryBuff);
		assert(status);
	}
	else
	{
		status = GLTF::LoadBasicMesh(gltfModel, runModel, geAttrib, pBinaryBuff);
		assert(status);
	}

	//---------------------------------
	// Set texture and const color data
	//---------------------------------

	for (unsigned int i = 0; i < gltfModel.materials.size(); i++)
	{
		if (gltfModel.images.size() > 0)
		{
			int textureIndex = gltfModel.materials[i].pbrMetallicRoughness.baseColorTexture.index;
			if (textureIndex >= 0)
			{
				GLTF::SetTexture(gltfModel, textureIndex, runModel.text_color[i], pBinaryBuff);
				runModel.text_color[i].Print("text_color", (int)i);
			}
		}
	}

	//---------------------------------
	// Model Name
	//---------------------------------
	/*for (unsigned int i = 0; i < gltfModel.nodes.size(); i++)
	{
		const int meshIndex = gltfModel.nodes[i].mesh;
		if (meshIndex >= 0)
		{
			if (gltfModel.nodes[i].name.empty())
			{
				memcpy_s(runModel.pName[static_cast<unsigned int>(meshIndex)], meshData::FILE_NAME_SIZE,
					gltfModel.meshes[static_cast<unsigned int>(meshIndex)].name.c_str(), gltfModel.meshes[static_cast<unsigned int>(meshIndex)].name.length());
			}
			else
			{
				memcpy_s(runModel.pName[static_cast<unsigned int>(meshIndex)], meshData::FILE_NAME_SIZE,
					gltfModel.nodes[i].name.c_str(), gltfModel.nodes[i].name.length());
			}
		}
	}*/

	delete[] poBuff;

	//Serialization

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

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

	const char* pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
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

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// ---  End of File ---------------