//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "MathEngine.h"
#include "Debug.h"

namespace Azul
{

	// Do your magic here
	void Debug::Print(const char* pName, const Vect& r)
	{
		Trace::out("%s:(Vect) \n", pName);
		Trace::out(" %9.4g %9.4g %9.4g %9.4g \n", r._vx, r._vy, r._vz, r._vw);
		Trace::out("\n");
	}

	void Debug::Print(const char *pName, const Quat &r)
	{
		Trace::out("%s:(Quat) \n", pName);
		Trace::out(" %9.4g %9.4g %9.4g %9.4g \n", r._qx, r._qy, r._qz, r._qw);
		Trace::out("\n");
	}

	void Debug::Print(const char* pName, const Matrix& r)
	{
		Trace::out("%s:(Matrix) \n", pName);
		Trace::out(" %9.4g %9.4g %9.4g %9.4g \n", r._m0, r._m1, r._m2, r._m3);
		Trace::out(" %9.4g %9.4g %9.4g %9.4g \n", r._m4, r._m5, r._m6, r._m7);
		Trace::out(" %9.4g %9.4g %9.4g %9.4g \n", r._m8, r._m9, r._m10, r._m11);
		Trace::out(" %9.4g %9.4g %9.4g %9.4g \n", r._m12, r._m13, r._m14, r._m15);		
		Trace::out("\n");
	}

}

//--- End of File ---
