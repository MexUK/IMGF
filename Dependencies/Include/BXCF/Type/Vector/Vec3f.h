#pragma once

#define _USE_MATH_DEFINES

#include "bxcf.h"
#include "Type/Types.h"
#include <math.h>

class bxcf::Vec3f
{
public:
	float32	x;
	float32	y;
	float32	z;
	
public:
	Vec3f(void);
	Vec3f(float32 fX, float32 fY, float32 fZ);
	
	/*
	bxcf::Vec3f&	operator=	(VC::CVector& vecVectorVC)
	//operator VC::CVector&()
	{
		//return bxcf::Vec3f::operator=(vecVectorVC);
		//x = vecVectorVC.x;
		//y = vecVectorVC.y;
		//z = vecVectorVC.z;

		//return *this;

		bxcf::Vec3f vec(vecVectorVC.x, vecVectorVC.y, vecVectorVC.z);
		return vec;
	}
	*/

	/*
	bxcf::Vec3f&	operator=(VC::CVector& vecVectorVC)
	{
		this->x = 1.0f;
		this->y = 1.0f;
		this->z = 15.0f;
	}
	*/

	Vec3f&			operator=(const bxcf::Vec3f &vecVector3D);
	Vec3f			operator+(const bxcf::Vec3f &vecVector3D);
	Vec3f			operator-(const bxcf::Vec3f &vecVector3D);
	Vec3f			operator*(const bxcf::Vec3f &vecVector3D);
	Vec3f			operator/(const bxcf::Vec3f &vecVector3D);
	Vec3f			operator%(const bxcf::Vec3f &vecVector3D);
	bool				operator!=(float32 fValue);
	bool				operator!=(const bxcf::Vec3f &vecVector3D);
	Vec3f			operator-(void);
	template <class T>	bxcf::Vec3f		operator+(const T value);
	template <class T>	bxcf::Vec3f		operator-(const T value);
	template <class T>	bxcf::Vec3f		operator*(const T value);
	template <class T>	bxcf::Vec3f		operator/(const T value);
	template <class T>	bxcf::Vec3f		operator%(const T value);

	void				toRadians(void);
	void				toDegrees(void);

	void				capAngleRadians(void);
	void				capAngleDegrees(void);

	Vec3f			getCrossProduct(bxcf::Vec3f &vecVector3D);
	float32				getLength(void);
};

template <class T>
bxcf::Vec3f		bxcf::Vec3f::operator+(const T value)
{
	return bxcf::Vec3f(
		x + value,
		y + value,
		z + value
		);
}
template <class T>
bxcf::Vec3f		bxcf::Vec3f::operator-(const T value)
{
	return bxcf::Vec3f(
		x - value,
		y - value,
		z - value
		);
}
template <class T>
bxcf::Vec3f		bxcf::Vec3f::operator*(const T value)
{
	return bxcf::Vec3f(
		x * value,
		y * value,
		z * value
		);
}
template <class T>
bxcf::Vec3f		bxcf::Vec3f::operator/(const T value)
{
	return bxcf::Vec3f(
		x / value,
		y / value,
		z / value
		);
}
template <class T>
bxcf::Vec3f		bxcf::Vec3f::operator%(const T value)
{
	return bxcf::Vec3f(
		fmod(x, value),
		fmod(y, value),
		fmod(z, value)
		);
}