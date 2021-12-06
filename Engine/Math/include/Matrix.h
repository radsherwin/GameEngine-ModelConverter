//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "Vect.h"
#include "Debug.h"

namespace Azul
{
	class Quat;

	class Matrix final : public Align16
	{
	public:

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Trans
		{
			XYZ
		};

		enum class Scale
		{
			XYZ
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

		enum class Row
		{
			i0,
			i1,
			i2,
			i3
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

		// Do your magic here
		Matrix();
		Matrix(const Matrix& m);
		Matrix& operator=(const Matrix& m);
		~Matrix() = default;

		Matrix(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3);

		//rotation
		Matrix(Orient o, Vect& v0, Vect& v1);
		Matrix(Rot r, Vect& v, const float angle);
		Matrix(const Rot1 r, const float& angle);
		Matrix(Trans t, const float& x, const float& y, const float& z);
		Matrix(Trans t, const Vect& v);
		Matrix(Scale s, const float& x, const float& y, const float& z);
		Matrix(Scale s, const Vect& v);
		Matrix(Rot3 r, const float& x, const float& y, const float& z);
		Matrix(const Quat& q);

		Matrix(Special s);

		//Set axis angle
		void set(const Vect& axis, float angle);

		//SET
		Vect get(const Row r); //get row
		void set(const Row r, const Vect& v); //set row

		void set(const Special s); //set special
		void set(const Trans t, const float& _x, const float& _y, const float& _z); //set Translation
		void set(const Trans t, const Vect& v);
		void set(const Scale s, const float& x, const float& y, const float& z);
		void set(const Scale s, const Vect& v); // scale by vector
		void set(const Rot1 r, const float& f);
		void set(Rot3 r, const float& x, const float& y, const float& z);
		void set(const Rot r, const Vect& v, const float& angle); //set axis angle
		void set(const Orient o, Vect& dof, Vect& yUp); //orient
		void set(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3);
		void set(const Quat& q); //Quaternion to Matrix

		//Operators
		Matrix operator+(const Matrix& m); // Matrix + Matrix
		Matrix operator += (const Matrix& m); // Matrix += Matrix
		Matrix operator-(const Matrix& m); //Matrix - Matrix
		Matrix operator -= (const Matrix& m); //Matrix -= Matrix

		//Multiply
		Matrix operator*(const Matrix& m) const;
		Matrix operator*= (const Matrix& m);
		Matrix operator*(const float& scale) const; //Matrix * scale
		friend Matrix operator*(const float s, const Matrix& m); //scale * Matrix
		Matrix operator*=(const float& scale); //Matrix *= scale
		//Matrix operator*(const Quat& q) const;

		Matrix operator+(); //Unary plus operator
		Matrix operator-(); //Unary minus operator

		//Get const bracket operators
		const float& operator[](m0_enum) const;
		const float& operator[](m1_enum) const;
		const float& operator[](m2_enum) const;
		const float& operator[](m3_enum) const;
		const float& operator[](m4_enum) const;
		const float& operator[](m5_enum) const;
		const float& operator[](m6_enum) const;
		const float& operator[](m7_enum) const;
		const float& operator[](m8_enum) const;
		const float& operator[](m9_enum) const;
		const float& operator[](m10_enum) const;
		const float& operator[](m11_enum) const;
		const float& operator[](m12_enum) const;
		const float& operator[](m13_enum) const;
		const float& operator[](m14_enum) const;
		const float& operator[](m15_enum) const;

		//set brackets
		float& operator[](m0_enum);
		float& operator[](m1_enum);
		float& operator[](m2_enum);
		float& operator[](m3_enum);
		float& operator[](m4_enum);
		float& operator[](m5_enum);
		float& operator[](m6_enum);
		float& operator[](m7_enum);
		float& operator[](m8_enum);
		float& operator[](m9_enum);
		float& operator[](m10_enum);
		float& operator[](m11_enum);
		float& operator[](m12_enum);
		float& operator[](m13_enum);
		float& operator[](m14_enum);
		float& operator[](m15_enum);
		
		//Get
		const float& m0() const;
		const float& m1() const;
		const float& m2() const;
		const float& m3() const;
		const float& m4() const;
		const float& m5() const;
		const float& m6() const;
		const float& m7() const;
		const float& m8() const;
		const float& m9() const;
		const float& m10() const;
		const float& m11() const;
		const float& m12() const;
		const float& m13() const;
		const float& m14() const;
		const float& m15() const;

		//Set
		float& m0();
		float& m1();
		float& m2();
		float& m3();
		float& m4();
		float& m5();
		float& m6();
		float& m7();
		float& m8();
		float& m9();
		float& m10();
		float& m11();
		float& m12();
		float& m13();
		float& m14();
		float& m15();

		//Math
		//
		//deter
		const float det();
		//Transpose
		void T();
		const Matrix getT();
		
		void inv();
		const Matrix getInv();

		//Boolean
		bool isEqual(const Matrix& m);
		bool isEqual(const Matrix& m, const float& tolerance);

		const bool isIdentity();
		const bool isIdentity(const float& tolerance);

		const bool isRotation();

		// For printing
		friend void Debug::Print(const char *pName, const Matrix &r);

	private:

		union
		{

			struct
			{
				Vect _rows[4];
			};


			struct
			{
				Vect _v0;
				Vect _v1;
				Vect _v2;
				Vect _v3;
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};
	};
}

#endif

//--- End of File ---
