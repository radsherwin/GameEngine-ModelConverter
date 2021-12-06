//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include "Bone.h"
#include "sb7.h"
#include "MathEngine.h"
#include "DLink.h"
#include "BoundingSphere.h"
#include "Texture.h"
#include "Animation.h"

using namespace Azul;

class Mesh
{
public:
	enum class Name
	{
		CUBE,
		BONE_A,
		BONE_B,
		CHICKEN_BOT,
		CRATE,
		SNOWMAN,
		PYRAMID,
		BONE,
		BONE_R,
		BONE_R_001,
		BONE_R_002,
		BONE_L,
		BONE_L_001,
		BONE_L_002,
		BONE_01,
		SPACE_FRIGATE,
		CAMERA,
		POKE_BALL,
		SPHERE,
		NULL_MESH,
		NOT_INITIALIZED
	};

public:
	Mesh();
	Mesh(Mesh& copyMesh) = delete;
	Mesh& operator = (Mesh& copyMesh) = delete;
	virtual ~Mesh();

	// Data
	int numVerts;
	int numTris;
	
	GLuint vao;
	GLuint vbo_verts;	//x,y,z
	GLuint vbo_norms;	//nx, ny, nz
	GLuint vbo_texts;	//u v
	GLuint vbo_color;
	GLuint vbo_index;	//trilist

	void Wash();
	bool Compare(DLink* pTarget);
	char* GetName();
	void SetName(Name _name);
	Animation* GetAnimation() const;

	//Reference sphere before any transformations are applied
	Sphere* poRefSphere;

public:
	Name name;
	unsigned int textureIDInt;
	int texCount;
	Animation* pAnim;

};

#endif

// --- End of File ---