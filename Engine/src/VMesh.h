//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef V_MESH_H
#define V_MESH_H

#include "Mesh.h"

class VMesh : public Mesh
{
public:
	VMesh(const char* const pMeshFileName);

	VMesh() = delete;
	VMesh(const VMesh&) = delete;
	VMesh& operator = (VMesh&) = delete;
	virtual ~VMesh();

private:
	virtual void privCreateVAO(const char* const pMeshFileName) override;

	// Data

};

#endif

// --- End of File ---