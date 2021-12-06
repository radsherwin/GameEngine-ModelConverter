#ifndef PROTO_MESH_FACTORY_H
#define PROTO_MESH_FACTORY_H

#include <vector>

#include "Mesh.h"
#include "Texture.h"
#include "AnimationManager.h"

class meshData;
class textureData;

class ProtoMeshFactory
{
public:
	ProtoMeshFactory();
	ProtoMeshFactory(const ProtoMeshFactory*) = delete;
	ProtoMeshFactory& operator=(const ProtoMeshFactory*) = delete;
	~ProtoMeshFactory() = default;

	static void LoadMesh(const char* const pMeshFileName, meshData& mB, Texture::Name _name = Texture::Name::NOT_INITIALIZED);
	static void LoadTexture(const char* const pFileName, Texture::Name _name = Texture::Name::NOT_INITIALIZED);

	//static void GetAnimation(const char* const pAnimFileName, std::vector<AnimationManager::AnimationData>& ad);
	static void GetMesh(const char* const pMeshFileName, Mesh** MeshArray, Mesh::Name _meshName = Mesh::Name::NOT_INITIALIZED);
	static void GetAnimation(const char* const pMeshFileName, Animation** AnimationArray);
	static Mesh* GetSingleMesh(meshData& mB, int meshIndex, Mesh::Name _meshName = Mesh::Name::NOT_INITIALIZED);
};

#endif
