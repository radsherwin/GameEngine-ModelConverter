//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TRAPEZOID_MESH_H
#define TRAPEZOID_MESH_H

#include "Mesh.h"

class TrapezoidMesh : public Mesh
{
public:
	TrapezoidMesh(const char* const pMeshFileName);

	TrapezoidMesh() = delete;
	TrapezoidMesh(const TrapezoidMesh&) = delete;
	TrapezoidMesh& operator = (TrapezoidMesh&) = delete;
	virtual ~TrapezoidMesh();

private:
	virtual void privCreateVAO(const char* const pMeshFileName) override;

	// Data

};

#endif

// --- End of File ---