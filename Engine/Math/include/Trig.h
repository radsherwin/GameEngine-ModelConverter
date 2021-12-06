//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_TRIG_H
#define ENGINE_MATH_TRIG_H

namespace Azul
{
	class Trig
	{
	public:
		Trig() = default;
		Trig(const Trig & t) = default;
		Trig& operator=(const Trig & t) = default;
		~Trig() = default;

		// Do your magic here
		static const float cos(const float& f);
		static const float sin(const float& f);
		static const float tan(const float& f);
		static const float atan(const float& f);
		static const float atan2(const float& x, const float& y);
		static const float acos(const float& f);
		static const float asin(const float& f);
		static void cossin(float& x, float& y, const float& z);
		static const float sqrt(const float& f);
		static const float rsqrt(const float& f);

	};
}

#endif

//--- End of File ---
