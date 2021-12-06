//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "NullMesh.h"


NullMesh::NullMesh(const char* const MeshFileName)
	: Mesh()
{
	AZUL_UNUSED_VAR(MeshFileName);
}

NullMesh::NullMesh()
	: Mesh()
{
}


NullMesh::~NullMesh()
{
	// remove anything dynamic here
}

void NullMesh::privCreateVAO(const char* const MeshFileName)
{
	AZUL_UNUSED_VAR(MeshFileName);
}


// --- End of File ---