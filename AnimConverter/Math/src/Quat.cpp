//-----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{ 

	Quat::Quat()
		: _qx(0), _qy(0), _qz(0), _qw(1)
	{}

	Quat::Quat(const Quat& q)
		: _qx(q._qx), _qy(q._qy), _qz(q._qz), _qw(q._qw)
	{}

	Quat& Quat::operator=(const Quat& q)
	{
		this->_qx = q._qx;
		this->_qy = q._qy;
		this->_qz = q._qz;
		this->_qw = q._qw;

		return *this;
	}

	Quat::Quat(const float qx, const float qy, const float qz, const float qw)
		: _qx(qx), _qy(qy), _qz(qz), _qw(qw)
	{
	}

	Quat::Quat(const float qx, const float qy, const float qz)
		: _qx(qx), _qy(qy), _qz(qz), _qw(MATH_ONE)
	{
	}

	Quat::Quat(const Matrix& M)
	{
		float tr = M.m0() + M.m5() + M.m10();
		float S;

		if (tr > 0.0f)
		{
			S = 2 * sqrtf(tr + 1.0f);
			this->_qw = 0.25f * S;
			this->_qx = -(M.m9() - M.m6()) / S;
			this->_qy = -(M.m2() - M.m8()) / S;
			this->_qz = -(M.m4() - M.m1()) / S;

		}
		else if ((M.m0() > M.m5()) && (M.m0() > M.m10()))
		{
			S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
			this->_qw = -(M.m9() - M.m6()) / S;
			this->_qx = 0.25f * S;
			this->_qy = (M.m1() + M.m4()) / S;
			this->_qz = (M.m2() + M.m8()) / S;

		}
		else if (M.m5() > M.m10())
		{
			S = 2 * sqrtf(1.0f + M.m5() - M.m0() - M.m10());
			this->_qw = -(M.m2() - M.m8()) / S;
			this->_qx = (M.m1() + M.m4()) / S;
			this->_qy = 0.25f * S;
			this->_qz = (M.m6() + M.m9()) / S;
		}
		else
		{
			S = 2 * sqrtf(1.0f + M.m10() - M.m0() - M.m5());
			this->_qw = -(M.m4() - M.m1()) / S;
			this->_qx = (M.m2() + M.m8()) / S;
			this->_qy = (M.m6() + M.m9()) / S;
			this->_qz = 0.25f * S;
		}
	}

	Quat::Quat(const Vect& v, const float qw)
		: _qx(v.x()), _qy(v.y()), _qz(v.z()), _qw(qw)
	{}

	Quat::Quat(Quat::Special s)
	{
		switch (s)
		{
		case Quat::Special::Zero:
			this->_qx = 0;
			this->_qy = 0;
			this->_qz = 0;
			this->_qw = 0;
			break;
		case Quat::Special::Identity:
			this->_qx = 0;
			this->_qy = 0;
			this->_qz = 0;
			this->_qw = 1;
			break;
		}
	}

	Quat::Quat(Quat::Rot3 r, const float x, const float y, const float z)
	{
		Matrix M;
		switch (r)
		{
		case Rot3::XYZ:
			Matrix Rx;
			Matrix Ry;
			Matrix Rz;
			Rx.set(Matrix::Rot1::X, x);
			Ry.set(Matrix::Rot1::Y, y);
			Rz.set(Matrix::Rot1::Z, z);

			M = Rx * Ry * Rz;
			this->set(M);
			break;
		}
	}

	Quat::Quat(Quat::Rot1 r, const float f)
	{
		Matrix M;
		switch (r)
		{
		case Quat::Rot1::X:
			M.set(Matrix::Rot1::X, f);
			this->set(M);
			break;
		case Quat::Rot1::Y:
			M.set(Matrix::Rot1::Y, f);
			this->set(M);
			break;
		case Quat::Rot1::Z:
			M.set(Matrix::Rot1::Z, f);
			this->set(M);
			break;
		}
	}

	Quat::Quat(Quat::Rot r, const Vect& v, const float real)
	{
		AZUL_UNUSED_VAR(r);
		//Normalize Vector
		Quat q;

		q.set(v, 0);
		q.norm();

		const float angle = real;

		float f = Trig::sin(angle / 2);
		this->_qx = q._qx * f;
		this->_qy = q._qy * f;
		this->_qz = q._qz * f;
		this->_qw = Trig::cos(angle / 2);
	}

	Quat::Quat(const Quat::Orient o, const Vect& dof, const Vect& up)
	{
		Vect v1 = up.cross(dof);
		Vect v2 = dof.cross(v1);

		v1.norm();
		v2.norm();
		Vect v3 = dof;
		v3.norm();

		v1.w() = 0;
		v2.w() = 0;
		v3.w() = 0;


		Matrix M(v1, v2, v3, Vect(0, 0, 0, 1));

		switch (o) {
		case Orient::LocalToWorld:
			*this = Quat(M);
			break;

		case Orient::WorldToLocal:
			M.T();
			*this = Quat(M);
			break;
		}
	}

	Quat Quat::operator+(const Quat& q) const
	{
		Quat tmp = *this;
		tmp._qx = tmp._qx + q._qx;
		tmp._qy = tmp._qy + q._qy;
		tmp._qz = tmp._qz + q._qz;
		tmp._qw = tmp._qw + q._qw;

		return tmp;
	}

	Quat Quat::operator+=(const Quat& q)
	{
		this->_qx += q._qx;
		this->_qy += q._qy;
		this->_qz += q._qz;
		this->_qw += q._qw;

		return *this;
	}

	Quat Quat::operator-(const Quat& q) const
	{
		Quat tmp = *this;
		tmp._qx -= q._qx;
		tmp._qy -= q._qy;
		tmp._qz -= q._qz;
		tmp._qw -= q._qw;

		return tmp;
	}

	Quat Quat::operator-=(const Quat& q)
	{
		this->_qx -= q._qx;
		this->_qy -= q._qy;
		this->_qz -= q._qz;
		this->_qw -= q._qw;

		return *this;
	}

	Quat Quat::operator+(const float f) const
	{
		Quat tmp = *this;
		tmp._qx += f;
		tmp._qy += f;
		tmp._qz += f;
		tmp._qw += f;

		return tmp;
	}

	Quat Quat::operator+=(const float f)
	{
		this->_qx += f;
		this->_qy += f;
		this->_qz += f;
		this->_qw += f;

		return *this;
	}

	Quat Quat::operator-(const float f) const
	{
		Quat tmp = *this;
		tmp._qx -= f;
		tmp._qy -= f;
		tmp._qz -= f;
		tmp._qw -= f;

		return tmp;
	}

	Quat Quat::operator-=(const float f)
	{
		this->_qx -= f;
		this->_qy -= f;
		this->_qz -= f;
		this->_qw -= f;

		return *this;
	}

	Quat Quat::operator*(const Quat& q) const
	{
		float vecDot = _qx * q._qx + _qy * q._qy + _qz * q._qz;
		float qw = ((this->_qw * q._qw) - vecDot);
		Quat tmp = (q.cross(*this) + (q._qw * *this) + (this->_qw * q));
		
		return  Quat(tmp._qx, tmp._qy, tmp._qz, qw);
	}

	Quat Quat::operator*=(const Quat& q)
	{
		float vecDot = _qx * q._qx + _qy * q._qy + _qz * q._qz;
		float qw = ((this->_qw * q._qw) - vecDot);
		Quat tmp = (q.cross(*this) + (q._qw * *this) + (this->_qw * q));
		set(tmp._qx, tmp._qy, tmp._qz, qw);
		return  *this;
	}

	/*Quat Quat::operator*(const Matrix& M) const
	{
		Quat tmp(M);
		return *this * tmp;
	}*/

	Quat Quat::operator*=(const Matrix& M)
	{
		Quat tmp(M);
		*this *= tmp;
		return *this;
	}

	Quat Quat::operator/(const Quat& q) const
	{
		Quat tmp = *this;
		tmp._qx /= q._qx;
		tmp._qy /= q._qy;
		tmp._qz /= q._qz;
		tmp._qw /= q._qw;

		return tmp;
	}

	Quat Quat::operator/=(const Quat& q)
	{
		this->_qx /= q._qx;
		this->_qy /= q._qy;
		this->_qz /= q._qz;
		this->_qw /= q._qw;

		return *this;
	}

	Quat Quat::operator*(const float& scale) const
	{
		Quat result = *this;
		result._qx *= scale;
		result._qy *= scale;
		result._qz *= scale;
		result._qw *= scale;

		return result;
	}

	Quat Quat::operator*=(const float& scale)
	{
		this->_qx *= scale;
		this->_qy *= scale;
		this->_qz *= scale;
		this->_qw *= scale;

		return *this;		
	}

	Quat Quat::operator/(const float& scale) const
	{
		Quat result = *this;
		result._qx /= scale;
		result._qy /= scale;
		result._qz /= scale;
		result._qw /= scale;

		return result;
	}

	Quat Quat::operator/=(const float& scale)
	{
		this->_qx /= scale;
		this->_qy /= scale;
		this->_qz /= scale;
		this->_qw /= scale;

		return *this;
	}

	Quat Quat::operator+()
	{
		this->_qx = +this->_qx;
		this->_qy = +this->_qy;
		this->_qz = +this->_qz;
		this->_qw = +this->_qw;

		return *this;
	}

	Quat Quat::operator-()
	{
		this->_qx = -this->_qx;
		this->_qy = -this->_qy;
		this->_qz = -this->_qz;
		this->_qw = -this->_qw;

		return *this;
	}

	Quat Quat::operator-() const
	{
		Quat tmp = *this;

		tmp._qx = -this->_qx;
		tmp._qy = -this->_qy;
		tmp._qz = -this->_qz;
		tmp._qw = -this->_qw;

		return tmp;
	}

	Matrix operator*(const Quat& q, const Matrix& M)
	{
		/*Quat newQ = q;
		newQ *= M;

		return Matrix(newQ);*/

		Matrix newQ(q);
		return newQ * M;
	}

	Quat Azul::operator*(const float s, const Quat& q) {
		return q * s;
	}

	Quat operator+(const float s, const Quat& q)
	{
		return q + s;
	}

	Quat operator-(const float s, const Quat& q)
	{
		Quat tmp;

		tmp._qx = s - q._qx;
		tmp._qy = s - q._qy;
		tmp._qz = s - q._qz;
		tmp._qw = s - q._qw;

		return tmp;
	}

	Quat operator/(const float& s, const Quat& q)
	{
		Quat tmp;

		tmp._qx = s / q._qx;
		tmp._qy = s / q._qy;
		tmp._qz = s / q._qz;
		tmp._qw = s / q._qw;

		return tmp;
	}

	Matrix operator*(const Matrix& M, const Quat& q)
	{
		/*Quat tmp(M);
		float vecDot = tmp._qx * q._qx + tmp._qy * q._qy + tmp._qz * q._qz;
		float qw = ((tmp._qw * q._qw) - vecDot);
		tmp = (q.cross(tmp) + (q._qw * tmp) + (tmp._qw * q));*/

		Matrix newQ(q);

		return M * newQ;
	}

	void Quat::set(const float qx, const float qy, const float qz, const float qw)
	{
		this->_qx = qx;
		this->_qy = qy;
		this->_qz = qz;
		this->_qw = qw;
	}

	void Quat::set(const float qx, const float qy, const float qz)
	{
		this->_qx = qx;
		this->_qy = qy;
		this->_qz = qz;
		this->_qw = MATH_ONE;
	}

	void Quat::set(const Vect& v, float qw)
	{
		this->_qx = v.x();
		this->_qy = v.y();
		this->_qz = v.z();
		this->_qw = qw;
	}

	void Quat::set(const Matrix& M)
	{
		float tr = M.m0() + M.m5() + M.m10();
		float S;

		if(tr > 0.0f)
		{
			S = 2 * sqrtf(tr + 1.0f);
			this->_qw = 0.25f * S;
			this->_qx = -(M.m9() - M.m6()) / S;
			this->_qy = -(M.m2() - M.m8()) / S;
			this->_qz = -(M.m4() - M.m1()) / S;
			
		}
		else if((M.m0() > M.m5()) && (M.m0() > M.m10()))
		{
			S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
			this->_qw = -(M.m9() - M.m6()) / S;
			this->_qx = 0.25f * S;
			this->_qy = (M.m1() + M.m4()) / S;
			this->_qz = (M.m2() + M.m8()) / S;
			
		}
		else if(M.m5() > M.m10())
		{
			S = 2*sqrtf(1.0f + M.m5() - M.m0() - M.m10());
			this->_qw = -(M.m2() - M.m8()) / S;
			this->_qx = (M.m1() + M.m4()) / S;
			this->_qy = 0.25f * S;
			this->_qz = (M.m6() + M.m9()) / S;
		}
		else
		{
			S = 2*sqrtf(1.0f + M.m10() - M.m0() - M.m5());
			this->_qw = -(M.m4() - M.m1()) / S;
			this->_qx = (M.m2() + M.m8()) / S;
			this->_qy = (M.m6() + M.m9()) / S;
			this->_qz = 0.25f * S;
		}
	}

	//Axis Angle
	void Quat::set(Quat::Rot, const Vect& v, const float qw)
	{
		//Normalize Vector
		Quat q;

		q.set(v, 0);
		q.norm();

		const float angle = qw;

		float f = Trig::sin(angle / 2);
		this->_qx = q._qx * f;
		this->_qy = q._qy * f;
		this->_qz = q._qz * f;
		this->_qw = Trig::cos(angle / 2);

		//*this = (q * sinf(angle/2)) + (cosf(angle/2));

	}

	void Quat::set(Quat::Rot3 r, const float x, const float y, const float z)
	{
		Matrix M;
		switch (r)
		{
		case Rot3::XYZ:
			Matrix Rx;
			Matrix Ry;
			Matrix Rz;
			Rx.set(Matrix::Rot1::X, x);
			Ry.set(Matrix::Rot1::Y, y);
			Rz.set(Matrix::Rot1::Z, z);

			M = Rx * Ry * Rz;
			this->set(M);
			break;
		}
	}

	void Quat::set(const Quat::Orient o, const Vect& dof, const Vect& up)
	{
		Vect v1 = up.cross(dof);
		Vect v2 = dof.cross(v1);

		v1.norm();
		v2.norm();
		Vect v3 = dof;
		v3.norm();

		v1.w() = 0;
		v2.w() = 0;
		v3.w() = 0;


		Matrix M(v1, v2, v3, Vect(0, 0, 0, 1));

		switch (o) {
		case Orient::LocalToWorld:
			*this = Quat(M);
			break;

		case Orient::WorldToLocal:
			M.T();
			*this = Quat(M);
			break;
		}
	}

	void Quat::set(Quat::Special s)
	{
		switch(s)
		{
		case Quat::Special::Zero:
			this->_qx = 0;
			this->_qy = 0;
			this->_qz = 0;
			this->_qw = 0;
			break;
		case Quat::Special::Identity:
			this->_qx = 0;
			this->_qy = 0;
			this->_qz = 0;
			this->_qw = 1;
			break;
		}
	}

	void Quat::set(Quat::Rot1 r, const float f)
	{
		Matrix M;
		switch(r)
		{
		case Quat::Rot1::X:
			M.set(Matrix::Rot1::X, f);
			this->set(M);
			break;
		case Quat::Rot1::Y:
			M.set(Matrix::Rot1::Y, f);
			this->set(M);
			break;
		case Quat::Rot1::Z:
			M.set(Matrix::Rot1::Z, f);
			this->set(M);
			break;
		}
	}

	void Quat::setVect(const Vect& v)
	{
		this->_qx = v.x();
		this->_qy = v.y();
		this->_qz = v.z();
		this->_qw = 0;
	}

	float Quat::getAngle()
	{
		return 2 * Trig::acos(this->_qw);
	}

	void Quat::getVect(Vect& vOut)
	{
		vOut = Vect(_qx, _qy, _qz);
	}

	void Quat::getAxis(Vect& vOut)
	{
		const float theta = getAngle();
		vOut.x() = this->_qx / Trig::sin(theta/2);
		vOut.y() = this->_qy / Trig::sin(theta / 2);
		vOut.z() = this->_qz / Trig::sin(theta / 2);
		vOut.w() = 1;
		
	}

	const float& Quat::operator[](x_enum) const
	{
		return this->_qx;
	}

	const float& Quat::operator[](y_enum) const
	{
		return this->_qy;
	}

	const float& Quat::operator[](z_enum) const
	{
		return this->_qz;
	}

	const float& Quat::operator[](w_enum) const
	{
		return this->_qw;
	}

	float& Quat::operator[](x_enum)
	{
		float* p = &this->_qx;
		return *p;
	}

	float& Quat::operator[](y_enum)
	{
		float* p = &this->_qy;
		return *p;
	}

	float& Quat::operator[](z_enum)
	{
		float* p = &this->_qz;
		return *p;
	}

	float& Quat::operator[](w_enum)
	{
		float* p = &this->_qw;
		return *p;
	}

	//Get ()
	const float& Quat::qx() const
	{
		return this->_qx;
	}
	const float& Quat::qy() const
	{
		return this->_qy;
	}

	const float& Quat::qz() const
	{
		return this->_qz;
	}

	const float& Quat::real() const
	{
		return this->_qw;
	}

	//Set ()
	float& Quat::qx()
	{
		float* p = &this->_qx;
		return *p;
	}

	float& Quat::qy()
	{
		float* p = &this->_qy;
		return *p;
	}

	float& Quat::qz()
	{
		float* p = &this->_qz;
		return *p;
	}

	float& Quat::real()
	{
		float* p = &this->_qw;
		return *p;
	}

	float Quat::dot(const Quat& q) const
	{
		return _qx * q._qx + _qy*q._qy + _qz*q._qz + _qw*q._qw;
	}

	float Quat::dot(const Vect& v) const
	{
		return _qx * v.x() + _qy * v.y() + _qz*v.z();// + _qw*v.w();
	}

	Quat Quat::cross(const Quat& q) const
	{
		const Quat tmp = *this;
		const float tmpX = (tmp._qy * q._qz) - (tmp._qz * q._qy); 
		const float tmpY = (tmp._qz * q._qx) - (tmp._qx * q._qz);
		const float tmpZ = (tmp._qx * q._qy) - (tmp._qy * q._qx);

		return Quat(tmpX, tmpY, tmpZ);
	}

	Vect Quat::cross(const Vect& v) const
	{
		const Quat tmp = *this;
		const float tmpX = (tmp._qy * v.z()) - (tmp._qz * v.y());
		const float tmpY = (tmp._qz * v.x()) - (tmp._qx * v.z());
		const float tmpZ = (tmp._qx * v.y()) - (tmp._qy * v.x());

		return Vect(tmpX, tmpY, tmpZ);
	}

	Quat Quat::multByElement(const Quat& q)
	{
		return Quat(_qx * q._qx, _qy * q._qy, _qz * q._qz, _qw * q._qw);
	}

	Quat Quat::norm()
	{
		//For class assume always unit vector
		//Magnitude
		const float mag = sqrtf(_qx * _qx + _qy*_qy + _qz*_qz + _qw*_qw);

		this->_qx /= mag;
		this->_qy /= mag;
		this->_qz /= mag;
		this->_qw /= mag;

		return *this;
		
	}

	void Quat::conj()
	{
		this->_qx *= -1;
		this->_qy *= -1;
		this->_qz *= -1;
	}

	void Quat::T()
	{
		this->_qx *= -1;
		this->_qy *= -1;
		this->_qz *= -1;
	}

	void Quat::inv()
	{
		const float ms = magSquared();
		_qx /= -ms;
		_qy /= -ms;
		_qz /= -ms;
		_qw /= ms;
	}

	void Quat::Lqcvq(const Vect& v, Vect& vOut)
	{
		Quat q = *this;

		/*Vect p1 = (2 * q._qw) * (q.cross(v));
		Vect p2 = ((q._qw * q._qw) - (q.dot(q))) * v;
		Quat p3 = (2 * (q.dot(v))) * q;

		vOut = p1 + p2 + p3;*/
		vOut = v * q;
		//vOut = ((2 * q.real() * q.cross(v)) + (((q.real() * q.real()) - (q.qx() * q.qx() + q.qy() * q.qx() + q.qz() * q.qx())) * v) + (2 * (q.qx() * v.x() + q.qy() * v.y() + q.qz() * v.z())) * q);
	}

	void Quat::Lqvqc(const Vect& v, Vect& vOut)
	{
		Quat q = *this;
		q.T();
		vOut = v * q;
		//vOut = ((2 * q.real() * v.cross(q)) + (((q.real() * q.real()) - (q.qx() * q.qx() + q.qy() * q.qx() + q.qz() * q.qx())) * v)+ (2 * (q.qx() * v.x() + q.qy() * v.y() + q.qz() * v.z())) * q);
	}

	Quat Quat::getNorm() const
	{
		const float mag = sqrtf(_qx * _qx + _qy * _qy + _qz * _qz + _qw * _qw);
		Quat tmp = *this;
		tmp._qx /= mag;
		tmp._qy /= mag;
		tmp._qz /= mag;
		tmp._qw /= mag;

		return tmp;
	}

	Quat Quat::getConj() const
	{
		return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
	}

	Quat Quat::getT() const
	{
		return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
	}

	Quat Quat::getInv() const
	{
		const float ms =  magSquared();
		return Quat(_qx/-ms, _qy/-ms, _qz/-ms, _qw/ms);
	}

	float Quat::mag() const
	{
		return Trig::sqrt(_qx *_qx + _qy*_qy + _qz*_qz + _qw*_qw);
	}

	float Quat::magSquared() const
	{
		return (_qx * _qx + _qy * _qy + _qz * _qz + _qw * _qw);
	}

	float Quat::invMag() const
	{
		Quat tmp = this->getInv();
		return Trig::sqrt(	tmp._qx * tmp._qx + tmp._qy * tmp._qy 
							+ tmp._qz * tmp._qz + tmp._qw * tmp._qw);
	}

	bool Quat::isEqual(const Quat& q, const float tolerance) const
	{
		if(fabsf(this->_qx - q._qx) > tolerance) return false;
		if (fabsf(this->_qy - q._qy) > tolerance) return false;
		if (fabsf(this->_qz - q._qz) > tolerance) return false;
		if (fabsf(this->_qw - q._qw) > tolerance) return false;

		return true;
	}

	bool Quat::isNegEqual(const Quat& q, const float tolerance) const
	{
		if (fabsf(fabsf(this->_qx) - fabsf(q._qx)) > tolerance) return false;
		if (fabsf(fabsf(this->_qy) - fabsf(q._qy)) > tolerance) return false;
		if (fabsf(fabsf(this->_qz) - fabsf(q._qz)) > tolerance) return false;
		if (fabsf(fabsf(this->_qw) - fabsf(q._qw)) > tolerance) return false;

		return true;
	}

	bool Quat::isEquivalent(const Quat& q, const float tolerance) const
	{
		
		
		if (fabsf(this->_qx - q._qx) <= tolerance) //if true then both are positive. 
		{
			if (fabsf(this->_qy - q._qy) > tolerance) return false;
			if (fabsf(this->_qz - q._qz) > tolerance) return false;
			if (fabsf(this->_qw - q._qw) > tolerance) return false;
		}
		else //means either negative or flat out not equivalent
		{
			if (fabsf(fabsf(this->_qx) - fabsf(q._qx)) > tolerance) return false;
			if (fabsf(fabsf(this->_qy) - fabsf(q._qy)) > tolerance) return false;
			if (fabsf(fabsf(this->_qz) - fabsf(q._qz)) > tolerance) return false;
			if (fabsf(fabsf(this->_qw) - fabsf(q._qw)) > tolerance) return false;
		}
		

		return true;
	}

	bool Quat::isConjugateEqual(const Quat& q, const float tolerance) const
	{
		Quat qConj = getConj();

		if (fabsf(qConj._qx - q._qx) > tolerance) return false;
		if (fabsf(qConj._qy - q._qy) > tolerance) return false;
		if (fabsf(qConj._qz - q._qz) > tolerance) return false;
		if (fabsf(qConj._qw - q._qw) > tolerance) return false;

		return true;
	}

	bool Quat::isIdentity(const float tolerance) const
	{
		if (fabsf(this->_qx - 0) > tolerance) return false;
		if (fabsf(this->_qy - 0) > tolerance) return false;
		if (fabsf(this->_qz - 0) > tolerance) return false;
		if (fabsf(this->_qw - 1) > tolerance) return false;

		return true;
	}

	bool Quat::isNormalized(const float tolerance) const
	{
		float norm = _qx * _qx + _qy * _qy + _qz * _qz + _qw * _qw;

		if (fabsf(norm - 1) > tolerance) return false;

		return true;
	}

	bool Quat::isZero(const float tolerance) const
	{
		if (fabsf(this->_qx - 0) > tolerance) return false;
		if (fabsf(this->_qy - 0) > tolerance) return false;
		if (fabsf(this->_qz - 0) > tolerance) return false;
		if (fabsf(this->_qw - 0) > tolerance) return false;

		return true;
	}
}

// ---  End of File ---------------
