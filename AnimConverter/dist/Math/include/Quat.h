//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Matrix.h"
#include "Debug.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------
namespace Azul
{
	class Quat final : public Align16
	{
	public:
		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot
		{
			AxisAngle,
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

		// Do your magic here
		Quat();
		Quat(const Quat& q);
		Quat& operator=(const Quat& q);
		~Quat() = default;

		Quat(const float qx, const float qy, const float qz, const float qw);
		Quat(const float qx, const float qy, const float qz);
		Quat(const Matrix& M);
		Quat(const Vect& v, const float qw);
		Quat(Quat::Special);
		Quat(Quat::Rot3, const float x, const float y, const float z);
		Quat(Quat::Rot1, const float f); //rotation
		Quat(Quat::Rot, const Vect& v, const float real);
		Quat(const Quat::Orient, const Vect& dof, const Vect& up);

		//Operators
		//Addition
		Quat operator+(const Quat& q) const;
		Quat operator+=(const Quat& q);

		//Sub
		Quat operator-(const Quat& q) const;
		Quat operator-=(const Quat& q);

		//Multiply
		Quat operator*(const Quat& q) const;
		Quat operator*=(const Quat& q);
		//Quat operator*(const Matrix& M) const;
		Quat operator*=(const Matrix& M);
		friend Matrix operator*(const Quat& q, const Matrix& M);

		//Div
		Quat operator/(const Quat& q) const;
		Quat operator/=(const Quat& q);

		//Scale
		Quat operator+(const float f) const;
		Quat operator+=(const float f);
		Quat operator-(const float f) const;
		Quat operator-=(const float f);
		Quat operator*(const float& scale) const; //Quat * scale
		Quat operator*=(const float& scale);
		Quat operator/(const float& scale) const;
		Quat operator/=(const float& scale);
		friend Quat operator*(const float s, const Quat& q); //scale * Quat
		friend Quat operator+(const float s, const Quat& q);
		friend Quat operator-(const float s, const Quat& q);
		friend Quat operator/(const float& scale, const Quat& q);
		friend Matrix operator*(const Matrix& M, const Quat& q);
		Quat operator+(); //Unary plus operator
		Quat operator-(); //Unary minus operator
		Quat operator-() const;

		//Sets
		void set(const float qx, const float qy, const float qz, const float qw);
		void set(const float qx, const float qy, const float qz);
		void set(const Vect& v, float qw);
		void set(const Matrix& M);
		void set(Quat::Rot, const Vect& v, const float qz);
		void set(Quat::Rot3, const float x, const float y, const float z);
		
		void set(const Quat::Orient, const Vect& dof, const Vect& up);
		void set(Quat::Special s); //set special
		void set(Quat::Rot1 r, const float f); //rotation

		void setVect(const Vect& v);
		float getAngle();
		void getVect(Vect& vOut);
		void getAxis(Vect& vOut);

		//Bracket operators
		const float& operator[](x_enum) const;
		const float& operator[](y_enum) const;
		const float& operator[](z_enum) const;
		const float& operator[](w_enum) const;

		//set brackets
		float& operator[](x_enum);
		float& operator[](y_enum);
		float& operator[](z_enum);
		float& operator[](w_enum);

		//Get const ()
		const float& qx() const;
		const float& qy() const;
		const float& qz() const;
		const float& real() const;

		//Set
		float& qx();
		float& qy();
		float& qz();
		float& real();

		//Math operations
		float dot(const Quat& q) const;
		float dot(const Vect& v) const;
		Quat cross(const Quat& q) const;
		Vect cross(const Vect& v) const;
		Quat multByElement(const Quat& q);
		Quat norm();
		void conj();
		void T();
		void inv();

		void Lqcvq(const Vect& v, Vect& vOut);
		void Lqvqc(const Vect& v, Vect& vOut);
		
		Quat getNorm() const;
		Quat getConj() const;
		Quat getT() const;
		Quat getInv() const;
		float mag() const;
		float magSquared() const;
		float invMag() const;

		//Boolean
		bool isEqual(const Quat& q, const float tolerance) const;
		bool isNegEqual(const Quat& q, const float tolerance) const;
		bool isEquivalent(const Quat& q, const float tolerance) const;
		bool isConjugateEqual(const Quat& q, const float tolerance) const;
		bool isIdentity(const float tolerance) const;
		bool isNormalized(const float tolerance) const;
		bool isZero(const float tolerance) const;

		// For printing
		friend void Debug::Print(const char *pName, const Quat &r);

	private:

		// anonymous union
		union
		{
			__m128	_mq;

			// anonymous struct
			struct
			{
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};
		};

	};
}

#endif 

// ---  End of File ---------------
