//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include "Mesh.h"

namespace Azul
{
	class SphereMesh : public Mesh
	{
	public:
		SphereMesh(const char* const modelFileName);
		~SphereMesh();

		// tells the compiler do not create or allow it to be used, c++11
		SphereMesh(const SphereMesh&) = delete;
		SphereMesh& operator=(const SphereMesh& other) = delete;
	private:
		void privCreateVAO(const char* const modelFileName);
	};
}

#endif

// --- End of File ---