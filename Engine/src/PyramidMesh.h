//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PYRAMID_MESH_H
#define PYRAMID_MESH_H

#include "Mesh.h"

class PyramidMesh : public Mesh
{
public:
	PyramidMesh(const char* const pMeshFileName);

	PyramidMesh() = delete;
	PyramidMesh(const PyramidMesh&) = delete;
	PyramidMesh& operator = (PyramidMesh&) = delete;
	virtual ~PyramidMesh();

private:
	virtual void privCreateVAO(const char* const pMeshFileName) override;

	// Data

};

#endif

// --- End of File ---