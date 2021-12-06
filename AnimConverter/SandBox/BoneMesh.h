#ifndef BONE_MESH_H
#define BONE_MESH_H

#include "MathEngine.h"

using namespace Azul;

struct fVect2
{
	fVect2() = default;
	~fVect2() = default;

	float u;
	float v;
};

struct fVect3
{
	fVect3() = default;
	~fVect3() = default;

	fVect3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{}

	float x;
	float y;
	float z;
};

struct fVect4
{
	fVect4() = default;
	~fVect4() = default;

	fVect4(float _x, float _y, float _z, float _w)
		:x(_x), y(_y), z(_z), w(_w)
	{

	}

	float x;
	float y;
	float z;
	float w;
};

struct iuVect3
{
	iuVect3() = default;
	~iuVect3() = default;

	iuVect3(unsigned int _v0, unsigned int _v1, unsigned int _v2)
		: v0(_v0), v1(_v1), v2(_v2)
	{

	}

	unsigned int v0;
	unsigned int v1;
	unsigned int v2;
};

struct isVect3
{
	isVect3() = default;
	~isVect3() = default;

	isVect3(unsigned short _x, unsigned short _y, unsigned short _z)
		:x(_x), y(_y), z(_z)
	{

	}
	unsigned short x;
	unsigned short y;
	unsigned short z;

};


struct isVect4
{
	isVect4() = default;
	~isVect4() = default;

	isVect4(unsigned short _x, unsigned short _y, unsigned short _z, unsigned short _w)
		:x(_x), y(_y), z(_z), w(_w)
	{

	}
	unsigned short x;
	unsigned short y;
	unsigned short z;
	unsigned short w;
};

struct skin_weight_joint_index
{
	skin_weight_joint_index() = default;
	~skin_weight_joint_index() = default;
	size_t	index;
	fVect4	skinWeight;
	isVect4	jointIndex;
};

struct LocalToGlobalIndex
{
	LocalToGlobalIndex(size_t _local, size_t _global, size_t _joint)
		: localIndex(_local), globalIndex(_global), JointIndex(_joint)
	{}

	size_t localIndex;   // new model
	size_t globalIndex;  // original model	
	size_t JointIndex;   // Here for verification...should be same value for every index
};

struct BoneMesh
{
	std::string boneName;
	size_t      vertCount;
	size_t      jointIndex;
	Matrix      inverseMatrix;  // single - Inverse Matrix based on JointIndex
	bool        corrected;      // pos/norms corrected
	std::vector< LocalToGlobalIndex > l2gIndex;   // x
	std::vector< fVect3 > pos;
	std::vector< fVect3 > norms;
	std::vector< fVect2 > text_coord;
	std::vector< iuVect3 > index;                 // x
};

struct Mat4
{
	float m0;
	float m1;
	float m2;
	float m3;
	float m4;
	float m5;
	float m6;
	float m7;
	float m8;
	float m9;
	float m10;
	float m11;
	float m12;
	float m13;
	float m14;
	float m15;
};

#endif
