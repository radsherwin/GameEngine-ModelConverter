//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
// Do your magic here
   Matrix::Matrix()
	   : _m0(0.0f), _m1(0.0f), _m2(0.0f), _m3(0.0f), _m4(0.0f), _m5(0.0f), _m6(0.0f),
	   _m7(0.0f), _m8(0.0f), _m9(0.0f), _m10(0.0f), _m11(0.0f), _m12(0.0f), _m13(0.0f),
	   _m14(0.0f), _m15(0.0f)
	{}

   Matrix::Matrix(const Matrix& m)
	   : _m0(m._m0), _m1(m._m1), _m2(m._m2), _m3(m._m3), _m4(m._m4), _m5(m._m5), _m6(m._m6),
	   _m7(m._m7), _m8(m._m8), _m9(m._m9), _m10(m._m10), _m11(m._m11), _m12(m._m12), _m13(m._m13),
	   _m14(m._m14), _m15(m._m15)
   {

   }
   Matrix& Matrix::operator=(const Matrix& m) {
	   this->_m0 = m.m0();
	   this->_m1 = m.m1();
	   this->_m2 = m.m2();
	   this->_m3 = m.m3();
	   this->_m4 = m.m4();
	   this->_m5 = m.m5();
	   this->_m6 = m.m6();
	   this->_m7 = m.m7();
	   this->_m8 = m.m8();
	   this->_m9 = m.m9();
	   this->_m10 = m.m10();
	   this->_m11 = m.m11();
	   this->_m12 = m.m12();
	   this->_m13 = m.m13();
	   this->_m14 = m.m14();
	   this->_m15 = m.m15();

	   return *this;
   }

   Matrix::Matrix(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3)
   {
	   this->_m0 = v0.x();
	   this->_m1 = v0.y();
	   this->_m2 = v0.z();
	   this->_m3 = v0.w();
	   this->_m4 = v1.x();
	   this->_m5 = v1.y();
	   this->_m6 = v1.z();
	   this->_m7 = v1.w();
	   this->_m8 = v2.x();
	   this->_m9 = v2.y();
	   this->_m10 = v2.z();
	   this->_m11 = v2.w();
	   this->_m12 = v3.x();
	   this->_m13 = v3.y();
	   this->_m14 = v3.z();
	   this->_m15 = v3.w();
   }

   Matrix::Matrix(Special s) {
	   Matrix M;
	   switch (s) {
	   case Special::Zero:
		   *this = M;
		   break;
	   case Special::Identity:
		   this->set(s);
		   break;
	   }
   }

   //RotOrient
   Matrix::Matrix(Orient o, Vect& DOF, Vect& yUp)
   {
	   Vect v1 = yUp.cross(DOF);
	   Vect v2 = DOF.cross(v1);

	   v1.norm();
	   v2.norm();
	   Vect v3 = DOF;
	   v3.norm();

	   v1.w() = 0;
	   v2.w() = 0;
	   v3.w() = 0;


	   Matrix M(v1, v2, v3, Vect(0, 0, 0, 1));

	   switch (o) {
	   case Orient::LocalToWorld:
		   *this = M;
		   break;

	   case Orient::WorldToLocal:
		   M.T();
		   *this = M;
		   break;
	   }
	   //return *this;
   }

   Matrix::Matrix(Rot r, Vect& v, const float angle)
   {
	   if (r == Rot::AxisAngle) {
		   set(v, angle);
	   }
   }

   Matrix::Matrix(const Rot1 r, const float& f)
   {
	   switch (r) {
	   case Rot1::X:
		   this->set(Row::i0, Vect(1, 0, 0, 0));
		   this->set(Row::i1, Vect(0, Trig::cos(f), Trig::sin(f), 0));
		   this->set(Row::i2, Vect(0, -Trig::sin(f), Trig::cos(f), 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   case Rot1::Y:
		   this->set(Row::i0, Vect(Trig::cos(f), 0, -Trig::sin(f), 0));
		   this->set(Row::i1, Vect(0, 1, 0, 0));
		   this->set(Row::i2, Vect(Trig::sin(f), 0, Trig::cos(f), 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   case Rot1::Z:
		   this->set(Row::i0, Vect(Trig::cos(f), Trig::sin(f), 0, 0));
		   this->set(Row::i1, Vect(-Trig::sin(f), Trig::cos(f), 0, 0));
		   this->set(Row::i2, Vect(0, 0, 1, 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   }
   }

   Matrix::Matrix(Trans t, const float& _x, const float& _y, const float& _z)
   {
	   switch (t) {
	   case(Trans::XYZ):
		   this->set(Special::Identity);
		   this->_m12 = _x;
		   this->_m13 = _y;
		   this->_m14 = _z;
		   break;
	   }
   }

   Matrix::Matrix(Trans t, const Vect& v)
   {
	   this->set(t, v);
   }

   Matrix::Matrix(Scale _s, const float& _x, const float& _y, const float& _z) {
	   this->set(_s, _x, _y, _z);
   }

   Matrix::Matrix(Scale _s, const Vect& v)
   {
	   this->set(_s, v);
   }

   Matrix::Matrix(Rot3 r, const float& _x, const float& _y, const float& _z) {
	   this->set(r, _x, _y, _z);
   }

	Matrix::Matrix(const Quat& q)
	{
		_m0 = 1 - 2 * (q.qy() * q.qy() + q.qz() * q.qz());
		_m1 = 2 * (q.qx() * q.qy() + q.real() * q.qz());
		_m2 = 2 * (q.qx() * q.qz() - q.real() * q.qy());
		_m3 = 0;
		_m4 = 2 * (q.qx() * q.qy() - q.real() * q.qz());
		_m5 = 1 - 2 * (q.qx() * q.qx() + q.qz() * q.qz());
		_m6 = 2 * (q.qy() * q.qz() + q.real() * q.qx());
		_m7 = 0;
		_m8 = 2 * (q.qx() * q.qz() + q.real() * q.qy());
		_m9 = 2 * (q.qy() * q.qz() - q.real() * q.qx());
		_m10 = 1 - 2 * (q.qx() * q.qx() + q.qy() * q.qy());
		_m11 = 0;
		_m12 = 0;
		_m13 = 0;
		_m14 = 0;
		_m15 = 1;
	}

//Set Axis angle
   void Matrix::set(const Vect& axis, float angle)
   {
	   // angle
	   // axis;
   	   Vect tmpAxis = axis;
	   const float angle_a = 0.5f * angle;
	   float cos_a;
	   float sin_a;

	   cos_a = cosf(angle_a);
	   sin_a = sinf(angle_a);

	   Vect qV = tmpAxis.getNorm();

	   qV *= sin_a;

	   Vect Q;
	   Q[x] = qV[x];
	   Q[y] = qV[y];
	   Q[z] = qV[z];
	   Q[w] = cos_a;

	   // this function has been transposed
	   float x2, y2, z2;
	   float xx, xy, xz;
	   float yy, yz, zz;
	   float wx, wy, wz;

	   // ADD test to make sure that quat is normalized

	   x2 = Q[x] + Q[x];
	   y2 = Q[y] + Q[y];
	   z2 = Q[z] + Q[z];

	   xx = Q[x] * x2;
	   xy = Q[x] * y2;
	   xz = Q[x] * z2;

	   yy = Q[y] * y2;
	   yz = Q[y] * z2;
	   zz = Q[z] * z2;

	   wx = Q[w] * x2;
	   wy = Q[w] * y2;
	   wz = Q[w] * z2;

	   this->_m0 = 1.0f - (yy + zz);
	   this->_m1 = xy + wz;
	   this->_m2 = xz - wy;
	   this->_m3 = 0.0f;

	   this->_m4 = xy - wz;
	   this->_m5 = 1.0f - (xx + zz);
	   this->_m6 = yz + wx;
	   this->_m7 = 0.0f;

	   this->_m8 = xz + wy;
	   this->_m9 = yz - wx;
	   this->_m10 = 1.0f - (xx + yy);
	   this->_m11 = 0.0f;

	   this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

   }

   //SET
   Vect Matrix::get(const Row r) { //get row
	   Vect tmp;
	   switch (r) {
	   case Row::i0:
		   tmp.set(this->_m0, this->_m1, this->_m2, this->_m3);
		   break;
	   case Row::i1:
		   tmp.set(this->_m4, this->_m5, this->_m6, this->_m7);
		   break;
	   case Row::i2:
		   tmp.set(this->_m8, this->_m9, this->_m10, this->_m11);
		   break;
	   case Row::i3:
		   tmp.set(this->_m12, this->_m13, this->_m14, this->_m15);
		   break;

	   }

	   return tmp;
   }

   void Matrix::set(const Row r, const Vect& v) { //get row
	   switch (r) {
	   case Row::i0:
		   this->_m0 = v.x();
		   this->_m1 = v.y();
		   this->_m2 = v.z();
		   this->_m3 = v.w();
		   break;
	   case Row::i1:
		   this->_m4 = v.x();
		   this->_m5 = v.y();
		   this->_m6 = v.z();
		   this->_m7 = v.w();
		   break;
	   case Row::i2:
		   this->_m8 = v.x();
		   this->_m9 = v.y();
		   this->_m10 = v.z();
		   this->_m11 = v.w();
		   break;
	   case Row::i3:
		   this->_m12 = v.x();
		   this->_m13 = v.y();
		   this->_m14 = v.z();
		   this->_m15 = v.w();
		   break;

	   }
   }

   void Matrix::set(const Special s) {
	   Matrix tmp;

	   switch (s) {
	   case Special::Identity:
		   tmp.set(Row::i0, Vect(1, 0, 0, 0));
		   tmp.set(Row::i1, Vect(0, 1, 0, 0));
		   tmp.set(Row::i2, Vect(0, 0, 1, 0));
		   tmp.set(Row::i3, Vect(0, 0, 0, 1));
		   *this = tmp;
		   break;
	   case Special::Zero:
		   tmp.set(Row::i0, Vect(0, 0, 0, 0));
		   tmp.set(Row::i1, Vect(0, 0, 0, 0));
		   tmp.set(Row::i2, Vect(0, 0, 0, 0));
		   tmp.set(Row::i3, Vect(0, 0, 0, 0));
		   *this = tmp;
	   }
   }

   void Matrix::set(const Trans t, const float& _x, const float& _y, const float& _z) {
	   switch (t) {
	   case(Trans::XYZ):
		   this->set(Special::Identity);
		   this->_m12 = _x;
		   this->_m13 = _y;
		   this->_m14 = _z;
		   break;
	   }
   }

   void Matrix::set(const Trans t, const Vect& _v) {
	   switch (t) {
	   case(Trans::XYZ):
		   this->set(Special::Identity);
		   this->_m12 = _v.x();
		   this->_m13 = _v.y();
		   this->_m14 = _v.z();
		   break;
	   }

   }

   void Matrix::set(const Scale s, const float& _x, const float& _y, const float& _z) {
	   switch (s) {
	   case(Scale::XYZ):
		   this->set(Row::i0, Vect(_x, 0, 0, 0));
		   this->set(Row::i1, Vect(0, _y, 0, 0));
		   this->set(Row::i2, Vect(0, 0, _z, 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   }
   }

   void Matrix::set(const Scale s, const Vect& _v) {
	   switch (s) {
	   case(Scale::XYZ):
		   this->set(Row::i0, Vect(_v.x(), 0, 0, 0));
		   this->set(Row::i1, Vect(0, _v.y(), 0, 0));
		   this->set(Row::i2, Vect(0, 0, _v.z(), 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   }
   }

   void Matrix::set(const Rot1 r, const float& f) {
	   switch (r) {
	   case Rot1::X:
		   this->set(Row::i0, Vect(1, 0, 0, 0));
		   this->set(Row::i1, Vect(0, Trig::cos(f), Trig::sin(f), 0));
		   this->set(Row::i2, Vect(0, -Trig::sin(f), Trig::cos(f), 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   case Rot1::Y:
		   this->set(Row::i0, Vect(Trig::cos(f), 0, -Trig::sin(f), 0));
		   this->set(Row::i1, Vect(0, 1, 0, 0));
		   this->set(Row::i2, Vect(Trig::sin(f), 0, Trig::cos(f), 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   case Rot1::Z:
		   this->set(Row::i0, Vect(Trig::cos(f), Trig::sin(f), 0, 0));
		   this->set(Row::i1, Vect(-Trig::sin(f), Trig::cos(f), 0, 0));
		   this->set(Row::i2, Vect(0, 0, 1, 0));
		   this->set(Row::i3, Vect(0, 0, 0, 1));
		   break;
	   }

   }

   void Matrix::set(Rot3 r, const float& _x, const float& _y, const float& _z) {
	   switch (r)
	   {
	   case Rot3::XYZ:
		   Matrix Rx;
		   Matrix Ry;
		   Matrix Rz;
		   Rx.set(Rot1::X, _x);
		   Ry.set(Rot1::Y, _y);
		   Rz.set(Rot1::Z, _z);

		   *this = Rx * Ry * Rz;

		   break;
	   }
   }

   void Matrix::set(const Rot r, const Vect& _v, const float& angle) {
	   AZUL_UNUSED_VAR(r);
	   this->set(_v, angle);
   }

   void Matrix::set(const Orient o, Vect& dof, Vect& yUp) {
	   Matrix M(o, dof, yUp);
	   *this = M;
   }

   void Matrix::set(const Vect& _vA, const Vect& _vB, const Vect& _vC, const Vect& _vD) {
	   Matrix M(_vA, _vB, _vC, _vD);
	   *this = M;
   }

void Matrix::set(const Quat& q)
{
   	_m0 = 1 - 2 * (q.qy()* q.qy() + q.qz() * q.qz());
   	_m1 = 2 * (q.qx()*q.qy() + q.real()*q.qz());
   	_m2 = 2 *(q.qx()*q.qz() - q.real()*q.qy());
   	_m3 = 0;
   	_m4 = 2 * (q.qx() * q.qy() - q.real() * q.qz());
   	_m5 = 1 - 2 * (q.qx() * q.qx() + q.qz() * q.qz());
   	_m6 = 2 * (q.qy() * q.qz() + q.real() * q.qx());
   	_m7 = 0;
   	_m8 = 2 * (q.qx() * q.qz() + q.real()*q.qy());
   	_m9 = 2*(q.qy()*q.qz() - q.real()*q.qx());
   	_m10 = 1 - 2*(q.qx() * q.qx() + q.qy() * q.qy());
   	_m11 = 0;
   	_m12 = 0;
   	_m13 = 0;
   	_m14 = 0;
   	_m15 = 1;
}

//Operators
   Matrix Matrix::operator+(const Matrix& _m) //Matrix + Matrix
   {
	   return Matrix(Vect(this->_m0 + _m._m0, this->_m1 + _m._m1, this->_m2 + _m._m2, this->_m3 + _m._m3),
		   Vect(this->_m4 + _m._m4, this->_m5 + _m._m5, this->_m6 + _m._m6, this->_m7 + _m._m7),
		   Vect(this->_m8 + _m._m8, this->_m9 + _m._m9, this->_m10 + _m._m10, this->_m11 + _m._m11),
		   Vect(this->_m12 + _m._m12, this->_m13 + _m._m13, this->_m14 + _m._m14, this->_m15 + _m._m15));
   }
   Matrix Matrix::operator+=(const Matrix& _m) //Matrix += Matrix
   {
	   this->_m0 += _m._m0;
	   this->_m1 += _m._m1;
	   this->_m2 += _m._m2;
	   this->_m3 += _m._m3;
	   this->_m4 += _m._m4;
	   this->_m5 += _m._m5;
	   this->_m6 += _m._m6;
	   this->_m7 += _m._m7;
	   this->_m8 += _m._m8;
	   this->_m9 += _m._m9;
	   this->_m10 += _m._m10;
	   this->_m11 += _m._m11;
	   this->_m12 += _m._m12;
	   this->_m13 += _m._m13;
	   this->_m14 += _m._m14;
	   this->_m15 += _m._m15;

	   return *this;
   }

   Matrix Matrix::operator-(const Matrix& _m) //Matrix - Matrix
   {
	   return Matrix(Vect(this->_m0 - _m._m0, this->_m1 - _m._m1, this->_m2 - _m._m2, this->_m3 - _m._m3),
		   Vect(this->_m4 - _m._m4, this->_m5 - _m._m5, this->_m6 - _m._m6, this->_m7 - _m._m7),
		   Vect(this->_m8 - _m._m8, this->_m9 - _m._m9, this->_m10 - _m._m10, this->_m11 - _m._m11),
		   Vect(this->_m12 - _m._m12, this->_m13 - _m._m13, this->_m14 - _m._m14, this->_m15 - _m._m15));
   }
   Matrix Matrix::operator-=(const Matrix& _m) //Matrix -= Matrix
   {
	   this->_m0 -= _m._m0;
	   this->_m1 -= _m._m1;
	   this->_m2 -= _m._m2;
	   this->_m3 -= _m._m3;
	   this->_m4 -= _m._m4;
	   this->_m5 -= _m._m5;
	   this->_m6 -= _m._m6;
	   this->_m7 -= _m._m7;
	   this->_m8 -= _m._m8;
	   this->_m9 -= _m._m9;
	   this->_m10 -= _m._m10;
	   this->_m11 -= _m._m11;
	   this->_m12 -= _m._m12;
	   this->_m13 -= _m._m13;
	   this->_m14 -= _m._m14;
	   this->_m15 -= _m._m15;

	   return *this;
   }

   Matrix Matrix::operator*(const Matrix& m) const
   {
	   Matrix result = *this;
	   result._m0 = (this->_m0 * m.m0() + this->_m1 * m.m4() + this->_m2 * m.m8() + this->_m3 * m.m12());
	   result._m1 = (this->_m0 * m.m1() + this->_m1 * m.m5() + this->_m2 * m.m9() + this->_m3 * m.m13());
	   result._m2 = (this->_m0 * m.m2() + this->_m1 * m.m6() + this->_m2 * m.m10() + this->_m3 * m.m14());
	   result._m3 = (this->_m0 * m.m3() + this->_m1 * m.m7() + this->_m2 * m.m11() + this->_m3 * m.m15());
	   result._m4 = (this->_m4 * m.m0() + this->_m5 * m.m4() + this->_m6 * m.m8() + this->_m7 * m.m12());
	   result._m5 = (this->_m4 * m.m1() + this->_m5 * m.m5() + this->_m6 * m.m9() + this->_m7 * m.m13());
	   result._m6 = (this->_m4 * m.m2() + this->_m5 * m.m6() + this->_m6 * m.m10() + this->_m7 * m.m14());
	   result._m7 = (this->_m4 * m.m3() + this->_m5 * m.m7() + this->_m6 * m.m11() + this->_m7 * m.m15());
	   result._m8 = (this->_m8 * m.m0() + this->_m9 * m.m4() + this->_m10 * m.m8() + this->_m11 * m.m12());
	   result._m9 = (this->_m8 * m.m1() + this->_m9 * m.m5() + this->_m10 * m.m9() + this->_m11 * m.m13());
	   result._m10 = (this->_m8 * m.m2() + this->_m9 * m.m6() + this->_m10 * m.m10() + this->_m11 * m.m14());
	   result._m11 = (this->_m8 * m.m3() + this->_m9 * m.m7() + this->_m10 * m.m11() + this->_m11 * m.m15());
	   result._m12 = (this->_m12 * m.m0() + this->_m13 * m.m4() + this->_m14 * m.m8() + this->_m15 * m.m12());
	   result._m13 = (this->_m12 * m.m1() + this->_m13 * m.m5() + this->_m14 * m.m9() + this->_m15 * m.m13());
	   result._m14 = (this->_m12 * m.m2() + this->_m13 * m.m6() + this->_m14 * m.m10() + this->_m15 * m.m14());
	   result._m15 = (this->_m12 * m.m3() + this->_m13 * m.m7() + this->_m14 * m.m11() + this->_m15 * m.m15());

	   return result;

   }

   Matrix Matrix::operator*=(const Matrix& m)
   {
	   Matrix tmp = *this * m;
	   *this = tmp;
	   return *this;
   }

   Matrix Matrix::operator*(const float& scale) const
   {
	   Matrix result = *this;
	   result._m0 = this->_m0 * scale;
	   result._m1 = this->_m1 * scale;
	   result._m2 = this->_m2 * scale;
	   result._m3 = this->_m3 * scale;
	   result._m4 = this->_m4 * scale;
	   result._m5 = this->_m5 * scale;
	   result._m6 = this->_m6 * scale;
	   result._m7 = this->_m7 * scale;
	   result._m8 = this->_m8 * scale;
	   result._m9 = this->_m9 * scale;
	   result._m10 = this->_m10 * scale;
	   result._m11 = this->_m11 * scale;
	   result._m12 = this->_m12 * scale;
	   result._m13 = this->_m13 * scale;
	   result._m14 = this->_m14 * scale;
	   result._m15 = this->_m15 * scale;

	   return result;

   }

   Matrix Azul::operator*(const float s, const Matrix& m) {
	   return m * s;
   }

   Matrix Matrix::operator*=(const float& scale) {
	   this->_m0 *= scale;
	   this->_m1 *= scale;
	   this->_m2 *= scale;
	   this->_m3 *= scale;
	   this->_m4 *= scale;
	   this->_m5 *= scale;
	   this->_m6 *= scale;
	   this->_m7 *= scale;
	   this->_m8 *= scale;
	   this->_m9 *= scale;
	   this->_m10 *= scale;
	   this->_m11 *= scale;
	   this->_m12 *= scale;
	   this->_m13 *= scale;
	   this->_m14 *= scale;
	   this->_m15 *= scale;

	   return *this;
   }

	/*Matrix Matrix::operator*(const Quat& q) const
	{
		Quat newM(*this);
		Quat tmp = q * newM;
		return Matrix(tmp);
	}*/

//Unary operators
   Matrix Matrix::operator+() {
	   this->m0() = +this->m0();
	   this->m1() = +this->m1();
	   this->m2() = +this->m2();
	   this->m3() = +this->m3();
	   this->m4() = +this->m4();
	   this->m5() = +this->m5();
	   this->m6() = +this->m6();
	   this->m7() = +this->m7();
	   this->m8() = +this->m8();
	   this->m9() = +this->m9();
	   this->m10() = +this->m10();
	   this->m11() = +this->m11();
	   this->m12() = +this->m12();
	   this->m13() = +this->m13();
	   this->m14() = +this->m14();
	   this->m15() = +this->m15();
	   return *this;
   }

   Matrix Matrix::operator-() {
	   Matrix copy = *this;
	   copy.m0() = -copy.m0();
	   copy.m1() = -copy.m1();
	   copy.m2() = -copy.m2();
	   copy.m3() = -copy.m3();
	   copy.m4() = -copy.m4();
	   copy.m5() = -copy.m5();
	   copy.m6() = -copy.m6();
	   copy.m7() = -copy.m7();
	   copy.m8() = -copy.m8();
	   copy.m9() = -copy.m9();
	   copy.m10() = -copy.m10();
	   copy.m11() = -copy.m11();
	   copy.m12() = -copy.m12();
	   copy.m13() = -copy.m13();
	   copy.m14() = -copy.m14();
	   copy.m15() = -copy.m15();
	   return copy;
   }

   //Get bracket
   const float& Matrix::operator[](m0_enum) const {
	   return this->_m0;
   }
   const float& Matrix::operator[](m1_enum) const {
	   return this->_m1;
   }
   const float& Matrix::operator[](m2_enum) const {
	   return this->_m2;
   }
   const float& Matrix::operator[](m3_enum) const {
	   return this->_m3;
   }
   const float& Matrix::operator[](m4_enum) const {
	   return this->_m4;
   }
   const float& Matrix::operator[](m5_enum) const {
	   return this->_m5;
   }
   const float& Matrix::operator[](m6_enum) const {
	   return this->_m6;
   }
   const float& Matrix::operator[](m7_enum) const {
	   return this->_m7;
   }
   const float& Matrix::operator[](m8_enum) const {
	   return this->_m8;
   }
   const float& Matrix::operator[](m9_enum) const {
	   return this->_m9;
   }
   const float& Matrix::operator[](m10_enum) const {
	   return this->_m10;
   }
   const float& Matrix::operator[](m11_enum) const {
	   return this->_m11;
   }
   const float& Matrix::operator[](m12_enum) const {
	   return this->_m12;
   }
   const float& Matrix::operator[](m13_enum) const {
	   return this->_m13;
   }
   const float& Matrix::operator[](m14_enum) const {
	   return this->_m14;
   }
   const float& Matrix::operator[](m15_enum) const {
	   return this->_m15;
   }

   //set brackets
   float& Matrix::operator[](m0_enum) {
	   float* p = &this->_m0;
	   return *p;
   }
   float& Matrix::operator[](m1_enum) {
	   float* p = &this->_m1;
	   return *p;
   }
   float& Matrix::operator[](m2_enum) {
	   float* p = &this->_m2;
	   return *p;
   }
   float& Matrix::operator[](m3_enum) {
	   float* p = &this->_m3;
	   return *p;
   }
   float& Matrix::operator[](m4_enum) {
	   float* p = &this->_m4;
	   return *p;
   }
   float& Matrix::operator[](m5_enum) {
	   float* p = &this->_m5;
	   return *p;
   }
   float& Matrix::operator[](m6_enum) {
	   float* p = &this->_m6;
	   return *p;
   }
   float& Matrix::operator[](m7_enum) {
	   float* p = &this->_m7;
	   return *p;
   }
   float& Matrix::operator[](m8_enum) {
	   float* p = &this->_m8;
	   return *p;
   }
   float& Matrix::operator[](m9_enum) {
	   float* p = &this->_m9;
	   return *p;
   }
   float& Matrix::operator[](m10_enum) {
	   float* p = &this->_m10;
	   return *p;
   }
   float& Matrix::operator[](m11_enum) {
	   float* p = &this->_m11;
	   return *p;
   }
   float& Matrix::operator[](m12_enum) {
	   float* p = &this->_m12;
	   return *p;
   }
   float& Matrix::operator[](m13_enum) {
	   float* p = &this->_m13;
	   return *p;
   }
   float& Matrix::operator[](m14_enum) {
	   float* p = &this->_m14;
	   return *p;
   }
   float& Matrix::operator[](m15_enum) {
	   float* p = &this->_m15;
	   return *p;
   }

   //Get accessors
   const float& Matrix::m0() const
   {
	   return this->_m0;
   }

   const float& Matrix::m1() const
   {
	   return this->_m1;
   }

   const float& Matrix::m2() const
   {
	   return this->_m2;
   }

   const float& Matrix::m3() const
   {
	   return this->_m3;
   }

   const float& Matrix::m4() const
   {
	   return this->_m4;
   }

   const float& Matrix::m5() const
   {
	   return this->_m5;
   }

   const float& Matrix::m6() const
   {
	   return this->_m6;
   }

   const float& Matrix::m7() const
   {
	   return this->_m7;
   }

   const float& Matrix::m8() const
   {
	   return this->_m8;
   }

   const float& Matrix::m9() const
   {
	   return this->_m9;
   }

   const float& Matrix::m10() const
   {
	   return this->_m10;
   }

   const float& Matrix::m11() const
   {
	   return this->_m11;
   }

   const float& Matrix::m12() const
   {
	   return this->_m12;
   }

   const float& Matrix::m13() const
   {
	   return this->_m13;
   }

   const float& Matrix::m14() const
   {
	   return this->_m14;
   }

   const float& Matrix::m15() const
   {
	   return this->_m15;
   }

   //Set
   float& Matrix::m0()
   {
	   float* p = &this->_m0;
	   return *p;
   }

   float& Matrix::m1()
   {
	   float* p = &this->_m1;
	   return *p;
   }

   float& Matrix::m2()
   {
	   float* p = &this->_m2;
	   return *p;
   }

   float& Matrix::m3()
   {
	   float* p = &this->_m3;
	   return *p;
   }

   float& Matrix::m4()
   {
	   float* p = &this->_m4;
	   return *p;
   }

   float& Matrix::m5()
   {
	   float* p = &this->_m5;
	   return *p;
   }

   float& Matrix::m6()
   {
	   float* p = &this->_m6;
	   return *p;
   }

   float& Matrix::m7()
   {
	   float* p = &this->_m7;
	   return *p;
   }

   float& Matrix::m8()
   {
	   float* p = &this->_m8;
	   return *p;
   }

   float& Matrix::m9()
   {
	   float* p = &this->_m9;
	   return *p;
   }

   float& Matrix::m10()
   {
	   float* p = &this->_m10;
	   return *p;
   }

   float& Matrix::m11()
   {
	   float* p = &this->_m11;
	   return *p;
   }

   float& Matrix::m12()
   {
	   float* p = &this->_m12;
	   return *p;
   }

   float& Matrix::m13()
   {
	   float* p = &this->_m13;
	   return *p;
   }

   float& Matrix::m14()
   {
	   float* p = &this->_m14;
	   return *p;
   }

   float& Matrix::m15()
   {
	   float* p = &this->_m15;
	   return *p;
   }

   bool Matrix::isEqual(const Matrix& m) {
	   if (fabs(this->_m0 - m._m0) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m1 - m._m1) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m2 - m._m2) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m3 - m._m3) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m4 - m._m4) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m5 - m._m5) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m6 - m._m6) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m7 - m._m7) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m8 - m._m8) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m9 - m._m9) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m10 - m._m10) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m11 - m._m11) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m12 - m._m12) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m13 - m._m13) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m14 - m._m14) > MATH_TOLERANCE) return false;
	   else if (fabs(this->_m15 - m._m15) > MATH_TOLERANCE) return false;

	   return true;
   }

   bool Matrix::isEqual(const Matrix& m, const float& _tolerance) {
	   if (fabs(this->_m0 - m._m0) > _tolerance) return false;
	   else if (fabs(this->_m1 - m._m1) > _tolerance) return false;
	   else if (fabs(this->_m2 - m._m2) > _tolerance) return false;
	   else if (fabs(this->_m3 - m._m3) > _tolerance) return false;
	   else if (fabs(this->_m4 - m._m4) > _tolerance) return false;
	   else if (fabs(this->_m5 - m._m5) > _tolerance) return false;
	   else if (fabs(this->_m6 - m._m6) > _tolerance) return false;
	   else if (fabs(this->_m7 - m._m7) > _tolerance) return false;
	   else if (fabs(this->_m8 - m._m8) > _tolerance) return false;
	   else if (fabs(this->_m9 - m._m9) > _tolerance) return false;
	   else if (fabs(this->_m10 - m._m10) > _tolerance) return false;
	   else if (fabs(this->_m11 - m._m11) > _tolerance) return false;
	   else if (fabs(this->_m12 - m._m12) > _tolerance) return false;
	   else if (fabs(this->_m13 - m._m13) > _tolerance) return false;
	   else if (fabs(this->_m14 - m._m14) > _tolerance) return false;
	   else if (fabs(this->_m15 - m._m15) > _tolerance) return false;

	   return true;
   }

   const bool Matrix::isIdentity(const float& _tolerance)
   {
	   Matrix M;
	   M.set(Special::Identity);
	   if (this->isEqual(M, _tolerance)) return true;
	   else return false;
   }

const bool Matrix::isRotation()
{
   	//M * M.T == M.T * M == I
   	Matrix MT = *this;
   	MT.T();
   	Matrix M = *this * MT;
   	if(!M.isIdentity()) return false;

   	if(this->det() != 1) return false;

   	return true;
   	
}

const bool Matrix::isIdentity()
   {
	   Matrix M;
	   M.set(Special::Identity);
	   if (this->isEqual(M, MATH_TOLERANCE)) return true;
	   else return false;
   }

   const float Matrix::det()
   {
	   const float a1 = this->_m5 * (this->_m10 * this->_m15 - this->_m11 * this->_m14);
	   const float a2 = this->_m6 * (this->_m9 * this->_m15 - this->_m11 * this->_m13);
	   const float a3 = this->_m7 * (this->_m9 * this->_m14 - this->_m10 * this->_m13);

	   const float a00 = this->_m0 * (a1 - a2 + a3);

	   const float a4 = this->_m4 * (this->_m10 * this->_m15 - this->_m11 * this->_m14);
	   const float a5 = this->_m6 * (this->_m8 * this->_m15 - this->_m11 * this->_m12);
	   const float a6 = this->_m7 * (this->_m8 * this->_m14 - this->_m10 * this->_m12);

	   const float a01 = this->_m1 * (a4 - a5 + a6);

	   const float a7 = this->_m4 * (this->_m9 * this->_m15 - this->_m11 * this->_m13);
	   const float a8 = this->_m5 * (this->_m8 * this->_m15 - this->_m11 * this->_m12);
	   const float a9 = this->_m7 * (this->_m8 * this->_m13 - this->_m9 * this->_m12);

	   const float a02 = this->_m2 * (a7 - a8 + a9);

	   const float a10 = this->_m4 * (this->_m9 * this->_m14 - this->_m10 * this->_m13);
	   const float a11 = this->_m5 * (this->_m8 * this->_m14 - this->_m10 * this->_m12);
	   const float a12 = this->_m6 * (this->_m8 * this->_m13 - this->_m9 * this->_m12);

	   const float a03 = this->_m3 * (a10 - a11 + a12);

	   return a00 - a01 + a02 - a03;
   }

   void Matrix::T()
   {
	   Matrix* org = new Matrix(*this);
	   this->m0() = org->m0();
	   this->m1() = org->m4();
	   this->m2() = org->m8();
	   this->m3() = org->m12();
	   this->m4() = org->m1();
	   this->m5() = org->m5();
	   this->m6() = org->m9();
	   this->m7() = org->m13();
	   this->m8() = org->m2();
	   this->m9() = org->m6();
	   this->m10() = org->m10();
	   this->m11() = org->m14();
	   this->m12() = org->m3();
	   this->m13() = org->m7();
	   this->m14() = org->m11();
	   this->m15() = org->m15();

	   //this = transposed;
	   delete org;
   }

   const Matrix Matrix::getT()
   {
	   Matrix org = *this;

	   org.m1() = this->m4();
	   org.m2() = this->m8();
	   org.m3() = this->m12();
	   org.m4() = this->m1();
	   org.m6() = this->m9();
	   org.m7() = this->m13();
	   org.m8() = this->m2();
	   org.m9() = this->m6();
	   org.m11() = this->m14();
	   org.m12() = this->m3();
	   org.m13() = this->m7();
	   org.m14() = this->m11();

	   //Matrix tmp = *org;
	   //delete org;
	   return org;
   }

   void Matrix::inv() {
	   Matrix M;
	   *this = M.getInv();
   }

   const Matrix Matrix::getInv() {

	   float b00 = (this->_m6 * this->_m11 * this->_m13) - (this->_m7 * this->_m10 * this->_m13) + (this->_m7 * this->_m9 * this->_m14) - (this->_m5 * this->_m11 * this->_m14) -
		   (this->_m6 * this->_m9 * this->_m15) + (this->_m5 * this->_m10 * this->_m15);

	   float b01 = (this->_m3 * this->_m10 * this->_m13) - (this->_m2 * this->_m11 * this->_m13) - (this->_m3 * this->_m9 * this->_m14) + (this->_m1 * this->_m11 * this->_m14) +
		   (this->_m2 * this->_m9 * this->_m15) - (this->_m1 * this->_m10 * this->_m15);

	   float b02 = (this->_m2 * this->_m7 * this->_m13) - (this->_m3 * this->_m6 * this->_m13) + (this->_m3 * this->_m5 * this->_m14) - (this->_m1 * this->_m7 * this->_m14) -
		   (this->_m2 * this->_m5 * this->_m15) + (this->_m1 * this->_m6 * this->_m15);

	   float b03 = (this->_m3 * this->_m6 * this->_m9) - (this->_m2 * this->_m7 * this->_m9) - (this->_m3 * this->_m5 * this->_m10) + (this->_m1 * this->_m7 * this->_m10) +
		   (this->_m2 * this->_m5 * this->_m11) - (this->_m1 * this->_m6 * this->_m11);

	   float b10 = (this->_m7 * this->_m10 * this->_m12) - (this->_m6 * this->_m11 * this->_m12) - (this->_m7 * this->_m8 * this->_m14) + (this->_m4 * this->_m11 * this->_m14) +
		   (this->_m6 * this->_m8 * this->_m15) - (this->_m4 * this->_m10 * this->_m15);

	   float b11 = (this->_m2 * this->_m11 * this->_m12) - (this->_m3 * this->_m10 * this->_m12) + (this->_m3 * this->_m8 * this->_m14) - (this->_m0 * this->_m11 * this->_m14) -
		   (this->_m2 * this->_m8 * this->_m15) + (this->_m0 * this->_m10 * this->_m15);

	   float b12 = (this->_m3 * this->_m6 * this->_m12) - (this->_m2 * this->_m7 * this->_m12) - (this->_m3 * this->_m4 * this->_m14) + (this->_m0 * this->_m7 * this->_m14) +
		   (this->_m2 * this->_m4 * this->_m15) - (this->_m0 * this->_m6 * this->_m15);

	   float b13 = (this->_m2 * this->_m7 * this->_m8) - (this->_m3 * this->_m6 * this->_m8) + (this->_m3 * this->_m4 * this->_m10) - (this->_m0 * this->_m7 * this->_m10) -
		   (this->_m2 * this->_m4 * this->_m11) + (this->_m0 * this->_m6 * this->_m11);

	   float b20 = (this->_m11 * this->_m11 * this->_m12) - (this->_m7 * this->_m9 * this->_m12) + (this->_m7 * this->_m8 * this->_m13) - (this->_m4 * this->_m11 * this->_m13) -
		   (this->_m5 * this->_m8 * this->_m15) + (this->_m4 * this->_m9 * this->_m15);

	   float b21 = (this->_m3 * this->_m9 * this->_m12) - (this->_m1 * this->_m11 * this->_m12) - (this->_m3 * this->_m8 * this->_m13) + (this->_m0 * this->_m11 * this->_m13) +
		   (this->_m1 * this->_m8 * this->_m15) - (this->_m0 * this->_m9 * this->_m15);

	   float b22 = (this->_m1 * this->_m7 * this->_m12) - (this->_m3 * this->_m5 * this->_m12) + (this->_m3 * this->_m4 * this->_m13) - (this->_m0 * this->_m7 * this->_m13) -
		   (this->_m1 * this->_m4 * this->_m15) + (this->_m0 * this->_m5 * this->_m15);

	   float b23 = (this->_m3 * this->_m5 * this->_m8) - (this->_m1 * this->_m7 * this->_m8) - (this->_m3 * this->_m4 * this->_m9) + (this->_m0 * this->_m7 * this->_m9) +
		   (this->_m1 * this->_m4 * this->_m11) - (this->_m0 * this->_m5 * this->_m11);

	   float b30 = (this->_m6 * this->_m9 * this->_m12) - (this->_m5 * this->_m10 * this->_m12) - (this->_m6 * this->_m8 * this->_m13) + (this->_m4 * this->_m10 * this->_m13) +
		   (this->_m5 * this->_m8 * this->_m14) - (this->_m4 * this->_m9 * this->_m14);

	   float b31 = (this->_m1 * this->_m10 * this->_m12) - (this->_m2 * this->_m9 * this->_m12) + (this->_m2 * this->_m8 * this->_m13) - (this->_m0 * this->_m10 * this->_m13) -
		   (this->_m1 * this->_m8 * this->_m14) + (this->_m0 * this->_m9 * this->_m14);

	   float b32 = (this->_m2 * this->_m5 * this->_m12) - (this->_m1 * this->_m6 * this->_m12) - (this->_m2 * this->_m4 * this->_m13) + (this->_m0 * this->_m6 * this->_m13) +
		   (this->_m1 * this->_m4 * this->_m14) - (this->_m0 * this->_m5 * this->_m14);

	   float b33 = (this->_m1 * this->_m6 * this->_m8) - (this->_m2 * this->_m5 * this->_m8) + (this->_m2 * this->_m4 * this->_m9) - (this->_m0 * this->_m6 * this->_m9) -
		   (this->_m1 * this->_m4 * this->_m10) + (this->_m0 * this->_m5 * this->_m10);

	   const float det = this->det();

	   Matrix M;

	   M.set(Row::i0, Vect(b00, b01, b02, b03));
	   M.set(Row::i1, Vect(b10, b11, b12, b13));
	   M.set(Row::i2, Vect(b20, b21, b22, b23));
	   M.set(Row::i3, Vect(b30, b31, b32, b33));

	   return (1 / det) * M;


   }

}

// ---  End of File --------------
