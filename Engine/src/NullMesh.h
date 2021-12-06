//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NULL_MESH_H
#define NULL_MESH_H

#include "Mesh.h"

class NullMesh : public Mesh
{
public:
	NullMesh(const char* const MeshFileName);
	NullMesh();
	virtual ~NullMesh();

	// tells the compiler do not create or allow it to be used, c++11
	NullMesh(const NullMesh&) = delete;
	NullMesh& operator=(const NullMesh& other) = delete;

private:
	void privCreateVAO(const char* const MeshFileName);


};

#endif

// --- End of File ---