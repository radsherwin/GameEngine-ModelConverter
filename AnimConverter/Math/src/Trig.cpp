//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <math.h>    // <--- ONLY location for <math.h> allowed
#include "Trig.h"

namespace Azul
{

	const float Trig::cos(const float& f)
	{
		const float tmp = cosf(f);
		return tmp;
	}

	const float Trig::sin(const float& f)
	{
		const float tmp = sinf(f);
		return tmp;
	}

	const float Trig::tan(const float& f)
	{
		const float tmp = tanf(f);
		return tmp;
	}

	const float Trig::atan(const float& f)
	{
		const float tmp = atanf(f);
		return tmp;;
	}

	const float Trig::atan2(const float& x, const float& y)
	{
		const float tmp = atan2f(x, y);
		return tmp;
	}

	const float Trig::acos(const float& f)
	{
		const float tmp = acosf(f);
		return tmp;
	}

	const float Trig::asin(const float& f)
	{
		const float tmp = asinf(f);
		return tmp;
	}

	void Trig::cossin(float& x, float& y, const float& z)
	{
		x = cosf(z);
		y = sinf(z);
	}

	const float Trig::sqrt(const float& f)
	{
		const float tmp = sqrtf(f);
		return tmp;
	}

	const float Trig::rsqrt(const float& f)
	{
		const float tmp = 1 / sqrtf(f);

		return tmp;
	}

}

//--- End of File ---
