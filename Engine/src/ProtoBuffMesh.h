//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PROTO_BUFF_MESH_H
#define PROTO_BUFF_MESH_H

#include "Mesh.h"
#include "meshData.h"

class ProtoBuffMesh : public Mesh
{
public:
	ProtoBuffMesh(meshData& mB, unsigned int index);

	ProtoBuffMesh() = delete;
	ProtoBuffMesh(const ProtoBuffMesh&) = delete;
	ProtoBuffMesh& operator = (ProtoBuffMesh&) = delete;
	virtual ~ProtoBuffMesh();

private:
	void privCreateVAO(meshData& mB, unsigned int index);
	// Data

};

#endif

// --- End of File ---
