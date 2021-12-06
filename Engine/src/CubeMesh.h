//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "Mesh.h"

class CubeMesh : public Mesh
{
public:
	CubeMesh(const char* const pMeshFileName);

	CubeMesh() = delete;
	CubeMesh(const CubeMesh&) = delete;
	CubeMesh& operator = (CubeMesh&) = delete;
	virtual ~CubeMesh();

private:
	void privCreateVAO(const char* const pMeshFileName);

	// Data

};

#endif

// --- End of File ---