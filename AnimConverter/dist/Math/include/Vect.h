//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Enum.h"
#include "Constants.h"
#include "Debug.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Matrix;
	class Quat;

	class Vect final : public Align16
	{
	public:

		Vect();
		Vect(const Vect& v);
		Vect& operator=(const Vect& v);
		~Vect() = default;

		Vect(const float vx, const float vy, const float vz);
		Vect(const float vx, const float vy, const float vz, const float vw);
		
		//const bracket operators
		const float& operator[](x_enum) const;
		const float& operator[](y_enum) const;
		const float& operator[](z_enum) const;
		const float& operator[](w_enum) const;

		//set brackets
		float& operator[](x_enum);
		float& operator[](y_enum);
		float& operator[](z_enum);
		float& operator[](w_enum);

		//Get Accessors
		const float& x()const;
		const float& y() const;
		const float& z() const;
		const float& w() const;

		//Set Accessors
		float& x();
		float& y();
		float& z();
		float& w();
		
		//Operators
		Vect operator+(const Quat& q) const; //Vect + Quat
		Vect operator+(const Vect& v); // Vect + Vect
		Vect operator += (const Vect& v); // Vect += Vect
		Vect operator-(const Vect& v); //Vect - Vect
		Vect operator -= (const Vect& v); //Vect -= Vect
		friend Vect operator-(const Vect& a, const Vect& v);
		friend Vect operator+(const Vect& a, const Vect& v);
		

		const Vect operator*(const Matrix& m) const; //Vect * Matrix
		Vect operator*=(const Matrix& m); //Vect *= Matrix
		Vect operator*(const Quat& q) const; //Vect * Quat
		Vect operator*=(const Quat& q);

		//Scaling operators
		friend Vect operator*(const float s, const Vect& v);
		const Vect operator*(const float& v) const;
		Vect operator*=(const float& v);

		//Unary operators
		Vect operator+(); //Unary plus operator
		Vect operator-(); //Unary minus operator

		//Math
		const float mag();
		const float magSqr();

		const float dot(const Vect& v); //dot product
		Vect cross(const Vect& v) const; //cross product
		Vect cross(const Quat& q) const;

		Vect norm();
		Vect getNorm();
		const float getAngle(Vect& v);

		//Boolean
		const bool isEqual(const Vect& v, const float& tolerance);
		const bool isEqual(const Vect& v);
		const bool isZero(const float& tolerance);
		const bool isZero();

		//Set
		void set(const float& x, const float& y, const float& z);
		void set(const float& x, const float& y, const float& z, const float& w);
		void set(const Vect& v);
		
		// for printing
		friend void Debug::Print(const char *pName, const Vect &r);

	private:

		union
		{
			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				float _vw;
			};
		};
	};
}

#endif

//--- End of File ---
