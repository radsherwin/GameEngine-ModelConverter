#include "ProtoMeshFactory.h"
#include "File.h"
#include "meshData.h"
#include "MeshNodeManager.h"
#include "ProtoBuffMesh.h"
#include "TextureManager.h"

using namespace Azul;

ProtoMeshFactory::ProtoMeshFactory()
{

}

void ProtoMeshFactory::LoadMesh(const char* const pMeshFileName, meshData& _mB, Texture::Name _texName)
{
	//Read file
	//Create meshes and save to MeshNodeManager
	std::string fullMeshName = "./Models/" + (std::string)pMeshFileName;
	File::Handle fh;
	File::Error err;

	assert(fullMeshName.c_str());

	err = File::Open(fh, fullMeshName.c_str(), File::Mode::READ);
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

	//meshData mB;
	_mB.Deserialize(mB_proto);
	//mB.Print("mB");

	delete[] poNewBuff;
	if (_texName != Texture::Name::NOT_INITIALIZED)
	{
		TextureManager::Add(_mB, _texName);
	}
}

void ProtoMeshFactory::LoadTexture(const char* const pFileName, Texture::Name _name)
{
	//Read file
	//Create meshes and save to MeshNodeManager
	std::string fullMeshName = "./Textures/" + (std::string)pFileName;
	File::Handle fh;
	File::Error err;

	assert(fullMeshName.c_str());

	err = File::Open(fh, fullMeshName.c_str(), File::Mode::READ);
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

	if(_name != Texture::Name::NOT_INITIALIZED)
	{
		TextureManager::Add(mB.text_color[0], _name);
	}
	else
	{
		assert(false);
	}

	delete[] poNewBuff;
}



void ProtoMeshFactory::GetMesh(const char* const pMeshFileName, Mesh** MeshArray, Mesh::Name _meshName)
{
	meshData mB;
	ProtoMeshFactory::LoadMesh(pMeshFileName, mB);
	const unsigned int _count = mB.meshCount;
	for (unsigned int i = 0; i < _count; i++)
	{
		Mesh* tmp = new ProtoBuffMesh(mB, i);
		if (_meshName == Mesh::Name::NOT_INITIALIZED)
		{
			MeshNodeManager::Add(tmp->name, tmp);
		}
		else
		{
			MeshNodeManager::Add(_meshName, tmp);
		}

		MeshArray[i] = tmp;
	}

}

void ProtoMeshFactory::GetAnimation(const char* const pMeshFileName, Animation** AnimationArray)
{
	meshData mB;
	ProtoMeshFactory::LoadMesh(pMeshFileName, mB);
	const unsigned int _count = mB.animCount;
	for (unsigned int index = 0; index < _count; index++)
	{
		Animation* tmpAnim = new Animation();

		tmpAnim->parent = mB.anim_data[index].parent;
		tmpAnim->joint = mB.nodeNumber[index];
		tmpAnim->frames = mB.anim_data[index].frameBucketCount;
		tmpAnim->protoName = mB.pName[index];

		Bone tmp;
		tmpAnim->meshBone.reserve(mB.anim_data[index].frameBucketCount);
		for (int i = 0; i < mB.anim_data[index].frameBucketCount; i++)
		{
			float* pTrans = (float*)&mB.anim_data[index].bone_data[i].pTranslation[0];
			tmp.T.set(*&pTrans[0], *&pTrans[1], *&pTrans[2]);

			float* pQuat = (float*)&mB.anim_data[index].bone_data[i].pRotation[0];
			tmp.Q.set(*&pQuat[0], *&pQuat[1], *&pQuat[2], *&pQuat[3]);

			float* pScale = (float*)&mB.anim_data[index].bone_data[i].pScale[0];
			tmp.S.set(*&pScale[0], *&pScale[1], *&pScale[2]);

			tmpAnim->meshBone.push_back(tmp);
		}

		AnimationManager::Add(tmpAnim);
		AnimationArray[index] = tmpAnim;
	}
}

Mesh* ProtoMeshFactory::GetSingleMesh(meshData& mB, int meshIndex, Mesh::Name _meshName)
{
	Mesh* pMesh = new ProtoBuffMesh(mB, (unsigned int)meshIndex);
	MeshNodeManager::Add(_meshName, pMesh);

	return pMesh;
}


