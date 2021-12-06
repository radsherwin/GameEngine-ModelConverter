//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{

	Vect::Vect()
		: _vx(0), _vy(0), _vz(0), _vw(MATH_ONE)
	{}

	Vect::Vect(const Vect& v)
		: _vx(v._vx), _vy(v._vy), _vz(v._vz), _vw(v._vw)
	{}

	Vect& Vect::operator=(const Vect& v)
	{
		this->_vx = v._vx;
		this->_vy = v._vy;
		this->_vz = v._vz;
		this->_vw = v._vw;

		return *this;
	}

	Vect::Vect(const float vx, const float vy, const float vz)
		:_vx(vx), _vy(vy), _vz(vz), _vw(MATH_ONE)
	{
		
	}

	Vect::Vect(const float vx, const float vy, const float vz, const float vw)
		: _vx(vx), _vy(vy), _vz(vz), _vw(vw)
	{

	}

	//get bracket const
	const float& Vect::operator[](x_enum) const
	{
		return this->_vx;
	}

	const float& Vect::operator[](y_enum) const
	{
		return this->_vy;
	}

	const float& Vect::operator[](z_enum) const
	{
		return this->_vz;
	}

	const float& Vect::operator[](w_enum) const
	{
		return this->_vw;
	}

	//Set bracket
	float& Vect::operator[](x_enum)
	{
		float* p = &this->_vx;
		return *p;
	}

	float& Vect::operator[](y_enum)
	{
		float* p = &this->_vy;
		return *p;
	}

	float& Vect::operator[](z_enum)
	{
		float* p = &this->_vz;
		return *p;
	}

	float& Vect::operator[](w_enum)
	{
		float* p = &this->_vw;
		return *p;
	}
	
	//get dot operator
	const float& Vect::x() const
	{
		return this->_vx;
	}

	const float& Vect::y() const
	{
		return this->_vy;
	}

	const float& Vect::z() const
	{
		return this->_vz;
	}

	const float& Vect::w() const
	{
		return this->_vw;
	}

	//set dot accessor
	float& Vect::x()
	{
		float* p = &this->_vx;
		return *p;
	}

	float& Vect::y()
	{
		float* p = &this->_vy;
		return *p;
	}

	float& Vect::z()
	{
		float* p = &this->_vz;
		return *p;
	}

	float& Vect::w()
	{
		float* p = &this->_vw;
		return *p;
	}

	Vect Vect::operator+(const Quat& q) const
	{
		return Vect(_vx + q.qx(), _vy + q.qy(), _vz + q.qz(), _vw + q.real());
	}

	//Math operators
	
	Vect Vect::operator+(const Vect& v) // Vect + Vect
	{
		return Vect(this->_vx + v._vx, this->_vy + v._vy, this->_vz + v._vz, MATH_ONE);
	}

	Vect Vect::operator+=(const Vect& v) //Vect += Vect
	{
		this->_vx += v._vx;
		this->_vy += v._vy;
		this->_vz += v._vz;
		this->_vw = MATH_ONE;

		return *this;
	}

	Vect Vect::operator-(const Vect& v) //Vect - Vect
	{
		return Vect(this->_vx - v._vx, this->_vy - v._vy, this->_vz - v._vz, MATH_ONE);
	}

	Vect Vect::operator-=(const Vect& v) //Vect -= Vect
	{
		this->_vx -= v._vx;
		this->_vy -= v._vy;
		this->_vz -= v._vz;
		this->_vw = MATH_ONE;

		return *this;
	}

	Vect operator-(const Vect& a, const Vect& v)
	{
		return Vect(a.x() - v.x(), a.y() - v.y(), a.z() - v.z(), MATH_ONE);
	}

	Vect operator+(const Vect& a, const Vect& v)
	{
		return Vect(a.x() + v.x(), a.y() + v.y(), a.z() + v.z(), MATH_ONE);
	}

	//Scaler operators
	Vect Azul::operator*(const float s, const Vect& v)
	{
		Vect copy = v;
		copy.x() *= s;
		copy.y() *= s;
		copy.z() *= s;
		copy.w() = 1;
		return copy;
	}

	const Vect Vect::operator*(const float& s) const
	{
		Vect copy = *this;
		copy.x() *= s;
		copy.y() *= s;
		copy.z() *= s;
		copy.w() = 1;
		return copy;
	}

	Vect Vect::operator*=(const float& s)
	{
		this->x() *= s;
		this->y() *= s;
		this->z() *= s;
		this->w() = 1;
		return *this;
	}

	//Multiply with Matrix
	const Vect Vect::operator*(const Matrix& m) const
	{
		Vect result = *this;

		result._vx = this->_vx * m.m0() + this->_vy * m.m4() + this->_vz * m.m8() + this->_vw * m.m12();
		result._vy = this->_vx * m.m1() + this->_vy * m.m5() + this->_vz * m.m9() + this->_vw * m.m13();
		result._vz = this->_vx * m.m2() + this->_vy * m.m6() + this->_vz * m.m10() + this->_vw * m.m14();
		result._vw = this->_vx * m.m3() + this->_vy * m.m7() + this->_vz * m.m11() + this->_vw * m.m15();

		return result;
	}

	Vect Vect::operator*=(const Matrix& m)
	{
		Vect result = *this;

		result._vx = this->_vx * m.m0() + this->_vy * m.m4() + this->_vz * m.m8() + this->_vw * m.m12();
		result._vy = this->_vx * m.m1() + this->_vy * m.m5() + this->_vz * m.m9() + this->_vw * m.m13();
		result._vz = this->_vx * m.m2() + this->_vy * m.m6() + this->_vz * m.m10() + this->_vw * m.m14();
		result._vw = this->_vx * m.m3() + this->_vy * m.m7() + this->_vz * m.m11() + this->_vw * m.m15();

		this->_vx = result._vx;
		this->_vy = result._vy;
		this->_vz = result._vz;
		this->_vw = result._vw;

		return *this;
	}

	Vect Vect::operator*(const Quat& q) const
	{
		Matrix M(q);

		return *this * M;
		//Vect tmp((2 * q.real() * this->cross(q)) + (((q.real() * q.real()) - (q.qx() * q.qx() + q.qy() * q.qx() + q.qz() * q.qx())) * *this) + (2 * (q.qx() * _vx + q.qy() * _vy + q.qz() * _vz)) * q);
		//Vect tmp((2 * q.real() * q.cross(*this)) + (((q.real() * q.real()) - (q.qx() * q.qx() + q.qy() * q.qx() + q.qz() * q.qx())) * *this) + (2 * (q.qx() * _vx + q.qy() * _vy + q.qz() * _vz)) * q);
		//tmp.w() = 1;

		//return tmp;
	}

	Vect Vect::operator*=(const Quat& q)
	{
		*this = ((2 * q.real() * q.cross(*this)) + (((q.real() * q.real()) - (q.qx() * q.qx() + q.qy() * q.qx() + q.qz() * q.qx())) * *this) + (2 * (q.qx() * _vx + q.qy() * _vy + q.qz() * _vz)) * q);
		this->w() = 1;

		return *this;
	}

	//Unary operator
	Vect Vect::operator+() {
		this->x() = +this->_vx;
		this->y() = +this->_vy;
		this->z() = +this->_vz;
		this->w() = +this->_vw;

		Vect copy = *this;
		copy.w() = 1;
		return copy;
	}

	Vect Vect::operator-() {
		Vect copy = *this;
		copy.x() = -copy._vx;
		copy.y() = -copy._vy;
		copy.z() = -copy._vz;
		copy.w() = 1;
		return copy;
	}

	//Math

	//Dot product
	const float Vect::dot(const Vect& _v) {
		const float tmpX = this->_vx * _v._vx;
		const float tmpY = this->_vy * _v._vy;
		const float tmpZ = this->_vz * _v._vz;

		const float returnVal = tmpX + tmpY + tmpZ;

		return returnVal;
	}

	//cross product
	Vect Vect::cross(const Vect& _v) const{
		Vect copy = *this; 
		const float tmpX = (copy._vy * _v._vz) - (copy._vz * _v._vy); //3385
		const float tmpY = (copy._vx * _v._vz) - (copy._vz * _v._vx);
		const float tmpZ = (copy._vx * _v._vy) - (copy._vy * _v._vx);

		copy.set(tmpX, -tmpY, tmpZ);
		return copy;
	}

	Vect Vect::cross(const Quat& q) const
	{
		const Vect tmp = *this;
		const float tmpX = (tmp._vy * q.qz()) - (tmp._vz * q.qy());
		const float tmpY = (tmp._vz * q.qx()) - (tmp._vx * q.qz());
		const float tmpZ = (tmp._vx * q.qy()) - (tmp._vy * q.qx());

		return Vect(tmpX, tmpY, tmpZ);
	}

	//norm
	Vect Vect::norm() {
		const float mag = this->mag();

		this->_vx /= mag;
		this->_vy /= mag;
		this->_vz /= mag;


		return *this;
	}

	Vect Vect::getNorm() {
		const float mag = this->mag();
		Vect tmp = *this;

		const float fx = tmp._vx / mag;
		const float fy = tmp._vy / mag;
		const float fz = tmp._vz / mag;

		tmp.set(fx, fy, fz);
		return tmp;
	}

	//magnitude
	const float Vect::mag() {
		return sqrtf(this->x() * this->x() + this->y() * this->y() + this->z() * this->z());
	}

	const float Vect::magSqr() {
		return (this->x() * this->x() + this->y() * this->y() + this->z() * this->z());
	}

	const float Vect::getAngle(Vect& v) {
		const float dotTmp = this->dot(v);
		const float magA = this->mag();
		const float magB = v.mag();

		return Trig::acos(dotTmp / (magA * magB));
	}

	//Boolean
	const bool Azul::Vect::isEqual(const Vect& _v, const float& _tolerance)
	{
		if (fabs(this->_vx - _v._vx) > _tolerance) return false;
		else if (fabs(this->_vy - _v._vy) > _tolerance) return false;
		else if (fabs(this->_vz - _v._vz) > _tolerance) return false;
		else if (fabs(this->_vw - _v._vw) > _tolerance) return false;

		return true;
	}

	const bool Vect::isEqual(const Vect& _v) { //isEqual default
		if (this->_vx == _v._vx) return false;
		else if (this->_vy == _v._vy) return false;
		else if (this->_vz == _v._vz) return false;
		else if (this->_vw == _v._vw) return false;

		return true;

	}

	const bool Vect::isZero(const float& _tolerance) { //isZero with tolerance
		if (fabs(this->_vx - MATH_ZERO) > _tolerance) return false;
		else if (fabs(this->_vy - MATH_ZERO) > _tolerance) return false;
		else if (fabs(this->_vz - MATH_ZERO) > _tolerance) return false;
		else if (fabs(this->_vw - MATH_ONE) > _tolerance) return false;

		return true;
	}

	const bool Vect::isZero() { //isZero default
		if (this->_vx == MATH_ZERO) return false;
		else if (this->_vy == MATH_ZERO) return false;
		else if (this->_vz == MATH_ZERO) return false;
		else if (this->_vw == MATH_ONE) return false;

		return true;
	}

	//Set
	void Vect::set(const float& x, const float& y, const float& z)
	{
		this->x() = x;
		this->y() = y;
		this->z() = z;
		this->w() = MATH_ONE;
	}

	void Vect::set(const float& x, const float& y, const float& z, const float& w) {
		this->x() = x;
		this->y() = y;
		this->z() = z;
		this->w() = w;
	}

	void Vect::set(const Vect& _v) {
		*this = _v;
	}
  
}

//--- End of File ---
