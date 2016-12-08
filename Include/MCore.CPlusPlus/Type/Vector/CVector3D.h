#ifndef CVector3D_H
#define CVector3D_H

#define _USE_MATH_DEFINES

#include "mcore.h"
#include "Type/Types.h"
#include <math.h>

class mcore::CVector3D
{
public:
	float32	m_x;	// todo - rename to .x and .y and .z
	float32	m_y;
	float32	m_z;
	
public:
	mcore::CVector3D(void);
	mcore::CVector3D(float32 fX, float32 fY, float32 fZ);
	
	/*
	mcore::CVector3D&	operator=	(VC::CVector& vecVectorVC)
	//operator VC::CVector&()
	{
		//return mcore::CVector3D::operator=(vecVectorVC);
		//m_X = vecVectorVC.m_X;
		//m_Y = vecVectorVC.m_Y;
		//m_Z = vecVectorVC.m_Z;

		//return *this;

		mcore::CVector3D vec(vecVectorVC.m_X, vecVectorVC.m_Y, vecVectorVC.m_Z);
		return vec;
	}
	*/

	/*
	mcore::CVector3D&	operator=(VC::CVector& vecVectorVC)
	{
		this->m_X = 1.0f;
		this->m_Y = 1.0f;
		this->m_Z = 15.0f;
	}
	*/

	mcore::CVector3D&		operator=(const mcore::CVector3D &vecVector3D);
	mcore::CVector3D		operator+(const mcore::CVector3D &vecVector3D);
	mcore::CVector3D		operator-(const mcore::CVector3D &vecVector3D);
	mcore::CVector3D		operator*(const mcore::CVector3D &vecVector3D);
	mcore::CVector3D		operator/(const mcore::CVector3D &vecVector3D);
	mcore::CVector3D		operator%(const mcore::CVector3D &vecVector3D);
	bool			operator!=(float32 fValue);
	bool			operator!=(const mcore::CVector3D &vecVector3D);
	mcore::CVector3D		operator-(void);
	template <class T>	mcore::CVector3D		operator+(const T value);
	template <class T>	mcore::CVector3D		operator-(const T value);
	template <class T>	mcore::CVector3D		operator*(const T value);
	template <class T>	mcore::CVector3D		operator/(const T value);
	template <class T>	mcore::CVector3D		operator%(const T value);

	void			toRadians(void);
	void			toDegrees(void);

	void			capAngleRadians(void);
	void			capAngleDegrees(void);

	mcore::CVector3D		getCrossProduct(mcore::CVector3D &vecVector3D);
	float32			getLength(void);
};

template <class T>
mcore::CVector3D		mcore::CVector3D::operator+(const T value)
{
	return mcore::CVector3D(
		m_x + value,
		m_y + value,
		m_z + value
		);
}
template <class T>
mcore::CVector3D		mcore::CVector3D::operator-(const T value)
{
	return mcore::CVector3D(
		m_x - value,
		m_y - value,
		m_z - value
		);
}
template <class T>
mcore::CVector3D		mcore::CVector3D::operator*(const T value)
{
	return mcore::CVector3D(
		m_x * value,
		m_y * value,
		m_z * value
		);
}
template <class T>
mcore::CVector3D		mcore::CVector3D::operator/(const T value)
{
	return mcore::CVector3D(
		m_x / value,
		m_y / value,
		m_z / value
		);
}
template <class T>
mcore::CVector3D		mcore::CVector3D::operator%(const T value)
{
	return mcore::CVector3D(
		fmod(m_x, value),
		fmod(m_y, value),
		fmod(m_z, value)
		);
}

#endif